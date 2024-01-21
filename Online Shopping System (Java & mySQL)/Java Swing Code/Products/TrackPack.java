package project.products;

import java.sql.ResultSet;
import java.sql.SQLException;

public class TrackPack extends Product implements Product.ExtraDetails {
    // Waiting for implement

    public TrackPack(ResultSet resultSet) throws SQLException {
        super(resultSet);
    }

    @Override
    public StringBuilder getDetails(StringBuilder text) {
        return text;
    }

}