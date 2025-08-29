# analisador
trabalho para analise de algoritmo
# analisador de algoritmos (c)

ferramenta didatica em c para analisar algoritmos de dois jeitos:
1) **analise estatica** do codigo .c (heuristica de complexidade)
2) **analise empirica** (tempo real de execucao + contagem basica de operacoes)


## o que foi usado

- linguagem c (c11)
- bibliotecas padrao: `stdio.h`, `stdlib.h`, `string.h`, `time.h`, `ctype.h`
- `struct` para acumular metrica de analise estatica
- ponteiro de funcao (`typedef void (*FuncaoAlgoritmo)(int)`)
- `clock()` para medir tempo
- `malloc/free` para alocacao
- recursao (merge sort, n-queens)
- contadores globais volateis para comparacoes, atribuicoes e chamadas

## para que foi

- servir de **laboratorio** pra complexidade
- gerar **relatorio rapido** de um arquivo .c (loops, ifs, recursao, flags de padrao)
- medir **tempo vs n** e **comparar algoritmos** no mesmo grafico de saida (csv friendly)

## o que ele faz

menu principal:

1. **analise estatica (arquivo .c)**  
   - le um .c e conta: for/while/do, nivel max de aninhamento, if/switch, recursao.  
   - seta flags se achar sinais de **divide & conquer**, **programacao dinamica**, **backtracking**.  
   - imprime heuristica de **Omega / O / Theta** com base nas contagens.

2. **funcao nao implementada**  
   - reservado pra pseudocodigo (futuro).

3. **analise empirica (simulados)**  
   - roda algoritmos “vazios” de custo **O(n^2)**, **O(n log n)**, **O(log n)**, **O(n^3)** so pra medir tempo bruto.

4. **algoritmos classicos (execucao real + contagem)**  
   - **busca binaria**
   - **insertion sort**
   - **merge sort (recursivo)**
   - **floyd–warshall**
   - **n-queens (backtracking, conta solucoes)**
   - imprime `tempo` e contadores: `comps`, `movs/atrs`, `calls`

5. **comparar insertion x merge**  
   - preenche vetores iguais, roda os dois, imprime `N, tempo_insertion, tempo_merge` pra comparar.

6. **sair**

## como implementei a analise de algoritmo

### analise estatica (heuristica)
- parsing linha a linha com limpeza de espaco (`isspace`) e filtros pra ignorar comentario e libs.
- extracao simples do **nome da funcao** pra detectar **recursao**.
- contagem de **loops** e controle de **aninhamento** por4 “pilha” de blocos.
- flags por palavras–sinal: `merge`, `partition`, `mid`, `n/2` => **divide & conquer**;  
  `dp`, `memo`, `cache`, `tabela` => **DP**;  
  `backtrack`, `visited`, `desmarca` + recursao => **BT**.
- regra heuristica pra chutar complexidade:  
  - se DP + aninhamento >= 3 → tende a **O(n^3)**  
  - se recursao com ramificacao >=2 → **O(2^n)**  
  - se divide & conquer → **O(n log n)**  
  - se 2 loops aninhados → **O(n^2)**  
  - se 1 loop → **O(n)**  
  - senao **O(1)**  
  - define **Omega** e **Theta** combinando os sinais acima.

### analise empirica (tempo real)
- usa `clock()` pra medir tempo pra cada N dobrando: 1,2,4,… ate limite ou se 5s estourar.
- contadores globais:  
  - `g_cont_comp` = comparacoes  
  - `g_cont_atr`  = atribuicoes/movimentos  
  - `g_cont_calls` = chamadas recursivas
- gera linhas estilo csv pra voce colar no excel/gnuplot/python.

## build

### gcc (linux/macos)
```bash
gcc -std=c11 -O2 -Wall -Wextra -o analisador analisador_algoritmos_lucas.c
./analisador
```

### mingw (windows)
```bat
gcc -std=c11 -O2 -Wall -Wextra -o analisador.exe analisador_algoritmos_lucas.c
analisador.exe
```

se nao tem gcc no windows: instale **mingw-w64** ou use **wsl**.

## uso rapido

- **opcao 1 (analise estatica)**: quando pedir o arquivo, digite o caminho do `.c`.
- **opcao 3/4/5**: escolha o algoritmo e deixe rodar. a saida ja sai formatada `N, metricas...`

## exemplos de saida (curtos)

```
--- Medindo Performance de: Quadratico O(n^2) ---
Tamanho (N), Tempo (segundos)
1, 0.000000
2, 0.000000
4, 0.000000
...
```

```
--- Relatorio da Analise Estatica ---
Total de loops (for/while/do) encontrados: X
Nivel maximo de aninhamento de loop detectado: Y
ifs: A | switch: B
funcoes recursivas: C (max auto-chamadas diretas numa func: D)
flags: DC=1, DP=0, BT=0
Melhor caso (Omega): Omega(n)
Pior caso (Big-O): O(n log n)
Caso medio (Theta): Theta(n log n)
```

## TODO / melhorias
- implementar parser de pseudocodigo (opcao 2)
- refinar heuristica da analise estatica (menos falso positivo)
- trocar `clock()` por `clock_gettime` ou `QueryPerformanceCounter` quando fizer sentido
- testes automatizados simples

## licenca
MIT
