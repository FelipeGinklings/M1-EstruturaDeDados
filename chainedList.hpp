#ifndef genericList_H_INCLUDED
#define genericList_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename Tipo>
struct Item {
    Tipo dado;
    Item<Tipo> *proximo;
};

template <typename Tipo>
struct ListaEncadeada {
    Item<Tipo> *inicio;
};

template <typename Tipo>
void inicializarLista(ListaEncadeada<Tipo> &listaEncadeada) {
    listaEncadeada.inicio = nullptr;
};

template <typename Tipo>
int obterTamanhoLista(ListaEncadeada<Tipo> listaEncadeada) {
    Item<Tipo> *temp = listaEncadeada.inicio;

    if (listaEncadeada.inicio == nullptr) {
        return 0;
    }

    int i;

    for (i = 0; temp != nullptr; i++)
        temp = temp->proximo;

    return i;
}

template <typename Tipo>
bool removerFim(ListaEncadeada<Tipo> &listaEncadeada) {
    Item<Tipo> *temp = listaEncadeada.inicio;

    if (temp == nullptr)
        return false;

    if (temp->proximo == nullptr) {
        delete temp;
        listaEncadeada.inicio = nullptr;
        return true;
    }

    while (temp->proximo->proximo != nullptr)
        temp = temp->proximo;

    Item<Tipo> *paraDeletar = temp->proximo;
    temp->proximo = nullptr;
    delete paraDeletar;
    return true;
}

template <typename Tipo>
bool adicionarFim(ListaEncadeada<Tipo> &listaEncadeada, Tipo item) {
    Item<Tipo> *temp = listaEncadeada.inicio;
    auto *novoItem = new Item<Tipo>;
    novoItem->dado = item;
    novoItem->proximo = nullptr;

    if (temp == nullptr) {
        listaEncadeada.inicio = novoItem;
        return true;
    }

    while (temp->proximo != nullptr)
        temp = temp->proximo;

    temp->proximo = novoItem;

    return true;
}

template <typename Tipo>
bool removerInicio(ListaEncadeada<Tipo> &listaEncadeada) {
    if (listaEncadeada.inicio == nullptr) {
        return false;
    }

    Item<Tipo> *paraDeletar = listaEncadeada.inicio;
    listaEncadeada.inicio = paraDeletar->proximo;
    delete paraDeletar;

    return true;
}

template <typename Tipo>
bool adicionarInicio(ListaEncadeada<Tipo> &listaEncadeada, Tipo item) {
    auto *novoItem = new Item<Tipo>;
    novoItem->dado = item;
    if (listaEncadeada.inicio == nullptr)
        novoItem->proximo = nullptr;
    else
        novoItem->proximo = listaEncadeada.inicio;
    listaEncadeada.inicio = novoItem;

    return true;
}

template <typename Tipo>
bool removerPosicao(ListaEncadeada<Tipo> &listaEncadeada, int indice) {
    int tamanho = obterTamanhoLista(listaEncadeada);
    Item<Tipo> *temp = listaEncadeada.inicio;
    if (indice < 0 || indice >= tamanho || temp == nullptr)
        return false;

    if (indice == 0)
        return removerInicio(listaEncadeada);

    for (int i = 0; i < indice - 1; i++)
        temp = temp->proximo;

    Item<Tipo> *paraDeletar = temp->proximo;
    temp->proximo = temp->proximo->proximo;
    delete paraDeletar;
    return true;
}

template <typename Tipo>
bool adicionarPosicao(ListaEncadeada<Tipo> &listaEncadeada, Tipo item, int indice) {
    int tamanho = obterTamanhoLista(listaEncadeada);
    if (indice < 0 || indice >= tamanho)
        return false;
    Item<Tipo> *temp = listaEncadeada.inicio;
    auto *novoItem = new Item<Tipo>;
    novoItem->dado = item;

    if (indice == 0)
        return adicionarInicio(listaEncadeada, item);

    for (int i = 0; i < indice - 1; i++)
        temp = temp->proximo;

    novoItem->proximo = temp->proximo;
    temp->proximo = novoItem;

    return true;
}

template <typename Tipo>
Item<Tipo> *obterItem(ListaEncadeada<Tipo> &listaEncadeada, int indice) {
    if (indice < 0 || indice >= obterTamanhoLista(listaEncadeada) || listaEncadeada.inicio == nullptr) return nullptr;
    Item<Tipo> *item = listaEncadeada.inicio;

    for (int i = 0; i < indice; i++)
        item = item->proximo;

    return item;
}

template <typename Tipo>
void trocarItens(Item<Tipo> *itemA, Item<Tipo> *itemB) {
    Tipo tempDado = itemA->dado;
    itemA->dado = itemB->dado;
    itemB->dado = tempDado;
}

template <typename Tipo>
void embaralhar(ListaEncadeada<Tipo> &listaEncadeada) {
    srand(time(nullptr));
    for (int i = obterTamanhoLista(listaEncadeada) - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        Item<Tipo> *itemI = obterItem(listaEncadeada, i);
        Item<Tipo> *itemJ = obterItem(listaEncadeada, j);
        trocarItens(itemI, itemJ);
    }
}

template <typename Tipo>
bool distribuir(ListaEncadeada<Tipo> &listaOrigem, ListaEncadeada<Tipo> &listaDestino, int quantidade) {
    if (listaOrigem.inicio == nullptr || quantidade < 0) {
        return false;
    }
    for (int i = 0; i < quantidade; i++) {
        Tipo primeiroDaOrigem = listaOrigem.inicio->dado;
        adicionarInicio(listaDestino, primeiroDaOrigem);
        removerInicio(listaOrigem);
    }
    return true;
}

inline int contador = 0;

// Uma versão otimizada do Bubble Sort
template <typename Tipo>
void bubbleSort(ListaEncadeada<Tipo> &listaEncadeada) {
    contador = 0;
    int n = obterTamanhoLista(listaEncadeada);

    std::cout << "Contador BubbleSort: " << contador << std::endl;

    for (int i = 0; i < n - 1; i++) {
        bool trocado = false;
        for (int j = 0; j < n - i - 1; j++) {
            Item<Tipo> *dadoJ = obterItem(listaEncadeada, j);
            Item<Tipo> *dadoJ1 = obterItem(listaEncadeada, j + 1);
            if (dadoJ->dado > dadoJ1->dado) {
                trocarItens(dadoJ, dadoJ1);
                trocado = true;
                contador++;
            }
        }
        if (!trocado)
            break;
    }

    std::cout << "Contador BubbleSort: " << contador << std::endl;
}

template <typename Tipo>
int particionar(ListaEncadeada<Tipo> &listaEncadeada, int baixo, int alto) {
    Item<Tipo> *pivo = obterItem(listaEncadeada, alto);
    int indice = baixo;

    for (int j = baixo; j <= alto - 1; j++) {
        if (Item<Tipo> *itemJ = obterItem(listaEncadeada, j); itemJ->dado <= pivo->dado) {
            trocarItens(obterItem(listaEncadeada, indice), itemJ);
            indice++;
            contador++;
        }
    }

    trocarItens(obterItem(listaEncadeada, indice), pivo);
    contador++;
    return indice;
}

template <typename Tipo>
void quickSort(ListaEncadeada<Tipo> &listaEncadeada, int baixo, int alto) {
    if (baixo < alto) {
        const int pi = particionar(listaEncadeada, baixo, alto);
        quickSort(listaEncadeada, baixo, pi - 1);
        quickSort(listaEncadeada, pi + 1, alto);
    }
}

template <typename Tipo>
void quickSort(ListaEncadeada<Tipo> &listaEncadeada) {
    contador = 0;
    quickSort(listaEncadeada, 0, obterTamanhoLista(listaEncadeada) - 1);
    std::cout << "Contador QuickSort: " << contador << std::endl;
}

#endif