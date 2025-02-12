import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

// Classe base Pessoa
abstract class Pessoa {
    //ajustei: protected foi usado em vez de private para que as subclasses possam acessar diretamente esses atributos
    protected int codPessoa;
    protected String nome;

    public Pessoa(int codPessoa, String nome) {
        this.codPessoa = codPessoa;
        this.nome = nome;
    }

    public int getCodPessoa() { return codPessoa; }
    public String getNome() { return nome; }

    public abstract void cadastrar();
}

// Subclasse Cliente
class Cliente extends Pessoa {
    //corrigido: Antes, este método estava definido como int em vez de string e agora ele retorna o email corretamente
    private String email;

    public Cliente(int codPessoa, String nome, String email) {
        super(codPessoa, nome);
        this.email = email;
    }

    public String getEmail() { return email; }
    public void setEmail(String email) { this.email = email; }

    @Override
    public void cadastrar() {
        System.out.println("Cliente cadastrado: " + nome + " (Código: " + codPessoa + ", Email: " + email + ")");
    }

    public void consultar() {
        System.out.println("Detalhes do Cliente: Código: " + codPessoa + ", Nome: " + nome + ", Email: " + email);
    }
}

// Subclasse Atendente
class Atendente extends Pessoa {
    private int numAtendente;

    public Atendente(int codPessoa, String nome, int numAtendente) {
        super(codPessoa, nome);
        this.numAtendente = numAtendente;
    }

    @Override
    public void cadastrar() {
        System.out.println("Atendente cadastrado: " + nome + " (Código: " + codPessoa + ", Nº Atendente: " + numAtendente + ")");
    }
}

// Subclasse Técnico
class Tecnico extends Pessoa {
    //correção: numTecnico agora é PRIVATE e foi renomeado para evitar conflito
    private int numTecnico;

    public Tecnico(int codPessoa, String nome, int numTecnico) {
        super(codPessoa, nome);
        this.numTecnico = numTecnico;
    }

    public int getNumTecnico() { return numTecnico; }
    public void setNumTecnico(int numTecnico) { this.numTecnico = numTecnico; }

    @Override
    public void cadastrar() {
        System.out.println("Técnico cadastrado: " + nome + " (Código: " + codPessoa + ", Nº Técnico: " + numTecnico + ")");
    }

    public void realizarManutencao() {
        System.out.println("Técnico " + nome + " realizando manutenção.");
    }
}

// Classe Item
class Item {
    private String nome;
    private double preco;

    public Item(String nome, double preco) {
        this.nome = nome;
        this.preco = preco;
    }

    public String getNome() { return nome; }
    public double getPreco() { return preco; }

    @Override
    public String toString() {
        return nome + " - R$" + preco;
    }
}

// Classe Pedido
class Pedido {
    private int numeroPedido;
    private String descricao;
    private List<Item> itens;
    private Cliente cliente;
    private double valorTotal;

    public Pedido(int numeroPedido, String descricao, Cliente cliente) {
        this.numeroPedido = numeroPedido;
        this.descricao = descricao;
        this.cliente = cliente;
        this.itens = new ArrayList<>();
        this.valorTotal = 0.0;
    }

    public void adicionarItem(Item item) {
        itens.add(item);
        valorTotal += item.getPreco();
        System.out.println("Item adicionado: " + item);
    }

    public void removerItem(Item item) {
        if (itens.remove(item)) {
            valorTotal -= item.getPreco();
            System.out.println("Item removido: " + item);
        } else {
            System.out.println("Item não encontrado: " + item);
        }
    }

    public void exibirDetalhes() {
        System.out.println("Pedido #" + numeroPedido + ": " + descricao + " - Cliente: " + cliente.getNome());
        System.out.println("Itens do Pedido:");
        for (Item item : itens) {
            System.out.println(" - " + item);
        }
        System.out.println("Valor Total: R$" + valorTotal);
    }
}

// Classes para o sistema de biblioteca
class Livro {
    private String titulo;
    private String autor;

    public Livro(String titulo, String autor) {
        this.titulo = titulo;
        this.autor = autor;
    }

    @Override
    public String toString() {
        return "Título: " + titulo + ", Autor: " + autor;
    }
}

class Emprestimo {
    private Livro livro;
    private Cliente cliente;
    private LocalDate dataEmprestimo;

    public Emprestimo(Livro livro, Cliente cliente) {
        this.livro = livro;
        this.cliente = cliente;
        this.dataEmprestimo = LocalDate.now();
    }

    @Override
    public String toString() {
        DateTimeFormatter formato = DateTimeFormatter.ofPattern("dd/MM/yyyy");
        return "Empréstimo do livro: " + livro + ", Cliente: " + cliente.getNome() + ", Data: " + dataEmprestimo.format(formato);
    }
}

class Biblioteca {
    private List<Livro> livros;
    private List<Cliente> clientes;
    private List<Emprestimo> emprestimos;

    public Biblioteca() {
        this.livros = new ArrayList<>();
        this.clientes = new ArrayList<>();
        this.emprestimos = new ArrayList<>();
    }

    public void adicionarLivro(Livro livro) { livros.add(livro); }
    public void adicionarCliente(Cliente cliente) { clientes.add(cliente); }

    public void listarLivros() {
        System.out.println("Livros disponíveis:");
        for (Livro livro : livros) { System.out.println(livro); }
    }

    public void emprestarLivro(Livro livro, Cliente cliente) {
        if (livros.contains(livro)) {
            Emprestimo emprestimo = new Emprestimo(livro, cliente);
            emprestimos.add(emprestimo);
            livros.remove(livro);
            System.out.println("Empréstimo realizado: " + emprestimo);
        } else {
            System.out.println("Livro não disponível para empréstimo.");
        }
    }
}

// Main padraozin
public class Main {
    public static void main(String[] args) {
        // Clientes e Livros
        Cliente cliente1 = new Cliente(1, "Jacinto Pinto", "jacintopintoakinorego@.com");
        cliente1.cadastrar();
        
        Livro livro1 = new Livro("Dom Casmurro", "Machado de Assis");
        Livro livro2 = new Livro("O Alquimista", "Paulo Coelho");

        // Pedido com itens
        Pedido pedido1 = new Pedido(1, "Pedido de Teste", cliente1);
        Item item1 = new Item("Produto A", 50.0);
        Item item2 = new Item("Produto B", 30.0);
        
        pedido1.adicionarItem(item1);
        pedido1.adicionarItem(item2);
        pedido1.exibirDetalhes();

        // Biblioteca
        Biblioteca biblioteca = new Biblioteca();
        biblioteca.adicionarLivro(livro1);
        biblioteca.adicionarLivro(livro2);
        biblioteca.listarLivros();
        biblioteca.emprestarLivro(livro1, cliente1);
        biblioteca.listarLivros();
    }
}
