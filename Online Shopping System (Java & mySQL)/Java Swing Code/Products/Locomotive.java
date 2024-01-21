package project.products;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Locomotive extends Product implements Product.ExtraDetails {
    private String eraList;
    private String dccCode;

    public Locomotive(ResultSet resultSet) throws SQLException {
        super(resultSet);
        this.eraList = resultSet.getString("era");
        this.dccCode = resultSet.getString("dccCode");
    }

    public String getEraList() {
        return eraList;
    }

    public String getDCCCode() {
        return dccCode;
    }

    @Override
    public StringBuilder getDetails(StringBuilder text) {
        text.append("Era: " + eraList + "<br>")
            .append("DCC Code: " + dccCode + "<br>");
        return text;
    }

}