#pragma once
#include "Node.h"
#include "Product.h"

class Shop {
public:
    Shop();
    ~Shop();
    Shop(const Shop& other);
    bool IsEmpty() const;
    bool IsFull() const;
    void push(Product v);
    void pop();
    void clear();
    void print() const;
    Shop& operator=(const Shop& other);
    void SaveProducts() const;
    Shop& DownloadProducts();
private:
    Node<Product>* head;
    Node<Product>* tail;
    size_t counter;

    void pushFront(Product v);
    void pushBack(Product v);

   friend ostream& operator<<(ostream& out, const Shop& queue);
};
