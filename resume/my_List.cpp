template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* prev; 
        Node* next;
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List() {
        clear();
    }

    void push_back(const T& value) {
        Node* newNode = new Node{ value, this->tail, nullptr };
        if (tail) {
            tail->next = newNode;
        }
        else {
            head = newNode;
        }
        tail = newNode;
        size++;
    }

    void push_front(const T& value) {
        Node* newNode = new Node{ value, nullptr, head };
        if (head) {
            head->prev = newNode;
        }
        else {
            tail = newNode;
        }
        head = newNode;
        size++;
    }

    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete temp;
        size--;
    }

    void pop_front() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    // Итераторы базовая реализация
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}
        T& operator*() { return current->data; }
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) { return current != other.current; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }


    // Вставка элемента перед указанным итератором
    void insert(Iterator position, const T& value) {
        if (position.current == head) {
            push_front(value);
            return;
        }

        Node* newNode = new Node{ value, position.current->prev, position.current };
        position.current->prev->next = newNode;
        position.current->prev = newNode;
        size++;
    }

    // Удаление элемента по итератору
    void erase(Iterator position) {
        if (position.current == head) {
            pop_front();
            return;
        }
        if (position.current == tail) {
            pop_back();
            return;
        }

        Node* temp = position.current;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        size--;
    }
};

