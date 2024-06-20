#ifndef rbtree_h
#define rbtree_h

#include <iostream>

enum colors { RED, BLACK };

// Nodos del árbol:
template <typename T>
class rbtnode {
public:
    T key;
    rbtnode<T> *p, *left, *right;
    enum colors color;
    
    // Constructor por omisión.
    rbtnode() : key(T()), p(nullptr), left(nullptr), right(nullptr), color(RED) {}
    
    // Inicialización de datos miembro.
    rbtnode(const T& k, rbtnode<T> *w = nullptr, rbtnode<T> *y = nullptr, rbtnode<T> *z = nullptr, enum colors c = RED)
        : key(k), p(w), left(y), right(z), color(c) {}
    
    ~rbtnode() {}
};

// Arbol rojinegro:
template <typename T>
class rbtree {
public:
    rbtnode<T> *root;    // raíz del árbol
    rbtnode<T> *nil;     // nodo nil (hoja) del árbol

    rbtree() {
        nil = new rbtnode<T>();
        nil->color = BLACK;
        root = nil;
    }

    ~rbtree() {
        clear(root);
        delete nil;
    }

    void clear(rbtnode<T> *node) {
        if (node != nil) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

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

    void InorderWalk(rbtnode<T> *x) {
        if (x != nil) {
            InorderWalk(x->left);
            std::cout << x->key << std::endl;
            InorderWalk(x->right);
        }
    }

    rbtnode<T>* Search(rbtnode<T> *x, const T& k) {
        while (x != nil && k != x->key) {
            if (k < x->key)
                x = x->left;
            else
                x = x->right;
        }
        return x;
    }

    rbtnode<T>* IterativeSearch(rbtnode<T> *x, const T& k) {
        return Search(x, k);
    }

    rbtnode<T>* Minimum(rbtnode<T> *x) {
        while (x->left != nil)
            x = x->left;
        return x;
    }

    rbtnode<T>* Maximum(rbtnode<T> *x) {
        while (x->right != nil)
            x = x->right;
        return x;
    }

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

    void Transplant(rbtnode<T> *u, rbtnode<T> *v) {
        if (u->p == nil)
            root = v;
        else if (u == u->p->left)
            u->p->left = v;
        else
            u->p->right = v;
        v->p = u->p;
    }

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
