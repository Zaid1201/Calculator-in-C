package project.gui;

import project.users.User;
import project.products.*;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TabPanel<T extends Product & Product.ExtraDetails> extends JPanel {

    private JLabel titleLabel;
    private JLabel iconLabel;
    private JSpinner quantitySpinner;
    private JButton addButton;
    private JButton editButton;
    private JButton deleteButton;
    private T localProduct;
    private User localUser;

    public TabPanel(T product, String tabFlag) {
        this.localProduct = product;
        StringBuilder floatText = new StringBuilder();
        floatText.append("Code: " + product.getCode() + "<br>")
                 .append("Brand: " + product.getBrand() + "<br>")
                 .append("Brand: " + product.getPrice() + "<br>")
                 .append("Gauge: " + product.getGauge() + "<br>")
                 .append("Quantity " + product.getQuantity() + "<br>");
        product.getDetails(floatText);

        setLayout(new BorderLayout());
        JPanel titlePanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        titleLabel = new JLabel("<html><font size='5'>" + product.getName() + "</font></html>");
        titlePanel.add(titleLabel);
        add(titlePanel, BorderLayout.NORTH);

        JPanel bottomPanel = new JPanel(new BorderLayout());

        // Left bottom Panel
        iconLabel = new JLabel(UIManager.getIcon("OptionPane.informationIcon"));
        iconLabel.setToolTipText("<html>" + floatText.toString() + "</html>");
        JPanel leftPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        leftPanel.add(iconLabel);
        leftPanel.add(editButton = new JButton("Edit"));
        bottomPanel.add(leftPanel, BorderLayout.WEST);

        // Right bottom Panel
        JPanel rightPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        quantitySpinner = new JSpinner(new SpinnerNumberModel(1, 1, 99, 1));

        rightPanel.add(quantitySpinner);
        rightPanel.add(deleteButton = new JButton("Delete"));
        rightPanel.add(addButton = new JButton("Add"));

        bottomPanel.add(rightPanel, BorderLayout.EAST);

        add(bottomPanel, BorderLayout.CENTER);

        if (tabFlag.equals("staff"))
            rightPanel.setVisible(false);
        else if (tabFlag.equals("order")) {
            editButton.setVisible(false);
            addButton.setVisible(false);
        }
        else {
            editButton.setVisible(false);
            deleteButton.setVisible(false);
            quantitySpinner.setVisible(false);
        }

        /*
         * Listeners
         */
        editButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                EditProduct<T> edit = new EditProduct<T>(product);
            }
        });
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Container container = SwingUtilities.getAncestorOfClass(ProductView.class, addButton);
                if (container instanceof ProductView) {
                    ProductView productView = (ProductView) container;
                    productView.getOrderPanel().addTab(new TabPanel<T>(product, "order"));
                    productView.revalidate();
                    productView.repaint();
                }
            }
        });
        deleteButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Container container = SwingUtilities.getAncestorOfClass(TabPanel.class, deleteButton);
                if (container instanceof TabPanel) {
                    TabPanel<?> tab = (TabPanel<?>) container;
                    JPanel orderView = (JPanel) tab.getParent();
                    orderView.remove(tab);
                    orderView.revalidate();
                    orderView.repaint();
                }
            }
        });

    }

    public void setQuantity(int quantity) {
        this.quantitySpinner.setValue(quantity);
    }

    public int getQuantity() {
        int quantity = (int) quantitySpinner.getValue();
        return quantity;
    }

    public T getProduct() {
        return localProduct;
    }

    public User getUser() {
        return localUser;
    }

}
