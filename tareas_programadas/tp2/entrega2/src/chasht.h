#ifndef chtable_h
#define chtable_h

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
     */
    void Insert(const T& k) {
        int index = hashFunction(k);
        if (table[index].Search(k) == nullptr) {
            table[index].Insert(new llnode<T>(k));
        }
    }

    /**
     * @brief Retorna un puntero a la llave o nullptr si no se encuentra.
     * 
     * @param k Llave a buscar.
     * 
     * @return T* Puntero a la llave encontrada o nullptr si no se encuentra.
     */
    T* Search(const T& k) {
        int index = hashFunction(k);
        llnode<T>* node = table[index].Search(k);
        if (node != nullptr) {
            return &node->getKeyRef();
        }
        return nullptr;
    }

    /**
     * @brief Elimina el elemento de la tabla.
     * 
     * @param k Elemento a eliminar.
     */
    void Delete(const T& k) {
        int index = hashFunction(k);
        llnode<T>* node = table[index].Search(k);
        if (node != nullptr) {
            table[index].Delete(node);
        }
    }

    /**
     * @brief Imprime los datos de la tarea.
     * 
     * @return std::string Datos de la tarea.
     */
    std::string ImprimirDatosDeTarea() {
        return "c15424 Tarea 2 Etapa 1";
    }

private:
    /**
     * @brief Función de dispersión.
     * 
     * @param k Llave a dispersar.
     * 
     * @return int Resultado de la función de dispersión.
     */
    int hashFunction(const T& k) const {
        return k % size;
    }

    int size;                      ///< Número de entradas en la tabla.
    std::vector<llist<T>> table;   ///< La tabla es un vector de listas enlazadas.
};

#endif  // chtable_h
