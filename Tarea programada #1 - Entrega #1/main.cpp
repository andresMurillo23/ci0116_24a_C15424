#include <iostream>
#include <chrono> // Para medir el tiempo
#include <random> // Para generar números aleatorios
#include "Ordenador.h"

int main() {
    Ordenador ordenador;
    const int num_arreglos = 5;
    const int tam_arreglo = 200000; // Tamaño del arreglo

    // Generar números aleatorios para los arreglos
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000000, 1000000); // Números entre -1,000,000 y 1,000,000

    for (int i = 0; i < num_arreglos; ++i) {
        // Crear un nuevo arreglo dinámicamente para evitar el uso de VLA (Variable Length Array) que no es parte del estándar C++
        int* arreglo = new int[tam_arreglo];

        // Llenar el arreglo con números aleatorios
        for (int j = 0; j < tam_arreglo; ++j) {
            arreglo[j] = dis(gen);
        }

        // Medir el tiempo de ejecución del algoritmo de ordenamiento
        auto start = std::chrono::high_resolution_clock::now(); // Iniciar el temporizador
        ordenador.insercion(arreglo, tam_arreglo); // Llamar al algoritmo de ordenamiento
        auto end = std::chrono::high_resolution_clock::now(); // Detener el temporizador

        // Calcular la duración en milisegundos
        std::chrono::duration<double, std::milli> duration = end - start;

        // Imprimir la duración de la ejecución
        std::cout << "Duracion de ejecucion " << i + 1 << ": " << duration.count() << " ms" << std::endl;

        // Limpiar el arreglo dinámico
        delete[] arreglo;
    }

    return 0;
}
