#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudante.h"

// Limpa de forma segura o buffer de entrada do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Procura por duplicados de matrícula na memória do sistema
int matriculaExiste(Estudante estudantes[], int total, int matricula) {
    for (int i = 0; i < total; i++) {
        if (estudantes[i].matricula == matricula) {
            return i;
        }
    }
    return -1;
}

// Controla o comportamento dos critérios de ordenação
int precisaTrocar(Estudante a, Estudante b, int criterio) {
    switch(criterio) {
        case 1: return a.matricula > b.matricula;      // Matrícula Crescente
        case 2: return strcmp(a.nome, b.nome) > 0;     // Nome Alfabético
        case 3: return a.nota < b.nota;                // Nota Decrescente
        default: return 0;
    }
}

// SOLUÇÃO DO BUG: Leitura robusta linha por linha com fgets e sscanf
int lerFicheiroTexto(const char *nomeFicheiro, Estudante estudantes[], int *total) {
    FILE *f = fopen(nomeFicheiro, "r");
    if (f == NULL) return 0;

    int i = 0;
    char linha[256];

    // Lê o ficheiro linha por linha com segurança
    while (i < MAX_ESTUDANTES && fgets(linha, sizeof(linha), f) != NULL) {
        // Remove quebras de linha residuais (\n ou \r do Windows)
        linha[strcspn(linha, "\r\n")] = 0;

        // Ignora linhas completamente vazias no ficheiro
        if (strlen(linha) == 0) continue;

        // O espaço antes e depois de ';' garante tolerância a espaços extras no ficheiro txt
        if (sscanf(linha, "%d ; %[^;]; %f", &estudantes[i].matricula, estudantes[i].nome, &estudantes[i].nota) == 3) {

            // Remove espaços em branco que possam ter ficado no final do nome
            int len = strlen(estudantes[i].nome);
            while (len > 0 && estudantes[i].nome[len - 1] == ' ') {
                estudantes[i].nome[len - 1] = '\0';
                len--;
            }
            i++;
        }
    }
    *total = i;
    fclose(f);
    return 1;
}

// Gravação em Texto
int gravarFicheiroTexto(const char *nomeFicheiro, Estudante estudantes[], int total) {
    FILE *f = fopen(nomeFicheiro, "w");
    if (f == NULL) return 0;

    for (int i = 0; i < total; i++) {
        fprintf(f, "%d;%s;%.2f\n", estudantes[i].matricula, estudantes[i].nome, estudantes[i].nota);
    }
    fclose(f);
    return 1;
}

// Gravação em Binário
int gravarFicheiroBinario(const char *nomeFicheiro, Estudante estudantes[], int total) {
    FILE *f = fopen(nomeFicheiro, "wb");
    if (f == NULL) return 0;

    size_t gravados = fwrite(estudantes, sizeof(Estudante), total, f);
    fclose(f);
    return (int)gravados == total;
}

// Algoritmos de Ordenação
void bubbleSort(Estudante estudantes[], int total, int criterio) {
    Estudante temp;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (precisaTrocar(estudantes[j], estudantes[j+1], criterio)) {
                temp = estudantes[j];
                estudantes[j] = estudantes[j+1];
                estudantes[j+1] = temp;
            }
        }
    }
}

void selectionSort(Estudante estudantes[], int total, int criterio) {
    int idx_alvo;
    Estudante temp;
    for (int i = 0; i < total - 1; i++) {
        idx_alvo = i;
        for (int j = i + 1; j < total; j++) {
            if (precisaTrocar(estudantes[idx_alvo], estudantes[j], criterio)) {
                idx_alvo = j;
            }
        }
        if (idx_alvo != i) {
            temp = estudantes[i];
            estudantes[i] = estudantes[idx_alvo];
            estudantes[idx_alvo] = temp;
        }
    }
}

void insertionSort(Estudante estudantes[], int total, int criterio) {
    Estudante chave;
    int j;
    for (int i = 1; i < total; i++) {
        chave = estudantes[i];
        j = i - 1;
        while (j >= 0 && precisaTrocar(estudantes[j], chave, criterio)) {
            estudantes[j + 1] = estudantes[j];
            j = j - 1;
        }
        estudantes[j + 1] = chave;
    }
}

// Algoritmos de Pesquisa
int pesquisaLinearMatricula(Estudante estudantes[], int total, int matricula) {
    for (int i = 0; i < total; i++) {
        if (estudantes[i].matricula == matricula) return i;
    }
    return -1;
}

int pesquisaBinariaMatricula(Estudante estudantes[], int total, int matricula) {
    int inicio = 0, fim = total - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        if (estudantes[meio].matricula == matricula) return meio;
        if (estudantes[meio].matricula < matricula) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int pesquisaLinearNome(Estudante estudantes[], int total, const char *nome) {
    int encontrados = 0;

    for (int i = 0; i < total; i++) {
        // strstr verifica se o termo pesquisado está contido no nome do estudante
        if (strstr(estudantes[i].nome, nome) != NULL) {

            // Se for o primeiro que encontrou, desenha o cabeçalho da tabela
            if (encontrados == 0) {
                printf(" _________________________________________________________________________________________________________________\n");
                printf("| MATRÍCULA        | NOME COMPLETO                                                     | NOTA FINAL               |\n");
                printf("|__________________|___________________________________________________________________|__________________________|\n");
            }

            // Exibe o estudante atual que coincide com a pesquisa
            exibirEstudante(estudantes[i]);
            encontrados++;
        }
    }

    // Se encontrou pelo menos um, fecha a moldura da tabela
    if (encontrados > 0) {
        printf("|__________________|___________________________________________________________________|__________________________|\n");
    }

    // Retorna a quantidade total de alunos encontrados com esse nome
    return encontrados;
}

// Cadastrar Estudante
int cadastrarEstudante(Estudante estudantes[], int *total) {
    if (*total >= MAX_ESTUDANTES) {
        printf("\n  [!] Erro: Capacidade máxima do sistema atingida.\n");
        return 0;
    }

    int mat;
    float nota;
    char nome[100];

    while (1) {
        printf("  Introduza o Número de Matrícula: ");
        if (scanf("%d", &mat) != 1) {
            printf("  [!] Dígitos inválidos. Tente novamente.\n");
            limparBuffer();
            continue;
        }
        if (matriculaExiste(estudantes, *total, mat) != -1) {
            printf("  [!] Erro: Esta matrícula já está registada no sistema!\n");
            continue;
        }
        break;
    }

    limparBuffer();
    printf("  Introduza o Nome Completo do estudante: ");
    scanf(" %[^\n]", nome);

    while (1) {
        printf("  Introduza a Nota (0.00 a 20.00): ");
        if (scanf("%f", &nota) != 1) {
            printf("  [!] Valor inválido. Insira um número real.\n");
            limparBuffer();
            continue;
        }
        if (nota < 0.00 || nota > 20.00) {
            printf("  [!] Nota fora do intervalo permitido! Insira um valor entre 0 e 20.\n");
            continue;
        }
        break;
    }

    estudantes[*total].matricula = mat;
    strcpy(estudantes[*total].nome, nome);
    estudantes[*total].nota = nota;
    (*total)++;

    printf("\n  [+] Estudante cadastrado com sucesso em memória!\n");
    return 1;
}

// Actualizar Estudante
int actualizarEstudante(Estudante estudantes[], int total) {
    int mat;
    printf("  Introduza a Matrícula do estudante que deseja actualizar: ");
    if (scanf("%d", &mat) != 1) {
        printf("  [!] Entrada inválida.\n");
        limparBuffer();
        return 0;
    }

    int pos = matriculaExiste(estudantes, total, mat);
    if (pos == -1) {
        printf("\n  [-] Erro: Estudante com matrícula %d não foi localizado.\n", mat);
        return 0;
    }

    printf("\n  [Dados Actuais] Nome: %s | Nota: %.2f\n", estudantes[pos].nome, estudantes[pos].nota);
    printf("  -----------------------------------------------------------------\n");

    limparBuffer();
    printf("  Introduza o Novo Nome Completo: ");
    scanf(" %[^\n]", estudantes[pos].nome);

    while (1) {
        printf("  Introduza a Nova Nota (0.00 a 20.00): ");
        if (scanf("%f", &estudantes[pos].nota) != 1) {
            printf("  [!] Valor inválido.\n");
            limparBuffer();
            continue;
        }
        if (estudantes[pos].nota < 0.00 || estudantes[pos].nota > 20.00) {
            printf("  [!] Nota inválida! Deve estar entre 0 e 20.\n");
            continue;
        }
        break;
    }
    printf("\n  [+] Dados do estudante actualizados com sucesso em memória!\n");
    return 1;
}

// Função para eliminar estudante com confirmação de segurança
int eliminarEstudante(Estudante estudantes[], int *total) {
    if (*total == 0) {
        printf("\n  [!] Erro: Não existem estudantes carregados em memória para eliminar.\n");
        return 0;
    }

    int mat;
    printf("  Introduza a Matrícula do estudante que deseja eliminar: ");
    if (scanf("%d", &mat) != 1) {
        printf("  [!] Entrada inválida.\n");
        limparBuffer();
        return 0;
    }

    // Verifica se o estudante existe no sistema
    int pos = matriculaExiste(estudantes, *total, mat);
    if (pos == -1) {
        printf("\n  [-] Erro: Estudante com matrícula %d não foi localizado.\n", mat);
        return 0;
    }

    // Exibe os dados do alvo antes de confirmar
    printf("\n  [Registo Localizado] Nome: %s | Nota: %.2f\n", estudantes[pos].nome, estudantes[pos].nota);
    printf("  -----------------------------------------------------------------\n");

    char confirmacao;
    limparBuffer(); // Limpa o buffer antes de ler o caractere
    printf("  Tem a certeza de que deseja eliminar definitivamente este estudante? (S/N): ");
    scanf("%c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's') {
        // Algoritmo de compressão (shift à esquerda): move todos os elementos seguintes uma posição para trás
        for (int i = pos; i < *total - 1; i++) {
            estudantes[i] = estudantes[i + 1];
        }

        // Diminui o contador global de estudantes na memória
        (*total)--;

        printf("\n  [+] Estudante removido com sucesso da memória do sistema!\n");
        return 1; // Retorna 1 para ativar o aviso de alterações pendentes
    } else {
        printf("\n  [-] Operação cancelada. O registo do estudante permanece intacto.\n");
        return 0; // Nenhuma alteração foi feita
    }
}

// Emissão de Relatório Estatístico
void gerarRelatorioEstatistico(Estudante estudantes[], int total) {
    if (total == 0) {
        printf("\n  [!] Sem dados para processar relatórios.\n");
        return;
    }

    float soma = 0.0, maiorNota = estudantes[0].nota, menorNota = estudantes[0].nota;
    int acimaMedia = 0, abaixoMedia = 0;

    for (int i = 0; i < total; i++) {
        soma += estudantes[i].nota;
        if (estudantes[i].nota > maiorNota) maiorNota = estudantes[i].nota;
        if (estudantes[i].nota < menorNota) menorNota = estudantes[i].nota;
    }

    float mediaTurma = soma / total;

    for (int i = 0; i < total; i++) {
        if (estudantes[i].nota >= mediaTurma) acimaMedia++;
        else abaixoMedia++;
    }

    printf(" _________________________________________________________________________________________________________________\n");
    printf("|                                            SIGE-UNIKIVI - DASHBOARD ESTATÍSTICO                                 |\n");
    printf("|_________________________________________________________________________________________________________________|\n");
    printf("|  Total de Alunos Cadastrados : %-81d|\n", total);
    printf("|  Média Geral da Turma        : %-81.2f|\n", mediaTurma);
    printf("|  Alunos com Nota >= Média    : %-81d|\n", acimaMedia);
    printf("|  Alunos com Nota < Média     : %-81d|\n", abaixoMedia);
    printf("|  Maior Nota Registada        : %-81.2f|\n", maiorNota);
    printf("|  Menor Nota Registada        : %-81.2f|\n", menorNota);
    printf("|_________________________________________________________________________________________________________________|\n");
}

// Exibição Individual (Perfeitamente alinhada com as larguras fixas da tabela)
void exibirEstudante(Estudante e) {
    printf("| %-16d | %-65s | %-24.2f |\n", e.matricula, e.nome, e.nota);
}

// Exibição da Lista Completa de Estudantes
void exibirLista(Estudante estudantes[], int total) {
    if (total == 0) {
        printf("  [!] Não existem dados carregados em memória.\n");
        return;
    }
    printf("| MATRÍCULA        | NOME COMPLETO                                                     | NOTA FINAL               |\n");
    printf("|__________________|___________________________________________________________________|__________________________|\n");
    for (int i = 0; i < total; i++) {
        exibirEstudante(estudantes[i]);
    }
    printf("|__________________|___________________________________________________________________|__________________________|\n");
    printf("  Total de estudantes em memória: %d\n", total);
}
