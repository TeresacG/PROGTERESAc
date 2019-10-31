#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 9

int inicia_matriz(char matriz[DIM][DIM]);

int ler_coordenadas(int n1, int n2, char ch, FILE *cp, char matriz[DIM][DIM], FILE *np, char linha[100]);

void abrir_ficheiro(char matriz[DIM][DIM], char linha[100], FILE *np);

void deteta_erro_coordenadas_1(int n1, int n2, char ch, int *v, FILE *np, char linha[100]);

void deteta_erro_coordenadas_2(int l, int c, char matriz[DIM][DIM], int *v, FILE *np, char linha[100]);

void deteta_erro_caracteres_1(int n1, int n2, char ch, int *v, FILE *np, char linha[100]);

void deteta_mesmo_numero_func_aero(int a, int b, char *ch, FILE *np);

int deteta_erro_1(int a, int b);

int deteta_erro_2(char matriz[DIM][DIM], FILE *np, char linha[100]);

int deteta_erro_3(char matriz[DIM][DIM], FILE *np, char linha[100]);

int main(void) {

    char matriz[DIM][DIM];
    char linha[100];
    char vetor[100];
    FILE *fp; //apontador para o ficheiro distribuicoes //
    FILE *np; // apontador para o subficheiro aberto depois do distribuicoes//
    fp = fopen("distribuicoes.txt", "r");
    if (fp == NULL) {
        fprintf(stdout, "ERRO. Ficheiro vazio.\n"); /* Verificacao da leitura do ficheiro*/
        return 0;}

    np = fopen("resultados.txt", "w"); /*abertura do subficheiro*/

    if (np == NULL){
        printf("Erro na criacao do ficheiro."); /* verificacao da leitura do ficheiro*/
        return 0;}

    while (fgets(vetor, 100, fp) != NULL){
        sscanf(vetor, "%s", linha);         /* eenquanto a leitura das linhas do ficheiro distribuicoes nao der erro, vai ser feita a leitura linha a linha do conteudo do ficheiro*/
        abrir_ficheiro(matriz, linha, np);}

    fclose(fp); //vao ser fechados ambos os ficheiros abertos //
    fclose(np);

return 0;
}

int inicia_matriz(char matriz[DIM][DIM]) {

    int l, c, i;
    for (i = 1; i <= 8; i++){  /* imprime a linha 0 e coluna 0 com os numeros correspondentes as coordenadas*/
        matriz[0][i] = '0' + i - 1;
        matriz[i][0] = '0' + i - 1;}

    for (l = 1; l <= 8; l++){     /* esta funcao ira iniciar a matriz apenas com pontos, antes sequer de serem lidas as coordenadas contidas no ficheiro */
        for (c = 1; c <= 8; ++c){
            matriz[l][c] = '.';}}

return 0;
}

void abrir_ficheiro(char matriz[DIM][DIM], char linha[100], FILE *np) {
/*funcao onde é aberto o subficheiro, indicando o seu nome, e onde sao testados os erros logicos rlativos a distribuicao*/
    int n1=0, n2=0, i, j;
    int resultado;
    char ch='\0';
    FILE *cp;
    cp = fopen(linha, "r"); /*abertura do ficheiro*/

    printf("Distribuicao (%s)\n", linha);

    inicia_matriz(matriz);
    resultado = ler_coordenadas(n1, n2, ch, cp, matriz, np, linha);

    if (resultado != 1){             /*se o resultado for diferente de 1, significa que o erro anterior nao foi verificado */

        resultado = deteta_erro_2(matriz, np, linha);} /*e portanto passamos para a verificacao do erro seguinte*/

    if (resultado != 1){
        resultado = deteta_erro_3(matriz, np, linha);}

    if(resultado!= 1){
        printf("OK!\n");
        fprintf(np, "%s:\nOK!\n", linha);}


    fclose(cp);
}

int ler_coordenadas(int n1, int n2, char ch, FILE *cp, char matriz[DIM][DIM], FILE *np, char linha[100]) {

    int vr, v = 0, a = 0, b = 0;
    int i, j;

    if (cp == NULL){
        printf("ERRO. Ficheiro vazio.\n");
        fprintf(np, "%s:\nERRO. Ficheiro vazio.\n", linha);
        return 0;}




    vr = fscanf(cp, "%d %d %c", &n1, &n2, &ch);
    while (vr != -1){
        /* o flow  do loop abaixo e e o seguinte:

        *      - Executar código dentro do loop (1ª vez)
        *      - Ler linha seguinte (2ª linha)
        *     - Verificação do while
        *      - Executar código dentro do loop (2ª vez)
        *      - Ler linha seguinte (3ª linha).......

        * Falta só ler a primeira linha, pelo que há que adicionar essa linha antes do while */

        if (vr == 3){
            deteta_erro_coordenadas_1(n1, n2, ch, &v, np, linha);
            deteta_erro_caracteres_1(n1, n2, ch, &v, np, linha);}
        if (v == 0){
            matriz[n1 + 1][n2 + 1] = ch;}

        if (ch == '*')
            /* a-contador do numero de aeronaves
            * b-contador do numero de funcionarios */
            a = a + 1;
        else
            if (ch == 'V')
                b = b + 1;

    vr = fscanf(cp, "%d %d %c", &n1, &n2, &ch);}

    for (i = 0; i < DIM; i++){

        for (j = 0; j < DIM; j++){
            printf("%c ", matriz[i][j]);}
        printf("\n");}
     if (vr == 3){
            deteta_erro_coordenadas_1(n1, n2, ch, &v, np, linha);
            deteta_erro_caracteres_1(n1, n2, ch, &v, np, linha);}
        if (v == 0){
            matriz[n1 + 1][n2 + 1] = ch;}

    if (deteta_erro_1(a, b) == 1){
        printf("Erro. Numero de funcionarios diferente de numero de aeronaves\nFuncionários: %d\nAeronaves: %d\n", a, b);
        fprintf(np, "%s:\nErro. Numero de funcionarios diferente de numero de aeronaves\nFuncionários: %d\nAeronaves: %d\n", linha, a, b);
        return 1;}
    return 0;
}

void deteta_erro_coordenadas_1(int n1, int n2, char ch, int *v, FILE *np, char linha[100]){
/* Deteta se as coordenadas se encontram entre 0 e 7*/
    if (n1 < 0 || n1 > 7 || n2 < 0 || n2 > 7){
        printf("Coordenadas invalidas");
        fprintf(np, "%s:\n Coordenadas invalidas", linha);
        *v = 1;} /*Apontador para passar para o erro seguinte*/
}

void deteta_erro_coordenadas_2(int l, int c, char matriz[DIM][DIM], int *v, FILE *np, char linha[100]){

    if ((matriz[l][c] == '*') && (matriz[l][c] == 'V')){ /* esta funcao ira verificar se esta atribuida uma aeronave e um funcionario para as mesmas coordenadas */
        printf("ERRO. Coordenadas invalidas");
        fprintf(np, "%s:\n Coordenadas invalidas", linha);
        *v = 1;} // retorna um se o erro for detetado//
}

void deteta_erro_caracteres_1(int n1, int n2, char ch, int *v, FILE *np, char linha[100]){

    if (ch != '*' && ch != 'V'){ /* se o caracter lido for diferente de * e V as cooordenadas serao invalidas */
        printf("Caracter invalido");
        fprintf(np, "%s:\n Caracter invalido", linha);
        *v = 1;} //apontador para a funcao abrir ficheiro, utilizado com a variavel resultado
}

int deteta_erro_1(int a, int b){

    if (a != b) /* apos terem sido contados o numero de aeronaves e o numero de funcionarios, se este for diferente, a funcao retorna 1, ou seja, foi detetado o erro um */
        return 1;
return 0;
}

int deteta_erro_2(char matriz[DIM][DIM], FILE *np, char linha[100]){

    int contador, l, c, r;
    /*O que esta funcao ira executar e o seguinte:
    *ira verificar se nas posicoes em redor de uma aeronave arbitrarea existe algum funcionario.
    * se existir, o contador incrementa um. o contrario se nao existir.
    *quando encontra um funcionario, a aeronave e o respetivo funcionario passa a pontos, o que verifica se um funcionario enontrado posteriormente
    * ja nao ira ter uma aeronave, indicando erro.
    *a variavel r funciona como um interruptor, passando a funcao para a condicao seguinte se este for igual a 1 */

    for (l = 1; l < 9; l++){
        for(c = 1; c < 9; c++){
            if (matriz[l][c] == 'V'){
                r = 0;
                contador = 0;
                if(((l - 1) >= 1) && (matriz[l - 1][c] == '*') && (r = 0))
                {
                    contador = contador + 1;
                    r = 1;
                    matriz[l][c] = '.';
                    matriz[l-1][c] = '.';
                }

                if(((c - 1) >= 1) && (matriz[l][c - 1] == '*'))
                {
                    contador = contador + 1;
                    r = 1;
                    matriz[l][c] = '.';
                    matriz[l][c-1] = '.';
                }

                if(((c + 1) <= 7) && (matriz[l][c + 1] == '*'))
                {
                    contador = contador + 1;
                    r = 1;
                    matriz[l][c] = '.';
                    matriz[l][c+1] = '.';
                }

                if((l + 1 <= 7) && (matriz[l + 1][c] == '*'))
                {
                    contador = contador + 1;
                    r = 1;
                    matriz[l][c] = '.';
                    matriz[l+1][c] = '.';
                }

                if(contador == 0) {
                    printf("Erro. Não há nenhum funcionário atribuído a aeronave nas coordenadas (%d, %d)\n", l - 1, c - 1);
                    fprintf(np, "%s:\nErro. Não há nenhum funcionário atribuído a aeronave nas coordenadas (%d, %d)\n", linha, l - 1, c - 1);
                    return 1;}

                }
            }
    }


return 0;
}

int deteta_erro_3(char matriz[DIM][DIM], FILE *np, char linha[100])
  { /* Verifica se ha um funcionario atribuido a cada aeronave*/
    int l2 = -1, c2 = -1;
    int l, c;
    for (l = 1; l <= 8; l++){ /*Verifica se para cada posicao imediatamente acima, abaixo, do lado esquerdo ou do lado direito ou nas diagonais encontra um funcionario */
        for (c = 1; c <= 8; c++){
            if (matriz[l][c] == '*'){
                if (((l - 1) >= 1) && (matriz[l - 1][c] == '*')){
                    l2 = l - 1;
                    c2 = c;}
                if (((c - 1) >= 1) && (matriz[l][c - 1] == '*')){
                    l2 = l;
                    c2 = c - 1;}
                if (((c + 1) <= 8) && (matriz[l][c + 1] == '*')){
                    l2 = l;
                    c2 = c + 1;}
                if ((l + 1 <= 8) && (matriz[l + 1][c] == '*')){
                    l2 = l + 1;
                    c2 = c;}

                if (l2 != -1){
                    printf("Erro. Funcionário em (%d, %d) está adjacente ao funcionário em (%d, %d)\n", l2 - 1, c2 - 1, l - 1, c - 1);
                    fprintf(np, "%s:\nErro. Funcionário em (%d, %d) está adjacente ao funcionário em (%d, %d)\n", linha, l2 - 1, c2 - 1, l - 1, c - 1);
                    return 1;}
            }
        }
    }
    return 0;
}
