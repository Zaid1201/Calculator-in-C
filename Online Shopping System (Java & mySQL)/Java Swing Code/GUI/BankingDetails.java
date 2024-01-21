package project.gui;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.Window;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.sql.PreparedStatement;
import javax.swing.text.AbstractDocument;
import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.DocumentFilter;

import project.lib.Encryption;
import project.lib.connect;
import project.users.User;

public class BankingDetails extends JFrame {
    private final JPanel newPanel = new JPanel();
    private final JPanel northPanel = new JPanel();
    private final JPanel panel1 = new JPanel();
    private final JPanel panel2 = new JPanel();
    private final JPanel panel3 = new JPanel();
    private final JPanel panel4 = new JPanel();
    private final JPanel midPanel = new JPanel();
    private final JPanel upperPanel = new JPanel();
    private final JPanel midPanelandpanel2 = new JPanel();
    private final JLabel instructions = new JLabel("Please choose a type of bank card");
    private final JLabel label2 = new JLabel("Please enter your bank card number:");
    private final JLabel label3 = new JLabel("Please enter your card's expiry date:");
    private final JLabel label4 = new JLabel("m");
    private final JLabel label5 = new JLabel("yy");
    private final JLabel label6 = new JLabel("Please enter your card's security number:");
    private JRadioButton visaRadioButton = new JRadioButton("Visa");
    private JRadioButton visaDebitRadioButton = new JRadioButton("Visa Debit");
    private JRadioButton mastercardRadioButton = new JRadioButton("Mastercard");
    private JRadioButton maestroRadioButton = new JRadioButton("Maestro");
    private JRadioButton americanExpressRadioButton = new JRadioButton("American Express");
    private JRadioButton JCBRadioButton = new JRadioButton("JCB");
    private final JComboBox<Integer> month;
    private final JComboBox<Integer> year;
    private JTextField cardNumberField = new JTextField();
    private JTextField securityCodeField = new JTextField();
    private final JTextField empty1 = new JTextField();
    private final JTextField empty2 = new JTextField();
    private final JButton submitButton = new JButton("Submit");

    // Constructor for the BankingDetails class
    public BankingDetails(User user) {
        super("Payment Information");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        this.setVisible(true);
        this.pack();
        this.setSize(590, 345);
        // Integer arrays for JComboBox initialization
        Integer[] numbers = new Integer[12];
        Integer[] numbers2 = new Integer[76];

        for(int i = 0; i < 12; i++){
            numbers[i] = i + 1;
        }
        for(int i = 0; i < 76; i++){
            numbers2[i] = 24 + i;
        }
        // Initializing JComboBox for month and year
        month = new JComboBox<>(numbers);
        year = new JComboBox<>(numbers2);
        
        this.add(northPanel, BorderLayout.NORTH);
        this.add(midPanelandpanel2, BorderLayout.CENTER);
        this.add(panel4, BorderLayout.SOUTH);
       
        panel1.setLayout(new GridLayout(0,1));
        panel1.add(visaRadioButton);
        panel1.add(visaDebitRadioButton);
        panel1.add(mastercardRadioButton);
        panel1.add(maestroRadioButton);
        panel1.add(americanExpressRadioButton);
        panel1.add(JCBRadioButton);
       
        upperPanel.setLayout(new BorderLayout());
        upperPanel.add(instructions, BorderLayout.NORTH);
        upperPanel.add(panel1, BorderLayout.CENTER);
       
        panel2.setLayout(new GridLayout(0,2));
        panel2.add(label2);
        panel2.add(cardNumberField);
       
        panel3.setLayout(new GridLayout(2,2));
        panel3.add(month);
        panel3.add(year);
        label4.setHorizontalAlignment(SwingConstants.CENTER);
        label5.setHorizontalAlignment(SwingConstants.CENTER);
        panel3.add(label4);
        panel3.add(label5);
       
        midPanel.setLayout(new BorderLayout());
        midPanel.add(panel3, BorderLayout.EAST);
        midPanel.add(label3, BorderLayout.WEST);
       
        panel4.setLayout(new GridLayout(2,2));
        panel4.add(label6);
        panel4.add(securityCodeField);
        panel4.add(submitButton);
        midPanelandpanel2.setLayout(new BorderLayout());
        midPanelandpanel2.add(panel2, BorderLayout.NORTH);
        midPanelandpanel2.add(midPanel, BorderLayout.CENTER);
        
        empty1.setVisible(false);
        empty2.setVisible(false);

        
        northPanel.setLayout(new BorderLayout());
        northPanel.add(newPanel,BorderLayout.NORTH);
        northPanel.add(upperPanel, BorderLayout.CENTER);

        // Restricting input length for security code field
        securityCodeField.addKeyListener(new KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                if (securityCodeField.getText().length() >= 3)
                    e.consume();
            }
        });
        // Restricting input length for card number field
        cardNumberField.addKeyListener(new KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                if (cardNumberField.getText().length() >= 16)
                    e.consume();
            }
        });

        // Document filter for restricting input to numeric characters in cardNumberField
        ((AbstractDocument) cardNumberField.getDocument()).setDocumentFilter(new DocumentFilter() {
            @Override
            public void insertString(DocumentFilter.FilterBypass fb, int offset, String text, AttributeSet attr) throws BadLocationException {
                if (text != null && text.matches("^[0-9]*$")) {
                    super.insertString(fb, offset, text, attr);
                }
            }

            @Override
            public void replace(DocumentFilter.FilterBypass fb, int offset, int length, String text, AttributeSet attr) throws BadLocationException {
                if (text != null && text.matches("^[0-9]*$")) {
                    super.replace(fb, offset, length, text, attr);
                }
            }
        });
        // Document filter for restricting input to numeric characters in securityCodeField
        ((AbstractDocument) securityCodeField.getDocument()).setDocumentFilter(new DocumentFilter() {
            @Override
            public void insertString(DocumentFilter.FilterBypass fb, int offset, String text, AttributeSet attr) throws BadLocationException {
                if (text != null && text.matches("^[0-9]*$")) {
                    super.insertString(fb, offset, text, attr);
                }
            }

            @Override
            public void replace(DocumentFilter.FilterBypass fb, int offset, int length, String text, AttributeSet attr) throws BadLocationException {
                if (text != null && text.matches("^[0-9]*$")) {
                    super.replace(fb, offset, length, text, attr);
                }
            }
        });
            
        visaRadioButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                visaDebitRadioButton.setSelected(false);
                mastercardRadioButton.setSelected(false);
                maestroRadioButton.setSelected(false);
                americanExpressRadioButton.setSelected(false);
                JCBRadioButton.setSelected(false);
            }
        });
        visaDebitRadioButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                visaRadioButton.setSelected(false);
                mastercardRadioButton.setSelected(false);
                maestroRadioButton.setSelected(false);
                americanExpressRadioButton.setSelected(false);
                JCBRadioButton.setSelected(false);
            }
        });
        mastercardRadioButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                visaRadioButton.setSelected(false);
                visaDebitRadioButton.setSelected(false);
                maestroRadioButton.setSelected(false);
                americanExpressRadioButton.setSelected(false);
                JCBRadioButton.setSelected(false);
            }
        });
        maestroRadioButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                visaRadioButton.setSelected(false);
                visaDebitRadioButton.setSelected(false);
                americanExpressRadioButton.setSelected(false);
                JCBRadioButton.setSelected(false);
                mastercardRadioButton.setSelected(false);
            }
        });
        americanExpressRadioButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                maestroRadioButton.setSelected(false);
                visaRadioButton.setSelected(false);
                visaDebitRadioButton.setSelected(false);
                JCBRadioButton.setSelected(false);
                mastercardRadioButton.setSelected(false);
            }
        });
        JCBRadioButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                americanExpressRadioButton.setSelected(false);
                maestroRadioButton.setSelected(false);
                visaRadioButton.setSelected(false);
                visaDebitRadioButton.setSelected(false);
                mastercardRadioButton.setSelected(false);
            }
        });
        // Submit button action listener for form validation and database update
        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!JCBRadioButton.isSelected() && !americanExpressRadioButton.isSelected() && !maestroRadioButton.isSelected() 
                && !visaRadioButton.isSelected() && !visaDebitRadioButton.isSelected() && !mastercardRadioButton.isSelected()) {
                    JOptionPane.showMessageDialog(null, "ERROR: Please select the type of bank card");
                    } else if (cardNumberField.getText().trim().isEmpty() || securityCodeField.getText().trim().isEmpty()) {
                        JOptionPane.showMessageDialog(null, "ERROR: Missing field(s)");
                    } else if (cardNumberField.getText().length() < 16 && securityCodeField.getText().length() < 3) {
                        JOptionPane.showMessageDialog(null, "Error: Invalid Card Number & Invalid Security Number");
                    } else if (securityCodeField.getText().length() < 3) {
                        JOptionPane.showMessageDialog(null, "Error: Invalid Security Code");
                    } else if (cardNumberField.getText().length() < 16) {
                        JOptionPane.showMessageDialog(null, "Error: Invalid Card Number");
                    } else {
                        String selectedCard = null;
                        if (visaRadioButton.isSelected()) {
                            selectedCard = "Visa";
                        } else if (visaDebitRadioButton.isSelected()) {
                            selectedCard = "Visa Debit";
                        } else if (mastercardRadioButton.isSelected()) {
                            selectedCard = "Mastercard";
                        } else if (maestroRadioButton.isSelected()) {
                            selectedCard = "Maestro";
                        } else if (americanExpressRadioButton.isSelected()) {
                            selectedCard = "American Express";
                        } else if (JCBRadioButton.isSelected()) {
                            selectedCard = "JCB";
                        }
                        String insertBank = "UPDATE team012.User SET bankCardName = ?, bankCardNumber = ?, securityCode =?, expiryDate = ? WHERE userID = ? ";
                        String securityCode = String.valueOf(month.getSelectedItem()) + "/" + String.valueOf(year.getSelectedItem());
                        try (PreparedStatement statement = connect.connection.prepareStatement(insertBank)) {
                            statement.setBytes(1, Encryption.encrypt(selectedCard));
                            statement.setBytes(2, Encryption.encrypt(cardNumberField.getText()));
                            statement.setBytes(3, Encryption.encrypt(securityCodeField.getText()));
                            statement.setBytes(4, Encryption.encrypt(securityCode));
                            statement.setString(5, user.getUserID());
                            int count = statement.executeUpdate();
                            if (count == 1) {
                                JOptionPane.showMessageDialog(null, "Payment Information Set");
                                Timer timer = new Timer(3000, new ActionListener() {
                                    @Override
                                    public void actionPerformed(ActionEvent e) {
                                        Window window = SwingUtilities.windowForComponent(submitButton);
                                        window.dispose();
                                    }
                                });
                                timer.setRepeats(false);
                                timer.start();
                            }
                            else
                                JOptionPane.showMessageDialog(null, "Payment Information Does Not Set");

                        } catch (Exception ex) {
                            throw new RuntimeException(ex);
                        }
                    }
            }
        });
    }

}

