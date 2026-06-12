#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // Importante para carregar suporte de acentuação nativa
#include "estudante.h"

// Splash Screen oficial executada no início do programa
void exibirSplash() {
    system("cls");
    printf(" _________________________________________________________________________________________________________________\n");
    printf("|                                                                                                                 |\n");
    printf("|                                             BEM-VINDO AO SIGE-UNIKIVI                                           |\n");
    printf("|                                                    Versão 1.0                                                   |\n");
    printf("|_________________________________________________________________________________________________________________|\n");
    printf("|                                                                                                                 |\n");
    printf("|  O SIGE-UNIKIVI é um sistema completo para gestão de dados de estudantes, desenvolvido para facilitar           |\n");
    printf("|  o controle de cadastros, ordenação, pesquisas, relatórios estatísticos e persistência de dados.                |\n");
    printf("|                                                                                                                 |\n");
    printf("|  EQUIPE DE DESENVOLVIMENTO:                                                                                     |\n");
    printf("|  1. ANTÓNIO JOAQUIM BERNARDO                                                                                    |\n");
    printf("|  2. IGRAÇA NZINGA DE SOUSA KIAWETE                                                                              |\n");
    printf("|  3. JOÃO ISAÍAS TRUVÃO                                                                                          |\n");
    printf("|  4. MARIA TUSSONGUA BENEDITH                                                                                    |\n");
    printf("|  5. NELSA NZAGE JOÃO                                                                                            |\n");
    printf("|_________________________________________________________________________________________________________________|\n\n");
    system("pause");
}

// Tela de Segurança com Bloqueio por excesso de tentativas
int executarLogin() {
    char email[50];
    char senha[50];
    int tentativas = 0;
    const int MAX_TENTATIVAS = 3;

    while (tentativas < MAX_TENTATIVAS) {
        system("cls");
        printf(" _________________________________________________________________________________________________________________\n");
        printf("|                                               AUTENTICAÇÃO REQUERIDA                                            |\n");
        printf("|_________________________________________________________________________________________________________________|\n");
        printf("\n  Tentativa (%d de %d)\n", tentativas + 1, MAX_TENTATIVAS);

        printf("  Email: ");
        scanf("%s", email);
        printf("  Senha: ");
        scanf("%s", senha);

        if (strcmp(email, "admin@gmail.com") == 0 && strcmp(senha, "admin2026") == 0) {
            printf("\n  [+] Acesso autorizado com sucesso! Entrando no sistema...\n");
            system("pause");
            return 1;
        } else {
            printf("\n  [!] Erro: Email ou Senha incorrectos!\n");
            tentativas++;
            system("pause");
        }
    }

    system("cls");
    printf(" _________________________________________________________________________________________________________________\n");
    printf("|                                          !!! SISTEMA BLOQUEADO !!!                                              |\n");
    printf("|_________________________________________________________________________________________________________________|\n");
    printf("|                                                                                                                 |\n");
    printf("|  Número máximo de tentativas de login excedido de forma consecutiva.                                            |\n");
    printf("|  O acesso foi revogado por questões de segurança da Universidade Kimpa Vita.                                    |\n");
    printf("|_________________________________________________________________________________________________________________|\n\n");
    return 0;
}

int main() {
    // Ativa a acentuação para o idioma português no terminal do Windows/Linux
    setlocale(LC_ALL, "Portuguese");

    Estudante lista[MAX_ESTUDANTES];
    int totalEstudantes = 0;

    int arquivoLido = 0;
    int ordenadoPorMatricula = 0;
    int alteracoesPendentes = 0;

    int opcao = 0;
    char arquivoAlvo[] = "estudantes.txt";

    exibirSplash();

    if (!executarLogin()) {
        return 0;
    }

    // MENU PRINCIPAL SUPERIOR HORIZONTAL
    do {
        system("cls");
        printf(" ____________________________________________________________________________________________________________________\n");
        printf("|                                         SIGE-UNIKIVI - PAINEL PRINCIPAL                                            |\n");
        printf("|   1-Ler Ficheiro | 2-Ordenar | 3-Pesquisar | 4-Gerir Alunos | 5-Relatórios | 6-Exibir Lista | 0-Sair do Sistema    |\n");
        printf("|____________________________________________________________________________________________________________________|\n");
        printf(" Escolha a operação superior: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\n  [!] Entrada inválida. Escolha usando os números indicados do menu.\n");
            limparBuffer();
            system("pause");
            continue;
        }

        // Bloqueio Inicial de segurança: Não permite avançar sem ler a base de dados (.txt) [cite: 39]
        if (opcao != 1 && opcao != 0 && !arquivoLido) {
            printf("\n  [!] REQUISITO OBRIGATÓRIO: Primeiro deve carregar a base de dados utilizando a opção 1.\n");
            printf("  ---------------------------------------------------------------------------------------------------\n");
            system("pause");
            continue;
        }

        switch(opcao) {
            case 1: // OPÇÃO 1 COM MENU FIXO SUPERIOR ANTES DA MENSAGEM
                system("cls");
                printf(" _________________________________________________________________________________________________________________\n");
                printf("|                                       SIGE-UNIKIVI - LEITURA DE FICHEIRO                                        |\n");
                printf("|_________________________________________________________________________________________________________________|\n\n");

                if (lerFicheiroTexto(arquivoAlvo, lista, &totalEstudantes)) {
                    arquivoLido = 1;
                    ordenadoPorMatricula = 0;
                    alteracoesPendentes = 0;
                    printf("  [+] Base de dados carregada! %d registos importados com sucesso.\n", totalEstudantes);
                } else {
                    printf("  [!] Alerta: O arquivo '%s' não foi localizado ou está inacessível.\n", arquivoAlvo);
                }
                system("pause");
                break;

            case 2: { // SUBMENU PERSISTENTE DE ORDENAÇÃO [cite: 40]
                int crit = -1;
                do {
                    system("cls");
                    printf(" _________________________________________________________________________________________________________________\n");
                    printf("|                                      SIGE-UNIKIVI - CRITÉRIOS DE ORDENAÇÃO                                      |\n");
                    printf("|                     1-Matrícula (Cresc) | 2-Nome (Alfab) | 3-Nota (Decresc) | 0-Voltar                          |\n");
                    printf("|_________________________________________________________________________________________________________________|\n");
                    printf(" Seleccione o critério: ");
                    if (scanf("%d", &crit) != 1) {
                        limparBuffer();
                        continue;
                    }

                    if (crit == 0) break;

                    if (crit < 1 || crit > 3) {
                        printf("  [!] Opção inválida.\n");
                        system("pause");
                        continue;
                    }

                    int alg = -1;
                    system("cls");
                    printf(" _________________________________________________________________________________________________________________\n");
                    printf("|                                         SIGE-UNIKIVI - SELECÇÃO DE ALGORITMO                                    |\n");
                    printf("|                           1-Bubble Sort | 2-Selection Sort | 3-Insertion Sort | 0-Cancelar                      |\n");
                    printf("|_________________________________________________________________________________________________________________|\n");
                    printf(" Seleccione o algoritmo: ");
                    if (scanf("%d", &alg) != 1) {
                        limparBuffer();
                        continue;
                    }

                    if (alg == 0) continue;

                    if (alg >= 1 && alg <= 3) {
                        if (alg == 1) bubbleSort(lista, totalEstudantes, crit);
                        else if (alg == 2) selectionSort(lista, totalEstudantes, crit);
                        else if (alg == 3) insertionSort(lista, totalEstudantes, crit);

                        ordenadoPorMatricula = (crit == 1) ? 1 : 0;
                        alteracoesPendentes = 1; // Ordenar altera a disposição na memória, precisa ser salva
                        printf("\n  [+] Operação realizada! Os dados foram reordenados em memória.\n");
                    } else {
                        printf("\n  [!] Algoritmo inválido.\n");
                    }
                    system("pause");
                } while (crit != 0);
                break;
            }
case 3: { // SUBMENU PERSISTENTE DE PESQUISA (TOTALMENTE ISOLADO)
                int escolhaPesquisa = -1;
                do {
                    system("cls");
                    printf(" _________________________________________________________________________________________________________________\n");
                    printf("|                                       SIGE-UNIKIVI - SUBMENU DE PESQUISA                                        |\n");
                    printf("|                               1-Por Código (Matrícula) | 2-Por Nome | 0-Voltar                                  |\n");
                    printf("|_________________________________________________________________________________________________________________|\n");
                    printf(" Escolha o modelo de busca: ");
                    if (scanf("%d", &escolhaPesquisa) != 1) {
                        limparBuffer();
                        continue;
                    }

                    if (escolhaPesquisa == 0) break;

                    // --- MODELO 1: PESQUISA POR MATRÍCULA ---
                    if (escolhaPesquisa == 1) {
                        int mat, metodo;
                        int pos = -1; // Variável local e exclusiva deste bloco

                        printf("\n  Digite o número de Matrícula: ");
                        scanf("%d", &mat);
                        printf("  Método de pesquisa [1-Linear | 2-Binária]: ");
                        scanf("%d", &metodo);

                        if (metodo == 1) {
                            pos = pesquisaLinearMatricula(lista, totalEstudantes, mat);
                        } else if (metodo == 2) {
                            if (ordenadoPorMatricula) {
                                pos = pesquisaBinariaMatricula(lista, totalEstudantes, mat);
                            } else {
                                printf("\n  [!] Erro: A pesquisa binária exige ordenação prévia por Matrícula (Menu 2 -> Opção 1).\n");
                                system("pause");
                                continue;
                            }
                        }

                        if (pos >= 0) {
                            printf("\n  [+] REGISTO ENCONTRADO:\n");
                            printf(" _________________________________________________________________________________________________________________\n");
                            printf("| MATRÍCULA        | NOME COMPLETO                                                     | NOTA FINAL               |\n");
                            printf("|__________________|___________________________________________________________________|__________________________|\n");
                            exibirEstudante(lista[pos]);
                            printf("|__________________|___________________________________________________________________|__________________________|\n");
                        } else {
                            printf("\n  [-] Nenhuma matrícula corresponde ao valor inserido.\n");
                        }
                        system("pause");
                    }

                    // --- MODELO 2: PESQUISA POR NOME ---
                    else if (escolhaPesquisa == 2) {
                        char nomeBusca[100];
                        printf("\n  Digite o Nome (ou parte dele): ");
                        limparBuffer();
                        scanf(" %[^\n]", nomeBusca);

                        printf("\n  [+] A executar pesquisa no sistema por '%s'...\n\n", nomeBusca);

                        // A própria função já desenha a tabela completa com as linhas de 113 caracteres
                        int totalEncontrados = pesquisaLinearNome(lista, totalEstudantes, nomeBusca);

                        if (totalEncontrados == 0) {
                            printf("  [-] Nenhum resultado corresponde ao nome inserido.\n");
                        } else {
                            printf("\n  [+] Pesquisa concluída. Total de registos encontrados: %d\n", totalEncontrados);
                        }
                        system("pause");
                    }

                    else {
                        printf("\n  [!] Opção incorrecta. Escolha 1, 2 ou 0.\n");
                        system("pause");
                    }

                } while (escolhaPesquisa != 0);
                break;
            }

case 4: { // SUBMENU PERSISTENTE DE GESTÃO (ATUALIZADO COM ELIMINAÇÃO)
                int opGerir = -1;
                do {
                    system("cls");
                    printf(" _________________________________________________________________________________________________________________\n");
                    printf("|                                           SIGE-UNIKIVI - MANIPULAÇÃO DE DADOS                                   |\n");
                    printf("|             1-Cadastrar Aluno | 2-Actualizar Aluno | 3-Eliminar Aluno | 4-Gravar Dados | 0-Voltar               |\n");
                    printf("|_________________________________________________________________________________________________________________|\n");
                    printf(" Seleccione: ");
                    if (scanf("%d", &opGerir) != 1) {
                        limparBuffer();
                        continue;
                    }

                    if (opGerir == 0) break;

                    if (opGerir == 1) {
                        if (cadastrarEstudante(lista, &totalEstudantes)) {
                            alteracoesPendentes = 1;
                        }
                    } else if (opGerir == 2) {
                        if (actualizarEstudante(lista, totalEstudantes)) {
                            alteracoesPendentes = 1;
                        }
                    } else if (opGerir == 3) { // Nova Opção adicionada
                        if (eliminarEstudante(lista, &totalEstudantes)) {
                            alteracoesPendentes = 1; // Se apagou, a memória está diferente do ficheiro txt
                        }
                    } else if (opGerir == 4) { // Antiga opção 3 passou a ser 4
                        int tipoFich;
                        printf("\n  Escolha o Formato [1-Ficheiro Texto (.txt) | 2-Ficheiro Binário (.bin)]: ");
                        scanf("%d", &tipoFich);
                        if (tipoFich == 1) {
                            if (gravarFicheiroTexto(arquivoAlvo, lista, totalEstudantes)) {
                                printf("\n  [+] Alterações gravadas com sucesso em '%s'!\n", arquivoAlvo);
                                alteracoesPendentes = 0;
                            }
                        } else if (tipoFich == 2) {
                            if (gravarFicheiroBinario("estudantes_backup.bin", lista, totalEstudantes))
                                printf("\n  [+] Cópia de segurança gerada em 'estudantes_backup.bin'!\n");
                        }
                    } else {
                        printf("\n  [!] Opção inexistente.\n");
                    }
                    system("pause");
                } while (opGerir != 0);
                break;
            }

            case 5: // RELATÓRIOS ESTATÍSTICOS
                system("cls");
                gerarRelatorioEstatistico(lista, totalEstudantes);
                system("pause");
                break;

            case 6: // OPÇÃO 6 COM MENU FIXO SUPERIOR ANTES DA TABELA
                system("cls");
                printf(" _________________________________________________________________________________________________________________\n");
                printf("|                                       SIGE-UNIKIVI - EXIBIÇÃO DA BASE DE DADOS                                  |\n");
                printf("|_________________________________________________________________________________________________________________|\n");
                exibirLista(lista, totalEstudantes);
                system("pause");
                break;

            case 0: // ENCERRAMENTO COM VALIDAÇÃO DE SEGURANÇA
                system("cls");
                if (alteracoesPendentes) {
                    char resp;
                    printf(" _________________________________________________________________________________________________________________\n");
                    printf("|                                        AVISO: ALTERAÇÕES NÃO GUARDADAS                                          |\n");
                    printf("|_________________________________________________________________________________________________________________|\n");
                    printf("\n  Existem cadastros, actualizações ou ordenações pendentes que não foram salvas.\n");
                    printf("  Deseja gravar as alterações antes de sair do sistema? (S/N): ");
                    limparBuffer();
                    scanf("%c", &resp);

                    if (resp == 'S' || resp == 's') {
                        if (gravarFicheiroTexto(arquivoAlvo, lista, totalEstudantes)) {
                            printf("\n  [+] Sucesso: Os dados foram guardados no disco de forma automática.\n");
                        } else {
                            printf("\n  [!] Erro ao tentar salvar os dados no encerramento.\n");
                        }
                    } else {
                        printf("\n  [-] Fechando sem salvar as modificações recentes.\n");
                    }
                    system("pause");
                }
                printf("\nSessão encerrada de forma segura. O SIGE-UNIKIVI agradece o vosso trabalho!\n");
                break;

            default:
                printf("\n  [!] Código incorrecto. Verifique a barra de menus superiores.\n");
                system("pause");
                break;
        }

    } while (opcao != 0);

    return 0;
}
