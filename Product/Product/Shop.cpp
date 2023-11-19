#define _CRT_SECURE_NO_WARNINGS
#include "Shop.h"

Shop::Shop() : head(nullptr), tail(nullptr), counter(0) {}
Shop::~Shop() { clear(); }
Shop::Shop(const Shop& other) : Shop() { *this = other; }

void Shop::pushFront(Product v)
{
    head = new Node<Product>(v, head);
    counter++;
}

void Shop::pushBack(Product v)
{
    Node<Product>* temp = new Node<Product>(v);
    if (tail)
        tail->setNext(temp);
    else
        head = temp;
    tail = temp;
    ++counter;
}

void Shop::push(Product v)
{
    if (!head ) {
        if (v.promotionalProduct() || v.expiredProduct()) {
            pushBack(v);
            return;
        }
    }
    if (v.promotionalProduct()) {
        pushFront(v);
        return;
    }
    if (v.expiredProduct()) {
        pushBack(v);
        return;
    }
}

void Shop::pop()
{
    if (!head) return;
    Node<Product>* temp = head;
    head = head->getNext();
    delete temp;
    if (!head) tail = nullptr;
    --counter;
}

void Shop::clear() { while (head) pop(); }

bool Shop::IsEmpty() const { return counter == 0; }

bool Shop::IsFull() const { return counter != 0; }

void Shop::print() const
{
    cout << "+--------------Promotional product--------------+" << endl;
    Node<Product>* cur = head;
    while (cur && cur->getValue().promotionalProduct()) {
        cur->print();
        cur = cur->getNext();
    }
    cout << "+--------------Expired product--------------+" << endl;
    while (cur) {
        cur->print();
        cur = cur->getNext();
    }
}

Shop& Shop::operator=(const Shop& other)
{
    if (this == &other) return *this;
    clear();
    Node<Product>* cur = other.head;
    while (cur) {
        push(cur->getValue());
        cur = cur->getNext();
    }
    return *this;
}

void Shop::SaveProducts() const
{
    FILE* file;
    Node<Product>* cur = head;
    {
        file = fopen("C:\\Users\\User\\Downloads\\PromotionalProducts.txt", "a");
        if (!file) return;
        while (cur && cur->getValue().promotionalProduct()) {
            fprintf(file, "Name: %s\nWeight: %i\nDate: %i.%i.%i\nExpiration Date: %i\nPrice =  %f\n\n",
                cur->getValue().getName().GetStr(), cur->getValue().getWeight(), cur->getValue().getIssueDate().days, cur->getValue().getIssueDate().months,
                cur->getValue().getIssueDate().years, cur->getValue().getExpirationDate(), cur->getValue().getPrice());
            cur = cur->getNext();
        }
        fclose(file);
    }
    file = fopen("C:\\Users\\User\\Downloads\\ExpiredProducts.txt", "a");
    if (!file) return;
    while (cur) {
        fprintf(file, "Name: %s\nWeight: %i\nDate: %i.%i.%i\nExpiration Date: %i\nPrice =  %f\n\n",
            cur->getValue().getName().GetStr(), cur->getValue().getWeight(), cur->getValue().getIssueDate().days, cur->getValue().getIssueDate().months,
            cur->getValue().getIssueDate().years, cur->getValue().getExpirationDate(), cur->getValue().getPrice());
        cur = cur->getNext();
    }
    fclose(file);
}

size_t GetSize_tNum(const char* Buffer) {
    size_t num = 0;
    for (size_t i = 0; i < strlen(Buffer); i++) {
        num += Buffer[i] - '0';
        num *= 10;
    }
    num /= 10;
    return num;
}

Shop& Shop::DownloadProducts()
{
    FILE* file;
    file = fopen("C:\\Users\\User\\Downloads\\Products.txt", "r");
    if (!file) return *this;
    Product product;
    Date date(0);
    String str(200), tempstr(200);
    char letter;
    do {
        fseek(file, 6, SEEK_CUR);
        fgets(str.GetStr(), 200, file);
        memcpy(tempstr.GetStr(), str.GetStr(), strlen(str.GetStr()) - 1);
        tempstr.GetStr()[strlen(str.GetStr()) - 1] = '\0';
        product.setName(tempstr.GetStr());
        fseek(file, 8, SEEK_CUR);
        fgets(str.GetStr(), 200, file);
        memcpy(tempstr.GetStr(), str.GetStr(), strlen(str.GetStr()) - 1);
        tempstr.GetStr()[strlen(str.GetStr()) - 1] = '\0';
        product.setWeight(GetSize_tNum(tempstr.GetStr()));
        fseek(file, 6, SEEK_CUR);
        fgets(str.GetStr(), 200, file);
        memcpy(tempstr.GetStr(), str.GetStr(), strlen(str.GetStr()) - 1);
        tempstr.GetStr()[strlen(str.GetStr()) - 1] = '\0';
        String str2;
        str2.SetStr(strtok(tempstr.GetStr(), "."));
        date.days = GetSize_tNum(str2.GetStr());
        str2.SetStr(strtok(NULL, "."));
        date.months = GetSize_tNum(str2.GetStr());
        str2.SetStr(strtok(NULL, "."));
        date.years = GetSize_tNum(str2.GetStr());
        product.setIssueDate(date);
        fseek(file, 17, SEEK_CUR);
        fgets(str.GetStr(), sizeof(str.GetStr()), file);
        memcpy(tempstr.GetStr(), str.GetStr(), strlen(str.GetStr()) - 1);
        tempstr.GetStr()[strlen(str.GetStr()) - 1] = '\0';
        product.setExpirationDate(GetSize_tNum(tempstr.GetStr()));
        fseek(file, 9, SEEK_CUR);
        fgets(str.GetStr(), 200, file);
        if (str.GetStr()[strlen(str.GetStr())] != '\n')
            product.setPrice(GetSize_tNum(str.GetStr()));
        else {
            memcpy(tempstr.GetStr(), str.GetStr(), strlen(str.GetStr()) - 1);
            tempstr.GetStr()[strlen(str.GetStr()) - 1] = '\0';
            product.setPrice(GetSize_tNum(tempstr.GetStr()));
        }
        push(product);
        fseek(file, 2, SEEK_CUR);
        letter = fgetc(file);
        fseek(file, -2, SEEK_CUR);
    } while (letter != EOF);
    fclose(file);
    return *this;
}

ostream& operator<<(ostream& out, const Shop& shop) {
    Node<Product>* cur = shop.head;
    while (cur) {
        out << cur->getValue() << '\t';
        cur = cur->getNext();
    }
    return out;
}