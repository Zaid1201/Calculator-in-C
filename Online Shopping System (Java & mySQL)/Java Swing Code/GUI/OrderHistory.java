package project.gui;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import java.sql.*;
import java.util.Vector;

import project.users.User;
import project.lib.connect;
import project.products.Order;

public class OrderHistory extends JFrame {
    DefaultTableModel model = new DefaultTableModel(
            null,
            new Object[]{"Order Number", "Date Of Purchase", "Status", "Total Cost"}
    ) {
        @Override
        public boolean isCellEditable(int row, int column) {
            return false;
        }
    };

    JTable orderTable = new JTable(model);

    // The user for whom to display the order history.
    // A flag indicating the type of order history to display.
    public OrderHistory(User user, String tabFlag) {
        setTitle("Order History");
        DefaultTableCellRenderer cR = new DefaultTableCellRenderer();
        cR.setHorizontalAlignment(SwingConstants.CENTER);
        orderTable.setDefaultRenderer(Object.class, cR);

        // Load orders based on the tabFlag
        if (tabFlag == "") {
            getAndGenerateOrders(model, user.getUserID());
            orderTable.getSelectionModel().addListSelectionListener(new ListSelectionListener() {
                @Override
                public void valueChanged(ListSelectionEvent e) {
                    if (!e.getValueIsAdjusting()) {
                        int selectedIndex = orderTable.getSelectedRow();
                        if (selectedIndex != -1) {
                            String status = String.valueOf(orderTable.getValueAt(selectedIndex, 2));
                            if (status.equals("pending")) {
                                Object selectedData = orderTable.getValueAt(selectedIndex, 0);
                                Order order = Order.getOrder(String.valueOf(selectedData));
                                ProductView productView = new ProductView(user, "", order);
                            }
                        }
                    }
                }
            });
        } else {

            getAndGenerateOrders(model, null);
            orderTable.getSelectionModel().addListSelectionListener(new ListSelectionListener() {
                @Override
                public void valueChanged(ListSelectionEvent e) {
                    if (!e.getValueIsAdjusting()) {
                        int selectedData = orderTable.getSelectedRow();
                        if (selectedData != -1) {
                            String orderNumber = String.valueOf(orderTable.getValueAt(selectedData, 0));
                            JFrame f = new JFrame("Selected Order");
                            DefaultTableModel model2 = new DefaultTableModel(
                                null,
                                new Object[]{"Line Number", "Quantity", "Line Cost", "Product Code"}
                            ) {
                            @Override
                            public boolean isCellEditable(int row, int column) {
                                return false;
                                }
                            };
                            getAndGenerateOrderLines(model2, String.valueOf(orderNumber));
                            JTable orderLineTable = new JTable(model2);
                            orderLineTable.setDefaultRenderer(Object.class, cR);
                            JScrollPane scrollPane = new JScrollPane(orderLineTable);
                            f.add(scrollPane);
                            f.setSize(475, 150);
                            f.setLocationRelativeTo(null);
                            f.setVisible(true);
                        }
                    }
                }
            });

        }
        
        JScrollPane scrollPane = new JScrollPane(orderTable);
        add(scrollPane);
        setSize(600, 400);
        setVisible(true);
    }

    // The DefaultTableModel for the order lines table.
    // The order number for which to retrieve and display order lines.
    private void getAndGenerateOrderLines(DefaultTableModel model, String orderNumber) {
        String q = "SELECT lineNumber, quantity, lineCost, code FROM team012.OrderLine WHERE orderNumber = ?";
        try (PreparedStatement preparedStatement = connect.connection.prepareStatement(q)) {
            preparedStatement.setString(1, orderNumber);
            try (ResultSet rS = preparedStatement.executeQuery()) {
                while (rS.next()) {
                    String lineNumber = rS.getString("lineNumber");
                    String quantity= rS.getString("quantity");
                    String lineCost = rS.getString("lineCost");
                    String code = rS.getString("code");

                    Vector<Object> row = new Vector<>();
                    row.add(lineNumber);
                    row.add(quantity);
                    row.add(lineCost);
                    row.add(code);

                    model.addRow(row);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // The DefaultTableModel for the main orders table.
    // The user ID for which to retrieve orders, or null for all users.
    private void getAndGenerateOrders(DefaultTableModel model, String userID) {
        String query = "SELECT * FROM team012.Order";
        if (userID != null)
            query = query +  " WHERE userID = '" + userID + "'";
        try (PreparedStatement preparedStatement = connect.connection.prepareStatement(query)) {
            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                String orderNumber = resultSet.getString("orderNumber");
                String dateOfPurchase = resultSet.getString("dateOfPurchase");
                String status = resultSet.getString("status");
                String totalCost = resultSet.getString("totalCost");

                Vector<Object> row = new Vector<>();
                row.add(orderNumber);
                row.add(dateOfPurchase);
                row.add(status);
                row.add(totalCost);
                ((DefaultTableModel) orderTable.getModel()).addRow(row);
            }

        } catch (SQLException E) {
            E.printStackTrace();
        }
    }
}
