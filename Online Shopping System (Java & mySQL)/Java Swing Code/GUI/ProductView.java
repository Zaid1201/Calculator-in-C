package project.gui;

import javax.swing.*;

import project.products.*;
import project.users.User;
import project.lib.*;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class ProductView extends JFrame {

    private final JPanel productPanel = new JPanel();
    private final JPanel topPanel = new JPanel();
    private final JPanel southPanel = new JPanel();
    private final JPanel trackPanel = new JPanel();
    private final JPanel controllPanel = new JPanel();
    private final JPanel locomotivePanel = new JPanel();
    private final JPanel rollingStockPanel = new JPanel();
    private final JPanel trainSetPanel = new JPanel();
    private final JPanel trackPackPanel = new JPanel();
    private final JPanel productBrowse = new JPanel();
    private final JComboBox<String> productType;
    private final Map<String, JPanel> panelMap = new HashMap<>();
    private final JLabel filter = new JLabel("Filter by product type");
    private final JButton addProduct = new JButton ("Add Product");
    private final JButton placedOrders = new JButton("Placed Orders");
    private final JButton orderHistory = new JButton ("Order History");
    private final JButton managerButton = new JButton ("Manager View");
    private OrderView orderView;
    private String flag;

    public ProductView(User loggedUser, String tabFlag) {
        this(loggedUser, tabFlag, null);
    }

    public ProductView(User loggedUser, String tabFlag, Order order) {
        super.setTitle("Product View");
        this.setSize(590, 345);
        this.setLayout(new BorderLayout());
        this.setLocationRelativeTo(null);
        this.flag = tabFlag;
        if (order != null)
            this.orderView = new OrderView(loggedUser, order);
        else
            this.orderView = new OrderView(loggedUser);
        this.setVisible(true);

        productPanel.setLayout(new BorderLayout());

        panelMap.put("", productBrowse);
        panelMap.put("Tracks", trackPanel);
        panelMap.put("Controllers", controllPanel);
        panelMap.put("Locomotives", locomotivePanel);
        panelMap.put("Rolling Stock", rollingStockPanel);
        panelMap.put("Train Sets", trainSetPanel);
        panelMap.put("Track Packs", trackPackPanel);
        productType = new JComboBox<>(panelMap.keySet().toArray(new String[7]));

        topPanel.setLayout(new GridLayout(0,2));
        topPanel.add(filter);
        topPanel.add(productType);
        productPanel.add(topPanel,BorderLayout.NORTH);

        southPanel.setLayout(new GridLayout(1,3));
        southPanel.add(addProduct);
        southPanel.add(placedOrders);
        southPanel.add(orderHistory);
        productPanel.add(southPanel, BorderLayout.SOUTH);

        this.add(productPanel, BorderLayout.CENTER);
        if (!flag.equals("staff")) {
            this.add(orderView, BorderLayout.EAST);
            southPanel.setVisible(false);
        }
        else if (loggedUser.getUserType() == 3) {
            southPanel.setLayout(new GridLayout(1,4));
            southPanel.add(managerButton);
        }

        String[] queries = new String[6];
        queries[0] = "SELECT team012.Product.* " +
                     "FROM team012.Track " +
                     "LEFT JOIN team012.Product ON team012.Track.t_code = team012.Product.code";
        queries[1] = "SELECT team012.Product.* " +
                     "FROM team012.Controller " +
                     "LEFT JOIN team012.Product ON team012.Controller.c_code = team012.Product.code";
        queries[2] = "SELECT team012.Product.*, team012.Locomotive.* " +
                     "FROM team012.Locomotive " +
                     "LEFT JOIN team012.Product ON team012.Locomotive.l_code = team012.Product.code";
        queries[3] = "SELECT team012.Product.*, team012.RollingStock.* " +
                     "FROM team012.RollingStock " +
                     "LEFT JOIN team012.Product ON team012.RollingStock.rs_code = team012.Product.code";
        queries[4] = "SELECT team012.Product.*, team012.TrainSet.* " +
                     "FROM team012.TrainSet " +
                     "LEFT JOIN team012.Product ON team012.TrainSet.ts_code = team012.Product.code";
        queries[5] = "SELECT team012.Product.* " +
                     "FROM team012.TrackPack " +
                     "LEFT JOIN team012.Product ON team012.TrackPack.tp_code = team012.Product.code";

        fetchDataAndPopulate(queries[0], Track.class, trackPanel);
        fetchDataAndPopulate(queries[1], Controller.class, controllPanel);
        fetchDataAndPopulate(queries[2], Locomotive.class, locomotivePanel);
        fetchDataAndPopulate(queries[3], RollingStock.class, rollingStockPanel);
        fetchDataAndPopulate(queries[4], TrainSet.class, trainSetPanel);
        fetchDataAndPopulate(queries[5], TrackPack.class, trackPackPanel);

        productBrowse.setLayout(new BoxLayout(productBrowse, BoxLayout.Y_AXIS));
        productBrowse.add(trackPanel);
        productBrowse.add(controllPanel);
        productBrowse.add(locomotivePanel);
        productBrowse.add(rollingStockPanel);
        productBrowse.add(trainSetPanel);
        productBrowse.add(trackPackPanel);

        JScrollPane scrollPane = new JScrollPane(productBrowse);
        productPanel.add(scrollPane, BorderLayout.CENTER);

        productType.addActionListener(e -> {
            String selection = (String) productType.getSelectedItem();
            Component[] components = productBrowse.getComponents();
            if ("".equals(selection))
                for (Component component : components)
                    component.setVisible(true);
            else {
                for (Component component : components)
                    component.setVisible(false);
                panelMap.get(selection).setVisible(true);
            }
        });

        addProduct.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                AddProduct addProduct = new AddProduct();
            }
        });

        orderHistory.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                OrderHistory orderHistory = new OrderHistory(loggedUser, tabFlag);
            }
        });

        placedOrders.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                OrderStatus orderStatus = new OrderStatus();
            }
        });

        managerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Manager managerView = new Manager();
            }
        });

    }


    public OrderView getOrderPanel() {
        return orderView;
    }

    private <T extends Product & Product.ExtraDetails> void fetchDataAndPopulate(String query, Class<T> clazz, JPanel panel) {
        try (PreparedStatement preparedStatement = connect.connection.prepareStatement(query)) {
            ResultSet resultSet = preparedStatement.executeQuery();
            ArrayList<T> dataList = new ArrayList<>();
            while (resultSet.next()) {
                dataList.add(clazz.getDeclaredConstructor(ResultSet.class).newInstance(resultSet));
            }
            panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
            for (T data : dataList) {
                TabPanel<T> tab = new TabPanel<>(data, flag);
                panel.add(tab);
            }
        } catch (SQLException | ReflectiveOperationException ex) {
            throw new RuntimeException(ex);
        }
    }

}
