package project;

import javax.swing.SwingUtilities;
import project.gui.*;

public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            final HomePage shoppingSystem = new HomePage();
        });
    }
}