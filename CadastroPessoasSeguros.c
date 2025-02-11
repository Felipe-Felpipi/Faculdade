#include <stdio.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char rua[30], bairro[20];
    int numero;
    char complemento[15];
    int numeroComplemento;
} Endereco;

typedef struct {
    char nome[50], cargo[12];
    float salario;
    Endereco endereco;
    int tipoSeguro;
    union {
        struct {
        } residencial;
        struct {
        } vida;
        struct {
            char marca[30], modelo[30];
            int ano;
        } automovel;
    } seguro;
} Pessoa;

void solicitarDados(int i, Pessoa *pessoa1) {
    printf("----Registro de informações da Pessoa %d----\n", i + 1);
    printf("Nome: ");
    scanf(" %[^\n]", pessoa1[i].nome);
    fflush(stdin);

    printf("Cargo: ");
    scanf(" %[^\n]", pessoa1[i].cargo);
    fflush(stdin);

    do {
        printf("Salário: ");
        scanf("%f", &pessoa1[i].salario);
        fflush(stdin);
        if (pessoa1[i].salario < 0) {
            printf("Salário inválido. Por favor, insira um valor positivo.\n");
        }
    } while (pessoa1[i].salario < 0);

    printf("\n\n----Endereço----\n");
    printf("Bairro: ");
    scanf(" %[^\n]", pessoa1[i].endereco.bairro);
    fflush(stdin);

    printf("Rua: ");
    scanf(" %[^\n]", pessoa1[i].endereco.rua);
    fflush(stdin);

    printf("Número: ");
    scanf("%d", &pessoa1[i].endereco.numero);
    fflush(stdin);

    printf("Tipo de complemento: ");
    scanf(" %[^\n]", pessoa1[i].endereco.complemento);
    fflush(stdin);

    printf("Número do complemento: ");
    scanf("%d", &pessoa1[i].endereco.numeroComplemento);
    fflush(stdin);

    do {
        printf("Tipo de seguro (1 - Residencial, 2 - Vida, 3 - Automóvel): ");
        scanf("%d", &pessoa1[i].tipoSeguro);
        fflush(stdin);
        if (pessoa1[i].tipoSeguro < 1 || pessoa1[i].tipoSeguro > 3) {
            printf("Tipo de seguro inválido. Por favor, insira um valor entre 1 e 3.\n");
        }
    } while (pessoa1[i].tipoSeguro < 1 || pessoa1[i].tipoSeguro > 3);

    if (pessoa1[i].tipoSeguro == 3) {
        printf("Marca do automóvel: ");
        scanf(" %[^\n]", pessoa1[i].seguro.automovel.marca);
        fflush(stdin);

        printf("Modelo do automóvel: ");
        scanf(" %[^\n]", pessoa1[i].seguro.automovel.modelo);
        fflush(stdin);

        do {
            printf("Ano do automóvel: ");
            scanf("%d", &pessoa1[i].seguro.automovel.ano);
            fflush(stdin);
            if (pessoa1[i].seguro.automovel.ano < 1900 || pessoa1[i].seguro.automovel.ano > 2023) {
                printf("Ano inválido. Por favor, insira um ano entre 1900 e 2023.\n");
            }
        } while (pessoa1[i].seguro.automovel.ano < 1900 || pessoa1[i].seguro.automovel.ano > 2023);
    }
}

void mostrarDados(int i, Pessoa *pessoa1) {
    printf("----Mostrando dados da Pessoa %d----\n", i + 1);
    printf("Nome: %s\n", pessoa1[i].nome);
    printf("Cargo: %s\n", pessoa1[i].cargo);
    printf("Salário: R$%.2f\n", pessoa1[i].salario);
    printf("\nEndereço\n");
    printf("Bairro: %s\n", pessoa1[i].endereco.bairro);
    printf("Rua: %s\n", pessoa1[i].endereco.rua);
    printf("Número: %d\n", pessoa1[i].endereco.numero);
    printf("Complemento: %s\n", pessoa1[i].endereco.complemento);
    printf("Número do complemento: %d\n", pessoa1[i].endereco.numeroComplemento);

    switch (pessoa1[i].tipoSeguro) {
        case 1:
            printf("Tipo de seguro: Residencial\n");
            break;
        case 2:
            printf("Tipo de seguro: Vida\n");
            break;
        case 3:
            printf("Marca do automóvel: %s\n", pessoa1[i].seguro.automovel.marca);
            printf("Modelo do automóvel: %s\n", pessoa1[i].seguro.automovel.modelo);
            printf("Ano do automóvel: %d\n", pessoa1[i].seguro.automovel.ano);
            break;
        default:
            printf("Tipo de seguro inválido.\n");
            break;
    }
}

int main(void) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int i;
    Pessoa pessoa1[3];

    for (i = 0; i < 3; i++) {
        solicitarDados(i, pessoa1);
    }

    for (i = 0; i < 3; i++) {
        mostrarDados(i, pessoa1);
        printf("\n\n\n");
    }

    return 0;
}
