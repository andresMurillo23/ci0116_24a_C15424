#ifndef llist_h
#define llist_h

#include <string>

/**
 * @class llnode
 * @brief Clase que representa un nodo en una lista doblemente enlazada.
 */
template <typename T>
class llnode {
private:
    T key;               ///< Llave del nodo
    llnode<T>* prev;     ///< Puntero al nodo previo
    llnode<T>* next;     ///< Puntero al nodo siguiente

public:
    /**
     * @brief Constructor por omisión.
     */
    llnode() : key(T()), prev(nullptr), next(nullptr) {}

    /**
     * @brief Constructor que inicializa los datos miembros.
     * @param k Llave del nodo.
     * @param w Puntero al nodo previo.
     * @param y Puntero al nodo siguiente.
     */
    llnode(const T& k, llnode<T>* w = nullptr, llnode<T>* y = nullptr) : key(k), prev(w), next(y) {}

    /**
     * @brief Destructor.
     */
    ~llnode() {}

    /**
     * @brief Obtiene la llave del nodo.
     * @return La llave del nodo.
     */
    T getKey() const { return key; }

    /**
     * @brief Establece la llave del nodo.
     * @param k La nueva llave del nodo.
     */
    void setKey(const T& k) { key = k; }

    /**
     * @brief Obtiene el puntero al nodo previo.
     * @return El puntero al nodo previo.
     */
    llnode<T>* getPrev() const { return prev; }

    /**
     * @brief Establece el puntero al nodo previo.
     * @param w El nuevo puntero al nodo previo.
     */
    void setPrev(llnode<T>* w) { prev = w; }

    /**
     * @brief Obtiene el puntero al nodo siguiente.
     * @return El puntero al nodo siguiente.
     */
    llnode<T>* getNext() const { return next; }

    /**
     * @brief Establece el puntero al nodo siguiente.
     * @param y El nuevo puntero al nodo siguiente.
     */
    void setNext(llnode<T>* y) { next = y; }
};

/**
 * @class llist
 * @brief Clase que representa una lista doblemente enlazada con un nodo centinela.
 */
template <typename T>
class llist {
private:
    llnode<T>* nil;  ///< Nodo centinela

    /**
     * @brief Inicializa la lista con el nodo centinela.
     */
    void initialize() {
        nil = new llnode<T>();
        nil->setNext(nil);
        nil->setPrev(nil);
    }

public:
    /**
     * @brief Constructor que crea una lista vacía.
     */
    llist() {
        initialize();
    }

    /**
     * @brief Destructor que borra la lista.
     */
    ~llist() {
        llnode<T>* current = nil->getNext();
        while (current != nil) {
            llnode<T>* toDelete = current;
            current = current->getNext();
            delete toDelete;
        }
        delete nil;
    }

    /**
     * @brief Inserta el nodo x después del nodo y.
     * @param x Nodo a insertar.
     * @param y Nodo después del cual se inserta el nuevo nodo.
     */
    void Insert(llnode<T>* x, llnode<T>* y) {
        x->setNext(y->getNext());
        x->setPrev(y);
        if (y->getNext() != nil) {
            y->getNext()->setPrev(x);
        }
        y->setNext(x);
    }

    /**
     * @brief Busca la llave especificada en la lista.
     * @param k Llave a buscar.
     * @return Puntero al nodo que contiene la llave, o al nodo centinela si no se encuentra.
     */
    llnode<T>* Search(const T& k) {
        llnode<T>* current = nil->getNext();
        while (current != nil && current->getKey() != k) {
            current = current->getNext();
        }
        return current;
    }

    /**
     * @brief Elimina el nodo especificado de la lista.
     * @param x Nodo a eliminar.
     */
    void Delete(llnode<T>* x) {
        if (x->getPrev() != nil) {
            x->getPrev()->setNext(x->getNext());
        } else {
            nil->setNext(x->getNext());
        }
        if (x->getNext() != nil) {
            x->getNext()->setPrev(x->getPrev());
        }
        delete x;
    }

    /**
     * @brief Devuelve el nodo centinela.
     * @return Puntero al nodo centinela.
     */
    llnode<T>* getNil() const { return nil; }

    /**
     * @brief Retorna una cadena con los detalles de la tarea.
     * @return Una cadena con los detalles de la tarea.
     */
    std::string ImprimirDatosDeTarea() const {
        return "c15424 Tarea 1 Etapa 2.";
    }
};

#endif /* llist_h */
