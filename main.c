#include <stdio.h>
#include "laboratorio.h"

int main() {
    loadClientsFromFile();
    int option;
    while (1) {
        printf("\nMenu de Opções:\n");
        printf("1. Novo cliente\n");
        printf("2. Apaga cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Debito\n");
        printf("5. Deposito\n");
        printf("6. Extrato\n");
        printf("7. Transferência Entre Contas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                createClient();
                break;
            case 2:
                deleteClient();
                break;
            case 3:
                listClients();
                break;
            case 4:
                debit();
                break;
            case 5:
                deposit();
                break;
            case 6:
                generateStatement();
                break;
            case 7:
                transfer();
                break;
            case 0:
                saveClientsToFile();
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}