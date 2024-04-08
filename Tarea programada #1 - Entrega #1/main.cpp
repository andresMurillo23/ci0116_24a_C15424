#include <iostream> // Para std::cout
#include "Ordenador.h" // Asegúrate de que el nombre del archivo coincida con tu archivo de encabezado

int main() {
    Ordenador ordenador;
    int arreglo[] = {4, 2, 5, 1, 3};
    int n = sizeof(arreglo) / sizeof(arreglo[0]);

    ordenador.mergesort(arreglo, n); // Llamada al método de inserción

    // Imprimir el arreglo ordenado
    for (int i = 0; i < n; i++) {
        std::cout << arreglo[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}