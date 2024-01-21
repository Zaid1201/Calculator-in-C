package project.lib;

import java.security.MessageDigest;
import java.security.SecureRandom;
import java.sql.Statement;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;

/**
 * Utility class for encryption and verification using a salted hash.
 */
public class Encryption {

    private static final int HASH_LENGTH = 32;
    private static final int TOTAL_LENGTH = 48;
    private static final String HASH_ALGORITHM = "SHA3-256";
    private static final String ENCRYPTION_ALGORITHM = "AES";
    private static final Charset CHARSET_NAME = StandardCharsets.UTF_8;
    private static SecretKey secretKey;

    /**
     * Verifies if the provided plaintext matches the stored hashed password.
     *
     * @param plainText    The plain text to be verified.
     * @param storedBytes  The hash with salt stored in database.
     * @return             True if the plain text is valid, false otherwise.
     */
    public static boolean verify(String plainText, byte[] storedBytes) {
        byte[] hash = Arrays.copyOfRange(storedBytes, 0, HASH_LENGTH);
        byte[] salt = Arrays.copyOfRange(storedBytes, HASH_LENGTH, TOTAL_LENGTH);
        byte[] combined = concatByteArrays(salt, plainText.getBytes(CHARSET_NAME));
        return Arrays.equals(hash, hash(combined));
    }

    /**
     * Generates a salted hash for the provided plaintext password.
     *
     * @param plainText  The plain text to be hashed.
     * @return           The salted hashed text with salt in byte array.
     */
    public static byte[] hashWithSalt(String plainText) {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        byte[] combined = concatByteArrays(salt, plainText.getBytes(CHARSET_NAME));
        return concatByteArrays(hash(combined), salt);
    }

    /**
     * Encrypts the given plain text using the current secret key.
     *
     * @param plainText The plain text to be encrypted.
     * @return The encrypted bytes.
     * @throws Exception If an error occurs during the encryption process.
     */
    public static byte[] encrypt(String plainText) throws Exception {
        getSecretKey();
        return encrypt(plainText, secretKey);
    }

    /**
     * Decrypts the given encrypted bytes using the current secret key.
     *
     * @param encryptedBytes The bytes to be decrypted.
     * @return The decrypted plain text.
     * @throws Exception If an error occurs during the decryption process.
     */
    public static String decrypt(byte[] encryptedBytes) throws Exception {
        getSecretKey();
        Cipher cipher = Cipher.getInstance(ENCRYPTION_ALGORITHM);
        cipher.init(Cipher.DECRYPT_MODE, secretKey);
        byte[] decryptedBytes = cipher.doFinal(encryptedBytes);
        return new String(decryptedBytes, CHARSET_NAME);
    }

    /**
     * Updates banking details in the "team012.User" table by decrypting existing values using the current secret key,
     * encrypting them with a new secret key, and then updating the records in the database.
     * Also updates the secret key stored in the "team012.SecretKey" table with the new key.
     *
     * @throws Exception If an error occurs during the encryption, decryption, or database update process.
     */
    public static void updateKey() throws Exception {
        String selectQuery = "SELECT bankCardNumber, bankCardName, expiryDate, securityCode FROM team012.User " +
                             "WHERE COALESCE(bankCardNumber, bankCardName, expiryDate, securityCode) IS NOT NULL;";
        SecretKey newKey = generateNewKey();

        try (Statement selectStatement = connect.connection.createStatement();
             ResultSet resultSet = selectStatement.executeQuery(selectQuery)) {

            while (resultSet.next()) {
                byte[] bankCardNumber = resultSet.getBytes("bankCardNumber");
                byte[] bankCardName = resultSet.getBytes("bankCardName");
                byte[] expiryDate = resultSet.getBytes("expiryDate");
                byte[] securityCode = resultSet.getBytes("securityCode");
    
                // Use the new key to encrypt the values
                byte[] encryptedBankCardNumber = encrypt(decrypt(bankCardNumber), newKey);
                byte[] encryptedBankCardName = encrypt(decrypt(bankCardName), newKey);
                byte[] encryptedExpiryDate = encrypt(decrypt(expiryDate), newKey);
                byte[] encryptedSecurityCode = encrypt(decrypt(securityCode), newKey);
    
                // Update the record in the database with the new encrypted values
                String updateQuery = "UPDATE team012.User " +
                                     "SET bankCardNumber = ?, bankCardName = ?, expiryDate = ?, securityCode = ? " +
                                     "WHERE bankCardNumber = ? AND bankCardName = ? AND expiryDate = ? AND securityCode = ?;";
    
                try (PreparedStatement updateStatement = connect.connection.prepareStatement(updateQuery)) {
                    updateStatement.setBytes(1, encryptedBankCardNumber);
                    updateStatement.setBytes(2, encryptedBankCardName);
                    updateStatement.setBytes(3, encryptedExpiryDate);
                    updateStatement.setBytes(4, encryptedSecurityCode);
                    updateStatement.setBytes(5, bankCardNumber);
                    updateStatement.setBytes(6, bankCardName);
                    updateStatement.setBytes(7, expiryDate);
                    updateStatement.setBytes(8, securityCode);

                    updateStatement.executeUpdate();
                }
            }

            // Update new secret key into the database
            String keyUpdateQuery = "UPDATE team012.SecretKey SET secretKey = ?";
            try (PreparedStatement preparedStatement = connect.connection.prepareStatement(keyUpdateQuery)) {
                preparedStatement.setBytes(1, newKey.getEncoded());
                preparedStatement.executeUpdate();
            }

        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    /**
     * Encrypts the given plain text using the provided SecretKey.
     *
     * @param plainText     The text to be encrypted.
     * @param newSecretKey  The SecretKey used for encryption.
     * @return              The encrypted byte array.
     * @throws Exception    If encryption fails.
     */
    private static byte[] encrypt(String plainText, SecretKey newSecretKey) throws Exception {
        Cipher cipher = Cipher.getInstance(ENCRYPTION_ALGORITHM);
        cipher.init(Cipher.ENCRYPT_MODE, newSecretKey);
        return cipher.doFinal(plainText.getBytes(CHARSET_NAME));
    }

    // Retrieves the SecretKey from the "team012.SecretKey" table in the database.
    private static void getSecretKey() throws NoSuchAlgorithmException {
        String query = "SELECT * FROM team012.SecretKey";
        try (Statement statement = connect.connection.createStatement();
            ResultSet resultSet = statement.executeQuery(query)) {
            if (resultSet.next()) {
                byte[] keyBytes = resultSet.getBytes("secretKey");
                secretKey = new SecretKeySpec(keyBytes, ENCRYPTION_ALGORITHM);
            }
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    private static SecretKey generateNewKey() throws NoSuchAlgorithmException {
        KeyGenerator keyGenerator = KeyGenerator.getInstance(ENCRYPTION_ALGORITHM);
        keyGenerator.init(128);
        return keyGenerator.generateKey();
    }

    /**
     * Computes the hash of the given byte array using SHA-3-256 algorithm.
     *
     * @param combinedBytes  The byte array to be hashed.
     * @return               The computed hash.
     */
    private static byte[] hash(byte[] combinedBytes) {
        try {
            MessageDigest md = MessageDigest.getInstance(HASH_ALGORITHM);
            md.update(combinedBytes);
            return md.digest();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(HASH_ALGORITHM + " algorithm not found", e);
        }
    }

    /**
     * Concatenates two byte arrays into a single byte array.
     *
     * @param byteArray1  The first byte array.
     * @param byteArray2  The second byte array.
     * @return            The concatenated byte array.
     */
    private static byte[] concatByteArrays(byte[] byteArray1, byte[] byteArray2) {
        ByteBuffer buffer = ByteBuffer.allocate(TOTAL_LENGTH);
        buffer.put(byteArray1);
        buffer.put(byteArray2);
        return buffer.array();
    }

}
