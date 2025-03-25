#ifndef POKER_H_INCLUDED
#define POKER_H_INCLUDED
#define TAM 52

#include <string>
#include <iostream>
#include "genericList.hpp"

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

bool criarBaralho(ListaDeT<TipoCarta, TAM> &listaDeCartas) {
    for (int suit = 2; suit <= 8; suit += 2) {
        for (int number = 1; number <= 13; number++) {
            TipoCarta newCard = {number, suit};
            listaDeCartas.itens[listaDeCartas.tamanho].dado = newCard;
            listaDeCartas.tamanho++;
        }
    }
    return true;
}

void imprimirBaralho(ListaDeT<TipoCarta, TAM> &listaDeCartas) {
    for (int i = 0; i < listaDeCartas.tamanho; i++) {
        std::cout << i << " -> ";
        imprimirCarta(listaDeCartas.itens[i].dado);
        std::cout << std::endl;
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