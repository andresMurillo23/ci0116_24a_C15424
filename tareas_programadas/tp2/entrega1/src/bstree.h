#ifndef bstree_h
#define bstree_h

#include <iostream>

/**
 * @class bstnode
 * @brief Clase que representa un nodo en un árbol binario de búsqueda.
 * @tparam T Tipo de dato de la clave del nodo.
 */
template <typename T>
class bstnode
{
private:
    T key; ///< Clave del nodo
    bstnode<T> *p; ///< Puntero al nodo padre
    bstnode<T> *left; ///< Puntero al hijo izquierdo
    bstnode<T> *right; ///< Puntero al hijo derecho

public:
    /**
     * @brief Constructor por omisión.
     */
    bstnode() : p(nullptr), left(nullptr), right(nullptr) {}

    /**
     * @brief Constructor que inicializa los datos miembro.
     * @param k Clave del nodo.
     * @param w Puntero al nodo padre.
     * @param y Puntero al hijo izquierdo.
     * @param z Puntero al hijo derecho.
     */
    bstnode(const T& k, bstnode<T> *w = nullptr, bstnode<T> *y = nullptr, bstnode<T> *z = nullptr) : key(k), p(w), left(y), right(z) {}

    /**
     * @brief Destructor.
     */
    ~bstnode() {}

    // Getters
    /**
     * @brief Obtiene la clave del nodo.
     * @return Clave del nodo.
     */
    T getKey() const { return key; }

    /**
     * @brief Obtiene el puntero al nodo padre.
     * @return Puntero al nodo padre.
     */
    bstnode<T>* getP() const { return p; }

    /**
     * @brief Obtiene el puntero al hijo izquierdo.
     * @return Puntero al hijo izquierdo.
     */
    bstnode<T>* getLeft() const { return left; }

    /**
     * @brief Obtiene el puntero al hijo derecho.
     * @return Puntero al hijo derecho.
     */
    bstnode<T>* getRight() const { return right; }

    // Setters
    /**
     * @brief Establece la clave del nodo.
     * @param k Nueva clave del nodo.
     */
    void setKey(T k) { key = k; }

    /**
     * @brief Establece el puntero al nodo padre.
     * @param parent Nuevo puntero al nodo padre.
     */
    void setP(bstnode<T>* parent) { p = parent; }

    /**
     * @brief Establece el puntero al hijo izquierdo.
     * @param l Nuevo puntero al hijo izquierdo.
     */
    void setLeft(bstnode<T>* l) { left = l; }

    /**
     * @brief Establece el puntero al hijo derecho.
     * @param r Nuevo puntero al hijo derecho.
     */
    void setRight(bstnode<T>* r) { right = r; }
};

/**
 * @class bstree
 * @brief Clase que representa un árbol binario de búsqueda.
 * @tparam T Tipo de dato de las claves en el árbol.
 */
template <typename T>
class bstree
{
private:
    bstnode<T> *root; ///< Puntero a la raíz del árbol

public:
    /**
     * @brief Constructor que crea un árbol vacío.
     */
    bstree() { setRoot(nullptr); }

    /**
     * @brief Destructor que borra el árbol.
     */
    ~bstree() { DeleteTree(getRoot()); }

    /**
     * @brief Borra el subárbol con raíz en el nodo dado.
     * @param node Puntero a la raíz del subárbol a borrar.
     */
    void DeleteTree(bstnode<T>* node) {
        if (node == nullptr) return;
        DeleteTree(node->getLeft());
        DeleteTree(node->getRight());
        delete node;
    }

    /**
     * @brief Inserta un nodo en la posición que le corresponde en el árbol.
     * @param z Puntero al nodo a insertar.
     */
    void Insert(bstnode<T>* z) {
        bstnode<T>* currentNode = getRoot();
        bstnode<T>* lastNode = nullptr;
        while (currentNode != nullptr) {
            lastNode = currentNode;
            if (z->getKey() >= currentNode->getKey()) {
                currentNode = currentNode->getRight();
            } else {
                currentNode = currentNode->getLeft();
            }
        }
        z->setP(lastNode);
        if (lastNode == nullptr) {
            setRoot(z);
        } else if (z->getKey() >= lastNode->getKey()) {
            lastNode->setRight(z);
        } else {
            lastNode->setLeft(z);
        }
    }

    /**
     * @brief Recorre en orden el subárbol con raíz en el nodo dado.
     * @param x Puntero a la raíz del subárbol a recorrer.
     */
    void InorderWalk(bstnode<T> *x) {
        if (x == nullptr) return;
        InorderWalk(x->getLeft());
        std::cout << x->getKey() << std::endl;
        InorderWalk(x->getRight());
    }

    /**
     * @brief Busca una clave recursivamente en el subárbol con raíz en el nodo dado.
     * @param x Puntero a la raíz del subárbol donde buscar.
     * @param k Clave a buscar.
     * @return Puntero al nodo que contiene la clave, o nullptr si no se encuentra.
     */
    bstnode<T>* Search(bstnode<T> *x, const T& k) {
        if (x == nullptr || x->getKey() == k) return x;
        return (k < x->getKey()) ? Search(x->getLeft(), k) : Search(x->getRight(), k);
    }

    /**
     * @brief Busca una clave iterativamente en el subárbol con raíz en el nodo dado.
     * @param x Puntero a la raíz del subárbol donde buscar.
     * @param k Clave a buscar.
     * @return Puntero al nodo que contiene la clave, o nullptr si no se encuentra.
     */
    bstnode<T>* IterativeSearch(bstnode<T> *x, const T& k) {
        while (x != nullptr && x->getKey() != k) {
            x = (k < x->getKey()) ? x->getLeft() : x->getRight();
        }
        return x;
    }

    /**
     * @brief Devuelve el nodo con la clave menor en el subárbol con raíz en el nodo dado.
     * @param x Puntero a la raíz del subárbol donde buscar.
     * @return Puntero al nodo con la clave menor, o nullptr si el árbol está vacío.
     */
    bstnode<T>* Minimum(bstnode<T> *x) {
        if (x == nullptr) return x;
        while (x->getLeft() != nullptr) {
            x = x->getLeft();
        }
        return x;
    }

    /**
     * @brief Devuelve el nodo con la clave mayor en el subárbol con raíz en el nodo dado.
     * @param x Puntero a la raíz del subárbol donde buscar.
     * @return Puntero al nodo con la clave mayor, o nullptr si el árbol está vacío.
     */
    bstnode<T>* Maximum(bstnode<T> *x) {
        if (x == nullptr) return x;
        while (x->getRight() != nullptr) {
            x = x->getRight();
        }
        return x;
    }

    /**
     * @brief Devuelve el sucesor del nodo dado.
     * @param x Puntero al nodo cuyo sucesor se desea encontrar.
     * @return Puntero al sucesor del nodo, o nullptr si no existe.
     */
    bstnode<T>* Successor(bstnode<T> *x) {
        if (x->getRight() != nullptr) {
            return Minimum(x->getRight());
        }
        bstnode<T>* y = x->getP();
        while (y != nullptr && x == y->getRight()) {
            x = y;
            y = y->getP();
        }
        return y;
    }

    /**
     * @brief Elimina un nodo del árbol.
     * @param z Puntero al nodo a eliminar.
     */
    void Delete(bstnode<T>* z) {
        if (z == nullptr) return;

        bstnode<T>* y; // Nodo que será eliminado
        bstnode<T>* x; // Nodo que reemplazará a y

        y = (z->getLeft() == nullptr || z->getRight() == nullptr) ? z : Successor(z);
        x = (y->getLeft() != nullptr) ? y->getLeft() : y->getRight();

        if (x != nullptr) {
            x->setP(y->getP());
        }

        if (y->getP() == nullptr) {
            root = x;
        } else if (y == y->getP()->getLeft()) {
            y->getP()->setLeft(x);
        } else {
            y->getP()->setRight(x);
        }

        if (y != z) {
            z->setKey(y->getKey());
        }

        delete y;
    }

    /**
     * @brief Obtiene la raíz del árbol.
     * @return Puntero a la raíz del árbol.
     */
    bstnode<T>* getRoot() const { return root; }

    /**
     * @brief Establece la raíz del árbol.
     * @param r Puntero a la nueva raíz del árbol.
     */
    void setRoot(bstnode<T>* r) { root = r; }

    /**
     * @brief Imprime los datos de la tarea.
     * @return Cadena con el número de carné, identificador de la tarea y etapa.
     */
    std::string ImprimirDatosDeTarea() {
        return "b12345 Tarea 1 Etapa 1";
    }
};

#endif /* bstree_h */