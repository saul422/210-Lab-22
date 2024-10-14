// COMSC-210 | Lab 22 | Joseph Graves


#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };
    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Push value at the end
    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Push value at the front
    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Insert after a position
    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    // Delete a node by value (renamed from delete_node)
    void delete_val(int value) {
        if (!head) return; // Empty list
        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;
        if (!temp) return; // Value not found
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; // Deleting the head
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; // Deleting the tail
        delete temp;
    }

    // Delete a node by position
    void delete_pos(int position) {
        if (position < 0 || !head) {
            cout << "Invalid position or empty list.\n";
            return;
        }
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp) return; // Position not found
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; // Deleting the head
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; // Deleting the tail
        delete temp;
    }

    // Pop the front node (head)
    void pop_front() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete temp;
    }

    // Pop the back node (tail)
    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;
        delete temp;
    }

    // Print list forward
    void print() {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Print list backward
    void print_reverse() {
        Node* current = tail;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

// Driver program
int main() {
    DoublyLinkedList list;
    srand(time(0));

    // Populate list with random values
    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);

    // Print the list forward and backward
    cout << "List forward: ";
    list.print();
    cout << "List backward: ";
    list.print_reverse();

    // Testing the new methods
    cout << "Pop front: \n";
    list.pop_front();
    list.print();

    cout << "Pop back: \n";
    list.pop_back();
    list.print();

    cout << "Delete position 2: \n";
    list.delete_pos(2);
    list.print();

    cout << "Delete value 50 (if exists): \n";
    list.delete_val(50);
    list.print();

    return 0;
}
