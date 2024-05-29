#ifndef llist_h
#define llist_h

#include <iostream>
#include <stdexcept>

/**
 * @class llnode
 * @brief Clase para representar un nodo en una lista enlazada.
 * @tparam T Tipo de dato almacenado en el nodo.
 */
template <typename T>
class llnode
{
private:
    T key; ///< Clave almacenada en el nodo.
    llnode<T> *prev; ///< Puntero al nodo anterior.
    llnode<T> *next; ///< Puntero al siguiente nodo.

public:
    /**
     * @brief Constructor por defecto.
     */
    llnode() : key(T()), prev(nullptr), next(nullptr) {}

    /**
     * @brief Constructor con inicialización de datos miembros.
     * @param k Clave a almacenar en el nodo.
     * @param w Puntero al nodo anterior.
     * @param y Puntero al siguiente nodo.
     */
    llnode(const T &k, llnode<T> *w = nullptr, llnode<T> *y = nullptr) : key(k), prev(w), next(y) {}

    /**
     * @brief Destructor.
     */
    ~llnode() {}

    /**
     * @brief Obtiene la clave almacenada en el nodo.
     * @return La clave almacenada en el nodo.
     */
    T getKey() const {
        return key;
    }

    /**
     * @brief Obtiene el puntero al nodo anterior.
     * @return El puntero al nodo anterior.
     */
    llnode<T>* getPrev() const {
        return prev;
    }

    /**
     * @brief Obtiene el puntero al siguiente nodo.
     * @return El puntero al siguiente nodo.
     */
    llnode<T>* getNext() const {
        return next;
    }

    /**
     * @brief Establece la clave del nodo.
     * @param k Clave a establecer.
     */
    void setKey(const T &k) {
        key = k;
    }

    /**
     * @brief Establece el puntero al nodo anterior.
     * @param p Puntero al nodo anterior.
     */
    void setPrev(llnode<T> *p) {
        prev = p;
    }

    /**
     * @brief Establece el puntero al siguiente nodo.
     * @param n Puntero al siguiente nodo.
     */
    void setNext(llnode<T> *n) {
        next = n;
    }
};

/**
 * @class llist
 * @brief Clase para representar una lista enlazada con nodo centinela.
 * @tparam T Tipo de dato almacenado en los nodos de la lista.
 */
template <typename T>
class llist
{
private:
    llnode<T> *nil; ///< Nodo centinela.

public:
    /**
     * @brief Constructor. Crea una lista vacía.
     */
    llist()
    {
        nil = new llnode<T>();
        nil->setNext(nil);
        nil->setPrev(nil);
    }

    /**
     * @brief Destructor. Borra todos los nodos de la lista.
     */
    ~llist()
    {
        llnode<T> *current = nil->getNext();
        while (current != nil)
        {
            llnode<T> *temp = current;
            current = current->getNext();
            delete temp;
        }
        delete nil;
    }

    /**
     * @brief Inserta un nodo en la lista.
     * @param x Puntero al nodo a insertar.
     */
    void Insert(llnode<T> *x)
    {
        if (!x) {
            throw std::invalid_argument("El nodo a insertar no puede ser nulo");
        }
        x->setNext(nil->getNext());
        nil->getNext()->setPrev(x);
        nil->setNext(x);
        x->setPrev(nil);
    }

    /**
     * @brief Busca una clave en la lista.
     * @param k Clave a buscar.
     * @return Puntero al nodo que contiene la clave, o al nodo centinela si no se encuentra.
     */
    llnode<T> *Search(const T &k)
    {
        llnode<T> *x = nil->getNext();
        while (x != nil && x->getKey() != k)
        {
            x = x->getNext();
        }
        if (x == nil) {
            std::cout << "Clave no encontrada en la lista." << std::endl;
        }
        return x;
    }

    /**
     * @brief Elimina un nodo de la lista.
     * @param x Puntero al nodo a eliminar.
     */
    void Delete(llnode<T> *x)
    {
        if (!x || x == nil) {
            throw std::invalid_argument("El nodo a eliminar no puede ser nulo ni el nodo centinela");
        }
        x->getPrev()->setNext(x->getNext());
        x->getNext()->setPrev(x->getPrev());
        delete x;
    }

    /**
     * @brief Imprime los datos de la tarea.
     * @return Cadena con el número de carné, identificador de la tarea y etapa.
     */
    std::string ImprimirDatosDeTarea()
    {
        return "b12345 Tarea 1 Etapa 1";
    }
};

#endif /* llist_h */
