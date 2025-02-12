public class Catioro {
    private String nome;
    private String raca;

    public Catioro(String nome, String raca) {
        this.nome = nome;
        this.raca = raca;
    }

    public String getNome() {
        return nome;
    }

    public String getRaca() {
        return raca;
    }

    public void info() {
        System.out.println("O cachorro se chama: " + getNome() + ". Ele é da raça: " + getRaca());
    }

    public void latir() {
        System.out.println(getNome() + " está latindo!");
    }

    public void comer() {
        System.out.println(getNome() + " está comendo.");
    }

    public static void main(String[] args) {
        Catioro catioro = new Catioro("Rex", "Labrador");
        catioro.info();
        catioro.latir();
        catioro.comer();
    }
}
