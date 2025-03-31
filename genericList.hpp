#ifndef genericList_H_INCLUDED
#define genericList_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

template<typename Tipo>
struct Item {
    Tipo dado;
};

template<typename Tipo, int MAX>
struct ListaDeT {
    Item<Tipo> itens[MAX];
    int tamanho;
};

template<typename Tipo, int MAX>
bool inicializarLista(ListaDeT<Tipo, MAX> &listaDeT) {
    listaDeT.tamanho = 0;
    return true;
}

template<typename Tipo, int MAX>
int obterTamanhoLista(ListaDeT<Tipo, MAX> &listaDeT) {
    return listaDeT.tamanho;
}

template<typename Tipo, int MAX>
bool removerFim(ListaDeT<Tipo, MAX> &listaDeT) {
    if (listaDeT.tamanho > 0 && listaDeT.tamanho <= MAX) {
        listaDeT.tamanho--;
        return true;
    }
    return false;
}

template<typename Tipo, int MAX>
bool adicionarFim(ListaDeT<Tipo, MAX> &listaDeT, Tipo item) {
    if (listaDeT.tamanho < MAX) {
        Item<Tipo> novoItem;
        novoItem.dado = item;
        listaDeT.itens[listaDeT.tamanho] = novoItem;
        listaDeT.tamanho++;
        return true;
    }
    return false;
}

template<typename Tipo, int MAX>
bool removerInicio(ListaDeT<Tipo, MAX> &listaDeT) {
    if (listaDeT.tamanho > 0 && listaDeT.tamanho <= MAX) {
        for (int i = 0; i < listaDeT.tamanho - 1; i++) {
            listaDeT.itens[i] = listaDeT.itens[i + 1];
        }
        listaDeT.tamanho--;
        return true;
    }
    return false;
}

template<typename Tipo, int MAX>
bool adicionarInicio(ListaDeT<Tipo, MAX> &listaDeT, Tipo item) {
    if (listaDeT.tamanho < MAX) {
        for (int i = listaDeT.tamanho - 1; i >= 0; i--) {
            listaDeT.itens[i + 1] = listaDeT.itens[i];
        }
        Item<Tipo> novoItem;
        novoItem.dado = item;
        listaDeT.itens[0] = novoItem;
        listaDeT.tamanho++;
        return true;
    }
    return false;
}

template<typename Tipo, int MAX>
bool removerPosicao(ListaDeT<Tipo, MAX> &listaDeT, int posicao) {
    if ((listaDeT.tamanho > 0 && listaDeT.tamanho <= MAX) && (posicao >= 0 && posicao < listaDeT.tamanho)) {
        for (int i = posicao; i < listaDeT.tamanho - 1; i++) {
            listaDeT.itens[i] = listaDeT.itens[i + 1];
        }
        listaDeT.tamanho--;
        return true;
    }
    return false;
}

template<typename Tipo, int MAX>
bool adicionarPosicao(ListaDeT<Tipo, MAX> &listaDeT, Tipo item, int posicao) {
    if ((listaDeT.tamanho < MAX) && (posicao >= 0 && posicao <= listaDeT.tamanho)) {
        for (int i = listaDeT.tamanho - 1; i >= posicao; i--) {
            listaDeT.itens[i + 1] = listaDeT.itens[i];
        }
        Item<Tipo> novoItem;
        novoItem.dado = item;
        listaDeT.itens[posicao] = novoItem;
        listaDeT.tamanho++;
        return true;
    }
    return false;
}

template<typename Tipo, int MAX>
void embaralhar(ListaDeT<Tipo, MAX> &listaDeT) {
    srand(time(nullptr));
    for (int i = listaDeT.tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(listaDeT.itens[i], listaDeT.itens[j]);
    }
}

template<typename T1, int MAX1, typename T2, int MAX2>
void distribuir(ListaDeT<T1, MAX1> &listaDeOrigem, ListaDeT<T2, MAX2> &listaDeDestino, int quantidade) {
    if (quantidade <= listaDeOrigem.tamanho && (quantidade <= (MAX2 - listaDeDestino.tamanho))) {
        for (int i = 0; i < quantidade; i++) {
            adicionarInicio(listaDeDestino, listaDeOrigem.itens[0].dado);
            removerInicio(listaDeOrigem);
        }
    }
}

int contador = 0;

// Uma versão otimizada do Bubble Sort
template<typename Tipo, int MAX>
void bubbleSort(ListaDeT<Tipo, MAX> &listaDeT) {
    contador = 0;
    int n = listaDeT.tamanho;
    bool trocado;

    std::cout << "Contador BubbleSort: " << contador << std::endl;

    for (int i = 0; i < n - 1; i++) {
        trocado = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (listaDeT.itens[j].dado > listaDeT.itens[j + 1].dado) {
                swap(listaDeT.itens[j], listaDeT.itens[j + 1]);
                trocado = true;
                contador++;
            }
        }
        if (!trocado) break;
    }

    std::cout << "Contador BubbleSort: " << contador << std::endl;
}

template<typename Tipo, int MAX>
int particionar(ListaDeT<Tipo, MAX> &arr, int baixo, int alto) {
    // Selecionando o último elemento como pivô
    Tipo pivo = arr.itens[alto].dado;

    // Índice do elemento logo antes do último elemento
    // É usado para troca
    int i = baixo - 1;

    for (int j = baixo; j <= alto - 1; j++) {
        // Se o elemento atual for menor ou
        // igual ao pivô
        if (arr.itens[j].dado <= pivo) {
            i++;
            swap(arr.itens[i], arr.itens[j]);
            contador++;
        }
    }

    // Colocar o pivô na sua posição
    swap(arr.itens[i + 1], arr.itens[alto]);
    contador++;

    // Retornar o ponto de partição
    return (i + 1);
}

template<typename Tipo, int MAX>
void quickSort(ListaDeT<Tipo, MAX> &arr, int baixo, int alto) {
    // Caso base: Esta parte será executada até que o índice inicial
    // baixo seja menor que o índice final alto
    if (baixo < alto) {
        // pi é o Índice de Partição, arr[p] está agora no
        // lugar certo
        int pi = particionar(arr, baixo, alto);

        // Separadamente ordenar elementos antes e depois do
        // Índice de Partição pi
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

template<typename Tipo, int MAX>
void quickSort(ListaDeT<Tipo, MAX> &arr) {
    contador = 0;
    quickSort(arr, 0, arr.tamanho - 1);
    std::cout << "Contador QuickSort: " << contador << std::endl;
}

#endif
