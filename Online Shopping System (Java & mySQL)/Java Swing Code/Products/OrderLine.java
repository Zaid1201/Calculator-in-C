package project.products;

import java.sql.ResultSet;
import java.sql.SQLException;

public class OrderLine {
    private String orderNumber;
    private String lineNumber;
    private int quantity;
    private Double lineCost;
    private String code;

    public OrderLine(ResultSet resultSet) throws SQLException {
        this.orderNumber = resultSet.getString("orderNumber");
        this.lineNumber = resultSet.getString("lineNumber");
        this.quantity = resultSet.getInt("quantity");
        this.lineCost = resultSet.getDouble("lineCost");
        this.code = resultSet.getString("code");
    }

    public String getOrderNumber() {
        return orderNumber;
    }

    public String getLineNumber() {
        return lineNumber;
    }

    public int getQuantity() {
        return quantity;
    }

    public Double getLineCost() {
        return lineCost;
    }

    public String getCode() {
        return code;
    }
}
