#ifndef MAINCHAINEDLIST_H_INCLUDED
#define MAINCHAINEDLIST_H_INCLUDED

#include <iostream>

#include "chainedList.hpp"
#include "pokerCL.hpp"

void jogo(
    ListaEncadeada<TipoCarta> dealer,
    ListaEncadeada<TipoCarta> mesa,
    ListaEncadeada<TipoCarta> jogadores[4]) {
    embaralhar(dealer);

    for (int i = 0; i < 4; i++) {
        distribuir(dealer, jogadores[i], 2);
        std::cout << "\n";
        std::cout << "Jogador " << i << ":" << std::endl;
        imprimirBaralho(jogadores[i]);
    }

    std::cout << "\n";
    std::cout << "Pressione enter para continuar: " << std::endl;
    std::cin.get();

    std::cout << "Mesa: " << std::endl;
    distribuir(dealer, mesa, 3);
    imprimirBaralho(mesa);
    std::cout << "\n";

    std::cout << "Pressione enter para continuar: " << std::endl;
    std::cin.get();

    std::cout << "Mesa: " << std::endl;
    distribuir(dealer, mesa, 1);
    imprimirBaralho(mesa);
    std::cout << "\n";

    std::cout << "Pressione enter para continuar: " << std::endl;
    std::cin.get();

    std::cout << "Mesa: " << std::endl;
    distribuir(dealer, mesa, 1);
    imprimirBaralho(mesa);
    std::cout << "\n";

    std::cout << "Pressione enter para continuar: " << std::endl;
    std::cin.get();

    std::cout << "\n";
    for (int i = 0; i < 4; i++) {
        std::cout << "\n";
        std::cout << "Jogador " << i << ":" << std::endl;
        imprimirBaralho(jogadores[i]);
    }
}

void testes(ListaEncadeada<TipoCarta> &dealer) {
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

int mainChainedList() {
    ListaEncadeada<TipoCarta> dealer;
    ListaEncadeada<TipoCarta> mesa;
    ListaEncadeada<TipoCarta> jogadores[4];
    inicializarLista(dealer);
    inicializarLista(mesa);

    for (int i = 0; i < 4; i++) {
        inicializarLista(jogadores[i]);
    }

    criarBaralho(dealer);

//     Testes
    testes(dealer);

    // Jogo
//    jogo(dealer, mesa, jogadores);

    return 0;
}

#endif // MAINCHAINEDLIST_H_INCLUDED