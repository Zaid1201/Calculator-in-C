package project.lib;

import java.sql.*;

public class connect {
    public static Connection connection;

    static {
        try {
            connection = DriverManager.getConnection("jdbc:mysql://stusql.dcs.shef.ac.uk:3306/?user=team012", "team012", "aajai0Aht");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

}