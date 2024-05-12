// #include <iostream>
// #include <chrono> // Para medir el tiempo
// #include <random> // Generar números aleatorios
// #include "Ordenador.h"

// int main() {
//     Ordenador ordenador;
//     const int num_arreglos = 5;
//     const int tam_arreglo = 200000;
//     // Generar números aleatorios
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(0, 10000); //Rango de los numeros 

//     // Imprimir los datos de la tarea
//     // std::cout << ordenador.ImprimirDatosDeTarea() << std::endl;
    
//     for (int i = 0; i < num_arreglos; ++i) {
//         int* arreglo = new int[tam_arreglo];
//         for (int j = 0; j < tam_arreglo; ++j) {
//             arreglo[j] = dis(gen);
//         }
//         // Medir el tiempo de ejecución del algoritmo de ordenamiento
//         auto start = std::chrono::high_resolution_clock::now();
//         ordenador.radixsort(arreglo, tam_arreglo);
//         auto end = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double, std::milli> duration = end - start;

//         std::cout << "Duracion de ejecucion " << i + 1 << ": " << duration.count() << " ms" << std::endl;
//         delete[] arreglo;
//     }

//     return 0;

// }
#include <iostream>
#include <chrono> // Para medir el tiempo
#include <random> // Generar números aleatorios
#include "Ordenador.h"

bool estaOrdenado(int *arreglo, int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (arreglo[i] > arreglo[i + 1]) {
            return false; // No está ordenado
        }
    }
    return true;
}

int main() {
    Ordenador ordenador;
    const int num_arreglos = 5;
    const int tam_arreglo = 200000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 10000); // Rango de los números

    for (int i = 0; i < num_arreglos; ++i) {
        int* arreglo = new int[tam_arreglo];
        for (int j = 0; j < tam_arreglo; ++j) {
            arreglo[j] = dis(gen);
        }

        auto start = std::chrono::high_resolution_clock::now();
        ordenador.radixsort(arreglo, tam_arreglo);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        // Verificar si el arreglo está ordenado
        bool ordenado = estaOrdenado(arreglo, tam_arreglo);
        std::cout << "Duracion de ejecucion " << i + 1 << ": " << duration.count() << " ms";
        std::cout << (ordenado ? " - Arreglo ordenado correctamente." : " - Error: Arreglo no ordenado.") << std::endl;

        delete[] arreglo;
    }

    return 0;
}