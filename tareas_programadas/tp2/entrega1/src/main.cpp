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
// #include "bstree.h" // Suponiendo que tienes un archivo bstree.h con las implementaciones del árbol

// const int N = 1000000;
// const int E = 10000;

// void insercionOrdenada(bstree<int>& tree) {
//     bstnode<int>* rightNode = new bstnode<int>(0);
//     tree.setRoot(rightNode);
//     for (int i = 1; i < N; ++i) {
//         rightNode->setRight(new bstnode<int>(i));
//         rightNode = rightNode->getRight();
//     }
// }

// void buscarElementos(bstree<int>& tree) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(0, 2 * N);

//     for (int i = 0; i < E; ++i) {
//         int key = dis(gen);
//         bstnode<int>* result = tree.IterativeSearch(tree.getRoot(), key);
//         // Si deseas imprimir los resultados, puedes hacerlo aquí
//     }
// }

// double medirTiempoBusqueda(bstree<int>& tree) {
//     auto start = std::chrono::high_resolution_clock::now();
//     buscarElementos(tree);
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration = end - start;
//     return duration.count();
// }

// int main() {

//     bstree<int> tree;
//     auto start = std::chrono::high_resolution_clock::now();
//     insercionOrdenada(tree);
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration = end - start;
//     std::cout << "Tiempo de insercion ordenada: " << duration.count() << " segundos" << std::endl;

//     double tiempoBusqueda = medirTiempoBusqueda(tree);
//     std::cout << "Tiempo de busqueda tras insercion ordenada: " << tiempoBusqueda << " segundos" << std::endl;


       
//     return 0;
// }




// #include <iostream>
// #include <chrono>
// #include <random>
// #include <vector>
// #include "bstree.h" // Suponiendo que tienes un archivo bstree.h con las implementaciones del árbol

// const int N = 1000000;
// const int E = 10000;

// void insercionAleatoria(bstree<int>& tree) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(0, 2 * N);

//     for (int i = 0; i < N; ++i) {
//         int key = dis(gen);
//         tree.Insert(new bstnode<int>(key));
//     }
// }

// void buscarElementos(bstree<int>& tree) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(0, 2 * N);

//     for (int i = 0; i < E; ++i) {
//         int key = dis(gen);
//         bstnode<int>* result = tree.IterativeSearch(tree.getRoot(), key);
//         // Si deseas imprimir los resultados, puedes hacerlo aquí
//     }
// }

// double medirTiempoBusqueda(bstree<int>& tree) {
//     auto start = std::chrono::high_resolution_clock::now();
//     buscarElementos(tree);
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration = end - start;
//     return duration.count();
// }

// int main() {
//     bstree<int> tree;
//     auto start = std::chrono::high_resolution_clock::now();
//     insercionAleatoria(tree);
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration = end - start;
//     std::cout << "Tiempo de insercion aleatoria: " << duration.count() << " segundos" << std::endl;

//     double tiempoBusqueda = medirTiempoBusqueda(tree);
//     std::cout << "Tiempo de busqueda tras insercion aleatoria: " << tiempoBusqueda << " segundos" << std::endl;

//     return 0;
// }
