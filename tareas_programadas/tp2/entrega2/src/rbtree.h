#ifndef rbtree_h
#define rbtree_h

#include <iostream>

/// Enum para representar los colores de los nodos.
enum colors { RED, BLACK };

/// Clase que representa un nodo del árbol rojinegro.
template <typename T>
class rbtnode {
public:
    T key; ///< Llave del nodo.
    rbtnode<T> *p, *left, *right; ///< Punteros al padre, hijo izquierdo e hijo derecho.
    enum colors color; ///< Color del nodo.

    /// Constructor por omisión.
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
    
    /// Destructor.
    ~rbtnode() {}
};

/// Clase que representa un árbol rojinegro.
template <typename T>
class rbtree {
public:
    rbtnode<T> *root;  ///< Raíz del árbol.
    rbtnode<T> *nil;  ///< Nodo nil (hoja) del árbol.

    /// Constructor.
    rbtree() {
        nil = new rbtnode<T>();
        nil->color = BLACK;
        root = nil;
    }

    /// Destructor.
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
            clear(node->left);
            clear(node->right);
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
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        z->p = y;
        if (y == nil)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        z->left = nil;
        z->right = nil;
        z->color = RED;
        RBInsertFixup(z);
    }

    /**
     * @brief Realiza un recorrido inorden del árbol.
     * 
     * @param x Nodo desde el cual se inicia el recorrido.
     */
    void InorderWalk(rbtnode<T> *x) {
        if (x != nil) {
            InorderWalk(x->left);
            std::cout << x->key << std::endl;
            InorderWalk(x->right);
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
        while (x != nil && k != x->key) {
            if (k < x->key)
                x = x->left;
            else
                x = x->right;
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
        while (x->left != nil)
            x = x->left;
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
        while (x->right != nil)
            x = x->right;
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
        if (x->right != nil)
            return Minimum(x->right);
        rbtnode<T> *y = x->p;
        while (y != nil && x == y->right) {
            x = y;
            y = y->p;
        }
        return y;
    }

    /**
     * @brief Realiza una rotación a la izquierda en el árbol.
     * 
     * @param x Nodo sobre el cual se realiza la rotación.
     */
    void LeftRotate(rbtnode<T> *x) {
        rbtnode<T> *y = x->right;
        x->right = y->left;
        if (y->left != nil)
            y->left->p = x;
        y->p = x->p;
        if (x->p == nil)
            root = y;
        else if (x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;
        y->left = x;
        x->p = y;
    }

    /**
     * @brief Realiza una rotación a la derecha en el árbol.
     * 
     * @param x Nodo sobre el cual se realiza la rotación.
     */
    void RightRotate(rbtnode<T> *x) {
        rbtnode<T> *y = x->left;
        x->left = y->right;
        if (y->right != nil)
            y->right->p = x;
        y->p = x->p;
        if (x->p == nil)
            root = y;
        else if (x == x->p->right)
            x->p->right = y;
        else
            x->p->left = y;
        y->right = x;
        x->p = y;
    }

    /**
     * @brief Corrige el árbol después de una inserción.
     * 
     * @param z Nodo insertado.
     */
    void RBInsertFixup(rbtnode<T> *z) {
        while (z->p->color == RED) {
            if (z->p == z->p->p->left) {
                rbtnode<T> *y = z->p->p->right;
                if (y->color == RED) {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                } else {
                    if (z == z->p->right) {
                        z = z->p;
                        LeftRotate(z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    RightRotate(z->p->p);
                }
            } else {
                rbtnode<T> *y = z->p->p->left;
                if (y->color == RED) {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                } else {
                    if (z == z->p->left) {
                        z = z->p;
                        RightRotate(z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    LeftRotate(z->p->p);
                }
            }
        }
        root->color = BLACK;
    }

    /**
     * @brief Transplanta un subárbol en el lugar de otro subárbol.
     * 
     * @param u Nodo a ser reemplazado.
     * @param v Nodo que reemplaza.
     */
    void Transplant(rbtnode<T> *u, rbtnode<T> *v) {
        if (u->p == nil)
            root = v;
        else if (u == u->p->left)
            u->p->left = v;
        else
            u->p->right = v;
        v->p = u->p;
    }

    /**
     * @brief Elimina un nodo del árbol rojinegro.
     * 
     * @param z Nodo a eliminar.
     */
    void Delete(rbtnode<T> *z) {
        rbtnode<T> *y = z;
        rbtnode<T> *x;
        enum colors y_original_color = y->color;
        if (z->left == nil) {
            x = z->right;
            Transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            Transplant(z, z->left);
        } else {
            y = Minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->p == z)
                x->p = y;
            else {
                Transplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }
            Transplant(z, y);
            y->left = z->left;
            y->left->p = y;
            y->color = z->color;
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
        while (x != root && x->color == BLACK) {
            if (x == x->p->left) {
                rbtnode<T> *w = x->p->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->p->color = RED;
                    LeftRotate(x->p);
                    w = x->p->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->p;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        RightRotate(w);
                        w = x->p->right;
                    }
                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->right->color = BLACK;
                    LeftRotate(x->p);
                    x = root;
                }
            } else {
                rbtnode<T> *w = x->p->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->p->color = RED;
                    RightRotate(x->p);
                    w = x->p->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->p;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        LeftRotate(w);
                        w = x->p->left;
                    }
                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->left->color = BLACK;
                    RightRotate(x->p);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
};

#endif // rbtree_h
