// #include <iostream>
// #include <chrono>
// #include <random>
// #include "llist.h"

// const int N = 1000000;
// const int E = 10000;
// const int REPETITIONS = 3;

// void insercionAleatoria(llist<int>& lista) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(0, 2 * N);

//     for (int i = 0; i < N; ++i) {
//         int key = dis(gen);
//         lista.Insert(new llnode<int>(key));
//     }
// }

// void insercionOrdenada(llist<int>& lista) {
//     for (int i = 0; i < N; ++i) {
//         lista.Insert(new llnode<int>(i));
//     }
// }

// void buscarElementos(llist<int>& lista) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(0, 2 * N);

//     for (int i = 0; i < E; ++i) {
//         int key = dis(gen);
//         lista.Search(key);
//     }
// }

// void medirTiempoInsercionAleatoria() {
//     for (int i = 0; i < REPETITIONS; ++i) {
//         llist<int> lista;
//         auto start = std::chrono::high_resolution_clock::now();
//         insercionAleatoria(lista);
//         auto end = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double> duration = end - start;
//         std::cout << "Tiempo de insercion aleatoria (repeticion " << i + 1 << "): " << duration.count() << " segundos" << std::endl;
//     }
// }

// void medirTiempoInsercionOrdenada() {
//     for (int i = 0; i < REPETITIONS; ++i) {
//         llist<int> lista;
//         auto start = std::chrono::high_resolution_clock::now();
//         insercionOrdenada(lista);
//         auto end = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double> duration = end - start;
//         std::cout << "Tiempo de insercion ordenada (repeticion " << i + 1 << "): " << duration.count() << " segundos" << std::endl;
//     }
// }

// void medirTiempoBusqueda(llist<int>& lista) {
//     auto start = std::chrono::high_resolution_clock::now();
//     buscarElementos(lista);
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration = end - start;
//     std::cout << "Tiempo de busqueda: " << duration.count() << " segundos" << std::endl;
// }

// int main() {
//     std::cout << "Pruebas de inserción aleatoria:" << std::endl;
//     medirTiempoInsercionAleatoria();

//     std::cout << "\nPruebas de insercion ordenada:" << std::endl;
//     medirTiempoInsercionOrdenada();

//     std::cout << "\nPruebas de búsqueda tras insercion aleatoria:" << std::endl;
//     for (int i = 0; i < REPETITIONS; ++i) {
//         llist<int> lista;
//         insercionAleatoria(lista);
//         medirTiempoBusqueda(lista);
//     }

//     std::cout << "\nPruebas de búsqueda tras insercion ordenada:" << std::endl;
//     for (int i = 0; i < REPETITIONS; ++i) {
//         llist<int> lista;
//         insercionOrdenada(lista);
//         medirTiempoBusqueda(lista);
//     }

//     return 0;
// }
 ///////////////////////////////////////////////////////////////

#include <iostream>
#include <chrono>
#include <random>
#include "chasht.h"

const int N = 1000000;
const int E = 10000;
const int REPETITIONS = 3;

void insercionAleatoria(chtable<int>& tabla) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2 * N);

    for (int i = 0; i < N; ++i) {
        int key = dis(gen);
        tabla.Insert(key);
    }
}

void insercionOrdenada(chtable<int>& tabla) {
    for (int i = 0; i < N; ++i) {
        tabla.Insert(i);
    }
}

void buscarElementos(chtable<int>& tabla) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2 * N);

    for (int i = 0; i < E; ++i) {
        int key = dis(gen);
        tabla.Search(key);
    }
}

void medirTiempoInsercionAleatoria() {
    for (int i = 0; i < REPETITIONS; ++i) {
        chtable<int> tabla(N);
        auto start = std::chrono::high_resolution_clock::now();
        insercionAleatoria(tabla);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Tiempo de insercion aleatoria (repeticion " << i + 1 << "): " << duration.count() << " segundos" << std::endl;
    }
}

void medirTiempoInsercionOrdenada() {
    for (int i = 0; i < REPETITIONS; ++i) {
        chtable<int> tabla(N);
        auto start = std::chrono::high_resolution_clock::now();
        insercionOrdenada(tabla);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Tiempo de insercion ordenada (repeticion " << i + 1 << "): " << duration.count() << " segundos" << std::endl;
    }
}

void medirTiempoBusqueda(chtable<int>& tabla) {
    auto start = std::chrono::high_resolution_clock::now();
    buscarElementos(tabla);
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
        chtable<int> tabla(N);
        insercionAleatoria(tabla);
        medirTiempoBusqueda(tabla);
    }

    std::cout << "\nPruebas de búsqueda tras insercion ordenada:" << std::endl;
    for (int i = 0; i < REPETITIONS; ++i) {
        chtable<int> tabla(N);
        insercionOrdenada(tabla);
        medirTiempoBusqueda(tabla);
    }

    return 0;
}
  


  ////////////////////////////////////////////////////////////////////////////////

// #include <iostream>
// #include <chrono>
// #include <random>
// #include "rbtree.h"

// const int N = 1000000;
// const int E = 10000;
// const int REPETITIONS = 3;

// void insercionAleatoria(rbtree<int>& arbol) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(0, 2 * N);

//     for (int i = 0; i < N; ++i) {
//         int key = dis(gen);
//         rbtnode<int> *nuevoNodo = new rbtnode<int>(key, nullptr, arbol.nil, arbol.nil);
//         arbol.Insert(nuevoNodo);
//     }
// }

// void insercionOrdenada(rbtree<int>& arbol) {
//     for (int i = 0; i < N; ++i) {
//         rbtnode<int> *nuevoNodo = new rbtnode<int>(i, nullptr, arbol.nil, arbol.nil);
//         arbol.Insert(nuevoNodo);
//     }
// }

// void buscarElementos(rbtree<int>& arbol) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(0, 2 * N);

//     for (int i = 0; i < E; ++i) {
//         int key = dis(gen);
//         arbol.Search(arbol.root, key);
//     }
// }

// void medirTiempoInsercionAleatoria() {
//     for (int i = 0; i < REPETITIONS; ++i) {
//         rbtree<int> arbol;
//         auto start = std::chrono::high_resolution_clock::now();
//         insercionAleatoria(arbol);
//         auto end = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double> duration = end - start;
//         std::cout << "Tiempo de insercion aleatoria (repeticion " << i + 1 << "): " << duration.count() << " segundos" << std::endl;
//     }
// }

// void medirTiempoInsercionOrdenada() {
//     for (int i = 0; i < REPETITIONS; ++i) {
//         rbtree<int> arbol;
//         auto start = std::chrono::high_resolution_clock::now();
//         insercionOrdenada(arbol);
//         auto end = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double> duration = end - start;
//         std::cout << "Tiempo de insercion ordenada (repeticion " << i + 1 << "): " << duration.count() << " segundos" << std::endl;
//     }
// }

// void medirTiempoBusqueda(rbtree<int>& arbol) {
//     auto start = std::chrono::high_resolution_clock::now();
//     buscarElementos(arbol);
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration = end - start;
//     std::cout << "Tiempo de busqueda: " << duration.count() << " segundos" << std::endl;
// }

// int main() {
//     std::cout << "Pruebas de inserción aleatoria:" << std::endl;
//     medirTiempoInsercionAleatoria();

//     std::cout << "\nPruebas de insercion ordenada:" << std::endl;
//     medirTiempoInsercionOrdenada();

//     std::cout << "\nPruebas de búsqueda tras insercion aleatoria:" << std::endl;
//     for (int i = 0; i < REPETITIONS; ++i) {
//         rbtree<int> arbol;
//         insercionAleatoria(arbol);
//         medirTiempoBusqueda(arbol);
//     }

//     std::cout << "\nPruebas de búsqueda tras insercion ordenada:" << std::endl;
//     for (int i = 0; i < REPETITIONS; ++i) {
//         rbtree<int> arbol;
//         insercionOrdenada(arbol);
//         medirTiempoBusqueda(arbol);
//     }

//     return 0;
// }

