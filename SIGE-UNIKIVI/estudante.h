#ifndef ESTUDANTE_H
#define ESTUDANTE_H

#define MAX_ESTUDANTES 200

// Estrutura principal de dados do estudante
typedef struct {
    int matricula;
    char nome[100];
    float nota;
} Estudante;

// Funções de Persistência de Dados (I/O)
int lerFicheiroTexto(const char *nomeFicheiro, Estudante estudantes[], int *total);
int gravarFicheiroTexto(const char *nomeFicheiro, Estudante estudantes[], int total);
int gravarFicheiroBinario(const char *nomeFicheiro, Estudante estudantes[], int total);

// Funções de Ordenação Clássica
void bubbleSort(Estudante estudantes[], int total, int criterio);
void selectionSort(Estudante estudantes[], int total, int criterio);
void insertionSort(Estudante estudantes[], int total, int criterio);

// Funções de Pesquisa Estruturada
int pesquisaLinearMatricula(Estudante estudantes[], int total, int matricula);
int pesquisaBinariaMatricula(Estudante estudantes[], int total, int matricula);
int pesquisaLinearNome(Estudante estudantes[], int total, const char *nome);

// Funções de Gestão Dinâmica
int matriculaExiste(Estudante estudantes[], int total, int matricula);
int cadastrarEstudante(Estudante estudantes[], int *total);
int actualizarEstudante(Estudante estudantes[], int total);
int eliminarEstudante(Estudante estudantes[], int *total);

// Função de Relatório Estatístico Avançado
void gerarRelatorioEstatistico(Estudante estudantes[], int total);

// Utilitários de Interface e Validação
void limparBuffer();
void exibirEstudante(Estudante e);
void exibirLista(Estudante estudantes[], int total);

#endif // ESTUDANTE_H_INCLUDED
