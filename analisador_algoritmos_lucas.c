#include <stdio.h> 
//usei essa biblioteca para entrada e saída de dados, exemplo: printf, scanf
#include <stdlib.h> 
//usei essa biblioteca para funções de alocação de memória, controle de processos, conversões e outras utilidades. exemplo: malloc, free, exit
#include <string.h>
 //usei essa biblioteca para manipulação de strings, exemplo: strlen, strcpy, strcmp
#include <time.h> 
//usei essa biblioteca para manipulação de data e hora, exemplo: time, clock, difftime
#include <ctype.h> 
//usei essa biblioteca para manipulação de caracteres, exemplo: isspace, isdigit
#include <inttypes.h>
//pro tipo de dados long long


/*
    Autor: Lucas Araujo de Carvalho

*/

//a struct Analise foi criada p/ guardar os resultados da análise estática do código
//conta loops, ifs, switches, recursão, técnicas (dp, divide and conquer, backtracking)
//além de armazenar nome da última função encontrada p/ análise
typedef struct analisador_estatico
{
    int loops_encontrados; //contagem total de for/while/do
    int nivel_max_aninhamento; //profundidade maxima de loop
    int ifs_encontrados; //para analisar estruturas condicionais
    int switch_encontrados;//verificar os switches encontrados

    // recursao
    int funcoes_recursivas; //qtd de funcoes recursivas q se chamam
    int max_auto_chamadas_na_mesma_func; //qtd de chamadas recursivas diretas na mesma funcao

    int flag_divide_conquer; //merge/quick, uso de mid/n/2
    int flag_programacao_dinamica; //palavras tipo dp, memo, cache, tabela, triple-loop classico
    int flag_backtracking; //recursao + desmarca/visited + if de validade

    char nome_funcao[256]; //para analisar multiplas funcoes no mesmo arquivo (ultimo nome visto)
} Analise;

typedef void (*FuncaoAlgoritmo)(int n); 
//isso aqui define um tipo de ponteiro de função chamado FuncaoAlgoritmo.
//ponteiros de função são usados para passar funções como argumentos para outras funções, ou para armazenar referências a funções em estruturas de dados
//o typedef cria um novo tipo chamado FuncaoAlgoritmo que representa um ponteiro para uma função que recebe um int e retorna void
//isso é útil para criar funções genéricas que podem aceitar diferentes algoritmos como parâmetros, desde que eles sigam a mesma assinatura (receber um int e retornar void)
//exemplo: se você tiver várias funções que implementam diferentes algoritmos, todas elas podem ser passadas para uma função que mede o tempo de execução, desde que todas sigam essa assinatura
//sendo assim, você pode criar uma função que mede o tempo de execução de qualquer algoritmo que receba um int como parâmetro, sem se preocupar com a implementação específica do algoritmo
//ela servirá nesse algoritmo porque todos os algoritmos que queremos medir recebem um int (tamanho n) e retornam void (não retornam nada)
//ou seja, qualquer função que siga essa assinatura pode ser passada para a função medir_tempo


void algoritmo_simulado_n2(int n) 
{ //O(n^2)
    for (long i = 0; i < n; ++i) 
    {
        for (long j = 0; j < n; ++j) 
        {
            //nada acontece, feijoada
        }
    }
}

void algoritmo_simulado_n_log_n(int n) 
{ //O(n log n)
    for (long i = 0; i < n; ++i) 
    {
        for (long j = 1; j < n; j *= 2) 
        {
            //nada acontece, feijoada
        }
    }
}

void algoritmo_simulado_log_n(int n) 
{
    for (long i = 1; i < n; i *= 2) 
    {
        //nada acontece, feijoada
    }
}

void algoritmo_simulado_n3(int n) { //O(n^3)
    for (long i = 0; i < n; ++i) 
    {
        //por que long? porque se n for grande, int pode não ser suficiente. int vai até 2 bilhões, long vai mais longe, porém nunca iremos usar n tão grande assim
        //mas é uma boa prática usar long para evitar overflow em loops grandes
        //aprendi isso em C++ mas vale para C também, já que C++ é um C orientado a objetos
        //aprendi também na documentação do C, na seção sobre tipos de dados inteiros
        //tem um livro chamado "The C Programming Language" que é a bíblia do C, escrito pelos criadores da linguagem, Brian Kernighan e Dennis Ritchie
        //lá eles explicam sobre tipos de dados e como escolher o tipo certo para evitar problemas
        //outra coisa é que em C, o tamanho de int pode variar dependendo da arquitetura (32 bits, 64 bits), então usar long é mais seguro para loops grandes
        //mas se você tiver certeza que n nunca será tão grande, pode usar int para economizar memória
        for (long j = 0; j < n; ++j) 
        {
            for (long k = 0; k < n; ++k) 
            {
                //nada acontece, feijoada 
            }
        }
    }
}

static void medir_tempo(FuncaoAlgoritmo p_algoritmo, const char *nome_algoritmo) 
{ 
    //aqui espera um ponteiro de função como parâmetro
    //isso permite que a função medir_tempo seja genérica e possa medir o tempo de qualquer algoritmo que siga a assinatura definida por FuncaoAlgoritmo
    //
    printf("\n--- Medindo Performance de: %s ---\n", nome_algoritmo);
    printf("Tamanho (N), Tempo (segundos)\n");

    int limite = 32768; //limite padrão, embora nunca seja usado, mas é pra ficar só de segurança msm

    if (strcmp(nome_algoritmo, "Cubico O(n^3)") == 0) 
    { 
        limite = 2048; //esse aqui eh pesado entao vou usar só 2^11 
    }
    else if (strcmp(nome_algoritmo, "Quadratico O(n^2)") == 0) 
    {
        limite = 262144; 
    }
    else if (strcmp(nome_algoritmo, "Linearitmico O(n log n)") == 0) 
    {
        limite = 33554432; 
    }
    else if (strcmp(nome_algoritmo, "Logaritmico O(log n)") == 0) 
    { 
        limite = 67108864; 
    }

    for (int n = 1; n <= limite; n *= 2) //FUNCAO para contar o tempo de execucao
    { 
        if (n == 0) continue; //se n for 0, pula a iteracao pra nao ter loop infinito, apesar que n é 1 mas boas praticas
        clock_t inicio = clock(); 
        //a funcao clock pode devolver o tempo de CPU usado pelo programa desde que ele começou a rodar
        //por exemplo: se o clock() retornar 1000, significa que o processador já fez 1000 "ticks" desde que o programa começou a rodar
        p_algoritmo(n); 
        //chama o algoritmo que foi passado como parâmetro, executando-o com o tamanho n
        //a funcao p_algoritmo é um ponteiro para a função que implementa o algoritmo que queremos medir
        //a p algoritmo é do tipo FuncaoAlgoritmo, que é um ponteiro para uma função que recebe um int e retorna void
        //ponteiro para funcao é util aqui porque 
        //permite que a funcao medir_tempo seja generica e possa medir o tempo de qualquer algoritmo que siga a mesma assinatura
        clock_t fim = clock();
        double tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        //aqui converte para segundos. o CLOCKS_PER_SEC é uma constante que diz quantos "clocks" o processador faz por segundo.
        //converte p calculo para double pra evitar perda de precisao

        printf("%d, %.6f\n", n, tempo_gasto);
        fflush(stdout); 
        //garante que a saída seja impressa imediatamente
        //nao sei se eh util e vai funcionar mas testando
        if(tempo_gasto > 5.0) 
        {
            printf("Execução demorou mais de 5 segundos. Interrompendo...\n");
            break;
        }
    }
}

// =====================
//algoritmos uteis
// =====================

static char *remove_espaco(char *str) 
{
    while(isspace((unsigned char)*str)) str++;
    //enquanto o caractere atual for espaço em branco, avança o ponteiro para o próximo caractere
    //é sem sinal porque isspace espera um unsigned char ou EOF
    return str;//retorna o ponteiro quando encontrar o primeiro caractere não branco
}

static int eh_ident_inicio(char c){ return isalpha((unsigned char)c) || c=='_'; }
//explicando a linha acima: é uma função que verifica se um caractere pode ser o início de um identificador em C
//ela é static, ou seja, só pode ser usada dentro do arquivo onde foi definida
//ela espera um caractere como parâmetro e retorna um inteiro (1 para verdadeiro, 0 para falso)
//o isalpha verifica se o caractere é uma letra (a-z, A-Z), de um dado sem sinal
//a função retorna verdadeiro se o caractere for uma letra ou um underline _ 
static int eh_ident_parte(char c){ return isalnum((unsigned char)c) || c=='_'; }
//a funcao reotrna verdadeiro se o caractere for uma letra, um dos 10 digitos  ou um underline _

//funcao statica, so eh visivel aqui
//'int': Ela vai retornar um número inteiro. 1 pra OK e 0 pra falha.
// eh um ponteiro pra uma string que contém a linha de código a ser analisada. 
// 'char *saida' eh um ponteiro pra um buffer, um espaço na memória onde a função vai escrever o nome que ela encontrar.
// 'size_t out_sz', eh pra armazenar o tamanho do buffer 'out'. 
static int extrair_nome_funcao(const char *linha, char *saida, size_t out_sz)
{
    // o ponteiro 'p' aponta pro mesmo lugar que o argumento linha
    // ou seja, o p vai ''iterar' na cadeia de caracteres e começa em 0
    const char *p = linha;

    // enquanto o caractere (*p) for um espaço (função isspace), avança o ponteiro (p++)
    // aqui eh pra pula todos os espaços em branco no começo da linha.
    while(*p && isspace((unsigned char)*p)) p++;

    // se msm apos pular tudo, a gente chegou no fim da string ('\0'), então a linha era vazia ou só tinha espaços.
    // retorna 0, encerra
    if (!*p) return 0;

    // se a linha n tem um '(', não pode ser uma funcao.
    if (!strstr(p, "(")) return 0;

    // se a linha contém "if (", "for (", etc., provavelmente é um comando de controle, não uma função.
    if (strstr(p, "if (")) return 0;
    if (strstr(p, "for (")) return 0;
    if (strstr(p, "while (")) return 0;
    if (strstr(p, "switch (")) return 0;

    // 'strchr' encontra a primeira ocorrência de ( na string a partir de 'p'.
    // 'paren' vai apontar pra esse (. se n contiver um (, encerra
    const char *paren = strchr(p, '(');
    if (!paren) return 0;

    // cria um segundo ponteiro, 'q', e posiciona ele um caractere ANTES do '('.
    const char *q = paren - 1;

    // agr andando pra trás a partir da posicao de 'q', pula qualquer espaço em branco.
    // isso lida com casos como "int minha_funcao  (.  
    //a ideia n eh resolver todos as especificidades de alguem programar, mas abrangir a minha as vezes
    while(q > p && isspace((unsigned char)*q)) q--;

    // o end vai guardar a posicao do ultimo caractere do nome da funcao.
    const char *end = q;

    // aqui vai mover o ponteiro 'q' pra trás enquanto ele estiver dentro da string. funciona basicamente como uma lista encadeada
    // e o caractere for uma parte válida de um identificador (letra, número, _).
    while(q > p && eh_ident_parte(*q)) q--;
    //esse eh ident part eh pá verificar se é uma letra, digito ou um underline
    
    //depois do loop, 'q' parou no caractere ANTES do nome da função.
    // dai o nome da função começa em 'q + 1'.
    // Essa linha checa se o primeiro caractere do nome é válido pra iniciar um identificador (não pode ser um número, por exemplo).
    // 'eh_ident_inicio' é outra função que você tem que ter. Se não for válido, retorna 0.
    if (!eh_ident_inicio(*(q + 1))) return 0;

    //Calcula o tamanho do nome encontrado. ta na posição final end menos a posição inicial "q+1", mais 1.
    //aritmética de ponteiros pra voltar
    size_t len = (size_t)(end - (q + 1) + 1);

    // Verificação de segurança. Se o tamanho for 0 ou >= ao tamanho do buffer de saída,
    // algo está errado ou não cabe. Retorna 0 pra evitar problemas.
    if (len == 0 || len >= out_sz) return 0;

    // 'memcpy' copia 'len' bytes da memória, começando da posição 'q+1' (o início do nome)
    // para o buffer de saída 'out'. 
    memcpy(saida, q + 1, len);

    // depois de copiar o nome, adiciona o caractere nulo ('\0') no final.
    saida[len] = '\0';

    // Se chegou até aqui, tudo deu certo. Retorna 1 (sucesso).
    return 1;
}

// =====================
// analise estatica
// =====================

static void resultado(Analise analise)
{
    printf("\n--- Relatorio da Analise Estatica ---\n");
    printf("Total de loops (for/while/do) encontrados: %d\n", analise.loops_encontrados);
    printf("Nivel maximo de aninhamento de loop detectado: %d\n", analise.nivel_max_aninhamento);
    printf("ifs: %d | switch: %d\n", analise.ifs_encontrados, analise.switch_encontrados);
    printf("funcoes recursivas: %d (max auto-chamadas diretas numa func: %d)\n", analise.funcoes_recursivas, analise.max_auto_chamadas_na_mesma_func);
    printf("flags: DC=%d, DP=%d, BT=%d\n", analise.flag_divide_conquer, analise.flag_programacao_dinamica, analise.flag_backtracking);
    /*  DP (Dynamic Programming / Programação Dinâmica):
        quando o problema tá sendo quebrado em subproblemas menores sem recomputar tudo do zero.

        DC (Divide & Conquer / Dividir e Conquistar):
        flag p quando o algoritmo tem recursão que divide a entrada em partes menores e combina o resultado no final 
        (merge sort, quicksort, busca binária)

        BT (Backtracking):
        detectado quando aparece recursão + e tentaiva de voltar atras
        (remover item, desfazer escolha, return false/true no meio). 
    */


    printf("------------------------------------------\n");
    printf("Analise da Complexidade (heuristica):\n");

    // pior caso (O)
    const char *pior = "O(?)";
    if (analise.flag_programacao_dinamica && analise.nivel_max_aninhamento>=3) pior = "O(n^3)"; 
    //se o algoritmo em questao cair nessas duas condições entao ele eh cubico
    else if (analise.max_auto_chamadas_na_mesma_func>=2) pior = "O(2^n)"; //ramificacao >=2 eh classico exponencial
    else if (analise.flag_divide_conquer) pior = "O(n log n)"; //merge/quick pattern
    else if (analise.nivel_max_aninhamento>=2) pior = "O(n^2)";
    else if (analise.loops_encontrados>=1) pior = "O(n)";
    else pior = "O(1)";

    // melhor caso (Omega)
    const char *melhor = "Omega(?)";
    if (analise.loops_encontrados==0 && analise.funcoes_recursivas==0) melhor = "Omega(1)";
    else if (analise.flag_divide_conquer || analise.loops_encontrados>=1) melhor = "Omega(n)"; //na boa, muita coisa eh pelo menos linear


    //eh teta quando ambos limites (inferior e superior) sao iguais
    const char *theta = "Theta(?)";
    if (strcmp(pior,"O(n^2)")==0 && analise.loops_encontrados>=1 && analise.nivel_max_aninhamento>=2) theta = "Theta(n^2)";
    else if (strcmp(pior,"O(n log n)")==0 && analise.flag_divide_conquer) theta = "Theta(n log n)";
    else if (strcmp(pior,"O(n)")==0 && analise.loops_encontrados>=1 && analise.nivel_max_aninhamento<=1 && analise.funcoes_recursivas==0) theta = "Theta(n)";
    else if (strcmp(pior,"O(1)")==0) theta = "Theta(1)";

    printf("Melhor caso (Omega): %s\n", melhor);
    printf("Pior caso (Big-O): %s\n", pior);
    printf("Caso medio (Theta): %s\n", theta);
}


static void analise_buffer(FILE *arquivo)
{
    // essa funçao vai receber o arquivo .c
    // 'memset' zera a memória dessa struct. É uma garantia de que todos os nossos
    // contadores começam em 0, para não termos lixo de memória interferindo.
    Analise analise_global; memset(&analise_global, 0, sizeof(analise_global));

    // um buffer (espaço de memória temporário) para guardar cada linha que lermos do arquivo.
    char linha[2048];

    //flag para identificar se estamos dentor ou fora de funçao
    int dentro_da_funcao = 0;
    // contador para abertura e fechamento de chaves ''{'' e ''}''. Começa em 0. Quando entramos numa
    // função, vai pra 1. Cada ''{'' aumenta, cada ''}'' diminui. Quando volta a 0, saímos da função.
    int nivel_chave_funcao = 0;

    // quando estamos dentro de uma função, precisamos de informações específicas sobre ela.

    //guarda o nome da função que estamos analisando no momento.
    char nome_func_atual[256] = {0};
    //contador para funcoes  e o qnt elas se
    int chamadas_recursivas_na_func = 0;



    // Implementação de uma "pilha". vai ser usada para identificar se o
    // que abrimos é 'L' para Loop ou  'O' para Outra coisa
    char pilha_do_bloco[512];

    // topo da pilha em -1 pq ta vazia
    int topo_pilha = -1;

    //contabilizar o nivel de aninhamento (quantidades de codigo dentro de codigo de ifs e loops)
    int atual_aninhamento = 0;

    //flag que funciona como uma "memória de curto prazo". qnd virmos um 'for' ou 'while',
    // setamos essa flag. A próx '{' que aparecer, saberemos que pertence a um loop.
    int aguardando_bloco_de_loop = 0;

    printf("\nAnalisando arquivo para o relatorio...\n");

    // usei o 'fgets' aq pra lêr uma linha do ''arquivo'' e a colocar no buffer 'linha'
    // o loop vai continuar até 'fgets' não conseguir mais ler linhas (fim do arquivo).
    while (fgets(linha, sizeof(linha), arquivo))
    {

        //aqui a remove espaço vai checar se tem espaço nas linhas do arquivos e limpar
        char *linha_util = remove_espaco(linha);

        //se a linha ficou vazia após a limpeza, não há o que analisar. 'continue' pula para a próxima linha.
        if (linha_util[0]=='\0') continue;

        // se a linha começa com '//', '/*' ou '#', é um comentário ou biblioteca chamada
        if (strncmp(linha_util, "//", 2) == 0) continue;
        if (strncmp(linha_util, "/*", 2) == 0) continue;
        if (linha_util[0] == '#') continue;


        // contar qnts vezes 'if (' e 'switch (' aparecem. contabiliza abertura/inicio de ifs e switches
        if (strstr(linha_util, "if (")) analise_global.ifs_encontrados++;
        if (strstr(linha_util, "switch (")) analise_global.switch_encontrados++;

        // aqui vai procurar por palavras especificas, e se encontrar''merge'', ''partition'', etc., entao psosivelmente eh divisao e conquista
        if (strstr(linha_util, "merge") || strstr(linha_util, "partition") || strstr(linha_util, "mid") || strstr(linha_util, "n/2"))
            analise_global.flag_divide_conquer = 1;
            //condicional de ou e se achar, seta como 1 a flag de que o algoritmo em questao eh divisao se consuiqsta

        if (strstr(linha_util, "dp") || strstr(linha_util, "memo") || strstr(linha_util, "cache") || strstr(linha_util, "tabela") || strstr(linha_util, "table"))
            analise_global.flag_programacao_dinamica = 1;
            //mesma logica acima
        if (strstr(linha_util, "backtrack") || strstr(linha_util, "visited") || strstr(linha_util, "desmarca") || strstr(linha_util, "unmark"))
            analise_global.flag_backtracking = 1;


        char possivel_nome[256];
        //exxtrair nome de função da linha E verificar se há um ''{'' na mesma linha.
        //se ambos os dois estao vddro, entao é uma indicaç'ão de que estamos na funcao
        if (extrair_nome_funcao(linha_util, possivel_nome, sizeof(possivel_nome)) && strchr(linha_util,'{'))
        {
            dentro_da_funcao = 1; //flag pra sinalizar uma funcao
            nivel_chave_funcao = 1; //a chave '{' desta linha nos coloca no nível 1. ou seja, estamos em uma camada de chave
            //copiar o nome da funcao para possivelnome
            strncpy(nome_func_atual, possivel_nome, sizeof(nome_func_atual)-1);
            //zerar as flasgs da análise interna de uma função, para começar a nova análise do zero
            chamadas_recursivas_na_func = 0;
            topo_pilha = -1; atual_aninhamento = 0; aguardando_bloco_de_loop = 0;
            continue; //proxima linha 
        }

        //este bloco de código só é executado se a flag aativada acima que esta dentro da funcao
        if (dentro_da_funcao)
        {
            char *p_for = strstr(linha_util, "for");
            char *p_while = strstr(linha_util, "while");
            char *p_do = strstr(linha_util, "do");

            //aqui no (p_for && !isalnum(*(p_for - 1)) && !isalnum(*(p_for + 3)))
            // vai  checar se 'for' foi encontrado E se os caracteres antes e depois
            // não são letras ou números. Isso evita que a gente detecte 'for' dentro
            // de outras palavras como 'performance' ou 'before'. eh quase como um regex
            if  
            (
                (p_for && !isalnum(*(p_for - 1)) && !isalnum(*(p_for + 3))) ||
                (p_while && !isalnum(*(p_while - 1)) && !isalnum(*(p_while + 5))) ||
                (p_do && !isalnum(*(p_do - 1)) && !isalnum(*(p_do + 2)))
            )
            {
                //passou no se, entao eh um loop. Ligamos a flag para que a próxima '{'
                //seja registrada como um bloco de loop.
                aguardando_bloco_de_loop = 1;
                analise_global.loops_encontrados++;
            } 

            //se existe nome da função atual
            if (nome_func_atual[0] && strstr(linha_util, nome_func_atual))
            {
                //e se esse nome é seguido por um '(', tem uma alta chance de ser
                //uma funcao recursiva
                char *p = strstr(linha_util, nome_func_atual);
                if (p)
                {
                    p += strlen(nome_func_atual); // vança o ponteiro para depois do nome
                    while(*p && isspace((unsigned char)*p)) p++; //pula espaços em branco
                    if (*p=='(') // cnfirma se o que vem a seguir é um parêntese.
                    {
                        chamadas_recursivas_na_func++; //se for eh uma funcao recursiva
                    }
                }
            }

            // se a função eh recursiva e retorna true em algum lugar, pode ser baktracing
            if (strstr(linha_util, "return") && strstr(linha_util, "true"))
                analise_global.flag_backtracking = analise_global.flag_backtracking || (chamadas_recursivas_na_func>0);
        }

        //este loop varre a linha caractere por caractere para fazer a contagem
        //e o gerenciamento de estado dos blocos de código.
        for (int i = 0; linha[i] != '\0'; i++)
        {
            if (linha[i] == '{')
            {
                //se ainda não estávamos em uma função, uma '{' solta pode indicar o inicio de uma
                // porque tipo, meus codigos eu dou um \n. depende muito da formatacao do codder
                if (!dentro_da_funcao)
                {
                    dentro_da_funcao = 1;
                    nivel_chave_funcao = 1;
                    topo_pilha = -1; atual_aninhamento = 0; aguardando_bloco_de_loop = 0;
                } 
                else 
                {
                    //ja q estamos numa função, então esta '{' aumenta o nível de aninhamento
                    nivel_chave_funcao++;
                    if (topo_pilha < (int)(sizeof(pilha_do_bloco)-1)) { 
                        //pra n extrapolar o tamahnho da "pilha "
                        if (aguardando_bloco_de_loop) 
                        {
                            //a flag estava ligada, entao o o '{' pertence a um loop.
                            pilha_do_bloco[++topo_pilha] = 'L'; 
                            //empurra 'L' (Loop) na pilha

                            atual_aninhamento++; 
                            //aumenta o contador de aninhamento de loops

                            //atualiza o máximo de aninhamento dentro do arquivo
                            if (atual_aninhamento > analise_global.nivel_max_aninhamento)
                                analise_global.nivel_max_aninhamento = atual_aninhamento;
                            aguardando_bloco_de_loop = 0; //desliga a flag, 
                        } 
                        else 
                        {
                            //a flag estava desligada. É um bloco qualquer (if, else, etc.), n interesa, mas contabiliza
                            pilha_do_bloco[++topo_pilha] = 'O'; //empurra 'O' (Outro).
                        }
                    }
                }
            }
            else if (linha[i] == '}')//ou seja, eh o fim de um bloco
            {
                if (dentro_da_funcao)
                {
                    nivel_chave_funcao--; //diminui o nível de aninhamento de chaves

                    if (topo_pilha >= 0) //se a pilha não estiver vazia
                    {
                        //entao desempilha o tipo do bloco que está sendo fechado
                        char tipo_do_bloco = pilha_do_bloco[topo_pilha--];

                        //se o bloco que fechado era um loop
                        if (tipo_do_bloco == 'L')
                            atual_aninhamento--; 
                            //reduz o contador de aninhamento de loops.
                    }

                    //se o nível de chaves voltou a zero, significa que ESSA '}' fechou a função inteira.
                    if (nivel_chave_funcao == 0)
                    {
                        dentro_da_funcao = 0;
                        if (chamadas_recursivas_na_func > 0)
                        {
                            analise_global.funcoes_recursivas++;
                            if (chamadas_recursivas_na_func > analise_global.max_auto_chamadas_na_mesma_func)
                                analise_global.max_auto_chamadas_na_mesma_func = chamadas_recursivas_na_func;
                        }
                        //limpa o estado da funcao para a próx
                        nome_func_atual[0] = '\0';
                        chamadas_recursivas_na_func = 0;
                    }
                }
            }
        }
    }
    //deopis de ler o arquivo ta na hora da analise
    // se o aninhamento máximo de loops foi 3 ou mais, é possivel q seja uma 
    // programação dinâmica (tipo algoritmos como Floyd-Warshall q usa  3 fors aninhados).
    if (analise_global.nivel_max_aninhamento >= 3)
        analise_global.flag_programacao_dinamica = analise_global.flag_programacao_dinamica || 1;
    resultado(analise_global);
}

//funcao p abrir o arquivo e enviar p analise
static void analise_estatica_arquivo()
{
    char nome_arquivo[256];//limite de 256
    printf("\nDigite o nome do arquivo .c para a analise: ");
    if (scanf("%255s", nome_arquivo) != 1) { printf("entrada invalida\n"); return; }

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo '%s'.\n", nome_arquivo);
        return;
    }

    analise_buffer(arquivo);
    fclose(arquivo);
}


// =====================
// algoritmos classicos para analise empirica + contagem de operacoes basicas
// (comparacoes, atribuicoes).
// =====================

static volatile long long g_cont_comp = 0; //comparacoes
static volatile long long g_cont_atr  = 0; //atribuicoes/movimentos
static volatile long long g_cont_calls = 0; //chamadas recursivas

static void zera_contadores(){ g_cont_comp=0; g_cont_atr=0; g_cont_calls=0; }

// helpers
static void preenche_array_int(int *v, int n)
{
    //nao vou usar rand() sem seed. ok, seed aqui
    srand(123456);
    for (int i=0;i<n;i++) { v[i] = rand(); }
}

// 1) busca binaria (iterativa)
static int busca_binaria(int *v, int n, int alvo)
{
    int l=0, r=n-1;
    while(l<=r){
        int m = l + (r-l)/2; g_cont_atr++;
        g_cont_comp++; if (v[m]==alvo) return m;
        g_cont_comp++; if (v[m]<alvo) l=m+1; else r=m-1; g_cont_atr+=2;
    }
    return -1;
}

static void medir_busca_binaria(int n)
{
    int *v = (int*)malloc(n*sizeof(int)); if(!v){printf("sem memoria\n");return;}
    //pra busca binaria o vetor precisa estar ordenado
    for (int i=0;i<n;i++) v[i]=i; //ordenado bonitinho
    clock_t ini=clock();
    zera_contadores();
    //procurar um elemento que esta ou nao esta
    int pos = busca_binaria(v, n, n-1);
    (void)pos;
    clock_t fim=clock();
    printf("N=%d, tempo=%.6f s, comps=%lld, atrs=%lld\n", n, (double)(fim-ini)/CLOCKS_PER_SEC, g_cont_comp, g_cont_atr);
    free(v);
}

// 2) insertion sort (iterativo) O(n^2)
static void insertion_sort(int *v, int n)
{
    for (int i=1;i<n;i++){
        int chave=v[i]; g_cont_atr++;
        int j=i-1; g_cont_atr++;
        while (j>=0 && (++g_cont_comp, v[j]>chave)){
            v[j+1]=v[j]; g_cont_atr++;
            j--; g_cont_atr++;
        }
        v[j+1]=chave; g_cont_atr++;
    }
}

static void medir_insertion(int n)
{
    int *v=(int*)malloc(n*sizeof(int)); if(!v){printf("sem memoria\n");return;}
    preenche_array_int(v,n);
    clock_t ini=clock();
    zera_contadores();
    insertion_sort(v,n);
    clock_t fim=clock();
    printf("N=%d, tempo=%.6f s, comps=%lld, movs=%lld\n", n, (double)(fim-ini)/CLOCKS_PER_SEC, g_cont_comp, g_cont_atr);
    free(v);
}

// 3) merge sort O(n log n)
static void merge(int *v, int l, int m, int r)
{
    int n1=m-l+1, n2=r-m; g_cont_atr+=2;
    int *L=(int*)malloc(n1*sizeof(int)); int *R=(int*)malloc(n2*sizeof(int));
    if(!L||!R){printf("sem memoria\n");exit(1);}
    for (int i=0;i<n1;i++){ L[i]=v[l+i]; g_cont_atr++; }
    for (int j=0;j<n2;j++){ R[j]=v[m+1+j]; g_cont_atr++; }
    int i=0,j=0,k=l; g_cont_atr+=3;
    while(i<n1 && j<n2){ g_cont_comp+=2;
        if ((++g_cont_comp, L[i]<=R[j])){ v[k++]=L[i++]; g_cont_atr+=2; }
        else { v[k++]=R[j++]; g_cont_atr+=2; }
    }
    while(i<n1){ g_cont_comp++; v[k++]=L[i++]; g_cont_atr+=2; }
    while(j<n2){ g_cont_comp++; v[k++]=R[j++]; g_cont_atr+=2; }
    free(L); free(R);
}

static void merge_sort_rec(int *v, int l, int r)
{
    g_cont_calls++;
    if (l<r){ g_cont_comp++;
        int m = l+(r-l)/2; g_cont_atr++;
        merge_sort_rec(v,l,m);
        merge_sort_rec(v,m+1,r);
        merge(v,l,m,r);
    }
}

static void medir_merge(int n)
{
    int *v=(int*)malloc(n*sizeof(int)); if(!v){printf("sem memoria\n");return;}
    preenche_array_int(v,n);
    clock_t ini=clock();
    zera_contadores();
    merge_sort_rec(v,0,n-1);
    clock_t fim=clock();
    printf("N=%d, tempo=%.6f s, comps=%lld, movs=%lld, calls=%lld\n", n, (double)(fim-ini)/CLOCKS_PER_SEC, g_cont_comp, g_cont_atr, g_cont_calls);
    free(v);
}

// 4) Floyd-Warshall O(n^3)
static void floyd_warshall_run(int n)
{
    int INF = 1000000000;
    int **dist = (int**)malloc(n*sizeof(int*));
    for (int i=0;i<n;i++){
        dist[i]=(int*)malloc(n*sizeof(int));
        for (int j=0;j<n;j++){
            if (i==j) dist[i][j]=0; else dist[i][j]=(i+j)%7+1; //peso besta
        }
    }
    for (int k=0;k<n;k++){
        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                //contagem basica
                g_cont_comp+=2; //duas comparacoes no if
                int via = dist[i][k]+dist[k][j]; g_cont_atr++;
                if (via < dist[i][j]){ g_cont_comp++; dist[i][j]=via; g_cont_atr++; }
            }
        }
    }
    for (int i=0;i<n;i++) free(dist[i]);
    free(dist);
}

static void medir_floyd(int n)
{
    clock_t ini=clock();
    zera_contadores();
    floyd_warshall_run(n);
    clock_t fim=clock();
    printf("N=%d, tempo=%.6f s, ops_aprox=%lld\n", n, (double)(fim-ini)/CLOCKS_PER_SEC, g_cont_comp+g_cont_atr);
}

// 5) N-Queens backtracking (conta solucoes)
static int nqueens_count;

static int nqueens_valido(int *col, int linha, int c)
{
    for (int i=0;i<linha;i++){
        g_cont_comp+=3; //comparacoes: coluna, diag1, diag2 
        if (col[i]==c || (i - col[i])==(linha - c) || (i + col[i])==(linha + c))
            return 0;
    }
    return 1;
}

static void nqueens_bt(int *col, int n, int linha)
{
    g_cont_calls++;
    if (linha==n){ nqueens_count++; return; }
    for (int c=0;c<n;c++){
        if (nqueens_valido(col,linha,c)){
            col[linha]=c; g_cont_atr++;
            nqueens_bt(col,n,linha+1);
            //desfazer
            col[linha]=-1; g_cont_atr++;
        }
    }
}

static void medir_nqueens(int n)
{
    int *col=(int*)malloc(n*sizeof(int)); if(!col){printf("sem memoria\n");return;}
    for (int i=0;i<n;i++) col[i]=-1;
    clock_t ini=clock();
    zera_contadores(); nqueens_count=0;
    nqueens_bt(col,n,0);
    clock_t fim=clock();
    printf("N=%d, tempo=%.6f s, calls=%lld, solucoes=%d\n", n, (double)(fim-ini)/CLOCKS_PER_SEC, g_cont_calls, nqueens_count);
    free(col);
}

static void analise_tempo() 
{
    int escolha = 0;
    printf("\n--- Analise do Tempo do algoritmo (simulados) ---\n");
    printf("Qual algoritmo simulado voce quer medir?\n");
    printf("1. Algoritmo Quadratico O(n^2)\n");
    printf("2. Algoritmo Linearitmico O(n log n)\n");
    printf("3. Algoritmo Logaritmico O(log n)\n");
    printf("4. Algoritmo Cubico O(n^3)\n");
    printf("Escolha: ");
    if (scanf("%d", &escolha)!=1){ printf("entrada invalida\n"); return; }

    switch (escolha) 
    {
        case 1:
            medir_tempo(algoritmo_simulado_n2, "Quadratico O(n^2)");
            break;
        case 2:
            medir_tempo(algoritmo_simulado_n_log_n, "Linearitmico O(n log n)");
            break;
        case 3:
            medir_tempo(algoritmo_simulado_log_n, "Logaritmico O(log n)");
            break;
        case 4:
            medir_tempo(algoritmo_simulado_n3, "Cubico O(n^3)");
            break;
        default:
            printf("Opcao invalida.\n");
    }
}

static void analise_empirica_classicos()
{
    int op=0; printf("\n--- Algoritmos classicos (execucao real) ---\n");
    printf("1. Busca Binaria\n");
    printf("2. Insertion Sort\n");
    printf("3. Merge Sort\n");
    printf("4. Floyd-Warshall\n");
    printf("5. N-Queens (backtracking)\n");
    printf("Escolha: "); if (scanf("%d", &op)!=1){printf("invalido\n");return;}

    int limite = 1; //começa pequeno e dobra
    switch(op){
        case 1: limite=1<<24; printf("N, tempo, comps, atrs\n"); for(int n=2; n<=limite; n*=2){ medir_busca_binaria(n); if (n>2 && n%2==0) fflush(stdout);} break;
        case 2: limite=1<<16; printf("N, tempo, comps, movs\n"); for(int n=128;n<=limite;n*=2){ medir_insertion(n); if (n>128) fflush(stdout); if (n>=1<<15) break; } break;
        case 3: limite=1<<22; printf("N, tempo, comps, movs, calls\n"); for(int n=128;n<=limite;n*=2){ medir_merge(n); if (n>1<<21) break; } break;
        case 4: limite=1024; printf("N, tempo, ops_aprox\n"); for(int n=16;n<=limite;n*=2){ medir_floyd(n); if (n>=512) fflush(stdout); } break;
        case 5: limite=18; printf("N, tempo, calls, solucoes\n"); for(int n=4;n<=limite;n++){ medir_nqueens(n); if ((double)clock()/CLOCKS_PER_SEC>5.0) {printf("\n"); break;} } break;
        default: printf("Opcao invalida\n");
    }
}

static void comparar_ordenacoes()
{
    // compara insertion vs merge pra mesma N. saida lado a lado
    printf("\n--- Comparacao: Insertion x Merge ---\n");
    printf("N, insertion_tempo, merge_tempo\n");
    for (int n=256; n<= (1<<16); n*=2){
        int *a=(int*)malloc(n*sizeof(int)); int *b=(int*)malloc(n*sizeof(int));
        if(!a||!b){printf("sem memoria\n"); return;}
        preenche_array_int(a,n);
        memcpy(b,a,n*sizeof(int));
        clock_t i1=clock(); zera_contadores(); insertion_sort(a,n); clock_t i2=clock();
        double t_ins=(double)(i2-i1)/CLOCKS_PER_SEC;
        clock_t m1=clock(); zera_contadores(); merge_sort_rec(b,0,n-1); clock_t m2=clock();
        double t_mer=(double)(m2-m1)/CLOCKS_PER_SEC;
        printf("%d, %.6f, %.6f\n", n, t_ins, t_mer);
        free(a); free(b);
        if (t_mer>5.0) break; 
    }
}

// =====================
// menu principal
// =====================

int main() //menu de esclha
{
    int escolha = 0;

    while (1) 
    {
        printf("\n========= ANALISADOR DE ALGORITMOS =========\n");
        printf("1. Analise Estatica (arquivo .c)\n");
        //printf("2. Analise Estatica (pseudocodigo - colar)\n");
        printf("2. Funcao nao implementada\n");
        printf("3. Analise Empirica (simulados O(n), O(n log n), etc)\n");
        printf("4. Algoritmos Classicos (execucao real + contagem basica)\n");
        printf("5. Comparar Insertion x Merge\n");
        printf("6. Sair\n");
        printf("========================================================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &escolha) != 1) 
        {
            while(getchar() != '\n'); //quebra de linha para limpar o buffer do teclado se o usuario digitar algo que nao seja numero
            escolha = 0; 
        }

        switch (escolha) 
        {
            case 1:
                analise_estatica_arquivo(); 
                //a analise estatica consiste em analisar o codigo fonte e contar loops e aninhamentos
                break;
            case 2:
                //analise_estatica_pseudocodigo(); //tentar fazer depois
                printf("Funcao ainda nao implementada.\n");
                break;
            case 3:
                analise_tempo();
                //essa funcao mede o tempo de execucao de algoritmos simulados
                break;
            case 4:
                analise_empirica_classicos();
                //executa algs reais classicos e imprime tempo e contadores basicos
                break;
            case 5:
                comparar_ordenacoes();
                break;
            case 6:
                printf("\nSaindo.\n");
                return 0;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    }
    return 7;
}

//USAR O CAMINHO C:\Users\SeuUsuario\Desktop\analisador.c
//no meu caso: C:\Users\Lucas\Downloads\exerc\.vscode\analise_de_algoritmo\bubbleSortrecursivo.c