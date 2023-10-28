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

// Lista todos os clientes
void listClients() {
    for (int i = 0; i < num_clients; i++) {
        printf("%d. %s\n", i + 1, clients[i].name);
    }
}

// Realiza um débito na conta de um cliente
void debit () {
    char cpf[12];
    char password[50];
    double amount;
    printf("CPF: ");
    scanf("%s", cpf);
    int index = findClientByCPF(cpf);
    if (index != -1) {
        printf("Senha: ");
        scanf("%s", password);
        if (strcmp(clients[index].password, password) == 0) {
            printf("Valor a ser debitado: R$ ");
            scanf("%lf", &amount);
            if (clients[index].account_type == 'C') {
                amount *= 1.05;
                if (amount > clients[index].balance + 1000.0) {
                    printf("Saldo insuficiente.\n");
                    return;
                }
            } else if (clients[index].account_type == 'P') {
                amount *= 1.03;
                if (amount > clients[index].balance + 5000.0) {
                    printf("Saldo insuficiente.\n");
                    return;
                }
            }
            clients[index].balance -= amount;
            if (clients[index].num_transactions < MAX_TRANSACTIONS) {
                clients[index].transactions[clients[index].num_transactions] = -amount;
                clients[index].num_transactions++;
            }
            saveClientsToFile();
            printf("Debito realizado com sucesso. Novo saldo: R$ %.2f\n", clients[index].balance);
        } else {
            printf("Senha incorreta.\n");
        }
    } else {
        printf("Cliente nao encontrado.\n");
    }
}


// Realiza um depósito na conta de um cliente
void deposit(char cpf[12]) {

    double amount;
    printf("CPF: ");
    scanf("%s", cpf);
    int index = findClientByCPF(cpf);
    if (index != -1) {
        printf("Valor a ser depositado: R$ ");
        scanf("%lf", &amount);
        clients[index].balance += amount;
        if (clients[index].num_transactions < MAX_TRANSACTIONS) {
            clients[index].transactions[clients[index].num_transactions] = amount;
            clients[index].num_transactions++;
        }
        saveClientsToFile();
        printf("Deposito realizado com sucesso. Novo saldo: R$ %.2f\n", clients[index].balance);
    } else {
        printf("Cliente nao encontrado.\n");
    }
}


// Gera um extrato para um cliente
void generateStatement() {
    char cpf[12];
    char password[50];
    printf("CPF: ");
    scanf("%s", cpf);
    int index = findClientByCPF(cpf);
    if (index != -1) {
        printf("Senha: ");
        scanf("%s", password);
        if (strcmp(clients[index].password, password) == 0) {
            char filename[100];
            sprintf(filename, "extrato_%s.txt", cpf);
            FILE *file = fopen(filename, "w");
            if (file) {
                fprintf(file, "Extrato do Cliente: %s\n", clients[index].name);
                fprintf(file, "CPF: %s\n", clients[index].cpf);
                fprintf(file, "Saldo Inicial: R$ %.2f\n", clients[index].balance);
                fprintf(file, "--------------------------------\n");
                for (int i = 0; i < clients[index].num_transactions; i++) {
                    fprintf(file, "Transacao %d: R$ %.2f\n", i + 1, clients[index].transactions[i]);
                }
                fclose(file);
                printf("Extrato gerado com sucesso. Nome do arquivo: %s\n", filename);
            } else {
                printf("Erro ao gerar o extrato.\n");
            }
        } else {
            printf("Senha incorreta.\n");
        }
    } else {
        printf("Cliente não encontrado.\n");
    }
}

// Realiza uma transferência de dinheiro entre contas
void transfer() {
    char cpf_source[12];
    char password_source[50];
    char cpf_dest[12];
    double amount;
    printf("CPF da Conta de Origem: ");
    scanf("%s", cpf_source);
    int index_source = findClientByCPF(cpf_source);
    if (index_source != -1) {
        printf("Senha da Conta de Origem: ");
        scanf("%s", password_source);
        if (strcmp(clients[index_source].password, password_source) == 0) {
            printf("CPF da Conta de Destino: ");
            scanf("%s", cpf_dest);
            int index_dest = findClientByCPF(cpf_dest);
            if (index_dest != -1) {
                if (index_source == index_dest) {
                    printf("Voce nao pode transferir para a mesma conta.\n");
                } else {
                    printf("Valor a ser transferido: R$ ");
                    scanf("%lf", &amount);
                    if (amount > clients[index_source].balance) {
                        printf("Saldo insuficiente.\n");
                    } else {
                        clients[index_source].balance -= amount;
                        if (clients[index_source].num_transactions < MAX_TRANSACTIONS) {
                            clients[index_source].transactions[clients[index_source].num_transactions] = -amount;
                            clients[index_source].num_transactions++;
                        }
                        clients[index_dest].balance += amount;
                        if (clients[index_dest].num_transactions < MAX_TRANSACTIONS) {
                            clients[index_dest].transactions[clients[index_dest].num_transactions] = amount;
                            clients[index_dest].num_transactions++;
                        }
                        saveClientsToFile();
                        printf("Transferencia realizada com sucesso.\n");
                    }
                }
            } else {
                printf("Conta de Destino nao encontrada.\n");
            }
        } else {
            printf("Senha da Conta de Origem incorreta.\n");
        }
    } else {
        printf("Conta de Origem não encontrada.\n");
    }
}
