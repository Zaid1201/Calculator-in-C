package project.gui;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.swing.*;
import project.lib.*;
import project.users.User;

public class LoginPage extends JFrame {
    // Labels and input fields for email and password
    private final JPanel panel = new JPanel();
    private final JLabel label1 = new JLabel("E-mail:");
    private final JLabel label2 = new JLabel("Password:");
    private final JTextField textField = new JTextField();
    private final JPasswordField passwordField = new JPasswordField();
    // Button to submit the login information
    private final JButton submitButton = new JButton("Submit");

    public LoginPage() {
        super("Login");
        this.add(panel, BorderLayout.NORTH);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setVisible(true);
        this.pack();
        this.setSize(360,110);
        this.add(submitButton, BorderLayout.SOUTH);
        panel.setLayout(new GridLayout(2,2));
        panel.add(label1);
        panel.add(textField);
        panel.add(label2);
        panel.add(passwordField);
        // Add action listener for the submit button
        submitButton.addActionListener(new ActionListener() {
            @Override
            /**
             * This method is responsible for validating the entered email format,
             * querying the database to check for the existence of the email,
             * and verifying the correctness of the entered password.
             */
            public void actionPerformed(ActionEvent e) {
                // Get the entered email and password
                String email = textField.getText();
                String enteredPassword = new String(passwordField.getPassword());

                // Validate the email format
                if (!User.isEmailValid(email)) {
                    JOptionPane.showMessageDialog(null, "Invalid Email");
                    return;
                }

                // Database query to retrieve the password hash associated with the entered email
                String query = "SELECT * FROM team012.User WHERE email = ?";

                // Use try-with-resources to automatically close the PreparedStatement
                try (PreparedStatement preparedStatement = connect.connection.prepareStatement(query)) {
                    preparedStatement.setString(1, email);

                    // Execute the query and obtain the result set
                    ResultSet resultSet = preparedStatement.executeQuery();

                    // Check if the email exists in the database
                    if (resultSet.next()) {
                        // Retrieve the stored password hash from the result set
                        byte[] sqlPassword = resultSet.getBytes("password_hash");

                        // Verify the entered password against the stored password hash
                        if (Encryption.verify(enteredPassword, sqlPassword)) {
                            Window window = SwingUtilities.windowForComponent(submitButton);
                            if (window != null) {
                                window.dispose();
                            }
                            Browse shop = new Browse(new User(resultSet));

                        } else {
                            JOptionPane.showMessageDialog(null, "Wrong Password");
                        }
                    } else {
                        JOptionPane.showMessageDialog(null, "Email Does Not Exist");
                    }

                } catch (SQLException ex) {
                    throw new RuntimeException(ex);
                }
            }

        });

    }
}

