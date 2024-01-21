package project.gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.ResultSet;

import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import project.users.User;
import project.lib.connect;

public class Address extends JFrame {
    private final JPanel panel = new JPanel(new GridLayout(10, 2, 10, 5));
    private final JLabel houseNameLabel = new JLabel("Please enter your house number:");
    private final JLabel roadNameLabel = new JLabel("Please enter the name of your road:");
    private final JLabel cityNameLabel = new JLabel("Please enter the name of your city:");
    private final JLabel postCodeLabel = new JLabel("Please enter your post code:");
    private final JTextField houseNumberField = new JTextField();
    private final JTextField roadNameField = new JTextField();
    private final JTextField cityNameField = new JTextField();
    private final JTextField postCodeField = new JTextField();
    private final JLabel errorMessageLabel = new JLabel();
    private final JButton submitButton = new JButton("Submit");
    
    public Address(User loggedUser) {
        super("Address Details");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        this.setVisible(true);
        this.pack();
        this.setSize(650, 195);
        add(panel, BorderLayout.CENTER);
        postCodeField.setToolTipText("<html>*Must Use uppercase<br>"
                + "*Must contain a space between two parts<br>");
        errorMessageLabel.setForeground(Color.red);
        
        panel.setLayout(new GridLayout(5, 2));
        panel.add(houseNameLabel);
        panel.add(houseNumberField);
        panel.add(roadNameLabel);
        panel.add(roadNameField);
        panel.add(cityNameLabel);
        panel.add(cityNameField);
        panel.add(postCodeLabel);
        panel.add(postCodeField);
        panel.add(submitButton);
        panel.add(errorMessageLabel);
        // Set document filters for input fields
        setDocumentFilter(houseNumberField, "^[a-zA-Z0-9]{1,4}$");
        setDocumentFilter(roadNameField, "^[a-zA-Z]*$");
        setDocumentFilter(cityNameField, "^[a-zA-Z]*$");
        setDocumentFilter(postCodeField, "^[A-Z0-9\\s]{6,8}$");
        // Retrieve user details from the database
        User user = loggedUser;
        String userQuery = "SELECT * FROM team012.User WHERE userID = ?";
        try (PreparedStatement statement = connect.connection.prepareStatement(userQuery)) {
            statement.setString(1, loggedUser.getUserID());
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                user = new User(resultSet);
            }
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
        // Retrieve address details from the database and populate fields
        String query = "SELECT * FROM team012.Address WHERE houseNumber = ? AND postCode = ?";
        try (PreparedStatement statement = connect.connection.prepareStatement(query)) {
            statement.setString(1, user.getHouseNumber());
            statement.setString(2, user.getPostCode());
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                houseNumberField.setText(resultSet.getString("houseNumber"));
                roadNameField.setText(resultSet.getString("roadName"));
                cityNameField.setText(resultSet.getString("cityName"));
                postCodeField.setText(resultSet.getString("postCode"));
            }
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
        // ActionListener for the submitButton
        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JTextField[] fields = {
                    houseNumberField, roadNameField,
                    cityNameField, postCodeField
                };
           
                String[] contents = new String[fields.length];
                errorMessageLabel.setText("");
                // Validate fields
                int i = 0;
                for (JTextField field : fields) {
                    contents[i] = field.getText().trim();
                    if (field.getForeground().equals(Color.RED)) {
                        errorMessageLabel.setText("Invalid field(s)");
                    }
                    if (contents[i].isEmpty()) {
                        errorMessageLabel.setText("ERROR: Missing required field(s)");
                    }
                    i++;
                }
                // If there are errors, return without further processing
                if (!errorMessageLabel.getText().isEmpty()) {
                    return;
                }
                else {
                    // Check if the address already exists in the database
                    try (PreparedStatement statement = connect.connection.prepareStatement(query)) {
                        statement.setString(1, contents[0]);
                        statement.setString(2, contents[3]);
                        ResultSet resultSet = statement.executeQuery();
                        if (!resultSet.next()) {
                            // If the address doesn't exist, insert it into the database
                            String insert = "INSERT INTO team012.Address (houseNumber, roadName, cityName, postCode) VALUES (?, ?, ?, ?)";
                            try (PreparedStatement statement2 = connect.connection.prepareStatement(insert)) {
                                statement2.setString(1, contents[0]);
                                statement2.setString(2, contents[1]);
                                statement2.setString(3, contents[2]);
                                statement2.setString(4, contents[3]);
                                statement2.executeUpdate();
                            }
                        }
                        // Update the user's address in the User table
                        String update = "UPDATE team012.User SET houseNumber = ?, postCode = ? WHERE UserID = ?";
                        try (PreparedStatement statement3 = connect.connection.prepareStatement(update)) {
                            statement3.setString(1, contents[0]);
                            statement3.setString(2, contents[3]);
                            statement3.setString(3, loggedUser.getUserID());
                            statement3.executeUpdate();
                        }
                    } catch (SQLException ex) {
                        throw new RuntimeException(ex);
                    }

                    JOptionPane.showMessageDialog(null, "Success");
                }
            }
        });

    }
    // Method to set document filter for input fields
    private static void setDocumentFilter(JTextField textField, String regex) {
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