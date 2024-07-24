#include <iostream> 
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

//a base para o cadastro dos players
struct player {
    string nome;
    char simbolo;
    int pontuacao;
};

struct evento {
    char tipo; //vai utilizar o B para definir os Bonus e A para armadilhas,
    int pontos;
    int linha;
    int coluna;
};

//cadastrar os players
void cadastrarJogadores(player jogadores[], int qnt_players) {
    for(int i = 0; i < qnt_players; i++){
        cout << "Digite o nome do jogador " << i + 1 << ": ";
        cin >> jogadores[i].nome;
        cout << "Digite o simbolo do jogador " << i + 1 << ": ";
        cin >> jogadores[i].simbolo;
        jogadores[i].pontuacao = 0; //define a pontuacao inicial em zero
    }
}
//criacao da matriz
void preencher_matriz(int matriz[6][6]){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
           matriz[i][j] = 1 * 6 + j + 1;
        }
    }
}

//distribuir os itens na matriz
void distribuir_items(char campo[6][6], int nDiamantes, int nBonus, int nArmadilhas) {
    srand(time(0));//randomiza os numeros

    int itensColocados = 0;

    while(itensColocados < nDiamantes + nBonus + nArmadilhas){
        int linha = rand() % 6;
        int coluna = rand() % 6;

        if(campo[linha][coluna] == 0){
            campo[linha][coluna] = 1;
            itensColocados++;
        }
    }
}


//mostrar a matriz na tela (teste)
void imprimir_matriz(int matriz[6][6], int linhas, int colunas) {
    cout << "" << endl;
    for (int j = 0; j < colunas; j++) {
        cout << char('A' + j) << " "; //tentando automatizar as colunas com identificacao (tipo primeira coluna como A e etc...)
    }
    cout << endl;
    for (int i = 0; i < linhas; i++) {
        cout << i + 1 << " "; // mostra o numero das linhas como 1, 2, 3, etc...
        for (int j = 0; j < colunas; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    int matriz [6][6];
    int qnt_players;
    int dificuldade,linhas,colunas;

    cout << "escolha a dificuldade (1 - Facil, 2 - Normal, 3 - Dificil): " << endl;
    cin >> dificuldade;
//define a dificuldade, aumenta ou diminui o tamanho da matriz (os valores sao padronizados entre 6x6,7x7 e 8x8)
    switch(dificuldade){
        case 1:
            linhas = 6;
            colunas = 6;
            break;
        case 2:
            linhas = 7;
            colunas = 7;
            break;
        case 3:
            linhas = 8;
            colunas = 8;
            break;
        default:
            cout << "Dificuldade invalida! (Usando a Dificuldade Facil Como Padrao)" << endl;
            linhas = 6;
            colunas = 6;
    }
    //escolhe a quantidade de players, n pode ser jogador unico ou mais q quatro(no momento)
    do{
        cout << "Digite a quantidade de players(2-4)" << endl;
        cin >> qnt_players; 
    } while(qnt_players < 2 || qnt_players > 4);

    //chama as funcoes 
    player jogadores[qnt_players];
    cadastrarJogadores(jogadores, qnt_players); 
    preencher_matriz(matriz);
    imprimir_matriz(matriz,linhas,colunas);

    int linha,colunaNumerica;

    char colunaLetra;
    cout << "Escolha uma posicao (ex: 2 B): " << endl;
    cin >> linha >> colunaLetra;
    colunaNumerica = colunaLetra - 'A';

    if (linha >= 1 && linha <= linhas && colunaNumerica >= 0 && colunaNumerica < colunas) {
        matriz[linha - 1][colunaNumerica] = '+';
        imprimir_matriz(matriz,linhas,colunas);

    } else {
        cout << "Posicao invalida!" << endl;
    }

    return 0;
}