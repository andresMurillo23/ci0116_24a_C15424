#include <iostream>
#include <chrono>
#include <random>
#include "llist.h"

const int N = 1000000;
const int E = 10000;
const int REPETITIONS = 3;

void insercionAleatoria(llist<int>& lista) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2 * N);

    for (int i = 0; i < N; ++i) {
        int key = dis(gen);
        lista.Insert(new llnode<int>(key));
    }
}

void insercionOrdenada(llist<int>& lista) {
    for (int i = 0; i < N; ++i) {
        lista.Insert(new llnode<int>(i));
    }
}

void buscarElementos(llist<int>& lista) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2 * N);

    for (int i = 0; i < E; ++i) {
        int key = dis(gen);
        lista.Search(key);
    }
}

void medirTiempoInsercionAleatoria() {
    for (int i = 0; i < REPETITIONS; ++i) {
        llist<int> lista;
        auto start = std::chrono::high_resolution_clock::now();
        insercionAleatoria(lista);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Tiempo de insercion aleatoria (repeticion " << i + 1 << "): " << duration.count() << " segundos" << std::endl;
    }
}

void medirTiempoInsercionOrdenada() {
    for (int i = 0; i < REPETITIONS; ++i) {
        llist<int> lista;
        auto start = std::chrono::high_resolution_clock::now();
        insercionOrdenada(lista);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Tiempo de insercion ordenada (repeticion " << i + 1 << "): " << duration.count() << " segundos" << std::endl;
    }
}

void medirTiempoBusqueda(llist<int>& lista) {
    auto start = std::chrono::high_resolution_clock::now();
    buscarElementos(lista);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tiempo de busqueda: " << duration.count() << " segundos" << std::endl;
}

int main() {
    std::cout << "Pruebas de inserción aleatoria:" << std::endl;
    medirTiempoInsercionAleatoria();

    std::cout << "\nPruebas de insercion ordenada:" << std::endl;
    medirTiempoInsercionOrdenada();

    std::cout << "\nPruebas de búsqueda tras insercion aleatoria:" << std::endl;
    for (int i = 0; i < REPETITIONS; ++i) {
        llist<int> lista;
        insercionAleatoria(lista);
        medirTiempoBusqueda(lista);
    }

    std::cout << "\nPruebas de búsqueda tras insercion ordenada:" << std::endl;
    for (int i = 0; i < REPETITIONS; ++i) {
        llist<int> lista;
        insercionOrdenada(lista);
        medirTiempoBusqueda(lista);
    }

    return 0;
}




// #include <iostream>
// #include <chrono>
// #include <random>
// #include <vector>
// #include "bstree.h"
// #include "llist.h"

// const int N = 1000000;
// const int E = 10000;
// const int REPETITIONS = 3;

// void insercionAleatoriaBST(bstree<int>& arbol) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(0, 2 * N);

//     for (int i = 0; i < N; ++i) {
//         int key = dis(gen);
//         arbol.Insert(new bstnode<int>(key));
//     }
// }

// void insercionOrdenadaBST(bstree<int>& arbol) {
//     std::vector<int> keys;
//     for (int i = 0; i < N; ++i) {
//         keys.push_back(i);
//     }
//     arbol.buildBalancedTree(keys);
// }

// void buscarElementosBST(bstree<int>& arbol) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(0, 2 * N);

//     for (int i = 0; i < E; ++i) {
//         int key = dis(gen);
//         arbol.Search(arbol.getRoot(), key);
//     }
// }

// void medirTiempoInsercionAleatoriaBST() {
//     for (int i = 0; i < REPETITIONS; ++i) {
//         bstree<int> arbol;
//         auto start = std::chrono::high_resolution_clock::now();
//         insercionAleatoriaBST(arbol);
//         auto end = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double> duration = end - start;
//         std::cout << "Tiempo de inserción aleatoria en BST (repetición " << i + 1 << "): " << duration.count() << " segundos" << std::endl;
//     }
// }

// void medirTiempoInsercionOrdenadaBST() {
//     for (int i = 0; i < REPETITIONS; ++i) {
//         bstree<int> arbol;
//         auto start = std::chrono::high_resolution_clock::now();
//         insercionOrdenadaBST(arbol);
//         auto end = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double> duration = end - start;
//         std::cout << "Tiempo de inserción ordenada en BST (repetición " << i + 1 << "): " << duration.count() << " segundos" << std::endl;
//     }
// }

// void medirTiempoBusquedaBST(bstree<int>& arbol) {
//     auto start = std::chrono::high_resolution_clock::now();
//     buscarElementosBST(arbol);
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration = end - start;
//     std::cout << "Tiempo de búsqueda en BST: " << duration.count() << " segundos" << std::endl;
// }

// int main() {
//     std::cout << "Pruebas de inserción aleatoria en BST:" << std::endl;
//     medirTiempoInsercionAleatoriaBST();

//     std::cout << "\nPruebas de inserción ordenada en BST:" << std::endl;
//     medirTiempoInsercionOrdenadaBST();

//     std::cout << "\nPruebas de búsqueda tras inserción aleatoria en BST:" << std::endl;
//     for (int i = 0; i < REPETITIONS; ++i) {
//         bstree<int> arbol;
//         insercionAleatoriaBST(arbol);
//         medirTiempoBusquedaBST(arbol);
//     }

//     std::cout << "\nPruebas de búsqueda tras inserción ordenada en BST:" << std::endl;
//     for (int i = 0; i < REPETITIONS; ++i) {
//         bstree<int> arbol;
//         insercionOrdenadaBST(arbol);
//         medirTiempoBusquedaBST(arbol);
//     }

//     return 0;
// }
