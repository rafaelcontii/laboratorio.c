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