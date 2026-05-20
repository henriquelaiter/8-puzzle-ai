Aqui está o código completo do `README.md` formatado exatamente como você pediu, pronto para você copiar, colar e salvar no seu repositório:

```markdown
# 🧩 8-Puzzle Solver - Inteligência Artificial

Este projeto implementa um simulador e solucionador para o clássico jogo **8-Puzzle** (Jogo dos Oito), desenvolvido em **Linguagem C**. O objetivo do jogo é mover as peças numeradas de 1 a 8 em um tabuleiro $3 \times 3$ utilizando o espaço vazio (representado pelo número `0`) até atingir o estado meta (ordenado).

## 🎯 Estado Objetivo (Meta)
```text
1   2   3
4   5   6
7   8   0

```

---

## 🧠 Teoria das Técnicas Utilizadas

O projeto aborda a resolução do problema utilizando três abordagens distintas de busca e controle:

### 1. Solução Manual

Permite ao usuário interagir diretamente com o tabuleiro pelo console através do teclado (comandos `W`, `A`, `S`, `D`), testando a lógica de transição de estados e validação de vitória.

### 2. Busca em Largura (BFS - Breadth-First Search) Otimizada

A Busca em Largura explora o espaço de estados nível por nível. Ela garante o encontro da **solução ótima** (com o menor número de movimentos possíveis). Para viabilizar a execução em tempo hábil e evitar estouro de memória, foram aplicadas duas técnicas avançadas de otimização:

* **Mapeamento de Estados:** A matriz bidimensional $3 \times 3$ é "achatada" em um identificador numérico único de 9 dígitos (`long long`). Isso reduz drasticamente o custo computacional de comparar se dois tabuleiros são iguais, substituindo varreduras por laços `for` por uma igualdade direta.
* **Busca Binária e Inserção Ordenada:** Em vez de realizar uma busca linear lenta ($O(N)$) na lista de estados fechados (*Closed List*), os identificadores numéricos são inseridos de forma ordenada no vetor de visitados, permitindo que a verificação de duplicatas ocorra em tempo logarítmico ($O(\log N)$).

### 3. Busca em Profundidade Limitada Iterativa (IDDFS)

O IDDFS combina a economia de memória da busca em profundidade com a garantia de caminho mínimo da busca em largura. O algoritmo funciona definindo um limite de passos inicial (neste caso, nível 3) e realizando buscas em profundidade até esse ponto. Caso não encontre a solução, o limite é incrementado de 3 em 3 níveis e a busca recomeça do zero.

* **Vantagem:** Consumo de memória extremamente baixo, pois armazena apenas o caminho atual na pilha de recursão.
* **Desvantagem:** Alto custo de processamento (*trabalho repetitivo*), pois recalcula todos os níveis anteriores a cada aumento de limite. Além disso, por não possuir controle global de visitados, pode gerar loops locais (ir e voltar no mesmo movimento) dentro do limite estipulado.

---

## 🚀 Desafios Enfrentados no Desenvolvimento

* **Explosão Combinatória:** O 8-puzzle possui $9! = 362.880$ permutações possíveis. Sem um controle rígido de estados visitados na busca em largura, o programa estourava a memória RAM rapidamente ou ficava preso em loops infinitos.
* **Custo de Cópia em Memória:** A criação excessiva de ponteiros dinâmicos (`malloc`) para estruturar a árvore de nós pais consome muita paginação de hardware. A conversão de matrizes para chaves numéricas foi o ponto de virada para garantir a estabilidade e velocidade do software.

---

## ⚙️ Configuração do Tabuleiro (Teste vs. Aleatório)

Para facilitar a análise de desempenho, testes de corretude e depuração das rotas de solução, o código está configurado atualmente na função `main()` com uma **matriz de teste estática** (fácil resolução):

```c
// Tabuleiro para testes, comentar se ativar tabuleiro aleatório.
int tabuleiro[3][3] = {{1, 2, 0},
                       {4, 6, 3},
                       {7, 5, 8}};

```

### 🎲 Como ativar o Tabuleiro Aleatório?

Se você deseja testar o comportamento dos algoritmos com desafios gerados aleatoriamente pelo computador, basta inverter os comentários dentro da função `main()`, deixando desta forma:

```c
geraTabuleiro(tabuleiro);  // Tirar o comentário para funcionar aleatoriamente
geraCopia_matriz(tabuleiro, copia);

// int tabuleiro[3][3] = {{1, 2, 0},{4, 6, 3},{7, 5, 8}}; // Comente esta linha

```

> ⚠️ **Nota sobre Desempenho:** O gerador garante que o tabuleiro criado seja **solucionável** através do cálculo de paridade de inversões (onde o número de inversões precisa ser par). No entanto, dependendo da complexidade do tabuleiro gerado (profundidade da solução superior a 20 movimentos), os algoritmos — especialmente o IDDFS — podem demorar um tempo considerável para processar todos os bilhões de ramos possíveis.

---

## 📸 Demonstração do Funcionamento (Exemplos)

Abaixo estão os registros do comportamento do sistema em execução para cada modo de operação:

### Menu Inicial e Escolha

### Modo de Solução Manual

### Resolução via Busca em Largura (BFS)

### Resolução via Busca Iterativa (IDDFS)

---

## 🛠️ Como Executar o Projeto

1. Certifique-se de ter um compilador C instalado ou utilize uma IDE como o **Code::Blocks**.
2. Abra o projeto pela IDE ou compile pelo terminal com os comandos:
```bash
gcc src/main.c -o puzzle
./puzzle

```



```

```
