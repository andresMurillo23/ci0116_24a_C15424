// Copyright [2024] <Copyright Andres Murillo>
#ifndef chtable_h
#define chtable_h

#include <list>
#include <vector>
#include <stdexcept>
#include "llistD.h"

/**
 * @class chtable
 * @brief Tabla de dispersión con encadenamiento.
 * 
 * @tparam T Tipo de datos almacenados en la tabla.
 */
template <typename T>
class chtable {
public:
    /**
     * @brief Constructor que especifica el tamaño de la tabla.
     * 
     * @param sz Tamaño de la tabla.
     */
    chtable(int sz) : size(sz), table(sz) {}
    
    /**
     * @brief Destructor que borra la tabla.
     */
    ~chtable() {}

    /**
     * @brief Inserta el elemento en la tabla.
     * 
     * @param k Elemento a insertar.
     * 
     * @throw std::overflow_error Si la tabla está llena.
     */
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

    /**
     * @brief Retorna un puntero a la llave o nullptr si no se encuentra.
     * 
     * @param k Llave a buscar.
     * 
     * @return T* Puntero a la llave encontrada o nullptr si no se encuentra.
     */
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

    /**
     * @brief Elimina el elemento de la tabla.
     * 
     * @param k Elemento a eliminar.
     */
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

    /**
     * @brief Imprime los datos de la tarea.
     * 
     * @return std::string Datos de la tarea.
     */
    std::string ImprimirDatosDeTarea() {
        return "c15424 Tarea 2 Etapa 2";
    }

private:
    /**
     * @brief Función de dispersión.
     * 
     * @param k Llave a dispersar.
     * @param i Número de intento de dispersión.
     * 
     * @return int Resultado de la función de dispersión.
     */
    int hashFunction(const T& k, int i) const {
        return (k + i) % size;
    }

    int size; ///< Número de entradas en la tabla.
    std::vector<llist<T>> table; ///< La tabla es un vector de listas enlazadas.
};

#endif /* chtable_h */
