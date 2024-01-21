package project.gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class HomePage extends JFrame {
    // Buttons for login and registration
    private final JButton logiButton = new JButton("Login");
    private final JButton registerButton = new JButton("Register");
    private final JPanel panel = new JPanel();

    public HomePage() {
        super("Trains of Sheffield");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setVisible(true);
        // Set up the panel layout
        panel.setLayout(new GridLayout(2, 1));
        panel.add(logiButton);
        panel.add(registerButton);
        this.add(panel);
        this.pack();
        this.setSize(280, 95);

        logiButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                login();
            }
        });
        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                register();
            }
        });

    }
    //Opens the login window.
    public void login() {
        Window window = SwingUtilities.windowForComponent(logiButton);
        if (window != null) {
            window.dispose();
        }
        LoginPage LoginPage = new LoginPage();
    }
    //Opens the register window.
    public void register() {
        Window window = SwingUtilities.windowForComponent(registerButton);
        if (window != null) {
            window.dispose();
        }
        RegisterPage RegisterPage = new RegisterPage();
    }
    
}







