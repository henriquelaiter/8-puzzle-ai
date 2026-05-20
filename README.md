# 🧩 8-Puzzle Solver - Inteligência Artificial

Projeto desenvolvido em Linguagem C para simular e resolver o clássico problema do 8-Puzzle utilizando técnicas de Inteligência Artificial e algoritmos clássicos de busca.

---

# 🎯 Objetivo do Jogo

O objetivo do jogo é reorganizar as peças numeradas de `1` a `8` em um tabuleiro `3x3`, utilizando o espaço vazio (`0`) até alcançar o estado meta:

```text
1 2 3
4 5 6
7 8 0
```

---

# 🧠 Técnicas de IA Implementadas

O projeto utiliza três abordagens diferentes para resolução do problema:

---

## 1️⃣ Solução Manual

Permite ao usuário jogar diretamente pelo terminal utilizando:

| Tecla | Movimento |
|------|------|
| W | Cima |
| A | Esquerda |
| S | Baixo |
| D | Direita |

Essa abordagem foi utilizada para validar:
- movimentação das peças
- transição de estados
- condição de vitória

---

## 2️⃣ Busca em Largura (BFS)

A Busca em Largura (Breadth-First Search) explora o espaço de estados nível por nível, garantindo encontrar a solução ótima (menor número de movimentos possíveis).

### 🔹 Otimizações implementadas

### ✅ Mapeamento Numérico dos Estados

O tabuleiro é convertido em um identificador numérico único:

```text
1 2 3
4 5 6
7 8 0
```

vira:

```text
123456780
```

Isso reduz drasticamente o custo computacional de comparação entre estados.

---

### ✅ Busca Binária em Estados Visitados

Os estados visitados são armazenados ordenadamente, permitindo:

- busca em `O(log N)`
- inserção eficiente
- menor consumo de processamento

---

## 3️⃣ Busca em Profundidade Iterativa (IDDFS)

O IDDFS combina:
- baixo consumo de memória da DFS
- garantia de solução mínima da BFS

O algoritmo funciona aumentando gradualmente o limite de profundidade:

```text
3 → 6 → 9 → 12 ...
```

### ✅ Vantagens
- baixo consumo de memória
- implementação recursiva simples
- boa escalabilidade de memória

### ❌ Desvantagens
- recalcula níveis anteriores
- alto custo computacional
- pode gerar movimentos repetidos

---

# 🚀 Desafios do Projeto

## 🔥 Explosão Combinatória

O problema possui:

```text
9! = 362.880 estados possíveis
```

Sem controle de estados visitados:
- o programa entrava em loops
- consumia muita memória
- ficava extremamente lento

---

## ⚙️ Otimização de Memória

Inicialmente o projeto utilizava muitas alocações dinâmicas (`malloc`) para armazenar nós da árvore de estados.

A performance melhorou significativamente após:
- conversão das matrizes em chaves numéricas
- redução de cópias em memória
- implementação de busca binária

---

# 🎲 Configuração do Tabuleiro

---

## 🔹 Modo Teste

Tabuleiro fixo para depuração:

```c
int tabuleiro[3][3] = {
    {1, 2, 0},
    {4, 6, 3},
    {7, 5, 8}
};
```

---

## 🔹 Modo Aleatório

Para ativar:

```c
geraTabuleiro(tabuleiro);
geraCopia_matriz(tabuleiro, copia);
```

E comentar:

```c
// int tabuleiro[3][3] = {{1, 2, 0},{4, 6, 3},{7, 5, 8}};
```

---

# ⚠️ Observação

O gerador aleatório verifica a paridade de inversões para garantir que o tabuleiro gerado seja solucionável.

Mesmo assim:
- estados muito complexos podem demorar bastante
- o IDDFS pode consumir muito processamento
- algumas execuções podem explorar bilhões de possibilidades

---

# 📸 Demonstração

## Menu Inicial

```markdown
![Menu Inicial](images/menu.png)
```

---

## Solução Manual

```markdown
![Modo Manual](images/manual.png)
```

---

## Busca em Largura (BFS)

```markdown
![Busca em Largura](images/bfs.png)
```

---

## Busca Iterativa (IDDFS)

```markdown
![Busca Iterativa](images/iddfs.png)
```

---

# 🛠️ Como Executar

## Pré-requisitos

- GCC instalado
- Code::Blocks
- VS Code
- Dev-C++

---

## Compilar

```bash
gcc src/main.c -o puzzle
```

---

## Executar

### Linux / MacOS

```bash
./puzzle
```

### Windows

```bash
puzzle.exe
```

---

# 📂 Estrutura do Projeto

```text
8-puzzle-ai/
│
├── src/
│   ├── main.c
│   ├── bfs.c
│   ├── iddfs.c
│   └── ...
│
├── images/
│   ├── menu.png
│   ├── bfs.png
│   ├── iddfs.png
│   └── manual.png
│
└── README.md
```

---

# 📚 Conceitos Trabalhados

- Inteligência Artificial
- Estruturas de Dados
- Algoritmos de Busca
- BFS
- DFS
- IDDFS
- Grafos
- Complexidade Computacional
- Otimização de Memória
- Recursão
- Manipulação de Matrizes em C

---

# 👨‍💻 Autor

Desenvolvido por Henrique Laiter.

GitHub: https://github.com/henriquelaiter
