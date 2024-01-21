package project.gui;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import project.users.User;

public class Browse extends JFrame{
    private final JLabel instructions = new JLabel("WELCOME");
    private final JPanel topbuttons = new JPanel();
    private final JPanel bottombuttons = new JPanel();
    private final JPanel midbuttons = new JPanel();
    private final JButton logout = new JButton("Logout");
    private final JButton changeEmail = new JButton("Change Email");
    private final JButton editAddress = new JButton("Edit Address Information");
    private final JButton editBank = new JButton("Edit Payment Information");
    private final JButton customerViewButton = new JButton("Customer View");
    private final JButton orderHistoryButton = new JButton("Order History");
    private final JButton staffViewButton = new JButton("Staff View");


    public Browse(User loggedUser) {
        super("Trains of Sheffield");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setVisible(true);
        this.pack();
        this.setSize(450, 350);
        this.add(topbuttons, BorderLayout.NORTH);
        this.add(bottombuttons, BorderLayout.SOUTH);
        this.add(midbuttons, BorderLayout.CENTER);

        topbuttons.setLayout(new BorderLayout());
        topbuttons.add(changeEmail, BorderLayout.EAST);
        // Setting up the bottom buttons panel
        bottombuttons.setLayout(new BorderLayout());
        bottombuttons.add(editBank, BorderLayout.WEST);
        bottombuttons.add(editAddress, BorderLayout.EAST);
        // Setting preferred sizes for buttons
        topbuttons.add(logout, BorderLayout.WEST);
        changeEmail.setPreferredSize(new Dimension(185,25));
        logout.setPreferredSize(new Dimension(185,25));
        editAddress.setPreferredSize(new Dimension(185,25));
        editBank.setPreferredSize(new Dimension(185,25));

        midbuttons.setLayout(new GridLayout(0,1));
        instructions.setHorizontalAlignment(SwingConstants.CENTER);
        midbuttons.add(instructions);
        midbuttons.add(customerViewButton);
        midbuttons.add(orderHistoryButton);
        midbuttons.add(staffViewButton);
        midbuttons.add(new JLabel());
        // Hiding staff view button if the user is not a staff member
        if (loggedUser.getUserType() == 1)
            staffViewButton.setVisible(false);

        customerViewButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ProductView productView = new ProductView(loggedUser, "");
            }
        });

        orderHistoryButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                OrderHistory orderHistory = new OrderHistory(loggedUser, "");
            }
        });

        staffViewButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ProductView productView = new ProductView(loggedUser, "staff");
            }
        });

        logout.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFrame currentFrame = (JFrame) SwingUtilities.getWindowAncestor((Component) e.getSource());
                currentFrame.dispose();
                HomePage shoppingSystem = new HomePage();
            }
        });

        changeEmail.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ChangeEmail newEmail = new ChangeEmail(loggedUser);
            }
        });

        editAddress.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Address address = new Address(loggedUser);
            }

        });

        editBank.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                BankingDetails updatePaymentInfo = new BankingDetails(loggedUser);
            }

        });

    }

}

