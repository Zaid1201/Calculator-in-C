package project.users;

import java.sql.ResultSet;
import java.sql.SQLException;

public class User {
    private String userID;
    private int userType;
    private String forename;
    private String surname;
    private String email;
    private byte[] password_hash;
    private byte[] bankCardNumber;
    private byte[] bankCardName;
    private byte[] expiryDate;
    private byte[] securityCode;
    private String houseNumber;
    private String postCode;

    public User(ResultSet resultSet) throws SQLException {
        this.userID = resultSet.getString("userID");
        this.userType = resultSet.getInt("userType");
        this.forename = resultSet.getString("forename");
        this.surname = resultSet.getString("surname");
        this.email = resultSet.getString("email");
        this.password_hash = resultSet.getBytes("password_hash");
        this.bankCardNumber = resultSet.getBytes("bankCardNumber");
        this.bankCardName = resultSet.getBytes("bankCardName");
        this.expiryDate = resultSet.getBytes("expiryDate");
        this.securityCode = resultSet.getBytes("securityCode");
        this.houseNumber = resultSet.getString("houseNumber");
        this.postCode = resultSet.getString("postCode");
    }

    public static Boolean isEmailValid(String email) {
        return email.matches("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@" + "(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
    }

    public String getUserID() {
        return userID;
    }

    public int getUserType() {
        return userType;
    }

    public String getEmail() {
        return email;
    }

    public String getHouseNumber() {
        return houseNumber;
    }

    public String getPostCode() {
        return postCode;
    }

}
