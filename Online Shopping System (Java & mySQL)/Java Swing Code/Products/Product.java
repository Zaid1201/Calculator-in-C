package project.products;

import java.math.BigDecimal;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Product {
    protected String code;
    protected String brand;
    protected String name;
    protected BigDecimal price;
    protected String gauge;
    protected int quantity;

    public Product(ResultSet resultSet) throws SQLException {
        this.code = resultSet.getString("code");
        this.brand = resultSet.getString("brand");
        this.name = resultSet.getString("name");
        this.price = resultSet.getBigDecimal("price");
        this.gauge = resultSet.getString("gauge");
        this.quantity = resultSet.getInt("quantity");
    }

    public static String getProductQuery(String code){
        String query = "";

        switch (code.charAt(0)) {
            case 'L':
                query = "SELECT team012.Product.*, team012.Locomotive.* " +
                        "FROM team012.Locomotive " +
                        "LEFT JOIN team012.Product ON team012.Locomotive.l_code = team012.Product.code";

            break;

            case 'R':
                query = "SELECT team012.Product.* " +
                        "FROM team012.Track " +
                        "LEFT JOIN team012.Product ON team012.Track.t_code = team012.Product.code";

            break;

            case 'C':
                query = "SELECT team012.Product.* " +
                        "FROM team012.Controller " +
                        "LEFT JOIN team012.Product ON team012.Controller.c_code = team012.Product.code";
                break;

            case 'S':
                query = "SELECT team012.Product.*, team012.RollingStock.* " +
                        "FROM team012.RollingStock " +
                        "LEFT JOIN team012.Product ON team012.RollingStock.rs_code = team012.Product.code";
                break;
            
            case 'M':
                query = "SELECT team012.Product.*, team012.TrainSet.* " +
                        "FROM team012.TrainSet " +
                        "LEFT JOIN team012.Product ON team012.TrainSet.ts_code = team012.Product.code";
                break;

            case 'P':
                query = "SELECT team012.Product.* " +
                        "FROM team012.TrackPack " +
                        "LEFT JOIN team012.Product ON team012.TrackPack.tp_code = team012.Product.code";
                break;
        }

        query = query + " WHERE team012.Product.code = '" + code + "'";

        return query;
    }

    public interface ExtraDetails {
        StringBuilder getDetails(StringBuilder text);
    }

    public String getCode() {
        return code;
    }

    public String getBrand() {
        return brand;
    }

    public String getName() {
        return name;
    }

    public BigDecimal getPrice() {
        return price;
    }

    public String getGauge() {
        return gauge;
    }

    public int getQuantity() {
        return quantity;
    }

}
