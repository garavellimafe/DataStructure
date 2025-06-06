
# Sistema de Cadastro e Relatos de Desastres Naturais

## Integrantes do Grupo:
- Maria Fernanda Garavelli Dantas  RM:562686
- Rogério Deligi Ferreira Filho    RM:561942

## Matéria: Data Structures and Algorithms
## Curso: Ciência da Computação - 1º Ano
## Turma: 1CCPF

## Objetivo:
Desenvolver uma aplicação em C com uma interface de programação que permita aos usuários registrar e consultar relatos sobre desastres naturais ocorridos num raio de até 10 km. O sistema deve:
- Coletar informações completas e organizadas da pessoa que está fazendo o relato (como nome, contato, localização, etc.).
- Permitir a consulta eficiente dos relatos cadastrados.
- Armazenar os dados em um arquivo de texto, garantindo a persistência das informações mesmo após o encerramento do programa.

## Funcionalidades:
Armazena os dados da pessoa que registrou o relato:
- Nome
- Contato (telefone ou e-mail)
- Documento (CPF ou RG)

Representa a posição geográfica do relato:
- Latitude
- Longitude

Agrupa todas as informações de um relato:
- Dados da Pessoa
- Tipo de catástrofe (ex: enchente, deslizamento)
- Descrição do ocorrido
- Localização
- Data do evento

Utiliza a fórmula de Haversine para calcular a distância entre dois pontos geográficos (em km), com base em latitude e longitude. Isso permite verificar se um relato está dentro do raio de 10 km.

### Salvar um relato:
- Abre (ou cria) o arquivo relatos.txt no modo de acréscimo (ios::app).
- Escreve os dados do relato em uma linha, separados por ;.
- Garante a persistência dos dados mesmo após o encerramento do programa.

### Criar um relato:
- Interage com o usuário para coletar todos os dados necessários para um novo relato.
- Retorna um objeto Relato preenchido.

### Consultar Relato:
- Recebe uma localização de referência (latitude e longitude).
- Lê todos os relatos do arquivo relatos.txt.
- Para cada relato, calcula a distância até o ponto de referência.
- Exibe apenas os relatos que estão dentro do raio de 10 km.
- Mostra os dados completos de cada relato encontrado.

### Menu:
- Exibe um menu interativo com as opções:
  - Cadastrar novo relato
  - Consultar relatos por localização
  - Sair
- Controla o fluxo do programa com base na escolha do usuário.
- Apenas chama a função menu() para iniciar o programa.

### Persistência nos dados:
- Todos os relatos são salvos em um arquivo de texto (relatos.txt).
- Isso permite que os dados sejam recuperados em execuções futuras do programa.

### Validação de Entrada:
- Validações básicas de entrada para garantir que os dados sejam inseridos corretamente.

## Estrutura do Código:

### Bibliotecas:
- #include <stdio.h>
- #include <stdlib.h>
- #include <string.h>
- #include <math.h>

Essas bibliotecas fornecem funcionalidades essenciais:
- #include <stdio.h> – entrada e saída padrão
- #include <stdlib.h> – alocação de memória, controle de processos
- #include <string.h> – manipulação de strings
- #include <math.h> – funções matemáticas como sin, cos, sqrt

### Constante:
- const double RAIO_MAXIMO = 10.0;

### Estruturas:
- struct Pessoa { ... };
- struct Localizacao { ... };
- struct Relato { ... };

### Função de calcular distância:
- double calcularDistancia(double lat1, double lon1, double lat2, double lon2) { ... }

### Função de salvar relato:
- void salvarRelato(const Relato& relato) { ... }

### Função criar relato:
- Relato criarRelato() { ... }

### Função consultar relato:
- void consultarRelatos(double latRef, double lonRef) { ... }

### Função menu:
- void menu() { ... }

### Função main:
- int main() {
    menu();
    return 0;
}

## Exemplo do ficheiro:
Nome: Maria Silva
Contato: maria.silva@email.com
Documento: 12345678900
Tipo de Catástrofe: Enchente
Descrição: Rua completamente alagada após fortes chuvas
Latitude: -23.5505
Longitude: -46.6333
Data: 05/06/2025

## Exemplo do código:
menu: 
=== Sistema de Relatos de Catástrofes Naturais ===
1. Cadastrar novo relato
2. Consultar relatos por localização
0. Sair
Escolha uma opção:
