//bibliotecas e definições
#include <stdio.h>  // Biblioteca padrão para entrada e saída
#include <stdlib.h> // Biblioteca padrão para alocação de memória, controle de processos, etc.
#include <string.h> // Biblioteca padrão para manipulação de strings

#define MAX_CONTATOS 30   // Número máximo de contatos na agenda
#define TAM_NOME 40       // Tamanho máximo do nome do contato
#define TAM_TELEFONE 12   // Tamanho máximo do telefone do contato

//estrutura e variáveis
typedef struct {
    char nome[TAM_NOME];
    char telefone[TAM_TELEFONE];
} Contato;  // Definindo a estrutura Contato com campos 'nome' e 'telefone'

Contato agenda[MAX_CONTATOS]; // Array para armazenar os contatos
int total_contatos = 0;       // Contador para o total de contatos na agenda

//verifica se tem apenas digitos
int apenas_digitos(const char *num) {
    while (*num) {
        if (*num < '0' || *num > '9') {
            return 0; // Retorna 0 se encontrar um caractere que não é um dígito
        }
        num++;
    }
    return 1; // Retorna 1 se todos os caracteres forem dígitos
}

//adicionar contatos
void adicionar_contato() {
    if (total_contatos >= MAX_CONTATOS) {
        printf("Agenda cheia!\n");
        return;
    }

    Contato novo_contato;
    printf("Digite o nome: ");
    fgets(novo_contato.nome, TAM_NOME, stdin); // Lê o nome do contato
    novo_contato.nome[strcspn(novo_contato.nome, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Digite o telefone: ");
    fgets(novo_contato.telefone, TAM_TELEFONE, stdin); // Lê o telefone do contato
    novo_contato.telefone[strcspn(novo_contato.telefone, "\n")] = '\0'; // Remove o caractere de nova linha

    if (!apenas_digitos(novo_contato.telefone)) {
        printf("Numero de telefone deve conter apenas numeros.\n");
        return;
    }

    agenda[total_contatos++] = novo_contato; // Adiciona o novo contato na agenda e incrementa o contador

    printf("Contato adicionado com sucesso!\n");
}

//consultar contato
void consultar_contato() {
    char nome[TAM_NOME];
    printf("Digite o nome do contato a ser consultado: ");
    fgets(nome, TAM_NOME, stdin); // Lê o nome do contato a ser consultado
    nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha

    for (int i = 0; i < total_contatos; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) { // Compara o nome lido com os nomes na agenda
            printf("Nome: %s\n", agenda[i].nome);
            printf("Telefone: %s\n", agenda[i].telefone);
            return;
        }
    }

    printf("Contato nao encontrado.\n");
}

//remover contato
void remover_contato() {
    char nome[TAM_NOME];
    printf("Digite o nome do contato a ser removido: ");
    fgets(nome, TAM_NOME, stdin); // Lê o nome do contato a ser removido
    nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha

    for (int i = 0; i < total_contatos; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) { // Compara o nome lido com os nomes na agenda
            for (int j = i; j < total_contatos - 1; j++) {
                agenda[j] = agenda[j + 1]; // Desloca os contatos para preencher o espaço removido
            }
            total_contatos--; // Decrementa o contador de contatos
            printf("Contato removido com sucesso!\n");
            return;
        }
    }

    printf("Contato nao encontrado.\n");
}

//salvar contato
void salvar_contatos() {
    FILE *file = fopen("agenda.dat", "wb"); // Abre o arquivo para escrita binária
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fwrite(&total_contatos, sizeof(int), 1, file); // Escreve o número total de contatos no arquivo
    fwrite(agenda, sizeof(Contato), total_contatos, file); // Escreve os contatos no arquivo
    fclose(file); // Fecha o arquivo

    printf("Contatos salvos com sucesso!\n");
}

//menu 
void menu() {
    int opcao;
    do {
        printf("\nEscolha uma opcao:\n");
        printf("1. Adicionar contato\n");
        printf("2. Consultar contatos\n");
        printf("3. Remover contato\n");
        printf("4. Salvar contatos\n");
        printf("0. Sair\n");
        scanf("%d", &opcao); // Lê a opção escolhida pelo usuário
        getchar(); // Limpa o buffer do teclado

        switch(opcao) {
            case 1:
                adicionar_contato(); // Chama a função para adicionar um contato
                break;
            case 2:
                consultar_contato(); // Chama a função para consultar um contato
                break;
            case 3:
                remover_contato(); // Chama a função para remover um contato
                break;
            case 4:
                salvar_contatos(); // Chama a função para salvar os contatos
                break;
            case 0:
                printf("Saindo...\n"); // Sai do programa
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n"); // Informa que a opção é inválida
        }
    } while(opcao != 0); // Continua exibindo o menu enquanto a opção não for 0
}

//principal 
int main() {
    menu(); // Chama a função do menu para iniciar a interação com o usuário
    salvar_contatos(); // Salva os contatos ao sair do programa
    return 0; // Retorna 0 indicando que o programa terminou com sucesso
}


