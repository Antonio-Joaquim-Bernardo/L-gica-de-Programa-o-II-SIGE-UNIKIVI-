# L-gica-de-Programa-o-II-SIGE-UNIKIVI-
Repositório com o Objectivo de armazenar  o Sistema de Gestão de Estudantes em C de Lógica de Programações, no Curso de Engenharia Informática do 1º Ano da UNIKIVI

# SIGE-UNIKIVI 🎓 — Sistema de Gestão de Estudantes da Universidade Kimpa Vita

O **SIGE-UNIKIVI** é uma aplicação de consola robusta desenvolvida em linguagem C padrão (ANSI C) para a disciplina de **Lógica de Programação II** do 1º Ano de Engenharia Informática na **Universidade Kimpa Vita**. 

O sistema foi projetado sob os princípios da modularização de código, persistência de dados em disco e aplicação prática de algoritmos clássicos de ordenação e pesquisa (divisão e conquista), respeitando uma interface gráfica simulada em terminal com uma largura simétrica estrita de **113 caracteres**.

---

## 🔐 1. Credenciais de Acesso Padrão

* **E-mail de Acesso:** `admin@gmail.com`
* **Senha Provisória:** `admin2026`

> ⚠️ **Nota de Segurança:** Em ambiente de produção real, estas credenciais devem ser encriptadas ou validadas através de um ficheiro binário restrito para evitar o acesso não autorizado.

---

## 🚀 2. Funcionalidades Principais

* **Gestão Dinâmica (CRUD Completo):**
    * Registo de estudantes (Matrícula única, Nome Completo e Nota Final).
    * Atualização de dados cadastrais em tempo real.
    * **Eliminação Segura:** Remoção física do registo através do algoritmo de compressão de memória (*Shift à Esquerda*) com dupla confirmação do utilizador (`S/N`).
* **Algoritmos de Ordenação:**
    * *Bubble Sort* (Ordenação por flutuação)
    * *Selection Sort* (Ordenação por seleção)
    * *Insertion Sort* (Ordenação por inserção)
* **Algoritmos de Pesquisa:**
    * *Pesquisa Binária:* Busca instantânea por Matrícula com complexidade $O(\log N)$ (exige dados ordenados).
    * *Pesquisa Linear Avançada:* Rastreio total do vetor por Nome (ou parte dele), permitindo a listagem simultânea de múltiplos alunos homónimos.
* **Persistência e Segurança de Dados:**
    * Gravação e leitura automatizada em Ficheiro de Texto (`.txt`).
    * Geração de cópia de segurança (Backup) em Ficheiro Binário (`.bin`).
    * **Alerta de Alterações Pendentes:** O programa interseta a saída se o utilizador tentar fechar a consola com dados voláteis não salvos na memória RAM.

---

## 📂 3. Estrutura do Projeto

O código está dividido de forma modular em três ficheiros fundamentais:

```text
├── main.c          # Fluxo principal, ciclos de vida dos submenus e interface.
├── estudante.c     # Implementação dos algoritmos, lógica de ficheiros e CRUD.
└── estudante.h     # Contrato estrutural, definição da Struct e assinaturas.
