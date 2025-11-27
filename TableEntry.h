#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry
{
public:
    // atributos públicos
    std::string key_;
    V value_;
    
public:
    // miembros públicos
    TableEntry(std::string key, V value) : key_(key), value_(value) {}
    TableEntry(std::string key) : key_(key) {}
    TableEntry() {}
    friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2)
    {
        return ((te1.key_) == (te2.key_));
    }
    friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2)
    {
        return ((te1.key_) != (te2.key_));
    }
    friend std::ostream &operator<<(std::ostream &out, const TableEntry<V> &te)
    {
        out << "{" << te.key_ << ", " << te.value_ << "}";
        return (out);
    }
    friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return ((te1.key_) < (te2.key_));
    }
    friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return ((te1.key_) > (te2.key_));
    }
};

#endif