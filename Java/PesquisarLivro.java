public class Livro {
    private String titulo;
    private String autor;
    private String genero;

    public Livro(String titulo, String autor, String genero) {
        this.titulo = titulo;
        this.autor = autor;
        this.genero = genero;
    }

    public void imprimirDados() {
        System.out.println("Título:  " + titulo);
        System.out.println("Autor:  " + autor);
        System.out.println("Gênero:  " + genero);
    }

    // Adicionando o método main para testar a classe
    public static void main(String[] args) {
        Livro meuLivro = new Livro("O Senhor dos Anéis", "J.R.R. Tolkien", "Fantasia");
        meuLivro.imprimirDados();
    }
}
