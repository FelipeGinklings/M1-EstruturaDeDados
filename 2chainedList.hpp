#ifndef chained_list2_H_INCLUDED
#define chained_list2_H_INCLUDED

#include <iostream>

template <typename Tipo>
struct Item {
    Tipo dado;
    Item *proximo;
    Item *anterior;
};

template <typename Tipo>
struct ListaDuplamenteEncadeada {
    Item<Tipo> *inicio;
    Item<Tipo> *fim;
};

template <typename Tipo>
void inicializarLista(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada) {
    listaDuplamenteEncadeada.inicio = nullptr;
    listaDuplamenteEncadeada.fim = nullptr;
};

template <typename Tipo>
int obterTamanhoLista(ListaDuplamenteEncadeada<Tipo> listaDuplamenteEncadeada) {
    Item<Tipo> *nav = listaDuplamenteEncadeada.inicio;

    if (listaDuplamenteEncadeada.inicio == nullptr) {
        return 0;
    }

    int i;

    for (i = 0; nav != nullptr; i++)
        nav = nav->proximo;

    return i;
}

template <typename Tipo>
bool removerFim(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada) {
    if (listaDuplamenteEncadeada.fim == nullptr) return false;

    const Item<Tipo> *paraDeletar = listaDuplamenteEncadeada.fim;
    listaDuplamenteEncadeada.fim = listaDuplamenteEncadeada.fim->anterior;
    listaDuplamenteEncadeada.fim->proximo = nullptr;
    delete paraDeletar;
    return true;
}

template <typename Tipo>
bool adicionarFim(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada, Tipo item) {
    auto *novoItem = new Item<Tipo>;
    novoItem->dado = item;
    novoItem->proximo = nullptr;
    if (listaDuplamenteEncadeada.fim == nullptr) {
        novoItem->anterior = nullptr;
        listaDuplamenteEncadeada.fim = novoItem;
        listaDuplamenteEncadeada.inicio = novoItem;
        return true;
    }

    novoItem->anterior = listaDuplamenteEncadeada.fim;
    listaDuplamenteEncadeada.fim->proximo = novoItem;
    listaDuplamenteEncadeada.fim = novoItem;
    return true;
}

template <typename Tipo>
bool removerInicio(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada) {
    if (listaDuplamenteEncadeada.inicio == nullptr) {
        return false;
    }

    Item<Tipo> *paraDeletar = listaDuplamenteEncadeada.inicio;
    listaDuplamenteEncadeada.inicio = paraDeletar->proximo;
    listaDuplamenteEncadeada.inicio->anterior = nullptr;
    delete paraDeletar;

    return true;
}

template <typename Tipo>
bool adicionarInicio(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada, Tipo item) {
    auto *novoItem = new Item<Tipo>;
    novoItem->dado = item;
    novoItem->anterior = nullptr;

    if (listaDuplamenteEncadeada.fim == nullptr) {
        novoItem->proximo = nullptr;
        listaDuplamenteEncadeada.fim = novoItem;
        listaDuplamenteEncadeada.inicio = novoItem;
        return true;
    };

    novoItem->proximo = listaDuplamenteEncadeada.inicio;
    listaDuplamenteEncadeada.inicio->anterior = novoItem;
    listaDuplamenteEncadeada.inicio = novoItem;
    return true;
}

template <typename Tipo>
bool removerPosicao(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada, const int indice) {
    const int tamanho = obterTamanhoLista(listaDuplamenteEncadeada);
    if (listaDuplamenteEncadeada.inicio == nullptr || indice < 0 || indice > tamanho) return false;
    if (indice == 0) return removerInicio(listaDuplamenteEncadeada);
    if (indice == tamanho-1) return removerFim(listaDuplamenteEncadeada);

    const bool maiorQueMetade = indice > tamanho / 2;
    Item<Tipo> *nav;

    if (maiorQueMetade) {
        nav = listaDuplamenteEncadeada.fim;
        for (int i = tamanho - 1; i > indice; --i) {
            nav = nav->anterior;
        }
    } else {
        nav = listaDuplamenteEncadeada.inicio;
        for (int i = 0; i < indice; i++) {
            nav = nav->proximo;
        }
    }
    const Item<Tipo> *paraDeletar = nav;
    nav->anterior->proximo = nav->proximo;
    nav->proximo->anterior = nav->anterior;
    delete paraDeletar;
    return true;
}

template <typename Tipo>
bool adicionarPosicao(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada, Tipo item, const int indice) {
    const int tamanho = obterTamanhoLista(listaDuplamenteEncadeada);

    if (indice < 0 || indice > tamanho) return false;
    if (indice == 0) return adicionarInicio(listaDuplamenteEncadeada, item);
    if (indice - 1 == tamanho) return adicionarFim(listaDuplamenteEncadeada, item);

    auto *novoItem = new Item<Tipo>;
    novoItem->dado = item;
    if (listaDuplamenteEncadeada.fim == nullptr) {
        novoItem->anterior = nullptr;
        novoItem->proximo = nullptr;
        listaDuplamenteEncadeada.fim = novoItem;
        listaDuplamenteEncadeada.inicio = novoItem;
        return true;
    };

    const bool maiorQueMetade = indice > tamanho / 2;
    Item<Tipo> *nav;

    if (maiorQueMetade) {
        nav = listaDuplamenteEncadeada.fim;
        for (int i = tamanho-1; i > indice; --i) {
            nav = nav->anterior;
        }
    } else {
        nav = listaDuplamenteEncadeada.inicio;
        for (int i = 0; i < indice; i++) {
            nav = nav->proximo;
        }
    }
    novoItem->anterior = nav->anterior;
    novoItem->proximo = nav;
    nav->anterior->proximo = novoItem;
    nav->anterior = novoItem;
    return true;
}

template <typename Tipo>
Item<Tipo> *obterItem(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada, int indice) {
    if (indice < 0 && indice >= obterTamanhoLista(listaDuplamenteEncadeada) && listaDuplamenteEncadeada.inicio == nullptr) return nullptr;

    const int tamanho = obterTamanhoLista(listaDuplamenteEncadeada);
    const bool maiorQueMetade = indice > tamanho / 2;

    Item<Tipo> *item;

    if (maiorQueMetade) {
        item = listaDuplamenteEncadeada.fim;
        for (int i = tamanho; i > indice; --i) {
            item = item->anterior;
        }
    } else {
        item = listaDuplamenteEncadeada.inicio;
        for (int i = 0; i < indice; i++) {
            item = item->proximo;
        }
    }

    return item;
}

template <typename Tipo>
void trocarItens(Item<Tipo> *itemA, Item<Tipo> *itemB) {
    Tipo tempDado = itemA->dado;
    itemA->dado = itemB->dado;
    itemB->dado = tempDado;
}

template <typename Tipo>
void embaralhar(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada) {
    srand(time(nullptr));
    for (int i = obterTamanhoLista(listaDuplamenteEncadeada) - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        Item<Tipo> *itemI = obterItem(listaDuplamenteEncadeada, i);
        Item<Tipo> *itemJ = obterItem(listaDuplamenteEncadeada, j);
        trocarItens(itemI, itemJ);
    }
}

template<typename Tipo>
bool distribuir(ListaDuplamenteEncadeada<Tipo> &listaOrigem, ListaDuplamenteEncadeada<Tipo> &listaDestino,
                const int quantidade) {
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
void bubbleSort(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada) {
    contador = 0;
    std::cout << "Contador BubbleSort: " << contador << std::endl;
    Item<Tipo> *navFinal = listaDuplamenteEncadeada.fim;
    for (Item<Tipo> *navInicioI = listaDuplamenteEncadeada.inicio; navInicioI->proximo->proximo != nullptr;navInicioI = navInicioI->proximo) {
        bool trocado = false;
        navFinal = navFinal->anterior;
        for (Item<Tipo> *navInicioJ = listaDuplamenteEncadeada.inicio;navInicioJ != navFinal;navInicioJ=navInicioJ->proximo) {
            if (navInicioJ->dado > navInicioJ->proximo->dado) {
                trocarItens(navInicioJ, navInicioJ->proximo);
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
Item<Tipo> *particionar(Item<Tipo> *baixo, Item<Tipo> *alto) {
    Item<Tipo> *pivo = alto;
    Item<Tipo> *indice = baixo;

    for (Item<Tipo> *nav = baixo; nav != alto->anterior; nav=nav->proximo) {
        if (nav->dado <= pivo->dado) {
            trocarItens(indice, nav);
            indice = indice->proximo;
            contador++;
        }
    }

    trocarItens(indice, pivo);
    contador++;
    return indice;
}

template <typename Tipo>
void quickSort(Item<Tipo> *baixo, Item<Tipo> *alto) {
    if (baixo < alto) {
        const Item<Tipo> *pi = particionar(baixo, alto);
        quickSort(baixo, pi->anterior);
        quickSort(pi->proximo, alto);
    }
}

template <typename Tipo>
void quickSort(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada) {
    contador = 0;
    quickSort(listaDuplamenteEncadeada.inicio, listaDuplamenteEncadeada.fim);
    std::cout << "Contador QuickSort: " << contador << std::endl;
}

#endif