
package project.gui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.math.BigDecimal;

import static project.lib.connect.connection;

public class AddProduct extends JFrame {
    private final JPanel panel1 = new JPanel();
    private final JButton submitButton = new JButton("Submit");
    private final JComboBox<String> productType;
    private final JLabel filterLabel = new JLabel("Product Type");
    private final JLabel DccCodeLabel = new JLabel("DccCode:");
    private final JComboBox<String> DccCodeComboBox = new JComboBox<>();

    private final JLabel brandFilterLabel = new JLabel("Brand:");
    private final JComboBox<String> brandFilterComboBox = new JComboBox<>();

    private final JLabel gaugeTypeFilterLabel = new JLabel("Gauge Type:");
    private final JComboBox<String> gaugeTypeFilterComboBox = new JComboBox<>();
    private final JTable productTable;

    public AddProduct() {
        super("Add Products");

        // Product Type ComboBox
        String[] types = {"", "Train Sets", "Track Packs", "Rolling Stock", "Track", "Controllers", "Locomotive"};
        productType = new JComboBox<>(types);

        // Brand Filter ComboBox
        String[] brandOptions = {"Hornby", "Bachmann", "Graham Farish", "Peco", "Dapol"};
        brandFilterComboBox.addItem("");
        for (String option : brandOptions) {
            brandFilterComboBox.addItem(option);
        }

        // GaugeType Filter ComboBox
        String[] gaugeTypeOptions = {"OO", "TT", "N"};
        gaugeTypeFilterComboBox.addItem("");
        for (String option : gaugeTypeOptions) {
            gaugeTypeFilterComboBox.addItem(option);
        }


        // Layout
        panel1.setLayout(new GridLayout(2, 4));
        panel1.add(filterLabel);
        panel1.add(productType);
        panel1.add(DccCodeLabel);
        panel1.add(DccCodeComboBox);

        panel1.add(brandFilterLabel);
        panel1.add(brandFilterComboBox);
        panel1.add(gaugeTypeFilterLabel);
        panel1.add(gaugeTypeFilterComboBox);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                saveToDatabase();
            }
        });
        productType.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
                updateAdditionalFilter();
                updateProductTable();
            }
        });

        brandFilterComboBox.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
                updateProductTable();
            }
        });

        gaugeTypeFilterComboBox.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
                updateProductTable();
            }
        });

        this.setLocationRelativeTo(null);
        this.pack();
        this.setSize(800, 400);
        this.setVisible(true);

        // Table
        String[] columnNames = {"Code", "Brand", "Name", "Price", "Gauge", "Quantity", "Era"};

        String[][] rowData = {
                {String.valueOf(' '), " ", " ", " ", " ", " ", " "},
        };
        DefaultTableModel model = new DefaultTableModel(rowData, columnNames);
        productTable = new JTable(model);
        productTable.setEnabled(true);

        // Add JScrollPane for the table
        JScrollPane tableScrollPane = new JScrollPane(productTable);
        updateAdditionalFilter();
        // Main layout
        this.setLayout(new BorderLayout());
        this.add(panel1, BorderLayout.NORTH);
        this.add(tableScrollPane, BorderLayout.CENTER);
        this.add(submitButton, BorderLayout.SOUTH);

    }
    //save to database
    private void saveToDatabase() {
        // SQL Insert Queries
        String insert_query = "INSERT INTO team012.Product (code, brand, name, price, gauge, quantity) VALUES (?, ?, ?, ?, ?, ?)";
        String insert_query1 = "INSERT INTO team012.Locomotive (l_code, dccCode, era) VALUES (?, ?, ?)";
        String insert_query2 = "INSERT INTO team012.TrainSet (ts_code, era) VALUES (?, ?)";
        String insert_query3 = "INSERT INTO team012.RollingStock (rs_code, era) VALUES (?, ?)";
        String insert_query4 = "INSERT INTO team012.Controller (c_code) VALUES (?)";
        String insert_query5 = "INSERT INTO team012.Track (t_code) VALUES (?)";
        String insert_query6 = "INSERT INTO team012.TrackPack (tp_code) VALUES (?)";
        // Get selected values from the table
        Object selectedCode = productTable.getValueAt(0, 0);
        Object selectedBrand = productTable.getValueAt(0, 1);
        Object selectedName = productTable.getValueAt(0, 2);
        Object selectedPrice = productTable.getValueAt(0, 3);
        Object selectedGauge = productTable.getValueAt(0, 4);
        Object selectedQuantity = productTable.getValueAt(0, 5);
        Object selectedEra = productTable.getValueAt(0, 6);
        BigDecimal selectedPrice_Bd = new BigDecimal(((String) selectedPrice).trim());
        int selectedQuantity_int = Integer.parseInt(((String) selectedQuantity).trim());

        try (PreparedStatement preparedStatement = connection.prepareStatement(insert_query)) {
            preparedStatement.setString(1, (String) selectedCode);
            preparedStatement.setString(2, (String) selectedBrand);
            preparedStatement.setString(3, (String) selectedName);
            preparedStatement.setBigDecimal(4, selectedPrice_Bd);
            preparedStatement.setString(5, (String) selectedGauge);
            preparedStatement.setInt(6, selectedQuantity_int);
            preparedStatement.executeUpdate();

            String selectedProductType = (String) productType.getSelectedItem();
            try {
                switch (selectedProductType) {
                    case"Controllers":
                        try (PreparedStatement preparedStatement4 = connection.prepareStatement(insert_query4)) {
                            preparedStatement4.setString(1, (String) selectedCode);
                            preparedStatement4.executeUpdate();
                        }
                        break;
                    case"Track":
                        try (PreparedStatement preparedStatement5 = connection.prepareStatement(insert_query5)) {
                            preparedStatement5.setString(1, (String) selectedCode);
                            preparedStatement5.executeUpdate();
                        }
                        break;
                    case"Track Packs":
                        try (PreparedStatement preparedStatement6 = connection.prepareStatement(insert_query6)) {
                            preparedStatement6.setString(1, (String) selectedCode);
                            preparedStatement6.executeUpdate();
                        }
                        break;
                    case "Train Sets":
                        try (PreparedStatement preparedStatement2 = connection.prepareStatement(insert_query2)) {
                            preparedStatement2.setString(1, (String) selectedCode);
                            preparedStatement2.setString(2, (String) selectedEra);
                            preparedStatement2.executeUpdate();
                        }
                        break;
                    case "Rolling Stock":
                        try (PreparedStatement preparedStatement3 = connection.prepareStatement(insert_query3)) {
                            preparedStatement3.setString(1, (String) selectedCode);
                            preparedStatement3.setString(2, (String) selectedEra);
                            preparedStatement3.executeUpdate();
                        }
                        break;
                    case "Locomotive":
                        try (PreparedStatement preparedStatement1 = connection.prepareStatement(insert_query1)) {
                            preparedStatement1.setString(1, (String) selectedCode);
                            preparedStatement1.setString(2, (String) DccCodeComboBox.getSelectedItem());
                            preparedStatement1.setString(3, (String) selectedEra);
                            preparedStatement1.executeUpdate();
                        }
                        break;
                }
                JOptionPane.showMessageDialog(this, "Successful", "!!!", JOptionPane.INFORMATION_MESSAGE);
            } catch (SQLException e) {
                JOptionPane.showMessageDialog(this, "Failed to upload: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
    // Update visibility of additional filters based on product type
    private void updateAdditionalFilter() {
        String selectedType = (String) productType.getSelectedItem();
        String[] filterOptions;

        switch (selectedType) {
            case "Rolling Stock":
            case "Train Sets":
            case "Track Packs":
            case "Track":
            case "Controllers":
                showBrandFilter();
                showGaugeTypeFilter();
                hideAdditionalFilter();
                break;
            case "Locomotive":
                filterOptions = new String[]{"Analogue", "DCC-Ready", "DCC-Fitted", "DCC-Sound"};
                showAdditionalFilter(filterOptions);
                showBrandFilter();
                showGaugeTypeFilter();
                break;
            default:
                hideAdditionalFilter();
                hideBrandFilter();
                hideGaugeTypeFilter();
                break;
        }
    }

    private void showBrandFilter() {
        brandFilterLabel.setVisible(true);
        brandFilterComboBox.setVisible(true);
    }

    private void hideBrandFilter() {
        brandFilterLabel.setVisible(false);
        brandFilterComboBox.setVisible(false);
    }

    private void showGaugeTypeFilter() {
        gaugeTypeFilterLabel.setVisible(true);
        gaugeTypeFilterComboBox.setVisible(true);
    }

    private void hideGaugeTypeFilter() {
        gaugeTypeFilterLabel.setVisible(false);
        gaugeTypeFilterComboBox.setVisible(false);
    }

    private void showAdditionalFilter(String[] filterOptions) {
        DccCodeLabel.setVisible(true);
        DccCodeComboBox.setVisible(true);

        DccCodeComboBox.removeAllItems();
        for (String option : filterOptions) {
            DccCodeComboBox.addItem(option);
        }
    }

    private void hideAdditionalFilter() {
        DccCodeLabel.setVisible(false);
        DccCodeComboBox.setVisible(false);
    }
    // Update the product table based on selected filters
    private void updateProductTable() {
        DefaultTableModel model = (DefaultTableModel) productTable.getModel();
        model.setRowCount(0);

        String selectedProductType = (String) productType.getSelectedItem();
        String brandName = (String) brandFilterComboBox.getSelectedItem();
        String gaugeType = (String) gaugeTypeFilterComboBox.getSelectedItem();

        boolean hideEraColumn = selectedProductType.equals("Controllers") ||
                selectedProductType.equals("Track") ||
                selectedProductType.equals("Track Packs");

        switch (selectedProductType) {
            case "Train Sets":
                model.addRow(new Object[]{"M", brandName, " ", " ", gaugeType, "", ""});
                break;
            case "Track Packs":
                model.addRow(new Object[]{"P", brandName, " ", " ", gaugeType, "", ""});
                break;
            case "Rolling Stock":
                model.addRow(new Object[]{"S", brandName, " ", " ", gaugeType, "", ""});
                break;
            case "Track":
                model.addRow(new Object[]{"R", brandName, " ", " ", gaugeType, "", ""});
                break;
            case "Controllers":
                model.addRow(new Object[]{"C", brandName, " ", " ", gaugeType, "", ""});
                break;
            case "Locomotive":
                model.addRow(new Object[]{"L", brandName, " ", " ", gaugeType, "", ""});
                break;
        }

        // Hide/Show "era" column based on the selected product type
        productTable.getColumnModel().getColumn(6).setMinWidth(hideEraColumn ? 0 : 75);
        productTable.getColumnModel().getColumn(6).setMaxWidth(hideEraColumn ? 0 : 75);
        productTable.getColumnModel().getColumn(6).setWidth(hideEraColumn ? 0 : 75);
        productTable.getTableHeader().getColumnModel().getColumn(6).setMaxWidth(hideEraColumn ? 0 : 75);
        productTable.getTableHeader().getColumnModel().getColumn(6).setMinWidth(hideEraColumn ? 0 : 75);
    }

}