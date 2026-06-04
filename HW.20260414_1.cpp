#include <iostream>

struct Node {
    int data;
    Node* previous;
    Node* next;
    Node(int value) : data(value), previous(nullptr), next(nullptr) {}
};

class DoubleLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoubleLinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        }
    }

    void display() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // РЕАЛИЗАЦИЯ УДАЛЕНИЯ 
    bool remove(int value) {
        if (!head) return false;

        Node* current = head;
        while (current && current->data != value) {
            current = current->next;
        }

        if (!current) return false;

        if (current == head) {
            head = current->next;
            if (head) head->previous = nullptr;
            else tail = nullptr;
        }
        else if (current == tail) {
            tail = current->previous;
            tail->next = nullptr;
        }
        else {
            current->previous->next = current->next;
            current->next->previous = current->previous;
        }

        delete current;
        return true;
    }

    // РЕАЛИЗАЦИЯ ПОИСКА
    bool search(int value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }
};

int main() {
    DoubleLinkedList list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(2);

    std::cout << "List: ";
    list.display();

    // Поиск
    std::cout << "Search 2: " << (list.search(2) ? "found" : "not found") << std::endl;
    std::cout << "Search 5: " << (list.search(5) ? "found" : "not found") << std::endl;

    // Удаление
    list.remove(2);
    std::cout << "After removing 2: ";
    list.display();

    return 0;
}
