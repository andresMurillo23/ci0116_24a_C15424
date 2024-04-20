#include <iostream>
#include <chrono> // Para medir el tiempo
#include <random> // Generar números aleatorios
#include "Ordenador.h"

int main() {
    Ordenador ordenador;
    const int num_arreglos = 1;
    const int tam_arreglo = 25000;
    // Generar números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000000, 1000000); //Rango de los numeros 

    for (int i = 0; i < num_arreglos; ++i) {
        int* arreglo = new int[tam_arreglo];
        for (int j = 0; j < tam_arreglo; ++j) {
            arreglo[j] = dis(gen);
        }
        // Medir el tiempo de ejecución del algoritmo de ordenamiento
        auto start = std::chrono::high_resolution_clock::now();
        ordenador.seleccion(arreglo, tam_arreglo);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << "Duracion de ejecucion " << i + 1 << ": " << duration.count() << " ms" << std::endl;
        delete[] arreglo;
    }

    return 0;

    return 0;
}
