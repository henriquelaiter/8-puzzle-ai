#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define tam 3       //como o tamanho da matriz eh muito usado, evita repeticao de codigo
#define MAX_ESTADOS 362880 // 9! (número máximo de permutações possíveis para 8-puzzle)

///FUNÇÕES PARA SOLUÇÃO MANUAL.
//printa matriz
void Print_matriz(int Matriz[tam][tam]){
    for(int i=0; i<tam; i++)
    {
        for(int j=0; j<tam; j++)
        {
            printf("%d\t", Matriz[i][j]);
        }
    printf("\n");
    }
    return;
}

//Sempre que chamado gera uma cópia do estado atual da matriz
void geraCopia_matriz(int tabuleiro[tam][tam],int copia[tam][tam]){
    for(int i=0; i<tam; i++)
    {
        for(int j=0; j<tam; j++)
        {
            copia[i][j] = tabuleiro[i][j];
        }
    }
    return;
}

// para ter solução se baseia em paridade --> o num de inversões tem que ser par
int inversoes(int tabuleiro[tam][tam]) {
    int vetor[9];
    int index = 0;

    // Copia matriz para vetor
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            vetor[index++] = tabuleiro[i][j];
        }
    }

    // Conta inversões
    int inversao = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (vetor[i] && vetor[j] && vetor[i] > vetor[j]) {
                inversao++;
            }
        }
    }

    return inversao % 2 == 0 ? 0 : 1;
}

// Gerar tabuleiro aleatório
void geraTabuleiro(int tabuleiro[tam][tam]) {
    int nums[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    do {
        // Embaralha os números
        for (int i = 0; i < 9; i++) {
            int j = rand() % 9;
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }

        // Preenche o tabuleiro
        int index = 0;
        for (int i = 0; i < tam; i++) {
            for (int j = 0; j < tam; j++) {
                tabuleiro[i][j] = nums[index++];
            }
        }
    } while (inversoes(tabuleiro) != 0);
}


//funcao sucessora
int Movimento_Jogador(int tabuleiro[tam][tam]){
    printf("\nDigite o MOVIMENTO: ");
    fflush(stdin);          //limpa o buffer

    char ch = getchar();
    ch = toupper(ch);       //transforma o char em maiusculo para comparar
    int indexi, indexj, Aux, Movs = 0;

    for(int i=0; i<tam; i++)
    {
        for(int j=0; j<tam; j++)
        {
           if (tabuleiro[i][j] == 0){
                indexi = i;
                indexj = j;
           }
        }
    }

    switch (ch){
        case 'W':
            if (indexi != 0){
                Aux = tabuleiro[indexi - 1][indexj];
                tabuleiro[indexi - 1][indexj] = 0;
                tabuleiro[indexi][indexj] = Aux;
                Movs = 1;
            }
            else{

            }

        break;

        case 'A':
            if (indexj != 0){
                Aux = tabuleiro[indexi][indexj - 1];
                tabuleiro[indexi][indexj - 1] = 0;
                tabuleiro[indexi][indexj] = Aux;
                Movs = 1;
            }
            else{

            }

        break;

        case 'S':
            if (indexi != 2){
                Aux = tabuleiro[indexi + 1][indexj];
                tabuleiro[indexi + 1][indexj] = 0;
                tabuleiro[indexi][indexj] = Aux;
                Movs = 1;
            }
            else{

            }

        break;

        case 'D':
            if (indexj != 2){
                Aux = tabuleiro[indexi][indexj + 1];
                tabuleiro[indexi][indexj + 1] = 0;
                tabuleiro[indexi][indexj] = Aux;
                Movs = 1;
            }
            else{

            }

        break;

        default:
            return Movs;
    }
    return Movs;
}

//funcao de avaliacao do tabuleiro --> eh o resultado final?
int Avalia_Matriz(int tabuleiro[tam][tam]){
    int TabuleiroFinal[3][3] = {{1, 2, 3},
                                {4, 5, 6},
                                {7, 8, 0}};

    for(int i=0; i<tam; i++)
    {
        for(int j=0; j<tam; j++)
        {
           if (tabuleiro[i][j]!= TabuleiroFinal[i][j]){
                return 1;
           }
        }
    }
    return 0;
}



///FUNÇÕES DA BUSCA EM LARGURA
//Estrutura de estados do 8puzzle
struct estado {
    int tabuleiro[3][3];  // Representação do 8-puzzle
    int vazioX, vazioY;   // Coordenadas do espaço vazio
    struct estado* pai;   // Ponteiro para o estado pai
};
typedef struct estado Estado;

//Estrutura de no da fila
struct no{
    Estado info;
    struct no* prox;
};
typedef struct no No;
//Estrutura de fila
typedef struct fila{
    No * ini;
    No * fim;
} Fila;
//Função para criar a fila
Fila* CriaFila(){
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}
//Função auxiliar insere no fim
No* ins_fim(No* fim, Estado E){
    No* p = (No*)malloc(sizeof(No));
    p->info = E;
    p->prox = NULL;
    if (fim!=NULL){
        fim->prox = p;
    }
    return p;
}
//Função para inserir um elemento na fila
void insere (Fila* f, Estado E){
    f->fim = ins_fim(f->fim,E);
    if(f->ini==NULL){
        f->ini = f->fim;
    }
}
//Função auxiliar retira do início
No* ret_ini(No* ini){
    No* p = ini->prox;
    free(ini);
    return p;
}
//Função para retirar elementos da fila
Estado retira(Fila* f){
    Estado v;
    if(f->ini==NULL){
        printf("Fila vazia.\n");
        exit(1);
    }
    v = f->ini->info;
    f->ini = ret_ini(f->ini);
    if(f->ini==NULL){
        f->fim = NULL;
    }
    return v;
}
//Verifica se o estado atual é solução
int EhSolucao(Estado Atual) {
    int tabuleiroFinal[3][3] = {{1, 2, 3},
                                {4, 5, 6},
                                {7, 8, 0}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (Atual.tabuleiro[i][j] != tabuleiroFinal[i][j]) {
                return 0; // Retorna falso se algum elemento for diferente
            }
        }
    }
    return 1; // Retorna verdadeiro se todos os elementos forem iguais
}
// Movimentos possíveis (cima, baixo, esquerda, direita)
int movimentos[4][2] = {
    {-1, 0}, // Cima
    {1, 0},  // Baixo
    {0, -1}, // Esquerda
    {0, 1}   // Direita
};
// Função para gerar filhos
int GerarFilhos(Estado atual, Estado filhos[]) {
    int numFilhos = 0;

    for (int i = 0; i < 4; i++) {
        int novoX = atual.vazioX + movimentos[i][0];
        int novoY = atual.vazioY + movimentos[i][1];

        if (novoX >= 0 && novoX < 3 && novoY >= 0 && novoY < 3) {
            Estado novoEstado = atual;
            novoEstado.pai = (Estado*)malloc(sizeof(Estado)); // Aloca memória para o estado pai
            *novoEstado.pai = atual; // Copia o estado atual como pai

            novoEstado.tabuleiro[atual.vazioX][atual.vazioY] = novoEstado.tabuleiro[novoX][novoY];
            novoEstado.tabuleiro[novoX][novoY] = 0;

            novoEstado.vazioX = novoX;
            novoEstado.vazioY = novoY;

            filhos[numFilhos++] = novoEstado;
        }
    }

    return numFilhos;
}
// Função para imprimir o estado atual do tabuleiro
void imprimeEstado(Estado estado) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            printf("%d ", estado.tabuleiro[i][j]);
        }
        printf("\n");
    }
}
//Função para imprimir o caminho percorrido pelo BFS
void ImprimeCaminho(Estado* estado) {
    if (estado == NULL) {
        return;
    }

    ImprimeCaminho(estado->pai); // Chamada recursiva para imprimir o estado anterior

    // Imprime o estado atual
    imprimeEstado(*estado);
    printf("\n");
}
// Busca em Largura
int BFS(int tabuleiro[tam][tam]) {
    int ContEstados = 0;
    Fila* FilaDeEstados = CriaFila();

    Estado* EstadoInicial = (Estado*)malloc(sizeof(Estado));
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            EstadoInicial->tabuleiro[i][j] = tabuleiro[i][j];
            if (tabuleiro[i][j] == 0) {
                EstadoInicial->vazioX = i;
                EstadoInicial->vazioY = j;
            }
        }
    }
    EstadoInicial->pai = NULL; // Estado inicial não tem pai

    insere(FilaDeEstados, *EstadoInicial);

    while (FilaDeEstados->ini != NULL) {
        Estado atual = retira(FilaDeEstados);
        ContEstados++;

        if (EhSolucao(atual)) {
            printf("Estado final encontrado:\n");
            imprimeEstado(atual);
            printf("\nForam visitados %d estados\n", ContEstados);

            printf("Caminho percorrido para a solução:\n");
            ImprimeCaminho(&atual);
            return 1; // Solução encontrada
        }

        Estado filhos[4];
        int numFilhos = GerarFilhos(atual, filhos);

        for (int i = 0; i < numFilhos; i++) {
            insere(FilaDeEstados, filhos[i]);
        }
    }

    return 0; // Não encontrou a solução
}



///Busca em Profundidade Limitada Iterativa
//Estrutura de pilha
struct pilha{
    No* Topo;
};
typedef struct pilha Pilha;
//Função que inicializa a pilha
Pilha* CriaPilha(){
    Pilha* p;
    p = (Pilha*)malloc(sizeof(Pilha));
    p -> Topo = NULL;
    return p;
}
//Função auxiliar do push
No* ins_ini(No* t, Estado a){
    No* p = (No*)malloc(sizeof(No));
    p -> info = a;
    p -> prox = t;
    return p;
}
//Função Push (Insere um elemento no topo da pilha)
void push(Pilha* p, Estado v){
    p -> Topo = ins_ini(p -> Topo, v);
}
//Função auxiliar do pop
No* ret_ini_pilha(No* l){
    No* p = l -> prox;
    free(l);
    return p;
}
//Função Pop (Retira um elemento do topo da pilha)
Estado pop (Pilha* p){
    Estado v;
    if (p->Topo == NULL){
        printf("Pilha vazia.\n");
        exit(1);
    }
    v = p -> Topo -> info;
    p -> Topo = ret_ini_pilha(p -> Topo);
    return v;
}
//Explora os estados até o limite atual
int DFS_Limitada(Estado atual, int limite, int* ContEstados) {
    (*ContEstados)++; // Incrementa o contador de estados visitados

    if (EhSolucao(atual)) {
        printf("\nEstado final encontrado:\n");
        imprimeEstado(atual);
        printf("\nCaminho percorrido para a solucao:\n");
        ImprimeCaminho(&atual);
        return 1; // Solução encontrada
    }

    if (limite == 0) {
        return 0; // Limite atingido
    }

    Estado filhos[4];
    int numFilhos = GerarFilhos(atual, filhos);

    for (int i = 0; i < numFilhos; i++) {
        if (DFS_Limitada(filhos[i], limite - 1, ContEstados)) {
            return 1; // Solução encontrada em algum ramo
        }
    }
    return 0; // Nenhuma solução encontrada neste caminho
}

//Função que itera os limites
// Função que itera os limites de profundidade de maneira iterativa
int IDDFS(int tabuleiro[tam][tam]) {
    int ContEstados = 0; // Contador de estados visitados
    Estado* inicial = (Estado*)malloc(sizeof(Estado));

    // Copia o estado inicial para a estrutura
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            inicial->tabuleiro[i][j] = tabuleiro[i][j];
            if (tabuleiro[i][j] == 0) {
                inicial->vazioX = i;
                inicial->vazioY = j;
            }
        }
    }
    inicial->pai = NULL;

    // Define o limite inicial e começa a busca
    int limite = 3; // Limite inicial da profundidade
    while (1) {
        printf("Buscando com limite de profundidade: %d\n", limite);
        ContEstados = 0; // Resetando o contador de estados visitados
        if (DFS_Limitada(*inicial, limite, &ContEstados)) {
            printf("\nCaminho encontrado com %d estados visitados!\n", ContEstados);
            return 1; // Solução encontrada
        }
        limite += 3; // Aumenta o limite de profundidade a cada iteração
        printf("\nAumentando o limite de profundidade...\n");
    }

    return 0;
}


///FUNÇÕES GERAIS
void regras(){
    printf("Bem Vindo ao 8-puzzle!\n\n");
    printf("COMANDOS PARA MOVIMENTAR:\n'W' para CIMA.\n'S' para BAIXO.\n'A' para ESQUERDA.\n'D' para DIREITA.\n\n");
    printf("Resolva este tabuleiro:\n");
}

// funcao principal
int main() {
    int Mov = 0, ValidMov;       //contador de movimentos e movimentos válidos
    srand(time(0)); // inicializa o gerador de números aleatórios
    int tabuleiro[tam][tam];
    int copia[tam][tam];

    /*int tabuleiro[3][3] = {
        {4, 1, 8},
        {5, 6, 7},
        {2, 3, 0}
    };*/

    geraTabuleiro(tabuleiro);
    geraCopia_matriz(tabuleiro,copia);

    int solucao;
    printf("Escolha como solucionar o 8 puzzle:\n'1' para solucao MANUAL.\n'2' para solucao por BUSCA EM LARGURA.\n'3' para solucao por BUSCA EM PROFUNDIDADE LIMITADA ITERATIVA.\n");
    scanf("%d", &solucao);

    switch(solucao){
    case 1: //MANUAL
        while (Avalia_Matriz(tabuleiro) == 1){
            regras();
            Print_matriz(tabuleiro);
            ValidMov = Movimento_Jogador(tabuleiro);
            Mov = Mov + ValidMov;
            system("cls");
        }
        break;

    case 2:
        if (inversoes(tabuleiro) == 0){
            BFS(tabuleiro);
        }
        else{
            printf("Tabuleiro nao eh valido para resolucao.\n");
        }
        return 0;
    case 3: // BUSCA EM PROFUNDIDADE LIMITADA ITERATIVA
        if (inversoes(tabuleiro) == 0){
            IDDFS(tabuleiro);
        }
        else{
            printf("Tabuleiro nao eh valido para resolucao.\n");
        }

    return 0;
    }
    printf("\aPARABENS, VOCE RESOLVEU O TABULEIRO!!!\n\n");
    printf("Voce saiu do estado inicial:\n");
    Print_matriz(copia);
    printf("\nPara o estado final:\n");
    Print_matriz(tabuleiro);
    printf("\nVoce concluiu o desafio em %d movimentos validos.\n\n",Mov);

    return 0;
}
