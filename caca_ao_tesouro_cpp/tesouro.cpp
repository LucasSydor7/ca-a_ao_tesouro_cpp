#include <iostream> 
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

const int max_linhas = 20;
const int max_colunas = 20;
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
    for (int i = 0; i < qnt_players; i++) {
        cout << "Digite o nome do jogador " << i + 1 << ": ";
        cin >> jogadores[i].nome;
        cout << "Digite o símbolo do jogador " << i + 1 << ": ";
        cin >> jogadores[i].simbolo;
        jogadores[i].pontuacao = 0; // Pontuação inicial zerada
    }
}

// Função para criar a matriz do jogo
void preencher_matriz(int matriz[max_linhas][max_colunas]) {
    for (int i = 0; i < max_linhas; i++) {
        for (int j = 0; j < max_colunas; j++) {
            matriz[i][j] = 0; // Inicializar a matriz com zeros
        }
    }
}

void escolher_dificuldade(int &linhas, int &colunas) {
    int dificuldade;
    cout << "Escolha a dificuldade:\n";
    cout << "1 - Normal (6x6)\n";
    cout << "2 - Personalizado\n";
    cout << "Escolha a Dificuldade: ";
    cin >> dificuldade;
    switch (dificuldade) {
        case 1:
            linhas = 6;
            colunas = 6;
            break;
        case 2:
            do {
                cout << "Informe o numero de linhas(maximo " << max_linhas << ")" << endl;
                cin >> linhas;
            } while (linhas <= 0 || linhas > max_linhas);

            do {
                cout << "Digite o numero de colunas (maximo " << max_colunas << ")" << endl;
                cin >> colunas;
            } while (colunas <= 0 || colunas > max_colunas);
            break;
        default:
            cout << "Dificuldade invalida! (utilizando a dificuldade normal)" << endl;
            linhas = 6;
            colunas = 6;
            break;
    }
}

//distribuir os itens na matriz
void distribuir_items(char campo[max_linhas][max_colunas], int nDiamantes, int nBonus, int nArmadilhas) {
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
void imprimir_matriz(int matriz[max_linhas][max_colunas], int linhas, int colunas) {
    cout << "  "; // Espaço para alinhar com os números das linhas
    for (int j = 0; j < colunas; j++) {
        cout << char('A' + j) << " "; // Imprime a letra correspondente à coluna
    }
    cout << endl;
    for (int i = 0; i < linhas; i++) {
        cout << i + 1 << " "; // Mostra o número das linhas
        for (int j = 0; j < colunas; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

int converterColuna(char colunaLetra){
    return colunaLetra - 'A' + 1;
}

int main(){
    int matriz [max_linhas][max_colunas];
    int qnt_players;
    int linhas,colunas;

    escolher_dificuldade(linhas, colunas);

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
    colunaNumerica = converterColuna(colunaLetra);

    if (linha >= 1 && linha <= linhas && colunaNumerica >= 1 && colunaNumerica < colunas) {
        matriz[linha - 1][colunaNumerica - 1] = '+';
        imprimir_matriz(matriz,linhas,colunas);

    } else {
        cout << "Posicao invalida!" << endl;
    }

    return 0;
}