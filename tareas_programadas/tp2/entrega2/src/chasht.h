#ifndef chasht_h
#define chasht_h

#include <vector>
#include "llistd.h"

template <typename T>
class chtable {
public:
    // Constructor que especifica el tamaño de la tabla
    chtable(int sz) : size(sz), table(sz) {}

    // Destructor (borra la tabla)
    ~chtable() {}

    // Inserta el elemento en la tabla
    void Insert(const T& k) {
        int q = hashFunction(k);
        table[q].Insert(new llnode<T>(k));
    }

    // Retorna un puntero a la llave o nullptr si no se encuentra
    T* Search(const T& k) {
        int q = hashFunction(k);
        llnode<T>* node = table[q].Search(k);
        if (node != nullptr && node->getKey() == k) {
            return &node->getKeyRef();
        }
        return nullptr;
    }

    // Elimina el elemento de la tabla
    void Delete(const T& k) {
        int q = hashFunction(k);
        llnode<T>* node = table[q].Search(k);
        if (node != nullptr && node->getKey() == k) {
            table[q].Delete(node);
        }
    }

    // Imprime los datos de la tarea
    std::string ImprimirDatosDeTarea() {
        return "c15424 Tarea 2 Etapa 2";
    }

private:
    // Función de dispersión
    int hashFunction(const T& k) const {
        return k % size;
    }

    int size; // Número de entradas en la tabla
    std::vector<llist<T>> table; // La tabla es un vector de listas enlazadas
};

#endif /* chasht_h */
