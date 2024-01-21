package project.gui;

import project.products.*;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.BorderLayout;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.swing.table.TableColumn;
import java.math.BigDecimal;
import static project.lib.connect.connection;

public class EditProduct<P extends Product & Product.ExtraDetails> extends JFrame {
    private final JButton updateButton = new JButton("Update");
    private final JButton deleteButton = new JButton("Delete");
    DefaultTableModel editTable = new DefaultTableModel();

    public EditProduct(P product) {
        super("Edit Product");
        // Add columns to the table model based on the product type
        char type = product.getCode().charAt(0);
        editTable.addColumn("Code");
        editTable.addColumn("Brand");
        editTable.addColumn("Name");
        editTable.addColumn("Price");
        editTable.addColumn("Gauge");
        editTable.addColumn("Quantity");
        // Add additional columns for specific product types
        if (type == 'L') {
            editTable.addColumn("Era");
            editTable. addColumn("DCC Code");
            Locomotive locomotive = (Locomotive) product;
            Object[] rowData = {product.getCode(), product.getBrand(), product.getName(), product.getPrice(), product.getGauge(), product.getQuantity(), locomotive.getEraList(), locomotive.getDCCCode()};
            editTable.addRow(rowData);

        } else if (type == 'M') {
            editTable.addColumn("Era");
            TrainSet trainSet = (TrainSet) product;
            Object[] rowData = {product.getCode(), product.getBrand(), product.getName(), product.getPrice(), product.getGauge(), product.getQuantity(), trainSet.getEraList()};
            editTable.addRow(rowData);

        } else if (type == 'S') {
            editTable.addColumn("Era");
            RollingStock rollingStock = (RollingStock) product;
            Object[] rowData = {product.getCode(), product.getBrand(), product.getName(), product.getPrice(), product.getGauge(), product.getQuantity(), rollingStock.getEraList()};
            editTable.addRow(rowData);
        } else {
            Object[] rowData = {product.getCode(), product.getBrand(), product.getName(), product.getPrice(), product.getGauge(), product.getQuantity()};
            editTable.addRow(rowData);
        }

        JTable productTable = new JTable(editTable);
        productTable.setEnabled(true);
        // Set cell editor for the code column to be non-editable
        TableColumn codeColumn = productTable.getColumnModel().getColumn(0);
        codeColumn.setCellEditor(new DefaultCellEditor(new JTextField()) {
            @Override
            public boolean isCellEditable(java.util.EventObject e) {
                return false;
            }
        });
        // Add the table to a scroll pane and set up the layout
        JScrollPane tableScrollPane = new JScrollPane(productTable);
        this.setLayout(new BorderLayout());
        this.add(tableScrollPane, BorderLayout.CENTER);

        updateButton.addActionListener(e -> updateDatabase(product));
        deleteButton.addActionListener(e -> deleteFromDatabase(product));

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(updateButton);
        buttonPanel.add(deleteButton);
        this.add(buttonPanel, BorderLayout.SOUTH);

        this.setSize(600, 200);
        this.setLocationRelativeTo(null);
        this.setVisible(true);
    }
    //Updates the product details in the database based on the edited values.
    private void updateDatabase(P product) {
        char Type = product.getCode().charAt(0);
        // SQL queries for updating product and specific product type details
        String update_query = "UPDATE team012.Product SET brand = ?, name = ?, price = ?, gauge = ?, quantity = ? WHERE code = ?";
        String update_query1 = "UPDATE team012.Locomotive SET dccCode = ?, era = ? WHERE l_code = ?";
        String update_query2 = "UPDATE team012.TrainSet SET era = ? WHERE ts_code = ?";
        String update_query3 = "UPDATE team012.RollingStock SET era = ? WHERE rs_code = ?";
        // Get selected values from the table for updating
        Object selectedBrand = editTable.getValueAt(0, 1);
        Object selectedName = editTable.getValueAt(0, 2);
        Object selectedPrice = editTable.getValueAt(0, 3);
        Object selectedGauge = editTable.getValueAt(0, 4);
        Object selectedQuantity = editTable.getValueAt(0, 5);
        BigDecimal selectedPrice_Bd = new BigDecimal(((String) selectedPrice).trim());
        int selectedQuantity_int = Integer.parseInt(((String) selectedQuantity).trim());

        try (PreparedStatement preparedStatement = connection.prepareStatement(update_query)) {
            preparedStatement.setString(1, (String) selectedBrand);
            preparedStatement.setString(2, (String) selectedName);
            preparedStatement.setBigDecimal(3, selectedPrice_Bd);
            preparedStatement.setString(4, (String) selectedGauge);
            preparedStatement.setInt(5, selectedQuantity_int);
            preparedStatement.setString(6, product.getCode());
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        try {
            // Update details based on the product type
            switch (Type) {
                case 'L':
                    try (PreparedStatement preparedStatement1 = connection.prepareStatement(update_query1)) {
                        Locomotive locomotive = (Locomotive) product;
                        preparedStatement1.setString(1, locomotive.getDCCCode());
                        preparedStatement1.setString(2, (String) editTable.getValueAt(0, 5));
                        preparedStatement1.setString(3, product.getCode());

                        preparedStatement1.executeUpdate();
                    }
                    break;

                case 'M':
                    try (PreparedStatement preparedStatement2 = connection.prepareStatement(update_query2)) {
                        TrainSet trainSet = (TrainSet) product;
                        preparedStatement2.setString(1, trainSet.getEraList());
                        preparedStatement2.setString(2, product.getCode());
                        preparedStatement2.executeUpdate();
                    }
                    break;

                case 'S':
                    try (PreparedStatement preparedStatement3 = connection.prepareStatement(update_query3)) {
                        RollingStock rollingStock = (RollingStock) product;
                        preparedStatement3.setString(1, rollingStock.getEraList());
                        preparedStatement3.setString(2, product.getCode());
                        preparedStatement3.executeUpdate();
                    }
                    break;
            }

            JOptionPane.showMessageDialog(this, "Update successful!", "Success", JOptionPane.INFORMATION_MESSAGE);
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Failed to update: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void deleteFromDatabase(P product) {
        char Type = product.getCode().charAt(0);

        String delete_query = "DELETE FROM team012.Controller WHERE c_code = ?";
        String delete_query1 = "DELETE FROM team012.Locomotive WHERE l_code = ?";
        String delete_query2 = "DELETE FROM team012.TrainSet WHERE ts_code = ?";
        String delete_query3 = "DELETE FROM team012.RollingStock WHERE rs_code = ?";
        String delete_query4 = "DELETE FROM team012.Track WHERE t_code = ?";
        String delete_query5 = "DELETE FROM team012.TrackPack WHERE tp_code = ?";

        int confirm = JOptionPane.showConfirmDialog(this, "Are you sure you want to delete this product?", "Confirm Deletion", JOptionPane.YES_NO_OPTION);
        if (confirm != JOptionPane.YES_OPTION) {
            return;
        }
        try {
            switch (Type){
                case 'L':
                    try(PreparedStatement preparedStatement1 = connection.prepareStatement(delete_query1)){
                        Locomotive locomotive = (Locomotive) product;
                        preparedStatement1.setString(1, locomotive.getCode());
                        preparedStatement1.executeUpdate();
                    }
                    break;

                case 'C':
                    try(PreparedStatement preparedStatement2 = connection.prepareStatement(delete_query)) {
                        Controller controller = (Controller) product;
                        preparedStatement2.setString(1, controller.getCode());
                        preparedStatement2.executeUpdate();
                    }
                    break;

                case 'M':
                    try(PreparedStatement preparedStatement3 = connection.prepareStatement(delete_query2)) {
                        TrainSet trainSet = (TrainSet) product;
                        preparedStatement3.setString(1, trainSet.getCode());
                        preparedStatement3.executeUpdate();
                    }
                    break;

                case 'S':
                    try (PreparedStatement preparedStatement4 = connection.prepareStatement(delete_query3)) {
                        RollingStock rollingStock = (RollingStock) product;
                        preparedStatement4.setString(1, rollingStock.getCode());
                        preparedStatement4.executeUpdate();
                    }
                    break;
                case 'R':
                    try (PreparedStatement preparedStatement5 = connection.prepareStatement(delete_query4)) {
                        Track track = (Track) product;
                        preparedStatement5.setString(1, track.getCode());
                        preparedStatement5.executeUpdate();
                    }
                    break;
                case 'P':
                    try (PreparedStatement preparedStatement6 = connection.prepareStatement(delete_query5)) {
                        TrackPack trackPack = (TrackPack) product;
                        preparedStatement6.setString(1, trackPack.getCode());
                        preparedStatement6.executeUpdate();
                    }
                    break;
            }
        } catch (SQLException e) {
    }
        String delete_query6 = "DELETE FROM team012.Product WHERE code = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(delete_query6)) {
            preparedStatement.setString(1, product.getCode());
            preparedStatement.executeUpdate();
            JOptionPane.showMessageDialog(this, "Delete successful!", "Success", JOptionPane.INFORMATION_MESSAGE);
            this.dispose(); // Close the window after deletion
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Failed to delete: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
}
