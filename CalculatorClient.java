import java.rmi.Naming;

public class CalculatorClient {
    public static void main(String[] args) {
        try {
           
            CalculatorInterface calculator = (CalculatorInterface) Naming.lookup("rmi://localhost/CalculatorService");
            
            
            double a = 10, b = 5;
            System.out.println("Add: " + calculator.add(a, b));
            System.out.println("Subtract: " + calculator.subtract(a, b));
            System.out.println("Multiply: " + calculator.multiply(a, b));
            System.out.println("Divide: " + calculator.divide(a, b));
        } catch (Exception e) {
            System.out.println("Calculator Client failed: " + e.getMessage());
        }
    }
}



