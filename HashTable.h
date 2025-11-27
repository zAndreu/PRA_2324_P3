#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h" // ¡¡¡¡MODIFICAR!!!!

template <typename V>
class HashTable : public Dict<V>
{

private:
    // ...
    int n;
    int max;
    ListLinked<TableEntry<V>> *table;

    int h(std::string key)
    {
        if (max <= 0)
            throw std::runtime_error("Tabla hash con tamaño cero");
        int sum = 0;
        for (unsigned char c : key)
            sum += c;
        return (sum % max);
    }

public:
    // ...
    HashTable(int size) : n(0), max(size)
    {
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable()
    {
        delete[] (table);
    }

    // De Dict.h
    void insert(const std::string &key, const V &value) override
    {
        int index = h(key);
        TableEntry<V> te(key, value);
        int pos = table[index].search(TableEntry<V>(key));
        if (pos != -1)
        {
            throw std::runtime_error("La clave ya existe en la tabla");
        }
        table[index].append(te);
        n++;
    }

    V search(const std::string &key) override
    {
        int index = h(key);
        TableEntry<V> te(key);
        int pos = table[index].search(te);
        if (pos != -1)
        {
            return (table[index].get(pos).value_);
        }
        throw std::runtime_error("La clave no existe en la tabla");
    }

    V remove(const std::string &key) override
    {
        int index = h(key);
        TableEntry<V> te(key);
        int pos = table[index].search(te);
        if (pos != -1)
        {
            V val = table[index].get(pos).value_;
            table[index].remove(pos);
            n--;
            return (val);
        }
        throw std::runtime_error("La clave no existe en la tabla");
    }

    int entries() override { return (n); }

    // Métodos propios
    int capacity() { return (max); }

    friend std::ostream &operator<<(std::ostream &out, const HashTable<V> &th)
    {
        for (int i = 0; i < th.max; i++)
        {
            out << i << ": " << th.table[i] << std::endl;
        }
        return (out);
    }

    V operator[](const std::string &key)
    {
        return (this->search(key));
    }
};

#endif