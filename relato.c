#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EARTH_RADIUS 6371.0

typedef struct {
    char nome[50];
    char contato[50];
    char documento[20];
} Pessoa;

typedef struct {
    double latitude;
    double longitude;
} Localizacao;

typedef struct {
    Pessoa pessoa;
    char tipoCatastrofe[50];
    char descricao[200];
    Localizacao localizacao;
    char data[20];
} Relato;

#define PI 3.141592653589793

double toRadians(double degree) {
    return degree * (PI / 180.0);
}


double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);
    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1) * cos(lat2) *
               sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_RADIUS * c;
}

void salvarRelato(Relato relato) {
    FILE *file = fopen("relatos.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fprintf(file, "%s;%s;%s;%s;%s;%lf;%lf;%s\n",
            relato.pessoa.nome, relato.pessoa.contato, relato.pessoa.documento,
            relato.tipoCatastrofe, relato.descricao,
            relato.localizacao.latitude, relato.localizacao.longitude,
            relato.data);
    fclose(file);
}

Relato criarRelato() {
    Relato relato;
    printf("Nome: ");
    fgets(relato.pessoa.nome, 50, stdin);
    relato.pessoa.nome[strcspn(relato.pessoa.nome, "\n")] = 0;

    printf("Contato: ");
    fgets(relato.pessoa.contato, 50, stdin);
    relato.pessoa.contato[strcspn(relato.pessoa.contato, "\n")] = 0;

    printf("Documento (CPF ou RG): ");
    fgets(relato.pessoa.documento, 20, stdin);
    relato.pessoa.documento[strcspn(relato.pessoa.documento, "\n")] = 0;

    printf("Tipo de catástrofe: ");
    fgets(relato.tipoCatastrofe, 50, stdin);
    relato.tipoCatastrofe[strcspn(relato.tipoCatastrofe, "\n")] = 0;

    printf("Descrição do ocorrido: ");
    fgets(relato.descricao, 200, stdin);
    relato.descricao[strcspn(relato.descricao, "\n")] = 0;

    printf("Latitude: ");
    scanf("%lf", &relato.localizacao.latitude);

    printf("Longitude: ");
    scanf("%lf", &relato.localizacao.longitude);

    printf("Data do evento (dd/mm/aaaa): ");
    scanf("%s", relato.data);

    getchar(); // Limpar o buffer do teclado

    return relato;
}

void consultarRelatos(double refLat, double refLon) {
    FILE *file = fopen("relatos.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Relato relato;
    while (fscanf(file, "%49[^;];%49[^;];%19[^;];%49[^;];%199[^;];%lf;%lf;%19[^\n]\n",
                  relato.pessoa.nome, relato.pessoa.contato, relato.pessoa.documento,
                  relato.tipoCatastrofe, relato.descricao,
                  &relato.localizacao.latitude, &relato.localizacao.longitude,
                  relato.data) != EOF) {
        double distancia = haversine(refLat, refLon, relato.localizacao.latitude, relato.localizacao.longitude);
        if (distancia <= 10.0) {
            printf("Nome: %s\n", relato.pessoa.nome);
            printf("Contato: %s\n", relato.pessoa.contato);
            printf("Documento: %s\n", relato.pessoa.documento);
            printf("Tipo de catástrofe: %s\n", relato.tipoCatastrofe);
            printf("Descrição: %s\n", relato.descricao);
            printf("Localização: (%.6lf, %.6lf)\n", relato.localizacao.latitude, relato.localizacao.longitude);
            printf("Data: %s\n", relato.data);
            printf("Distância: %.2lf km\n\n", distancia);
        }
    }
    fclose(file);
}

void menu() {
    int opcao;
    do {
        printf("Menu:\n");
        printf("1. Cadastrar novo relato\n");
        printf("2. Consultar relatos por localização\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
            case 1: {
                Relato relato = criarRelato();
                salvarRelato(relato);
                break;
            }
            case 2: {
                double refLat, refLon;
                printf("Latitude de referência: ");
                scanf("%lf", &refLat);
                printf("Longitude de referência: ");
                scanf("%lf", &refLon);
                consultarRelatos(refLat, refLon);
                break;
            }
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 3);
}

int Main() {
    menu();
    return 0;
}

