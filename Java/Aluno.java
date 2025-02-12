public class Aluno {
    private String nome;
    private double nota1;
    private double nota2;
    private double nota3;

    public Aluno(String nome, double nota1, double nota2, double nota3) {
        this.nome = nome;
        this.nota1 = nota1;
        this.nota2 = nota2;
        this.nota3 = nota3;
    }

    public double calcularMedia() {
        double media = (nota1 + nota2 + nota3) / 3;
        return Math.round(media * 100.0) / 100.0; // Arredonda para 2 casas decimais
    }

    public static void main(String[] args) {
        Aluno aluno = new Aluno("Felipe", 7.5, 8.0, 6.5);
        System.out.println("Média do aluno: " + String.format("%.2f", aluno.calcularMedia()));
    }
}
