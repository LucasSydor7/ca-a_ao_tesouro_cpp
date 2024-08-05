#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <iomanip>

using namespace std;

const int max_linhas = 20;
const int max_colunas = 20;

// Estrutura para representar um jogador
struct player {
    string nome;
    char simbolo;
    int pontuacao;
    bool bonus_diamante_duplo;
    int jogadas_extras;
};

// Função para cadastrar os jogadores
void cadastrarJogadores(player jogadores[], int qnt_players) {
    for (int i = 0; i < qnt_players; i++) {
        cout << "Digite o nome do jogador " << i + 1 << ": ";
        cin >> jogadores[i].nome;
        cout << "Digite o símbolo do jogador " << i + 1 << ": ";
        cin >> jogadores[i].simbolo;
        jogadores[i].pontuacao = 0;
        jogadores[i].bonus_diamante_duplo = false;
        jogadores[i].jogadas_extras = 0;
        cout << "Jogador " << jogadores[i].nome << " escolheu o símbolo: " << jogadores[i].simbolo << endl;
    }
}

// Função para criar a matriz do jogo
void preencher_matriz(char matriz[max_linhas][max_colunas], int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = '0';
        }
    }
}

// Função para escolher a dificuldade do jogo
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

// Função para gerar um número aleatório entre min e max
int gerar_numero_aleatorio(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Função para distribuir os itens (diamantes, bônus e armadilhas) no tabuleiro
void distribuir_itens(char matriz[][max_colunas], int linhas, int colunas, int nDiamantes, int nBonus, int nArmadilhas) {
    srand(time(0));

    // Distribui os diamantes
    while (nDiamantes > 0) {
        int linha = gerar_numero_aleatorio(0, linhas - 1);
        int coluna = gerar_numero_aleatorio(0, colunas - 1);
        if (matriz[linha][coluna] == '0') {
            matriz[linha][coluna] = 'D';
            nDiamantes--;
        }
    }

    // Distribui os bônus
    while (nBonus > 0) {
        int linha = gerar_numero_aleatorio(0, linhas - 1);
        int coluna = gerar_numero_aleatorio(0, colunas - 1);
        if (matriz[linha][coluna] == '0') {
            matriz[linha][coluna] = 'B';
            nBonus--;
        }
    }

    // Distribui as armadilhas
    while (nArmadilhas > 0) {
        int linha = gerar_numero_aleatorio(0, linhas - 1);
        int coluna = gerar_numero_aleatorio(0, colunas - 1);
        if (matriz[linha][coluna] == '0') {
            matriz[linha][coluna] = 'A';
            nArmadilhas--;
        }
    }
}

// Função para obter o código de cor ANSI
string getCorANSI(char item) {
    switch (item) {
        case 'B': return "\033[32m"; // Verde
        case 'A': return "\033[33m"; // Amarelo
        case 'D': return "\033[34m"; // Azul
        default: return "\033[0m"; // Reset
    }
}

// Função para imprimir a matriz do jogo, revelando os itens que foram descobertos
void imprimir_matriz(char matriz[][max_colunas], int linhas, int colunas, bool itensRevelados[max_linhas][max_colunas]) {
    // Cabeçalho da coluna
    cout << "  ";
    for (char c = 'A'; c <= 'A' + colunas - 1; c++) {
        cout << "\033[34m" << setw(2) << c << "\033[0m";
    }
    cout << endl;

    // Linhas da matriz
    for (int i = 0; i < linhas; i++) {
        cout << "\033[34m" << setw(2) << i + 1 << "\033[0m" << " "; 
        for (int j = 0; j < colunas; j++) {
            if (itensRevelados[i][j]) {
                cout << getCorANSI(matriz[i][j]) << matriz[i][j] << "\033[0m" << " "; 
            } else {
                cout << "\033[37m" << "0" << "\033[0m" << " "; 
            }
        }
        cout << endl;
    }
}

// Função para converter uma letra de coluna para um número
int converterColuna(char colunaLetra){
    return colunaLetra - 'A' + 1;
}

// Função para verificar se uma posição é válida
bool posicaoValida(int linha, int coluna, int linhas, int colunas) {
    return linha >= 1 && linha <= linhas && coluna >= 1 && coluna <= colunas;
}

// Função para verificar se um jogador ganhou
bool verificaVitoria(char tabuleiro[max_linhas][max_colunas], char simbolo, int linhas, int colunas) {
    // Verifica linhas
    for (int i = 0; i < linhas; i++) {
        if (tabuleiro[i][0] == simbolo && tabuleiro[i][1] == simbolo && tabuleiro[i][2] == simbolo) {
            return true;
        }
    }

    // Verifica colunas
    for (int j = 0; j < colunas; j++) {
        if (tabuleiro[0][j] == simbolo && tabuleiro[1][j] == simbolo && tabuleiro[2][j] == simbolo) {
            return true;
        }
    }

    // Verifica diagonais
    if (tabuleiro[0][0] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][2] == simbolo) {
        return true;
    }
    if (tabuleiro[0][2] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][0] == simbolo) {
        return true;
    }

    return false; 
}

// Função para verificar se o jogo terminou em empate
bool verificaEmpate(char tabuleiro[max_linhas][max_colunas], int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (tabuleiro[i][j] == '0') {
                return false; 
            }
        }
    }
    return true; 
}

int main() {
    char matriz[max_linhas][max_colunas];
    int qnt_players;
    int linhas, colunas;
    int nDiamantes = 15;
    int nArmadilhas = 8;
    int nBonus = 5;

    // Pergunta ao usuário a quantidade de jogadores
    cout << "Digite a quantidade de jogadores (entre 2 e 4): ";
    while (!(cin >> qnt_players) || qnt_players < 2 || qnt_players > 4) { 
        cout << "Entrada inválida. Digite um número entre 2 e 4: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }

    // Cria um array de jogadores com a quantidade especificada
    player jogadores[qnt_players];
    cadastrarJogadores(jogadores, qnt_players);

    // Define a dificuldade do jogo
    escolher_dificuldade(linhas, colunas);

    // Preenche a matriz do jogo com "0"s
    preencher_matriz(matriz, linhas, colunas);

    // Distribui os itens no tabuleiro
    distribuir_itens(matriz, linhas, colunas, nDiamantes, nArmadilhas, nBonus);

    // Matriz para controlar quais itens foram revelados
    bool itensRevelados[max_linhas][max_colunas];
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            itensRevelados[i][j] = false; // Inicializa como falso (oculto)
        }
    }

    // Imprime a matriz do jogo (inicialmente com "0"s)
    imprimir_matriz(matriz, linhas, colunas, itensRevelados);

    // Variáveis para controlar o jogo
    int jogadorAtual = 0;
    bool jogoTerminou = false;

    // Loop principal do jogo
    while (!jogoTerminou) { 
        // Limpar a tela (opcional)
        // ..

        cout << "Jogador " << jogadores[jogadorAtual].nome << " (" << jogadores[jogadorAtual].simbolo << "), sua vez!" << endl;

        // Verifica se algum jogador atingiu 100 pontos
        if (jogadores[jogadorAtual].pontuacao >= 100) {
            cout << "Jogador " << jogadores[jogadorAtual].nome << " venceu com 100 pontos!" << endl;
            jogoTerminou = true;
            break; 
        }

        // Variável para indicar se o jogador fez uma jogada válida
        bool jogadaValida = false; 

        // Loop para garantir que o jogador escolha uma posição válida
        while (!jogoTerminou && !jogadaValida) { 
            // Verifica se o jogador digitou "status"
            cout << "Digite 'status' para ver sua pontuação ou digite a coluna (A-" << char('A' + colunas - 1) << "): ";
            string entrada;
            cin >> entrada;

            if (entrada == "status") {
                cout << "Status do jogador " << jogadores[jogadorAtual].nome << ": " << jogadores[jogadorAtual].pontuacao << " pontos" << endl;
                continue; // Volta para o início do loop 
            }

            // Obter a posição escolhida pelo jogador
            char colunaLetra = entrada[0]; // Pega o primeiro caractere da entrada

            // Lê a linha se o jogador não digitou "status"
            int linha;
            cout << "Digite a linha (1-" << linhas << "): ";
            cin >> linha;

            // Converter a coluna para um número
            int colunaNumerica = converterColuna(colunaLetra); 

            // Verificar se a posição é válida
            if (posicaoValida(linha, colunaNumerica, linhas, colunas)) {
                // Revelar o item na posição escolhida
                if (matriz[linha - 1][colunaNumerica - 1] == 'D') {
                    cout << "Você encontrou um diamante!" << endl;
                    int pontosDiamante = gerar_numero_aleatorio(2, 10);
                    if (jogadores[jogadorAtual].bonus_diamante_duplo) {
                        pontosDiamante *= 2;
                        jogadores[jogadorAtual].bonus_diamante_duplo = false; 
                    }
                    jogadores[jogadorAtual].pontuacao += pontosDiamante; 
                    cout << "Você ganhou " << pontosDiamante << " pontos!" << endl;
                } else if (matriz[linha - 1][colunaNumerica - 1] == 'B') {
                    cout << "Você encontrou um bônus!" << endl;
                    int tipoBonus = gerar_numero_aleatorio(1, 2);
                    if (tipoBonus == 1) {
                        cout << "Você ganhou uma jogada extra!" << endl;
                        jogadores[jogadorAtual].jogadas_extras++;
                        // O jogador atual continua jogando
                    } else {
                        cout << "Seu próximo diamante valerá o dobro de pontos!" << endl;
                        jogadores[jogadorAtual].bonus_diamante_duplo = true;
                    }
                } else if (matriz[linha - 1][colunaNumerica - 1] == 'A') {
                    cout << "Você encontrou uma armadilha!" << endl;
                    int pontosArmadilha = gerar_numero_aleatorio(5, 10); 
                    for (int i = 0; i < qnt_players; i++) {
                        if (i != jogadorAtual) {
                            jogadores[i].pontuacao -= pontosArmadilha; 
                            if (jogadores[i].pontuacao < 0) {
                                jogadores[i].pontuacao = 0; 
                            }
                            cout << "Jogador " << jogadores[i].nome << " perdeu " << pontosArmadilha << " pontos." << endl;
                        }
                    }
                    jogadores[jogadorAtual].pontuacao += pontosArmadilha; 
                } else { 
                    cout << "Esta posição está vazia." << endl;

                    // Atualiza a matriz com o símbolo do jogador atual
                    matriz[linha - 1][colunaNumerica - 1] = jogadores[jogadorAtual].simbolo; 
                }

                // Marca a posição como revelada
                itensRevelados[linha - 1][colunaNumerica - 1] = true;

                // Imprime a matriz do jogo (com itens revelados)
                imprimir_matriz(matriz, linhas, colunas, itensRevelados); 

                // Verifica se o jogador atual ganhou
                if (verificaVitoria(matriz, jogadores[jogadorAtual].simbolo, linhas, colunas)) {
                    cout << "Jogador " << jogadores[jogadorAtual].nome << " venceu!" << endl;
                    jogoTerminou = true;
                } else if (verificaEmpate(matriz, linhas, colunas)) {
                    cout << "Empate!" << endl;
                    jogoTerminou = true;
                }

                // A jogada foi válida, então atualiza a flag
                jogadaValida = true; 
            } else {
                cout << "Posicao invalida. Tente novamente." << endl;
            }
        }

        // Passa a vez para o próximo jogador, considerando as jogadas extras
        if (jogadores[jogadorAtual].jogadas_extras > 0) {
            jogadores[jogadorAtual].jogadas_extras--;
            // Continua a vez do jogador atual
        } else {
            jogadorAtual = (jogadorAtual + 1) % qnt_players; 
        }

        // Imprime a matriz do jogo (com itens revelados)
        imprimir_matriz(matriz, linhas, colunas, itensRevelados); 
    }

    // Exibe a pontuação final de cada jogador
    cout << "\n--- Pontuação Final ---" << endl;
    for (int i = 0; i < qnt_players; i++) {
        cout << "Jogador " << jogadores[i].nome << ": " << jogadores[i].pontuacao << " pontos" << endl;
    }

    return 0;
}