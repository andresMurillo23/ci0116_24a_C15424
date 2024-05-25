#ifndef bstree_h
#define bstree_h

#include <iostream>
#include <string>
#include <vector>

/**
 * @class bstnode
 * @brief Clase que representa un nodo en un árbol binario de búsqueda (BST).
 */
template <typename T>
class bstnode {
private:
    T key;               ///< Llave del nodo
    bstnode<T>* p;       ///< Puntero al nodo padre
    bstnode<T>* left;    ///< Puntero al hijo izquierdo
    bstnode<T>* right;   ///< Puntero al hijo derecho

public:
    /**
     * @brief Constructor por omisión.
     */
    bstnode() : key(T()), p(nullptr), left(nullptr), right(nullptr) {}

    /**
     * @brief Constructor que inicializa los datos miembros.
     * @param k Llave del nodo.
     * @param w Puntero al nodo padre.
     * @param y Puntero al hijo izquierdo.
     * @param z Puntero al hijo derecho.
     */
    bstnode(const T& k, bstnode<T>* w = nullptr, bstnode<T>* y = nullptr, bstnode<T>* z = nullptr) : key(k), p(w), left(y), right(z) {}

    /**
     * @brief Destructor.
     */
    ~bstnode() {}

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
     * @brief Obtiene el puntero al nodo padre.
     * @return El puntero al nodo padre.
     */
    bstnode<T>* getParent() const { return p; }

    /**
     * @brief Establece el puntero al nodo padre.
     * @param w El nuevo puntero al nodo padre.
     */
    void setParent(bstnode<T>* w) { p = w; }

    /**
     * @brief Obtiene el puntero al hijo izquierdo.
     * @return El puntero al hijo izquierdo.
     */
    bstnode<T>* getLeft() const { return left; }

    /**
     * @brief Establece el puntero al hijo izquierdo.
     * @param y El nuevo puntero al hijo izquierdo.
     */
    void setLeft(bstnode<T>* y) { left = y; }

    /**
     * @brief Obtiene el puntero al hijo derecho.
     * @return El puntero al hijo derecho.
     */
    bstnode<T>* getRight() const { return right; }

    /**
     * @brief Establece el puntero al hijo derecho.
     * @param z El nuevo puntero al hijo derecho.
     */
    void setRight(bstnode<T>* z) { right = z; }
};

/**
 * @class bstree
 * @brief Clase que representa un árbol binario de búsqueda (BST).
 */
template <typename T>
class bstree {
private:
    bstnode<T>* root;  ///< Raíz del árbol

    /**
     * @brief Reemplaza un subárbol como hijo de su padre con otro subárbol.
     * @param u Subárbol a ser reemplazado.
     * @param v Subárbol reemplazante.
     */
    void transplant(bstnode<T>* u, bstnode<T>* v) {
        if (u->getParent() == nullptr) {
            root = v;
        } else if (u == u->getParent()->getLeft()) {
            u->getParent()->setLeft(v);
        } else {
            u->getParent()->setRight(v);
        }
        if (v != nullptr) {
            v->setParent(u->getParent());
        }
    }

    /**
     * @brief Encuentra la ubicación adecuada para insertar un nuevo nodo.
     * @param z Nodo a insertar.
     * @return Puntero al nodo padre donde se debe insertar el nuevo nodo.
     */
    bstnode<T>* findInsertLocation(bstnode<T>* z) {
        bstnode<T>* y = nullptr;
        bstnode<T>* x = root;
        while (x != nullptr) {
            y = x;
            if (z->getKey() < x->getKey()) {
                x = x->getLeft();
            } else {
                x = x->getRight();
            }
        }
        return y;
    }

    /**
     * @brief Inserta un nodo en la ubicación especificada.
     * @param z Nodo a insertar.
     * @param y Nodo padre donde se debe insertar el nuevo nodo.
     */
    void insertAtLocation(bstnode<T>* z, bstnode<T>* y) {
        z->setParent(y);
        if (y == nullptr) {
            root = z;
        } else if (z->getKey() < y->getKey()) {
            y->setLeft(z);
        } else {
            y->setRight(z);
        }
    }

    /**
     * @brief Elimina un nodo que tiene uno o ningún hijo.
     * @param z Nodo a eliminar.
     */
    void deleteNodeWithOneOrNoChildren(bstnode<T>* z) {
        if (z->getLeft() == nullptr) {
            transplant(z, z->getRight());
        } else {
            transplant(z, z->getLeft());
        }
    }

    /**
     * @brief Elimina un nodo que tiene dos hijos.
     * @param z Nodo a eliminar.
     */
    void deleteNodeWithTwoChildren(bstnode<T>* z) {
        bstnode<T>* y = Minimum(z->getRight());
        if (y->getParent() != z) {
            transplant(y, y->getRight());
            y->setRight(z->getRight());
            y->getRight()->setParent(y);
        }
        transplant(z, y);
        y->setLeft(z->getLeft());
        y->getLeft()->setParent(y);
    }

    /**
     * @brief Construye un árbol balanceado a partir de un vector de nodos.
     * @param nodes Vector de punteros a nodos.
     * @param start Índice de inicio.
     * @param end Índice de fin.
     * @return Puntero a la raíz del subárbol balanceado.
     */
    bstnode<T>* buildBalancedTree(std::vector<bstnode<T>*>& nodes, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        bstnode<T>* node = nodes[mid];

        node->setLeft(buildBalancedTree(nodes, start, mid - 1));
        if (node->getLeft() != nullptr) {
            node->getLeft()->setParent(node);
        }

        node->setRight(buildBalancedTree(nodes, mid + 1, end));
        if (node->getRight() != nullptr) {
            node->getRight()->setParent(node);
        }

        return node;
    }

public:
    /**
     * @brief Constructor que crea un árbol vacío.
     */
    bstree() : root(nullptr) {}

    /**
     * @brief Destructor que borra el árbol.
     */
    ~bstree() {
        clear(root);
    }

    /**
     * @brief Limpia (elimina) el subárbol con raíz en el nodo especificado.
     * @param node Raíz del subárbol a eliminar.
     */
    void clear(bstnode<T>* node) {
        if (node != nullptr) {
            clear(node->getLeft());
            clear(node->getRight());
            delete node;
        }
    }

    /**
     * @brief Inserta un nodo en la posición correspondiente en el árbol.
     * @param z Nodo a insertar.
     */
    void Insert(bstnode<T>* z) {
        bstnode<T>* y = findInsertLocation(z);
        insertAtLocation(z, y);
    }

    /**
     * @brief Recorre en orden el subárbol con raíz en el nodo especificado e imprime las llaves.
     * @param x Raíz del subárbol a recorrer.
     */
    void InorderWalk(bstnode<T>* x) {
        if (x != nullptr) {
            InorderWalk(x->getLeft());
            std::cout << x->getKey() << std::endl;
            InorderWalk(x->getRight());
        }
    }

    /**
     * @brief Busca la llave especificada recursivamente en el subárbol con raíz en el nodo especificado.
     * @param x Raíz del subárbol donde buscar.
     * @param k Llave a buscar.
     * @return Puntero al nodo que contiene la llave, o nullptr si no se encuentra.
     */
    bstnode<T>* Search(bstnode<T>* x, const T& k) {
        if (x == nullptr || k == x->getKey()) {
            return x;
        }
        if (k < x->getKey()) {
            return Search(x->getLeft(), k);
        } else {
            return Search(x->getRight(), k);
        }
    }

    /**
     * @brief Busca la llave especificada iterativamente en el subárbol con raíz en el nodo especificado.
     * @param x Raíz del subárbol donde buscar.
     * @param k Llave a buscar.
     * @return Puntero al nodo que contiene la llave, o nullptr si no se encuentra.
     */
    bstnode<T>* IterativeSearch(bstnode<T>* x, const T& k) {
        while (x != nullptr && k != x->getKey()) {
            if (k < x->getKey()) {
                x = x->getLeft();
            } else {
                x = x->getRight();
            }
        }
        return x;
    }

    /**
     * @brief Devuelve el nodo con la llave menor en el subárbol con raíz en el nodo especificado.
     * @param x Raíz del subárbol donde buscar.
     * @return Puntero al nodo con la llave menor, o nullptr si el árbol está vacío.
     */
    bstnode<T>* Minimum(bstnode<T>* x) {
        while (x != nullptr && x->getLeft() != nullptr) {
            x = x->getLeft();
        }
        return x;
    }

    /**
     * @brief Devuelve el nodo con la llave mayor en el subárbol con raíz en el nodo especificado.
     * @param x Raíz del subárbol donde buscar.
     * @return Puntero al nodo con la llave mayor, o nullptr si el árbol está vacío.
     */
    bstnode<T>* Maximum(bstnode<T>* x) {
        while (x != nullptr && x->getRight() != nullptr) {
            x = x->getRight();
        }
        return x;
    }

    /**
     * @brief Devuelve el sucesor del nodo especificado.
     * @param x Nodo del cual se quiere encontrar el sucesor.
     * @return Puntero al nodo sucesor, o nullptr si no existe sucesor.
     */
    bstnode<T>* Successor(bstnode<T>* x) {
        if (x->getRight() != nullptr) {
            return Minimum(x->getRight());
        }
        bstnode<T>* y = x->getParent();
        while (y != nullptr && x == y->getRight()) {
            x = y;
            y = y->getParent();
        }
        return y;
    }

    /**
     * @brief Elimina el nodo especificado del árbol.
     * @param z Nodo a eliminar.
     */
    void Delete(bstnode<T>* z) {
        if (z->getLeft() == nullptr || z->getRight() == nullptr) {
            deleteNodeWithOneOrNoChildren(z);
        } else {
            deleteNodeWithTwoChildren(z);
        }
        delete z;
    }

    /**
     * @brief Devuelve la raíz del árbol.
     * @return Puntero a la raíz del árbol.
     */
    bstnode<T>* getRoot() const {
        return root;
    }

    /**
     * @brief Construye un árbol balanceado a partir de un vector de llaves.
     * @param keys Vector de llaves.
     */
    void buildBalancedTree(const std::vector<T>& keys) {
        std::vector<bstnode<T>*> nodes;
        for (const T& key : keys) {
            nodes.push_back(new bstnode<T>(key));
        }
        root = buildBalancedTree(nodes, 0, nodes.size() - 1);
    }

    /**
     * @brief Limpia el árbol entero.
     */
    void clearTree() {
        clear(root);
        root = nullptr;
    }

    /**
     * @brief Retorna una cadena con los detalles de la tarea.
     * @return Una cadena con los detalles de la tarea.
     */
    std::string ImprimirDatosDeTarea() const {
        return "c15424 Tarea 1 Etapa 2.";
    }
};

#endif /* bstree_h */
