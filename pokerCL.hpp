#ifndef POKER_H_INCLUDED
#define POKER_H_INCLUDED
#define TAM 52

#include <string>
#include "chainedList.hpp"

struct TipoCarta {
    int numero;
    int naipe;
};

void imprimirCarta(TipoCarta carta) {
    std::string simbolo;
    if (carta.naipe == 2) {
        simbolo = "Ouros";
    } else if (carta.naipe == 4) {
        simbolo = "Espadas";
    } else if (carta.naipe == 6) {
        simbolo = "Copas";
    } else if (carta.naipe == 8) {
        simbolo = "Paus";
    } else {
        simbolo = "Naipe Desconhecido";
    }
    std::cout << carta.numero << " de " << simbolo << std::endl;
}

bool criarBaralho(ListaEncadeada<TipoCarta> &listaDeCartas) {
    for (int naipe = 8; naipe >= 2; naipe -= 2) {
        for (int numero = 13; numero >= 1; numero--) {
            TipoCarta novaCarta = {numero, naipe};
            adicionarInicio(listaDeCartas, novaCarta);  // Porque este é o mais rápido para adicionar
        }
    }
    return true;
}

void imprimirBaralho(ListaEncadeada<TipoCarta> &listaDeCartas) {
    Item<TipoCarta> *temp = listaDeCartas.inicio;
    int i = 0;

    while (temp != nullptr) {
        std::cout << i << " -> ";
        imprimirCarta(temp->dado);
        temp = temp->proximo;
        i++;
    }
}

bool operator>(TipoCarta cartaA, TipoCarta cartaB) {
    return 10 * cartaA.naipe + cartaA.numero > 10 * cartaB.naipe + cartaB.numero;
}

bool operator<(TipoCarta cartaA, TipoCarta cartaB) {
    return 10 * cartaA.naipe + cartaA.numero < 10 * cartaB.naipe + cartaB.numero;
}

bool operator<=(TipoCarta cartaA, TipoCarta cartaB) {
    return 10 * cartaA.naipe + cartaA.numero <= 10 * cartaB.naipe + cartaB.numero;
}

#endif