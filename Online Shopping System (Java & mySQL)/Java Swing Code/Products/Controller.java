package project.products;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Controller extends Product implements Product.ExtraDetails {

    public Controller(ResultSet resultSet) throws SQLException {
        super(resultSet);
    }
    
    @Override
    public StringBuilder getDetails(StringBuilder text) {
        return text;
    }
}