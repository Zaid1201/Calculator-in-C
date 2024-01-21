package project.products;

import java.sql.ResultSet;
import java.sql.SQLException;

public class TrainSet extends Product implements Product.ExtraDetails {
    private String eraList;
    // Waiting for implement

    public TrainSet(ResultSet resultSet) throws SQLException {
        super(resultSet);
        this.eraList = resultSet.getString("era");
    }

    public String getEraList() {
        return eraList;
    }

    @Override
    public StringBuilder getDetails(StringBuilder text) {
        text.append("Era: " + eraList + "<br>");
        return text;
    }

}