#include <stdio.h>
#include <stdlib.h>

//Fun��o ler arquivo
void le_arquivo(char *nome, int mat[9][9]){
    FILE *arq = fopen(nome,"r");

    if(arq == NULL){
        printf("Erro de leitura\n");
        system("pause");
        exit(1);
    }

    int i,j;
    for(i=0; i< 9; i++)
        for(j=0; j< 9; j++)
            fscanf(arq,"%d",&mat[i][j]);

    fclose(arq);
}

//Fun��o para imprimir a matriz
void imprimiMatriz(int sudoku[9][9]){

    int i, j;

    for(i=0; i< 9; i++){
        for(j=0; j< 9; j++){
            printf("[%d]",sudoku[i][j]);
        }
        printf("\n");
    }
}

// Fun�ao que encontra posi��o de i e j e tamanho (final) para mapear um espa�o 3 por 3 da matriz
void encontraCubo(int pos, int *i, int *tamanho){

    if((pos >= 0 && pos <= 2)){
        *i = 0;
        *tamanho = 3;
    }else if((pos >= 3 && pos <= 5)){
        *i = 3;
        *tamanho = 6;
    }else {
        *i = 6;
        *tamanho = 9;
    }
}

//Fun��o verifica linha, coluna e matriz 3X3 se o numero se repete
void resolveSudoku(int sudoku[9][9], int posi, int posj){

    int num = 1, valor, i, j, naoTemNum = 0;

    // testa valor de 1 a 9 na posi��o da matriz onde o valor eh 0;
    while(num < 10){

        int temNum = 0;
        for(i = 0; i < 9; i++){
            //Verificando a linha se tem num
            if(sudoku[posi][i] == num){
                temNum = 1;
                break;
            }
            //Verifica a coluna se tem num
            if(sudoku[i][posj] == num){
                temNum = 1;
                break;
            }
        }

        int i2, j2, tamanhoi = 0, tamanhoj = 0, stop = 0;


        // Encontrar valores de i e j do cubo referente a posi��o
        encontraCubo(posi, &i2, &tamanhoi);
        encontraCubo(posj, &j2, &tamanhoj);


        // Verifica matriz 3x3 se tem num
        for(i = i2; i < tamanhoi; i++){
            for(j = j2; j < tamanhoj; j++ ){

                if(sudoku[i][j] == num){
                    temNum = 1;
                    stop = 1;
                    break;
                }
            }
            if(stop == 1){
                break;
            }
        }

        // Se n�o tiver num, variavel conta quantos valores cabem na posi��o
        if(temNum == 0){
            naoTemNum++;
            valor = num;
        }
        num++;
    }
    // Fim while

        // Se existir apenas 1 numero para posi��o, armazena valor na posi��o
        if(naoTemNum == 1){
            sudoku[posi][posj] = valor;
        }
}

// Funcao armazena posaicao onde o valor � zero na matriz
int ArmazenaPosZero(int sudoku[9][9]){

    int i, j, v1 = 0, qtdZero = 0;

    //Contando os zeros na matriz
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(sudoku[i][j] == 0){
                qtdZero++;
            }
        }
    }

    // Vetores para armazenar posi��o das celulas com valor 0;
    int vetori[qtdZero], vetorj[qtdZero];

    // Armazenar as posicoes nos vetores onde a celula � zero
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(sudoku[i][j] == 0){
                vetori[v1] = i;
                vetorj[v1] = j;

                v1++;
            }
        }
    }

    // Para cada posi��o em que a matriz eh zero chama a fun��o resolve sudoku
    for(i = 0; i < qtdZero; i++){
        resolveSudoku(sudoku, vetori[i], vetorj[i]);
    }

    //Retorna quantidade de zero na matriz
    return qtdZero;
}

//Fun��o principal
int main(){

    int mat[9][9], qtdZero = 1;
    le_arquivo("sudoku.txt", mat);

    // Imprimir matriz
    printf("\nSUDOKU:\n");
    imprimiMatriz(mat);

    // Repetir fun��o at� que n�o reste celula com valor zero
    while(qtdZero != 0){
       qtdZero = ArmazenaPosZero(mat);
    }

    // Imprimindo matriz
    printf("\nRESOLVIDO:\n");
    imprimiMatriz(mat);

    return 0;
}

