#ifndef LABORATORIO_H
#define LABORATORIO_H

#define MAX_CLIENTS 1000
#define MAX_TRANSACTIONS 100

typedef struct {
    char name[100];
    char cpf[12];
    char account_type;
    double balance;
    char password[50];
    double transactions[MAX_TRANSACTIONS];
    int num_transactions;
} Client;

void saveClientsToFile();
void loadClientsFromFile();
int findClientByCPF(const char *cpf);
void createClient();
void deleteClient();
void listClients();
void debit();
void deposit();
void generateStatement();
void transfer();

#endif