package project.gui;

import project.lib.Encryption;
import project.lib.connect;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;

import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Vector;
import java.util.regex.Pattern;

public class Manager extends JFrame {
    private JTable table1;
    private final JPanel panel1 = new JPanel();
    private final JPanel panel3 = new JPanel();
    private final JPanel panel2 = new JPanel();
    private final JButton demote = new JButton("Demote Staff Member");
    private final JButton promote = new JButton(("Promote to Staff"));
    private final JTextField email = new JTextField();
    private final JLabel label = new JLabel("Enter the email of an existing customer:");
    private final JLabel hiddenLabel = new JLabel();


    public Manager() {
        super("Manager");
        this.setLocationRelativeTo(null);
        this.pack();
        this.setSize(500, 600);

        DefaultTableModel tableModel = new DefaultTableModel();
        tableModel.addColumn("Email");
        tableModel.addColumn("Forename");
        tableModel.addColumn("Surname");

        table1 = new JTable(tableModel);
        DefaultTableCellRenderer cR = new DefaultTableCellRenderer();
        cR.setHorizontalAlignment(SwingConstants.CENTER);
        table1.setDefaultRenderer(Object.class, cR);

        // Populating the Staff table with the details regarding the current staff members
        String q = "SELECT email, forename, surname FROM team012.User WHERE userType = ?";
        try (PreparedStatement pS = connect.connection.prepareStatement(q)) {
            pS.setInt(1, 2);
            try (ResultSet rS = pS.executeQuery()) {
                while (rS.next()) {
                    String email = rS.getString("email");
                    String forename = rS.getString("forename");
                    String surname = rS.getString("surname");

                    //Setting the number of the rows in the table equal to the number of rows extracted from the database
                    Vector<Object> row = new Vector<>();
                    row.add(email);
                    row.add(forename);
                    row.add(surname);
                    ((DefaultTableModel) table1.getModel()).addRow(row);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        JScrollPane scrollPane = new JScrollPane(table1);

        panel1.setBorder(BorderFactory.createTitledBorder("Demote Staff Members"));
        panel1.add(scrollPane);
        panel3.add(demote);

        this.add(panel1, BorderLayout.NORTH);
        this.add(panel3, BorderLayout.CENTER);

        panel2.setBorder(BorderFactory.createTitledBorder("Hire Staff Members"));
        panel2.setLayout(new GridLayout(0,2));
        panel2.add(label);
        panel2.add(email);
        panel2.add(hiddenLabel);
        panel2.add(promote);

        this.add(panel2, BorderLayout.SOUTH);
        this.setVisible(true);

        hiddenLabel.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                int result = JOptionPane.showConfirmDialog(null, "This operation will re-encrypt all banking information", "WARNING", JOptionPane.YES_NO_OPTION);
                    if (result == JOptionPane.YES_OPTION) {
                        try {                        
                            Encryption.updateKey();
                            JOptionPane.showMessageDialog(null, "Key updated!");
                        } catch (Exception ex){
                            JOptionPane.showMessageDialog(null, "Failed to update: " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
                        }
                    }
            }
        });

        //This button is used to change the user type of the selected staff member from 2 (staff) to 1 (customer)
        demote.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int selectedData = table1.getSelectedRow();
                if (selectedData != -1) {
                    DefaultTableModel m = (DefaultTableModel) table1.getModel();
                    String demotedStaffEmail = (String) m.getValueAt(selectedData, 0);
                    String uQ = "UPDATE team012.User SET userType = '1' WHERE email = ?";
                    try (PreparedStatement uS = connect.connection.prepareStatement(uQ)) {
                        uS.setString(1, demotedStaffEmail);
                        uS.executeUpdate();
                    } catch (SQLException er) {
                        er.printStackTrace();
                    }
                    tableModel.removeRow(selectedData);
                    JOptionPane.showMessageDialog(null,"Staff member has been demoted to the customer role");


                } else {
                    JOptionPane.showMessageDialog(null, "ERROR: No row has been selected");
                }
            }
        });

        //This button is used to change the user type of the customer (based on entered email) from 1 (customer) to 2 (staff)
        promote.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (email.getForeground().equals(Color.red)) {
                    JOptionPane.showMessageDialog(null, "ERROR: Invalid Email");
                } else if (email.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "ERROR: Missing Email");
                } else{
                    String Email = email.getText();
                    String cQ = "SELECT * FROM team012.User WHERE email = ? AND userType = '1'";
                    try (PreparedStatement cS = connect.connection.prepareStatement(cQ)){
                        cS.setString(1, Email);
                        try (ResultSet rS = cS.executeQuery()) {
                            if(rS.next()) {
                                String uQ = "UPDATE team012.User SET userType = '2' WHERE email = ?";
                                try (PreparedStatement uS = connect.connection.prepareStatement(uQ)) {
                                    uS.setString(1, Email);
                                    uS.executeUpdate();

                                    DefaultTableModel m = (DefaultTableModel) table1.getModel();
                                    m.setRowCount(0);

                                    // Refreshing the staff table
                                    String q = "SELECT email, forename, surname FROM team012.User WHERE userType = ?";
                                    try (PreparedStatement pS = connect.connection.prepareStatement(q)) {
                                        pS.setInt(1, 2);
                                        try (ResultSet rS2 = pS.executeQuery()) {
                                            while (rS2.next()) {
                                                String email = rS2.getString("email");
                                                String forename = rS2.getString("forename");
                                                String surname = rS2.getString("surname");

                                                //Setting the number of the rows in the table equal to the number of rows extracted from the database
                                                Vector<Object> row = new Vector<>();
                                                row.add(email);
                                                row.add(forename);
                                                row.add(surname);
                                                ((DefaultTableModel) table1.getModel()).addRow(row);
                                            }
                                        }
                                    } catch (SQLException er) {
                                        er.printStackTrace();
                                    }

                                    JOptionPane.showMessageDialog(null,"Customer has been promoted to a staff member");

                                }
                            } else {
                                JOptionPane.showMessageDialog(null, "ERROR: Email does not belong to a customer");
                            }
                        }
                    } catch (SQLException er) {
                        er.printStackTrace();
                    }
                }
            }
        });

        //Setting the colour of the Email entered to red if the format of the Email is wrong, and setting it to black if its in the correct format
        email.getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent e) {
                String input = email.getText();
                if (!isEmailValid(input)){
                    email.setForeground(Color.RED);
                } else {
                    email.setForeground(Color.BLACK);
                }
            }

            @Override
            public void removeUpdate(DocumentEvent e) {
                String input = email.getText();
                if (!isEmailValid(input)){
                    email.setForeground(Color.RED);
                } else {
                    email.setForeground(Color.BLACK);
                }
            }

            @Override
            public void changedUpdate(DocumentEvent e) {
                String input = email.getText();
                if (!isEmailValid(input)){
                    email.setForeground(Color.RED);
                } else {
                    email.setForeground(Color.BLACK);
                }
            }

            //This function checks if the Email is in the correct format
            private boolean isEmailValid(String input){
                String emailFormat = "^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@" + "(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$";
                Pattern p = Pattern.compile(emailFormat);
                boolean result = p.matcher(input).matches();
                return result;
            }
        });
    }
}
