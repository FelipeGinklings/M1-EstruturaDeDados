#include <iostream>

#include "2chainedList.hpp"
#include "poker.hpp"

using namespace std;

void jogo(
    ListaDuplamenteEncadeada<TipoCarta> dealer,
    ListaDuplamenteEncadeada<TipoCarta> mesa,
    ListaDuplamenteEncadeada<TipoCarta> jogadores[4]) {
    embaralhar(dealer);

    for (int i = 0; i < 4; i++) {
        distribuir(dealer, jogadores[i], 2);
        cout << "\n";
        cout << "Jogador " << i << ":" << endl;
        imprimirBaralho(jogadores[i]);
    }

    cout << "\n";
    cout << "Pressione enter para continuar: " << endl;
    cin.get();

    cout << "Mesa: " << endl;
    distribuir(dealer, mesa, 3);
    imprimirBaralho(mesa);
    cout << "\n";

    cout << "Pressione enter para continuar: " << endl;
    cin.get();

    cout << "Mesa: " << endl;
    distribuir(dealer, mesa, 1);
    imprimirBaralho(mesa);
    cout << "\n";

    cout << "Pressione enter para continuar: " << endl;
    cin.get();

    cout << "Mesa: " << endl;
    distribuir(dealer, mesa, 1);
    imprimirBaralho(mesa);
    cout << "\n";

    cout << "Pressione enter para continuar: " << endl;
    cin.get();

    cout << "\n";
    for (int i = 0; i < 4; i++) {
        cout << "\n";
        cout << "Jogador " << i << ":" << endl;
        imprimirBaralho(jogadores[i]);
    }
}

void testes(ListaDuplamenteEncadeada<TipoCarta> &dealer) {
    cout << "Deck Inicial: \n\n";
    imprimirBaralho(dealer);

    cout << "\nDeck Embaralhado: \n\n";
    embaralhar(dealer);
    imprimirBaralho(dealer);

    cout << "\nDeck Arrumado Depois de Embaralhado(bubble): \n\n";
    bubbleSort(dealer);
    imprimirBaralho(dealer);

    cout << "\nDeck Embaralhado: \n\n";
    embaralhar(dealer);
    imprimirBaralho(dealer);

    cout << "\nDeck Arrumado Depois de Embaralhado(quickSort): \n\n";
    quickSort(dealer);
    imprimirBaralho(dealer);
}

int main() {
    ListaDuplamenteEncadeada<TipoCarta> dealer{};
    ListaDuplamenteEncadeada<TipoCarta> mesa{};
    ListaDuplamenteEncadeada<TipoCarta> jogadores[4];
    inicializarLista(dealer);
    inicializarLista(mesa);

    for (auto & jogadore : jogadores) {
        inicializarLista(jogadore);
    }

    criarBaralho(dealer);

    // Testes
    testes(dealer);

    // Jogo
    // jogo(dealer, mesa, jogadores);
    return 0;
}
