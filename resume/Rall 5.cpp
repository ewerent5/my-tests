// Разница лишь в уневирсальной ссылке
// нужно для перемещения в нужное место из больше ненужного
// незачем копировать если обектом больше никто нквладеет
#include "ZXC.h"

using namespace std;

class DynArray {

    int* data;
    size_t size {};

public:
    DynArray(size_t s);                          
    DynArray(const DynArray& other);   
    DynArray(DynArray&& other);

    DynArray& operator=(DynArray&& other);
    DynArray& operator=(const DynArray& other);

    void fill(int value); 
    void print() const;
    
    
    ~DynArray();                     
};

DynArray::DynArray(size_t s) {
    this->size = s;
    data = new int[size];
}

DynArray::DynArray(const DynArray& other) {
    this->size = other.size;
    this->data = new int[size];
    copy(other.data, other.data + size, this->data);
}


DynArray::DynArray(DynArray&& other) {
    this->size = other.size;
    this->data = other.data;

    other.data = nullptr;
    other.size = 0;
}

DynArray& DynArray::operator=(DynArray&& other) {
    if (this != &other) {
        delete[] this->data;
        this->size = other.size;
        this->data = other.data;

        other.data = nullptr;
        other.size = 0;
        
    }
    return *this;
}

DynArray& DynArray::operator=(const DynArray& other) {
    if (this != &other) {
        delete[] this->data;
        this->size = other.size;
        this->data = new int[size];
        std::copy(other.data, other.data + size, this->data);
    }
    return *this;
}

void DynArray::fill(int value) {
    std::fill(this->data, this->data + size, value);
}

void DynArray::print() const {
    for (int i = 0; i < this->size; ++i) {
        cout << data[i] << ' ';
    }
    cout << endl;
}

DynArray::~DynArray() {
    delete[] data;
}

int main() {
    DynArray a(1000000);
    DynArray b = std::move(a); 

    DynArray c(10);
    c = std::move(b);
}