//
//  chtable.h
//

#ifndef chtable_h
#define chtable_h

#include <list>
#include <vector>
#include <stdexcept>
#include "llistD.h"

template <typename T>

// Tabla de dispersión con encadenamiento
class chtable {
public:
    // Constructor que especifica el tamaño de la tabla
    chtable(int sz) : size(sz), table(sz) {}
        
    // Destructor (borra la tabla)
    ~chtable() {}

    // Inserta el elemento en la tabla
    void Insert(const T& k) {
        int i = 0;
        int q;
        do {
            q = hashFunction(k, i);
            if (table[q].Search(k) == nullptr) {
                table[q].Insert(new llnode<T>(k));
                return;
            }
            i++;
        } while (i < size);
        throw std::overflow_error("hash table overflow");
    }

    // Retorna un puntero a la llave o nullptr si no se encuentra
    T* Search(const T& k) {
        int i = 0;
        int q;
        do {
            q = hashFunction(k, i);
            llnode<T>* node = table[q].Search(k);
            if (node != nullptr && node->getKey() == k) {
                return &node->getKeyRef();
            }
            i++;
        } while (i < size && table[q].Search(k) != nullptr);
        return nullptr;
    }

    // Elimina el elemento de la tabla
    void Delete(const T& k) {
        int i = 0;
        int q;
        do {
            q = hashFunction(k, i);
            llnode<T>* node = table[q].Search(k);
            if (node != nullptr && node->getKey() == k) {
                table[q].Delete(node);
                return;
            }
            i++;
        } while (i < size && table[q].Search(k) != nullptr);
    }

    // Imprime los datos de la tarea
    std::string ImprimirDatosDeTarea() {
        return "c15424 Tarea 2 Etapa 2";
    }

private:
    // Función de dispersión
    int hashFunction(const T& k, int i) const {
        return (k + i) % size;
    }

    int size; // Número de entradas en la tabla
    std::vector<llist<T>> table; // La tabla es un vector de listas enlazadas
};

#endif /* chtable_h */
