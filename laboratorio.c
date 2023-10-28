#include <stdio.h>
#include <string.h>
#include "laboratorio.h" // Suponha que o arquivo "laboratorio.h" contenha a definição das estruturas e constantes usadas

Client clients[MAX_CLIENTS]; // Uma matriz que armazena informações dos clientes
int num_clients = 0; // Número atual de clientes

// Salva os clientes em um arquivo
void saveClientsToFile() {
    FILE *file = fopen("clients.dat", "wb");
    if (file) {
        fwrite(clients, sizeof(Client), num_clients, file);
        fclose(file);
    }
}

// Carrega os clientes de um arquivo
void loadClientsFromFile() {
    FILE *file = fopen("clients.dat", "rb");
    if (file) {
        num_clients = fread(clients, sizeof(Client), MAX_CLIENTS, file);
        fclose(file);
    }
}

// Encontra um cliente pelo CPF e retorna o índice na matriz de clientes
int findClientByCPF(const char *cpf) {
    for (int i = 0; i < num_clients; i++) {
        if (strcmp(clients[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1;
}

// Cria um novo cliente
void createClient(char cpf[12]) {
    if (num_clients < MAX_CLIENTS) {
        Client newClient;
        // Coleta informações do cliente
        printf("Nome: ");
        scanf(" %[^\n]s", newClient.name);
        printf("CPF: ");
        scanf("%s", newClient.cpf);
        printf("Tipo de Conta (C para Comum, P para Plus): ");
        scanf(" %c", &newClient.account_type);
        printf("Valor Inicial da Conta: ");
        scanf("%lf", &newClient.balance);
        printf("Senha: ");
        scanf("%s", newClient.password);
        newClient.num_transactions = 0;
        // Adiciona o cliente à matriz
        clients[num_clients] = newClient;
        num_clients++;
        saveClientsToFile(); // Salva os dados no arquivo
        printf("Cliente criado com sucesso.\n");
    } else {
        printf("Limite de clientes atingido.\n");
    }
}


// Deleta um cliente com base no CPF
void deleteClient(char cpf[12]) {

    printf("Digite o CPF do cliente que deseja apagar: ");
    scanf("%s", cpf);
    int index = findClientByCPF(cpf);
    if (index != -1) {
        for (int i = index; i < num_clients - 1; i++) {
            clients[i] = clients[i + 1];
        }
        num_clients--;
        saveClientsToFile(); // Atualiza o arquivo
        printf("Cliente apagado com sucesso.\n");
    } else {
        printf("Cliente não encontrado.\n");
    }
}
