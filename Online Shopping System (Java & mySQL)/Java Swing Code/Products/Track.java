package project.products;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Track extends Product implements Product.ExtraDetails {

    public Track(ResultSet resultSet) throws SQLException {
        super(resultSet);
    }

    @Override
    public StringBuilder getDetails(StringBuilder text) {
        return text;
    }
}