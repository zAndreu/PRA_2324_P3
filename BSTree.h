#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree
{
private:
    // miembros privados
    int nelem;
    BSNode<T> *root;
    BSNode<T> *search(BSNode<T> *n, T e) const
    {
        if (n == nullptr)
            return nullptr;
        if (e == n->elem)
            return n;
        else if (e < n->elem)
            return search(n->left, e);
        else
            return search(n->right, e);
    }

    BSNode<T> *insert(BSNode<T> *n, T e)
    {
        if (n == nullptr)
        {
            nelem++;
            return new BSNode<T>(e);
        }
        if (e == n->elem)
            throw std::runtime_error("Elemento ya existe");
        else if (e < n->elem)
            n->left = insert(n->left, e);
        else
            n->right = insert(n->right, e);
        return n;
    }

    void print_inorder(std::ostream &out, BSNode<T> *n) const
    {
        if (n != nullptr)
        {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    BSNode<T> *remove(BSNode<T> *n, T e)
    {
        if (n == nullptr)
            throw std::runtime_error("Elemento no encontrado");
        if (e < n->elem)
        {
            n->left = remove(n->left, e);
        }
        else if (e > n->elem)
        {
            n->right = remove(n->right, e);
        }
        else
        {
            // Nodo encontrado
            if (n->left == nullptr)
            {
                BSNode<T> *right = n->right;
                delete n;
                nelem--;
                return right;
            }
            else if (n->right == nullptr)
            {
                BSNode<T> *left = n->left;
                delete n;
                nelem--;
                return left;
            }
            else
            {
                // Nodo con dos hijos
                T pred = max(n->left);
                n->elem = pred;
                n->left = remove_max(n->left);
            }
        }
        return n;
    }

    T max(BSNode<T> *n) const
    {
        while (n->right != nullptr)
        {
            n = n->right;
        }
        return n->elem;
    }

    BSNode<T> *remove_max(BSNode<T> *n)
    {
        if (n->right == nullptr)
        {
            BSNode<T> *left = n->left;
            delete n;
            return left;
        }
        n->right = remove_max(n->right);
        return n;
    }

    void delete_cascade(BSNode<T> *n)
    {
        if (n != nullptr)
        {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:
    // miembros públicos

    ~BSTree() { delete_cascade(root); }
    BSTree() : nelem(0), root(nullptr) {}

    int size() const { return nelem; }

    T search(T e) const
    {
        BSNode<T> *res = search(root, e);
        if (res == nullptr)
            throw std::runtime_error("Elemento no encontrado");
        return res->elem;
    }

    T operator[](T e) const { return (search(e)); }

    void insert(T e) { root = insert(root, e); }

    friend std::ostream &operator<<(std::ostream &out, const BSTree<T> &bst)
    {
        out << "BSTree(inorder): ";
        bst.print_inorder(out, bst.root);
        return out;
    }

    void remove(T e) { root = remove(root, e); }
};

#endif