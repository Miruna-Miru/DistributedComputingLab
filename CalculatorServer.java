import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;

public class CalculatorServer {
    public static void main(String[] args) {
        try {
            CalculatorImpl calculator = new CalculatorImpl();
            
            LocateRegistry.createRegistry(1099);
            
            Naming.rebind("rmi://localhost/CalculatorService", calculator);
            System.out.println("Calculator RMI Server is ready.");
        } catch (Exception e) {
            System.out.println("Calculator Server failed: " + e.getMessage());
        }
    }
}
