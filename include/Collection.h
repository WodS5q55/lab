#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <type_traits>
#include "Publication.h"
#include "Reader.h"

using namespace std;

template <typename T>
class Collection {
private:
    vector<T> items;

public:
    void add(const T& item) {
        items.push_back(item);
    }

    void remove_by_index(size_t index) {
        if (index >= items.size()) {
            throw out_of_range("Индекс вне диапазона коллекции");
        }
        items.erase(items.begin() + index);
    }

    T get_by_index(size_t index) const {
        if (index >= items.size()) {
            throw out_of_range("Индекс вне диапазона коллекции");
        }
        return items[index];
    }

    int find(const T& item) const {
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i] == item) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    size_t size() const { return items.size(); }
    void clear() { items.clear(); }

    vector<T>& get_items() { return items; }
    const vector<T>& get_items() const { return items; }

    void print_publications() const {
        if (items.empty()) {
            cout << "[Коллекция пуста]" << endl;
            return;
        }
        for (size_t i = 0; i < items.size(); ++i) {
            cout << "[" << i << "] ";
            if constexpr (is_same_v<T, Publication*>) {
                cout << items[i]->get_title();
            }
            cout << endl;
        }
    }

    void print_readers() const {
        if (items.empty()) {
            cout << "[Коллекция пуста]" << endl;
            return;
        }
        for (size_t i = 0; i < items.size(); ++i) {
            cout << "[" << i << "] ";
            if constexpr (is_same_v<T, Reader*>) {
                cout << items[i]->get_name();
            }
            cout << endl;
        }
    }
};

template <typename T, typename Predicate>
vector<T> find_by_criteria(const Collection<T>& col, Predicate condition) {
    vector<T> result;
    for (size_t i = 0; i < col.size(); ++i) {
        T item = col.get_by_index(i);
        if (condition(item)) {
            result.push_back(item);
        }
    }
    return result;
}

#endif