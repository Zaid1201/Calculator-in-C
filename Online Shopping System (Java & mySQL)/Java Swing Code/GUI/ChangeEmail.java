package project.gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import project.users.User;
import project.lib.connect;

public class ChangeEmail extends JFrame {
    private final JPanel panel1 = new JPanel();
    private final JLabel emailLabel = new JLabel("Please enter your current email:");
    private final JTextField emailField = new JTextField();
    private final JTextField newEmailField = new JTextField();
    private final JLabel newEmail = new JLabel("Please enter your new email:");
    private final JButton submit = new JButton("Submit");
    private final static String emailRegex = "^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@" + "(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$";

    public ChangeEmail(User user) {
        super("Change Email");
        this.setLocationRelativeTo(null);
        this.setVisible(true);
        this.pack();
        this.setSize(400, 100); 
        this.add(panel1, BorderLayout.NORTH);
        this.add(submit, BorderLayout.CENTER);
        
        panel1.setLayout(new GridLayout(2,2));
        panel1.add(emailLabel);
        panel1.add(emailField);
        panel1.add(newEmail);
        panel1.add(newEmailField);

        RegisterPage.setDocumentFilter(emailField, emailRegex);
        RegisterPage.setDocumentFilter(newEmailField, emailRegex);
        
        submit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String enteredEmail = emailField.getText().trim();
                String enteredNewEmail = newEmailField.getText().trim();
                String checkEmailQuery = "SELECT * FROM team012.User WHERE email = ?";
                String updateEmailQuery = "UPDATE team012.User SET email = ? WHERE userID = ?";

                if (enteredEmail.isEmpty() || enteredNewEmail.isEmpty()) {
                    JOptionPane.showMessageDialog(null,"ERROR: Missing required field(s)");
                } else if (emailField.getForeground().equals(Color.red) || newEmailField.getForeground().equals(Color.red)){
                    JOptionPane.showMessageDialog(null,"ERROR: Invalid Email");
                } else {
                    if (user.getEmail().equals(enteredEmail)) {
                        try(PreparedStatement preparedStatement = connect.connection.prepareStatement(checkEmailQuery)) {
                            preparedStatement.setString(1, enteredNewEmail);
                            ResultSet resultSet = preparedStatement.executeQuery();
                            if (!resultSet.next()) {
                                try(PreparedStatement preparedStatement2 = connect.connection.prepareStatement(updateEmailQuery)) {
                                    preparedStatement2.setString(1, enteredNewEmail);
                                    preparedStatement2.setString(2, user.getUserID());
                                    preparedStatement2.executeUpdate();
                                    Window[] windows = Window.getWindows();
                                    for (Window window : windows) {
                                        if (window instanceof JFrame) {
                                            ((JFrame) window).dispose();
                                        }
                                    }
                                    HomePage shoppingSystem = new HomePage();
                                }
                            } else { 
                                JOptionPane.showMessageDialog(null, "ERROR: The new email entered already exists");
                            }
                        } catch (SQLException er) {
                            er.printStackTrace();
                        }

                    } else {
                        JOptionPane.showMessageDialog(null, "ERROR: Entered Email doesn't match the logged in Email");
                    }
                }
            }
        });

    }
}
