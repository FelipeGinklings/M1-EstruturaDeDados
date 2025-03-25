#include <time.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "genericList.hpp"
#include "poker.hpp"


void jogo(
    ListaDeT<TipoCarta, 52> dealer,
    ListaDeT<TipoCarta, 52> mesa,
    ListaDeT<TipoCarta, 52> jogadores[4]) {
    embaralhar(dealer);

    for (int i = 0; i < 4; i++) {
        distribuir(dealer, jogadores[i], 2);
        std::cout << "\n";
        std::cout << "Player " << i << ":" << std::endl;
        imprimirBaralho(jogadores[i]);
    }

    std::cout << "\n";
    std::cout << "Press enter to continue" << std::endl;
    std::cin.get();

    std::cout << "Mesa: " << std::endl;
    distribuir(dealer, mesa, 3);
    imprimirBaralho(mesa);
    std::cout << "\n";

    std::cout << "Press enter to continue" << std::endl;
    std::cin.get();

    std::cout << "Mesa: " << std::endl;
    distribuir(dealer, mesa, 1);
    imprimirBaralho(mesa);
    std::cout << "\n";

    std::cout << "Press enter to continue" << std::endl;
    std::cin.get();

    std::cout << "Mesa: " << std::endl;
    distribuir(dealer, mesa, 1);
    imprimirBaralho(mesa);
    std::cout << "\n";

    std::cout << "Press enter to continue" << std::endl;
    std::cin.get();

    std::cout << "\n";
    for (int i = 0; i < 4; i++) {
        std::cout << "\n";
        std::cout << "Player " << i << ":" << std::endl;
        imprimirBaralho(jogadores[i]);
    }
}

void testes(ListaDeT<TipoCarta, 52> dealer) {
    std::cout << "Deck Inicial: \n\n";
    imprimirBaralho(dealer);

    std::cout << "\nDeck Embaralhado: \n\n";
    embaralhar(dealer);
    imprimirBaralho(dealer);

    std::cout << "\nDeck Arrumado Depois de Embaralhado(bubble): \n\n";
    bubbleSort(dealer);
    imprimirBaralho(dealer);

    std::cout << "\nDeck Embaralhado: \n\n";
    embaralhar(dealer);
    imprimirBaralho(dealer);

    std::cout << "\nDeck Arrumado Depois de Embaralhado(quickSort): \n\n";
    quickSort(dealer);
    imprimirBaralho(dealer);
}

int main() {
    ListaDeT<TipoCarta, 52> dealer;
    ListaDeT<TipoCarta, 5> mesa;
    ListaDeT<TipoCarta, 2> jogadores[4];
    inicializarLista(dealer);
    inicializarLista(mesa);

    for (int i = 0; i < 4; i++) {
        inicializarLista(jogadores[i]);
    }

    criarBaralho(dealer);

    testes(dealer);

    // Game
    // jogo(dealer, mesa, jogadores);

    return 0;
}
