#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V>
{

private:
    // ...
    BSTree<TableEntry<V>> *tree;

public:
    // ...
    BSTreeDict() { tree = new BSTree<TableEntry<V>>(); }
    ~BSTreeDict() { delete (tree); }

    // De Dict.h
    void insert(const std::string &key, const V &value) override
    {
        TableEntry<V> te(key, value);
        tree->insert(te);
    }

    V search(const std::string &key) override
    {
        TableEntry<V> te(key);
        TableEntry<V> res = tree->search(te);
        return (res.value_);
    }

    V remove(const std::string &key) override
    {
        TableEntry<V> te(key);
        TableEntry<V> res = tree->search(te);
        tree->remove(te);
        return (res.value_);
    }

    int entries() override { return (tree->size()); }

    // Otros metodos propios
    friend std::ostream &operator<<(std::ostream &out, const BSTreeDict<V> &bs)
    {
        out << *(bs.tree);
        return (out);
    }

    V operator[](std::string key) { return (search(key)); }
};

#endif