#ifndef chained_list2_H_INCLUDED
#define chained_list2_H_INCLUDED

#include <iostream>

template <typename Tipo>
struct Item {
    Tipo dado;
    Item<Tipo> *proximo;
    Item<Tipo> *anterior;
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
    Item<Tipo> *temp = listaDuplamenteEncadeada.inicio;

    if (listaDuplamenteEncadeada.inicio == nullptr) {
        return 0;
    }

    int i;

    for (i = 0; temp != nullptr; i++)
        temp = temp->proximo;

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
    };

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
    Item<Tipo> *temp;

    if (maiorQueMetade) {
        temp = listaDuplamenteEncadeada.fim;
        for (int i = tamanho - 1; i > indice; --i) {
            temp = temp->anterior;
        }
    } else {
        temp = listaDuplamenteEncadeada.inicio;
        for (int i = 0; i < indice; i++) {
            temp = temp->proximo;
        }
    }
    const Item<Tipo> *paraDeletar = temp;
    temp->anterior->proximo = temp->proximo;
    temp->proximo->anterior = temp->anterior;
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
    Item<Tipo> *temp;

    if (maiorQueMetade) {
        temp = listaDuplamenteEncadeada.fim;
        for (int i = tamanho-1; i > indice; --i) {
            temp = temp->anterior;
        }
    } else {
        temp = listaDuplamenteEncadeada.inicio;
        for (int i = 0; i < indice; i++) {
            temp = temp->proximo;
        }
    }
    novoItem->anterior = temp->anterior;
    novoItem->proximo = temp;
    temp->anterior->proximo = novoItem;
    temp->anterior = novoItem;
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
    int n = obterTamanhoLista(listaDuplamenteEncadeada);

    std::cout << "Contador BubbleSort: " << contador << std::endl;

    for (int i = 0; i < n - 1; i++) {
        bool trocado = false;
        for (int j = 0; j < n - i - 1; j++) {
            Item<Tipo> *dadoJ = obterItem(listaDuplamenteEncadeada, j);
            Item<Tipo> *dadoJ1 = obterItem(listaDuplamenteEncadeada, j + 1);
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
int particionar(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada, int baixo, int alto) {
    // Selecionando o último elemento como pivô
    Item<Tipo> *pivo = obterItem(listaDuplamenteEncadeada, alto);

    // Índice do elemento logo antes do último elemento
    // É usado para troca
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        // Se o elemento atual for menor ou
        // igual ao pivô
        Item<Tipo> *itemJ = obterItem(listaDuplamenteEncadeada, j);
        if (itemJ->dado <= pivo->dado) {
            i++;
            trocarItens(obterItem(listaDuplamenteEncadeada, i), itemJ);
            contador++;
        }
    }

    // Colocar o pivô na sua posição
    trocarItens(obterItem(listaDuplamenteEncadeada, i + 1), pivo);
    contador++;

    // Retornar o ponto de partição
    return (i + 1);
}

template <typename Tipo>
void quickSort(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada, int baixo, int alto) {
    // Caso base: Esta parte será executada até o índice inicial
    // baixo ser menor que o índice final alto
    if (baixo < alto) {
        // pi é o Índice de Partição, listaDuplamenteEncadeada[p] está agora no
        // lugar certo
        int pi = particionar(listaDuplamenteEncadeada, baixo, alto);

        // Separadamente ordenar elementos antes e depois do
        // Índice de Partição pi
        quickSort(listaDuplamenteEncadeada, baixo, pi - 1);
        quickSort(listaDuplamenteEncadeada, pi + 1, alto);
    }
}

template <typename Tipo>
void quickSort(ListaDuplamenteEncadeada<Tipo> &listaDuplamenteEncadeada) {
    contador = 0;
    quickSort(listaDuplamenteEncadeada, 0, obterTamanhoLista(listaDuplamenteEncadeada) - 1);
    std::cout << "Contador QuickSort: " << contador << std::endl;
}

#endif