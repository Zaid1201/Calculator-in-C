package project.gui;

import javax.swing.*;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;
import java.util.Vector;

import static project.lib.connect.connection;

// The OrderStatus class represents the window displaying order status and allows fulfillment or rejection of orders.
public class OrderStatus extends JFrame {
    DefaultTableModel model = new DefaultTableModel(
            null,
            new Object[]{"Order Number", "Date Of Purchase", "Status", "Total Cost", "UserID"}
    ) {
        @Override
        public boolean isCellEditable(int row, int column) {
            return false;
        }
    };

    JTable table = new JTable(model);

    // Constructs the OrderStatus window.
    public OrderStatus() {
        setTitle("Order");

        DefaultTableCellRenderer cR = new DefaultTableCellRenderer();
        cR.setHorizontalAlignment(SwingConstants.CENTER);
        table.setDefaultRenderer(Object.class, cR);

        JScrollPane scrollPane = new JScrollPane(table);
        add(scrollPane);

        JButton fulfillButton = new JButton("Fulfill");
        fulfillButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int selectedRow = table.getSelectedRow();
                if (selectedRow != -1) {
                    String orderNumber = (String) table.getValueAt(selectedRow, 0);
                    fulfillOrder(orderNumber);
                    model.fireTableDataChanged(); // Refresh the table after Fulfill
                } else {
                    JOptionPane.showMessageDialog(OrderStatus.this, "Please select a row to fulfill.",
                            "No Row Selected", JOptionPane.WARNING_MESSAGE);
                }
            }
        });

        // Create Reject button
        JButton rejectButton = new JButton("Reject");
        rejectButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int selectedRow = table.getSelectedRow();
                if (selectedRow != -1) {
                    String orderNumber = (String) table.getValueAt(selectedRow, 0);
                    rejectOrder(orderNumber);
                    model.fireTableDataChanged(); // Refresh the table after Reject
                } else {
                    JOptionPane.showMessageDialog(OrderStatus.this, "Please select a row to reject.",
                            "No Row Selected", JOptionPane.WARNING_MESSAGE);
                }
            }
        });

        JPanel buttonPanel = new JPanel(new FlowLayout());
        buttonPanel.add(fulfillButton);
        buttonPanel.add(rejectButton);

        add(buttonPanel, BorderLayout.SOUTH);
        setSize(600, 400);
        setLocationRelativeTo(null);
        fetchDataFromDatabase(model);
        setVisible(true);
    }

    // Fetches order data from the database and populates the table model.
    private void fetchDataFromDatabase(DefaultTableModel model) {
        String q = "SELECT orderNumber, dateOfPurchase, status, totalCost, userID FROM team012.Order WHERE status = ?";
        try (PreparedStatement pS = connection.prepareStatement(q)) {
            pS.setString(1, "confirmed");
            try (ResultSet rS = pS.executeQuery()) {
                while (rS.next()) {
                    String orderNumber = rS.getString("orderNumber");
                    String dateOfPurchase = rS.getString("dateOfPurchase");
                    String status = rS.getString("status");
                    String totalCost = rS.getString("totalCost");
                    String userID = rS.getString("userID");

                    Vector<Object> row = new Vector<>();
                    row.add(orderNumber);
                    row.add(dateOfPurchase);
                    row.add(status);
                    row.add(totalCost);
                    row.add(userID);
                    ((DefaultTableModel) table.getModel()).addRow(row);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // Fulfills or rejects the selected order based on the provided status.
    private void fulfillOrder(String orderNumber) {
        try {
            if (!decreaseStock(orderNumber)) {
                return;
            }
            String updateSql = "UPDATE team012.Order SET Status = 'fulfilled' WHERE OrderNumber = ?";
            try (PreparedStatement statement = connection.prepareStatement(updateSql)) {
                statement.setString(1, orderNumber);
                int rowsUpdated = statement.executeUpdate();

                if (rowsUpdated > 0) {
                    JOptionPane.showMessageDialog(this, "Order " + orderNumber + " fulfilled successfully.",
                            "Fulfillment Success", JOptionPane.INFORMATION_MESSAGE);
                    model.removeRow(table.getSelectedRow());

                } else {
                    JOptionPane.showMessageDialog(this, "Order " + orderNumber + " not found in the database.",
                            "Fulfillment Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage(),
                    "Database Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void rejectOrder(String orderNumber) {
        String deleteOrderLine = "DELETE FROM team012.OrderLine WHERE OrderNumber = ?";
        try (PreparedStatement statement = connection.prepareStatement(deleteOrderLine)) {
            statement.setString(1, orderNumber);
            statement.executeUpdate();
            String deleteOrder = "DELETE FROM team012.Order WHERE OrderNumber = ?";
            try (PreparedStatement statement2 = connection.prepareStatement(deleteOrder)) {
                statement2.setString(1, orderNumber);
                int rowsDeleted = statement2.executeUpdate();

                if (rowsDeleted > 0) {
                    JOptionPane.showMessageDialog(this, "Order " + orderNumber + " rejected and removed from the database.",
                            "Rejection Success", JOptionPane.INFORMATION_MESSAGE);
                    model.removeRow(table.getSelectedRow());
                } else {
                    JOptionPane.showMessageDialog(this, "Order " + orderNumber + " not found in the database.",
                            "Rejection Error", JOptionPane.ERROR_MESSAGE);
                }
            } 
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage(),
                "Database Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private static boolean decreaseStock(String orderNumber) {
        String query = "SELECT * FROM team012.OrderLine WHERE orderNumber = ?";
        String productQuery = "SELECT * FROM team012.Product WHERE code = ?";
        String updatQuantity = "UPDATE team012.Product SET quantity = ? WHERE code = ?";
        try (PreparedStatement statement = connection.prepareStatement(query, ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY)) {
            statement.setString(1, orderNumber);
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                String code = resultSet.getString("code");
                int quantity = resultSet.getInt("quantity");
                try (PreparedStatement statement2 = connection.prepareStatement(productQuery)) {
                    statement2.setString(1, code);
                    ResultSet product = statement2.executeQuery();
                    product.next();
                    if (product.getInt("quantity") <= quantity) {
                        JOptionPane.showMessageDialog(null,
                        "Quantity not enough for" + product.getString("name"));
                        return false;
                    }
                }
            }

            resultSet.beforeFirst();
            while (resultSet.next()) {
                String code = resultSet.getString("code");
                int quantity = resultSet.getInt("quantity");
                try (PreparedStatement statement2 = connection.prepareStatement(productQuery)) {
                    statement2.setString(1, code);
                    ResultSet product = statement2.executeQuery();
                    product.next();
                    try (PreparedStatement statement3 = connection.prepareStatement(updatQuantity)) {
                        statement3.setInt(1, product.getInt("quantity") - quantity);
                        statement3.setString(2, code);
                        statement3.executeUpdate();
                    }
                }
            }
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
        return true;
    }
}
