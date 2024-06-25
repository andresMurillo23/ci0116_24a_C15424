// Copyright [2024] <Copyright Andres Murillo>
#ifndef rbtree_h
#define rbtree_h

#include <iostream>

// Enum para representar los colores de los nodos.
enum colors { RED, BLACK };

// Clase que representa un nodo del árbol rojinegro.
template <typename T>
class rbtnode {
private:
    T key;  ///< Llave del nodo.
    rbtnode<T> *p, *left, *right;    ///< Punteros al padre, hijo izquierdo e hijo derecho.
    enum colors color;               ///< Color del nodo.

public:
    /**
     * @brief Constructor por omisión.
     * 
     * Inicializa el nodo con valores predeterminados.
     * La llave se inicializa con el valor por defecto del tipo T.
     * Los punteros se inicializan a nullptr.
     * El color se inicializa a RED.
     */
    rbtnode() : key(T()), p(nullptr), left(nullptr), right(nullptr), color(RED) {}

    /**
     * @brief Inicialización de datos miembro.
     * 
     * @param k Llave del nodo.
     * @param w Puntero al padre.
     * @param y Puntero al hijo izquierdo.
     * @param z Puntero al hijo derecho.
     * @param c Color del nodo.
     */
    rbtnode(const T& k, rbtnode<T> *w = nullptr, rbtnode<T> *y = nullptr, rbtnode<T> *z = nullptr, enum colors c = RED)
        : key(k), p(w), left(y), right(z), color(c) {}

    /**
     * @brief Destructor.
     * 
     * Destructor por defecto para el nodo.
     */
    ~rbtnode() {}

    // Getters
    /**
     * @brief Obtiene la llave del nodo.
     * 
     * @return La llave del nodo.
     */
    T getKey() const { return key; }

    /**
     * @brief Obtiene el padre del nodo.
     * 
     * @return El padre del nodo.
     */
    rbtnode<T>* getParent() const { return p; }

    /**
     * @brief Obtiene el hijo izquierdo del nodo.
     * 
     * @return El hijo izquierdo del nodo.
     */
    rbtnode<T>* getLeft() const { return left; }

    /**
     * @brief Obtiene el hijo derecho del nodo.
     * 
     * @return El hijo derecho del nodo.
     */
    rbtnode<T>* getRight() const { return right; }

    /**
     * @brief Obtiene el color del nodo.
     * 
     * @return El color del nodo.
     */
    colors getColor() const { return color; }

    /// Setters
    /**
     * @brief Establece la llave del nodo.
     * 
     * @param k La nueva llave del nodo.
     */
    void setKey(const T& k) { key = k; }

    /**
     * @brief Establece el padre del nodo.
     * 
     * @param w El nuevo padre del nodo.
     */
    void setParent(rbtnode<T>* w) { p = w; }

    /**
     * @brief Establece el hijo izquierdo del nodo.
     * 
     * @param y El nuevo hijo izquierdo del nodo.
     */
    void setLeft(rbtnode<T>* y) { left = y; }

    /**
     * @brief Establece el hijo derecho del nodo.
     * 
     * @param z El nuevo hijo derecho del nodo.
     */
    void setRight(rbtnode<T>* z) { right = z; }

    /**
     * @brief Establece el color del nodo.
     * 
     * @param c El nuevo color del nodo.
     */
    void setColor(colors c) { color = c; }
};

// Clase que representa un árbol rojinegro.
template <typename T>
class rbtree {
public:
    rbtnode<T> *root;   ///< Raíz del árbol.
    rbtnode<T> *nil;    ///< Nodo nil (hoja) del árbol.

    // Constructor.
    rbtree() {
        nil = new rbtnode<T>();
        nil->setColor(BLACK);
        root = nil;
    }

    // Destructor.
    ~rbtree() {
        clear(root);
        delete nil;
    }

    /**
     * @brief Limpia el subárbol a partir de un nodo dado.
     * 
     * @param node Nodo desde el cual se limpia el subárbol.
     */
    void clear(rbtnode<T> *node) {
        if (node != nil) {
            clear(node->getLeft());
            clear(node->getRight());
            delete node;
        }
    }

    /**
     * @brief Inserta un nodo en el árbol rojinegro.
     * 
     * @param z Nodo a insertar.
     */
    void Insert(rbtnode<T>* z) {
        rbtnode<T> *y = nil;
        rbtnode<T> *x = root;
        while (x != nil) {
            y = x;
            if (z->getKey() < x->getKey())
                x = x->getLeft();
            else
                x = x->getRight();
        }
        z->setParent(y);
        if (y == nil)
            root = z;
        else if (z->getKey() < y->getKey())
            y->setLeft(z);
        else
            y->setRight(z);
        z->setLeft(nil);
        z->setRight(nil);
        z->setColor(RED);
        RBInsertFixup(z);
    }

    /**
     * @brief Realiza un recorrido inorden del árbol.
     * 
     * @param x Nodo desde el cual se inicia el recorrido.
     */
    void InorderWalk(rbtnode<T> *x) {
        if (x != nil) {
            InorderWalk(x->getLeft());
            std::cout << x->getKey() << std::endl;
            InorderWalk(x->getRight());
        }
    }

    /**
     * @brief Busca un nodo en el árbol.
     * 
     * @param x Nodo desde el cual se inicia la búsqueda.
     * @param k Llave a buscar.
     * 
     * @return rbtnode<T>* Puntero al nodo encontrado o nil si no se encuentra.
     */
    rbtnode<T>* Search(rbtnode<T> *x, const T& k) {
        while (x != nil && k != x->getKey()) {
            if (k < x->getKey())
                x = x->getLeft();
            else
                x = x->getRight();
        }
        return x;
    }

    /**
     * @brief Busca un nodo en el árbol de forma iterativa.
     * 
     * @param x Nodo desde el cual se inicia la búsqueda.
     * @param k Llave a buscar.
     * 
     * @return rbtnode<T>* Puntero al nodo encontrado o nil si no se encuentra.
     */
    rbtnode<T>* IterativeSearch(rbtnode<T> *x, const T& k) {
        return Search(x, k);
    }

    /**
     * @brief Encuentra el nodo con la llave mínima en el subárbol dado.
     * 
     * @param x Nodo desde el cual se busca la llave mínima.
     * 
     * @return rbtnode<T>* Puntero al nodo con la llave mínima.
     */
    rbtnode<T>* Minimum(rbtnode<T> *x) {
        while (x->getLeft() != nil)
            x = x->getLeft();
        return x;
    }

    /**
     * @brief Encuentra el nodo con la llave máxima en el subárbol dado.
     * 
     * @param x Nodo desde el cual se busca la llave máxima.
     * 
     * @return rbtnode<T>* Puntero al nodo con la llave máxima.
     */
    rbtnode<T>* Maximum(rbtnode<T> *x) {
        while (x->getRight() != nil)
            x = x->getRight();
        return x;
    }

    /**
     * @brief Encuentra el sucesor de un nodo dado.
     * 
     * @param x Nodo del cual se busca el sucesor.
     * 
     * @return rbtnode<T>* Puntero al sucesor del nodo.
     */
    rbtnode<T>* Successor(rbtnode<T> *x) {
        if (x->getRight() != nil)
            return Minimum(x->getRight());
        rbtnode<T> *y = x->getParent();
        while (y != nil && x == y->getRight()) {
            x = y;
            y = y->getParent();
        }
        return y;
    }

    /**
     * @brief Realiza una rotación a la izquierda en el árbol.
     * 
     * @param x Nodo sobre el cual se realiza la rotación.
     */
    void LeftRotate(rbtnode<T> *x) {
        rbtnode<T> *y = x->getRight();
        x->setRight(y->getLeft());
        if (y->getLeft() != nil)
            y->getLeft()->setParent(x);
        y->setParent(x->getParent());
        if (x->getParent() == nil)
            root = y;
        else if (x == x->getParent()->getLeft())
            x->getParent()->setLeft(y);
        else
            x->getParent()->setRight(y);
        y->setLeft(x);
        x->setParent(y);
    }

    /**
     * @brief Realiza una rotación a la derecha en el árbol.
     * 
     * @param x Nodo sobre el cual se realiza la rotación.
     */
    void RightRotate(rbtnode<T> *x) {
        rbtnode<T> *y = x->getLeft();
        x->setLeft(y->getRight());
        if (y->getRight() != nil)
            y->getRight()->setParent(x);
        y->setParent(x->getParent());
        if (x->getParent() == nil)
            root = y;
        else if (x == x->getParent()->getRight())
            x->getParent()->setRight(y);
        else
            x->getParent()->setLeft(y);
        y->setRight(x);
        x->setParent(y);
    }

    /**
     * @brief Corrige el árbol después de una inserción.
     * 
     * @param z Nodo insertado.
     */
    void RBInsertFixup(rbtnode<T> *z) {
        while (z->getParent()->getColor() == RED) {
            if (z->getParent() == z->getParent()->getParent()->getLeft()) {
                rbtnode<T> *y = z->getParent()->getParent()->getRight();
                if (y->getColor() == RED) {
                    z->getParent()->setColor(BLACK);
                    y->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    z = z->getParent()->getParent();
                } else {
                    if (z == z->getParent()->getRight()) {
                        z = z->getParent();
                        LeftRotate(z);
                    }
                    z->getParent()->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    RightRotate(z->getParent()->getParent());
                }
            } else {
                rbtnode<T> *y = z->getParent()->getParent()->getLeft();
                if (y->getColor() == RED) {
                    z->getParent()->setColor(BLACK);
                    y->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    z = z->getParent()->getParent();
                } else {
                    if (z == z->getParent()->getLeft()) {
                        z = z->getParent();
                        RightRotate(z);
                    }
                    z->getParent()->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    LeftRotate(z->getParent()->getParent());
                }
            }
        }
        root->setColor(BLACK);
    }

    /**
     * @brief Transplanta un subárbol en el lugar de otro subárbol.
     * 
     * @param u Nodo a ser reemplazado.
     * @param v Nodo que reemplaza.
     */
    void Transplant(rbtnode<T> *u, rbtnode<T> *v) {
        if (u->getParent() == nil)
            root = v;
        else if (u == u->getParent()->getLeft())
            u->getParent()->setLeft(v);
        else
            u->getParent()->setRight(v);
        v->setParent(u->getParent());
    }

    /**
     * @brief Elimina un nodo del árbol rojinegro.
     * 
     * @param z Nodo a eliminar.
     */
    void Delete(rbtnode<T> *z) {
        rbtnode<T> *y = z;
        rbtnode<T> *x;
        enum colors y_original_color = y->getColor();
        if (z->getLeft() == nil) {
            x = z->getRight();
            Transplant(z, z->getRight());
        } else if (z->getRight() == nil) {
            x = z->getLeft();
            Transplant(z, z->getLeft());
        } else {
            y = Minimum(z->getRight());
            y_original_color = y->getColor();
            x = y->getRight();
            if (y->getParent() == z)
                x->setParent(y);
            else {
                Transplant(y, y->getRight());
                y->setRight(z->getRight());
                y->getRight()->setParent(y);
            }
            Transplant(z, y);
            y->setLeft(z->getLeft());
            y->getLeft()->setParent(y);
            y->setColor(z->getColor());
        }
        if (y_original_color == BLACK)
            RBDeleteFixup(x);
    }

    /**
     * @brief Corrige el árbol después de una eliminación.
     * 
     * @param x Nodo afectado por la eliminación.
     */
    void RBDeleteFixup(rbtnode<T> *x) {
        while (x != root && x->getColor() == BLACK) {
            if (x == x->getParent()->getLeft()) {
                rbtnode<T> *w = x->getParent()->getRight();
                if (w->getColor() == RED) {
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    LeftRotate(x->getParent());
                    w = x->getParent()->getRight();
                }
                if (w->getLeft()->getColor() == BLACK && w->getRight()->getColor() == BLACK) {
                    w->setColor(RED);
                    x = x->getParent();
                } else {
                    if (w->getRight()->getColor() == BLACK) {
                        w->getLeft()->setColor(BLACK);
                        w->setColor(RED);
                        RightRotate(w);
                        w = x->getParent()->getRight();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(BLACK);
                    w->getRight()->setColor(BLACK);
                    LeftRotate(x->getParent());
                    x = root;
                }
            } else {
                rbtnode<T> *w = x->getParent()->getLeft();
                if (w->getColor() == RED) {
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    RightRotate(x->getParent());
                    w = x->getParent()->getLeft();
                }
                if (w->getRight()->getColor() == BLACK && w->getLeft()->getColor() == BLACK) {
                    w->setColor(RED);
                    x = x->getParent();
                } else {
                    if (w->getLeft()->getColor() == BLACK) {
                        w->getRight()->setColor(BLACK);
                        w->setColor(RED);
                        LeftRotate(w);
                        w = x->getParent()->getLeft();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(BLACK);
                    w->getLeft()->setColor(BLACK);
                    RightRotate(x->getParent());
                    x = root;
                }
            }
        }
        x->setColor(BLACK);
    }

    /**
     * @brief Imprime los datos de la tarea.
     * 
     * @return Una cadena con los datos de la tarea.
     */
    std::string ImprimirDatosDeTarea() {
        return "c15424 Tarea 2 Etapa 2";
    }
};

#endif  // rbtree_h
