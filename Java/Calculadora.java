public class Calculadora {

    public double adicionar(double a, double b) {
        return a + b;
    }

    public double subtrair(double a, double b) {
        return a - b;
    }

    public double multiplicar(double a, double b) {
        return a * b;
    }

    public double dividir(double a, double b) {
        if (b == 0) {
            throw new IllegalArgumentException("Divisão por zero não é permitida.");
        }
        return a / b;
    }

    public static void main(String[] args) {
        Calculadora calc = new Calculadora();

        System.out.println("Adição: " + calc.adicionar(5, 3));
        System.out.println("Subtração: " + calc.subtrair(5, 3));
        System.out.println("Multiplicação: " + calc.multiplicar(5, 3));
        System.out.println("Divisão: " + calc.dividir(5, 3));
    }
}
