package project.products;

import java.util.Date;
import java.math.BigDecimal;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import project.lib.*;

public class Order {
    private String orderNumber;
    private Date dateOfPurchase;
    private String status;
    private BigDecimal totalCost;
    private String userID;

    public Order(ResultSet resultSet) throws SQLException {
        this.orderNumber = resultSet.getString("orderNumber");
        this.dateOfPurchase = resultSet.getTimestamp("dateOfPurchase");
        this.status = resultSet.getString("status");
        this.totalCost = resultSet.getBigDecimal("totalCost");
        this.userID = resultSet.getString("userID");
    }

    public static void updateTotalCost(BigDecimal totalCost, String orderNumber) {
        String update = "UPDATE team012.Order SET totalCost = ? WHERE orderNumber = ?";
        try (PreparedStatement statement = connect.connection.prepareStatement(update)) {
            statement.setBigDecimal(1, totalCost);
            statement.setString(2, orderNumber);
            statement.executeUpdate();
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    public static Order getOrder(String orderNumber) {
        String query = "SELECT * FROM team012.Order WHERE orderNumber = ?";
        try (PreparedStatement statement = connect.connection.prepareStatement(query)) {
            statement.setString(1, orderNumber);
            ResultSet resultSet = statement.executeQuery();
            resultSet.next();
            return new Order(resultSet);
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    public String getOrderNumber() {
        return orderNumber;
    }

    public Date getDateOfPurchase() {
        return dateOfPurchase;
    }

    public String getStatus() {
        return status;
    }

    public BigDecimal getTotalCost() {
        return totalCost;
    }

    public String getUserID() {
        return userID;
    }

}