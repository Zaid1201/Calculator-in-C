package project.gui;

import javax.swing.*;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.math.BigDecimal;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.UUID;
import java.util.ArrayList;
import java.util.Date;
import java.sql.SQLException;
import java.sql.Timestamp;

import project.products.*;
import project.users.*;
import project.lib.*;

public class OrderView extends JPanel {
    private JButton confirmButton = new JButton("Confirm");
    private final JLabel title = new JLabel("Order Details");
    private final JPanel orderPanel = new JPanel();
    private final JPanel buttonPanel = new JPanel();
    private final JScrollPane scrollPane = new JScrollPane(orderPanel);
    private String orderNumber;

    public OrderView(User user) {
        this(user, null);
    }

    public OrderView(User user, Order order) {
        orderPanel.setLayout(new BoxLayout(orderPanel, BoxLayout.Y_AXIS));
        if (order != null) {
            orderNumber = order.getOrderNumber();
            fillTabs(orderNumber);
        }
        else {orderNumber = UUID.randomUUID().toString();}

        // Create Save and Confirm buttons
        JButton saveButton = new JButton("Save");

        // Create a panel for buttons
        buttonPanel.add(saveButton);
        buttonPanel.add(confirmButton);

        // Create a panel to hold the components
        setLayout(new BorderLayout());
        add(title, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.SOUTH);

        // Add action listeners to the buttons
        saveButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Component[] components = orderPanel.getComponents();
                BigDecimal totalCost = new BigDecimal("0.00");

                try {
                    if (order == null && components.length != 0) {
                        String insertOrder = "INSERT INTO team012.Order (orderNumber, dateOfPurchase, status, userID) VALUES (?, ?, ?, ?)";
                        try (PreparedStatement statement = connect.connection.prepareStatement(insertOrder)) {
                            statement.setString(1, orderNumber);
                            statement.setTimestamp(2, new Timestamp(new Date().getTime()));
                            statement.setString(3, "pending");
                            statement.setString(4, user.getUserID());
                            statement.executeUpdate();
                        } 
                    }
                    else {
                        String deleteOrderLine = "DELETE FROM team012.OrderLine WHERE orderNumber = ?";
                        try (PreparedStatement preparedStatement = connect.connection.prepareStatement(deleteOrderLine)) {
                            preparedStatement.setString(1, orderNumber);
                            preparedStatement.executeUpdate();
                        }

                        if (components.length == 0) {
                            String deleteOrder = "DELETE FROM team012.Order WHERE orderNumber = ?";
                            try (PreparedStatement preparedStatement = connect.connection.prepareStatement(deleteOrder)) {
                                preparedStatement.setString(1, orderNumber);
                                preparedStatement.executeUpdate();
                            }
                            return;
                        }
                    }
                } catch (SQLException ex) {
                        throw new RuntimeException(ex);
                }

                for (Component component : components) {
                    if (component instanceof TabPanel) {
                        TabPanel<?> tabPanel = (TabPanel<?>) component;
                        Product product = tabPanel.getProduct();
                        String insertOrderLine = "INSERT INTO team012.OrderLine (orderNumber, lineNumber, quantity, lineCost, code) VALUES (?, ?, ?, ?, ?)";
                        try (PreparedStatement statement = connect.connection.prepareStatement(insertOrderLine)) {
                            statement.setString(1, orderNumber);
                            statement.setString(2, UUID.randomUUID().toString());
                            statement.setInt(3, tabPanel.getQuantity());
                            statement.setBigDecimal(4, product.getPrice());
                            statement.setString(5, product.getCode());
                            statement.executeUpdate();
                        } catch (SQLException ex) {
                            throw new RuntimeException(ex);
                        }
                        totalCost = totalCost.add(product.getPrice().multiply(BigDecimal.valueOf(tabPanel.getQuantity())));
                    }
                }

                Order.updateTotalCost(totalCost, orderNumber);

                if (order == null) {
                    JFrame currentFrame = (JFrame) SwingUtilities.getWindowAncestor((Component) e.getSource());
                    currentFrame.dispose();
                    ProductView productView = new ProductView(user, "", Order.getOrder(orderNumber));
                }

            }
        });

        confirmButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                confirmOrder(user);
            }
        });

    }

    public void addTab(TabPanel<?> tab) {
        Component[] components = orderPanel.getComponents();
        boolean exists = false;
    
        for (Component component : components) {
            if (component instanceof TabPanel) {
                TabPanel<?> tabPanel = (TabPanel<?>) component;
                if (tabPanel.getProduct().equals(tab.getProduct())) {
                    exists = true;
                    break;
                }
            }
        }
    
        if (!exists) {
            orderPanel.add(tab);
        }
    }

    public OrderView getPanel() {
        return this;
    }

    private void confirmOrder(User user) {
        String update = "UPDATE team012.Order SET status = 'confirmed' WHERE orderNumber = ?";
        String bankDetail = "SELECT bankCardNumber, bankCardName, expiryDate, securityCode " +
                            "FROM team012.User " +
                            "WHERE userID = ? AND bankCardNumber IS NOT NULL AND bankCardName IS NOT NULL " +
                            "AND expiryDate IS NOT NULL AND securityCode IS NOT NULL";
        
        try (PreparedStatement preparedStatement = connect.connection.prepareStatement(bankDetail)) {
            preparedStatement.setString(1, user.getUserID());
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                try (PreparedStatement preparedStatement2 = connect.connection.prepareStatement(update)) {
                preparedStatement2.setString(1, orderNumber);
                int count = preparedStatement2.executeUpdate();
                if (count == 1) {
                    JOptionPane.showMessageDialog(null, "Order Confirmed");
                } else {
                    JOptionPane.showMessageDialog(null, "Press Save First");
                }
                    Timer timer = new Timer(3000, new ActionListener() {
                        @Override

                        public void actionPerformed(ActionEvent e) {
                            Window window = SwingUtilities.windowForComponent(confirmButton);
                            window.dispose();
                        }
                    });
                    timer.setRepeats(false);
                    timer.start();
                }
            }
            else {
                BankingDetails bankingDetails = new BankingDetails(user);
            }
                
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    private void fillTabs(String orderNumer) {
        String query = "SELECT * FROM team012.OrderLine WHERE orderNumber = ?";
        try (PreparedStatement preparedStatement = connect.connection.prepareStatement(query)) {
            preparedStatement.setString(1, orderNumber);
            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                OrderLine orderLine = new OrderLine(resultSet);
                String productQuery = Product.getProductQuery(resultSet.getString("code"));
                switch (resultSet.getString("code").charAt(0)) {
                    case 'L':
                        fetchDataAndPopulate(productQuery, Locomotive.class, orderPanel, "order", orderLine.getQuantity());
                    break;
        
                    case 'R':
                        fetchDataAndPopulate(productQuery, Track.class, orderPanel, "order", orderLine.getQuantity());
                    break;
        
                    case 'C':
                        fetchDataAndPopulate(productQuery, Controller.class, orderPanel, "order", orderLine.getQuantity());
                        break;
        
                    case 'S':
                        fetchDataAndPopulate(productQuery, RollingStock.class, orderPanel, "order", orderLine.getQuantity());
                        break;
                    
                    case 'M':
                        fetchDataAndPopulate(productQuery, Track.class, orderPanel, "order", orderLine.getQuantity());
                        break;
        
                    case 'P':
                        fetchDataAndPopulate(productQuery, TrackPack.class, orderPanel, "order", orderLine.getQuantity());
                        break;
                }
            }
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    private <T extends Product & Product.ExtraDetails> void fetchDataAndPopulate(String query, Class<T> clazz, JPanel panel, String flag, int quantity) {
        try (PreparedStatement preparedStatement = connect.connection.prepareStatement(query)) {
            ResultSet resultSet = preparedStatement.executeQuery();
            ArrayList<T> dataList = new ArrayList<>();
            while (resultSet.next()) {
                dataList.add(clazz.getDeclaredConstructor(ResultSet.class).newInstance(resultSet));
            }
            panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
            for (T data : dataList) {
                TabPanel<T> tab = new TabPanel<>(data, flag);
                tab.setQuantity(quantity);
                panel.add(tab);
            }
        } catch (SQLException | ReflectiveOperationException ex) {
            throw new RuntimeException(ex);
        }
    }

}
