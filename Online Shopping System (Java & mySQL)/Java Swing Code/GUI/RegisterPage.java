package project.gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.UUID;
import project.lib.*;

public class RegisterPage extends JFrame {
    private final JPanel panel = new JPanel(new GridLayout(10, 2, 10, 5));
    private final JLabel surnameLabel = new JLabel("Please enter your surname:");
    private final JLabel forenameLabel = new JLabel("Please enter your forename:");
    private final JLabel houseNameLabel = new JLabel("Please enter your house number:");
    private final JLabel roadNameLabel = new JLabel("Please enter the name of your road:");
    private final JLabel cityNameLabel = new JLabel("Please enter the name of your city:");
    private final JLabel postCodeLabel = new JLabel("Please enter your post code:");
    private final JLabel emailLabel = new JLabel("Please enter your E-mail");
    private final JLabel passwordLabel = new JLabel("Please enter a desired password:");
    private final JLabel rePasswordLabel = new JLabel("Please Re-enter your password:");
    private final JButton submitButton = new JButton("Submit");
    private final JTextField surnameField = new JTextField();
    private final JTextField forenameField = new JTextField();
    private final JTextField houseNumberField = new JTextField();
    private final JTextField roadNameField = new JTextField();
    private final JTextField cityNameField = new JTextField();
    private final JTextField postCodeField = new JTextField();
    private final JTextField emailField = new JTextField();
    private final JPasswordField passwordField1 = new JPasswordField();
    private final JPasswordField passwordField2 = new JPasswordField();
    private final JLabel errorMessageLabel = new JLabel();

    public RegisterPage() {
        super("Register");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        panel.add(surnameLabel);
        panel.add(surnameField);
        panel.add(forenameLabel);
        panel.add(forenameField);
        panel.add(houseNameLabel);
        panel.add(houseNumberField);
        panel.add(roadNameLabel);
        panel.add(roadNameField);
        panel.add(cityNameLabel);
        panel.add(cityNameField);
        panel.add(postCodeLabel);
        panel.add(postCodeField);
        panel.add(emailLabel);
        panel.add(emailField);
        panel.add(passwordLabel);
        panel.add(passwordField1);
        panel.add(rePasswordLabel);
        panel.add(passwordField2);
        panel.add(submitButton);
        panel.add(errorMessageLabel);

        postCodeField.setToolTipText("<html>*Must Use uppercase<br>"
                + "*Must contain a space between two parts<br>");
        // Add a tooltip to the password field
        passwordField1.setToolTipText("<html>*Must contain at least 1 upper-case letter<br>"
        + "*Must contain at least 1 lower-case letter<br>"
        + "*Must contain at least 1 symbol<br>"
        + "*Must be at least 8 characters long</html>");

        setLayout(new BorderLayout(10, 10));
        add(panel, BorderLayout.CENTER);

        errorMessageLabel.setForeground(Color.red);

        pack();
        setVisible(true);
        setDocumentFilter(surnameField, "^[A-Z][a-zA-Z]*$");
        setDocumentFilter(forenameField, "^[A-Z][a-zA-Z]*$");
        setDocumentFilter(houseNumberField, "^[a-zA-Z0-9]*$");
        setDocumentFilter(roadNameField, "^[a-zA-Z]*$");
        setDocumentFilter(cityNameField, "^[a-zA-Z]*$");
        setDocumentFilter(postCodeField, "^[A-Z0-9\\s]{6,8}$");
        setDocumentFilter(emailField, "^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@" + "(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JTextField[] fields = {
                    roadNameField, cityNameField, surnameField,
                    forenameField, houseNumberField, postCodeField,
                    emailField, 
                };
                String[] contents = new String[fields.length + 2];
                contents[7] = new String(passwordField1.getPassword());
                contents[8] = new String(passwordField2.getPassword());
                errorMessageLabel.setText("");

                int i = 0;
                for (JTextField field : fields) {
                    contents[i] = field.getText().trim();
                    if (field.getForeground().equals(Color.RED)) {
                        errorMessageLabel.setText("Invalid field(s)");
                    }
                    if (contents[i].isEmpty() || contents[7].isEmpty() || contents[8].isEmpty()) {
                        errorMessageLabel.setText("ERROR: Missing required field(s)");
                    }
                    i++;
                }

                if (!errorMessageLabel.getText().isEmpty()) {
                    return;
                } else if (!contents[7].matches("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$")) {
                    errorMessageLabel.setText("ERROR: Invalid Password");
                } else if (!contents[7].equals(contents[8])) {
                    errorMessageLabel.setText("ERROR: Passwords are not matched");
                } else {

                    String userID = UUID.randomUUID().toString();
                    String emailQuery = "SELECT * FROM team012.User WHERE email = ?";
                    String insertAddress = "INSERT INTO team012.Address (houseNumber, roadName, cityName, postCode) VALUES (?, ?, ?, ?)";
                    String insertSQL = "INSERT INTO team012.User (userID, surname, forename, houseNumber, postCode, email, password_hash) VALUES (?, ?, ?, ?, ?, ?, ?)";
                    try {
                        try (PreparedStatement preparedStatement = connect.connection.prepareStatement(emailQuery)) {
                            preparedStatement.setString(1, contents[6]);
                            ResultSet resultSet = preparedStatement.executeQuery();
                            if (resultSet.next()) {
                                errorMessageLabel.setText("ERROR: E-mail exists");
                                return;
                            }
                        }

                        try (PreparedStatement statement = connect.connection.prepareStatement(insertAddress)) {
                            statement.setString(1, contents[4]);
                            statement.setString(2, contents[0]);
                            statement.setString(3, contents[1]);
                            statement.setString(4, contents[5]);
                            statement.executeUpdate();
                        }

                        try (PreparedStatement statement = connect.connection.prepareStatement(insertSQL)) {
                            statement.setString(1, userID);
                            for (int j = 2; j<=6; j++) {
                                statement.setString(j, contents[j]);
                            }
                            statement.setBytes(7, Encryption.hashWithSalt(contents[7]));
                            statement.executeUpdate();
                        }

                    } catch (SQLException ex) {
                        throw new RuntimeException(ex);
                    }

                    Window window = SwingUtilities.windowForComponent(submitButton);
                    if (window != null) {
                        window.dispose();
                    }
                    LoginPage LoginPage = new LoginPage();

                }

            }
        });
    
    }

    public static void setDocumentFilter(JTextField textField, String regex) {
        textField.getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent e) {
                updateTextColor();
            }
        
            @Override
            public void removeUpdate(DocumentEvent e) {
                updateTextColor();
            }
        
            @Override
            public void changedUpdate(DocumentEvent e) {
                updateTextColor();
            }
        
            private void updateTextColor() {
                String text = textField.getText();
                textField.setForeground(text.matches(regex) ? Color.BLACK : Color.RED);
            }
        });
    }

}
