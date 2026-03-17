//COMSC-210-5068, Midterm2, Yang Liu
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// class to store name and VIP status
class Customer {
private:
    string name;
    bool isVIP;

public:
    Customer(string n = "", bool vip = false) : name(n), isVIP(vip) {}

    string getName() const { return name; }
    bool isVIPCustomer() const { return isVIP; }
};

class DoublyLinkedList {
private:
    struct Node {
        Customer data;
        Node* prev;
        Node* next;
        Node(Customer val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(Customer());
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
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data.getName() != to_string(value))
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(Customer v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(Customer v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data.getName() << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data.getName() << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void printFormattedLine() {
        Node* current = head;
        if (!current) {
            cout << "        List is empty." << endl;
            return;
        }
        while (current) {
            cout << "        " << current->data.getName() << endl;
            current = current->next;
        }
    }

    int getSize() const {
        int count = 0;
        Node* cur = head;
        while (cur != nullptr) {
            count++;
            cur = cur->next;
        }
        return count;
    }

    Customer getFrontCustomer() const {
        if (head != nullptr)
            return head->data;
        return Customer();
    }

    Customer getRearCustomer() const {
        if (tail) return tail->data;
        return Customer();
    }

    Customer getCustomerAt(int pos) const {
        if (pos < 1 || !head) return Customer();
        Node* cur = head;
        for (int i = 1; i < pos && cur; i++) cur = cur->next;
        return cur ? cur->data : Customer();
    }

};

//Prototypes
vector<string> readNames(const string& filename);
Customer getRandomCustomer(const vector<string>& names);
void runSimulation(DoublyLinkedList& line, const vector<string>& names);

vector<string> readNames(const string& filename) {
    vector<string> names;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (!line.empty())
            names.push_back(line);
    }
    return names;
}

//10% VIP chance
Customer getRandomCustomer(const vector<string>& names) {
    int idx = rand() % names.size();
    bool vip = (rand() % 100) < 10;
    return Customer(names[idx], vip);
}

void runSimulation(DoublyLinkedList& line, const vector<string>& names) {
    // Initial 5 customers
    cout << "Store opens:" << endl;
    for (int i = 0; i < 5; i++) {
        Customer cust = getRandomCustomer(names);
        line.push_back(cust);
        cout << "    " << cust.getName() << " joins the line" << endl;
    }
    cout << "    Resulting line:" << endl;
    line.printFormattedLine();
    cout << endl;

    // Step 1–19
    for (int step = 1; step <= 19; step++) {
        cout << "Time step #" << step << ":" << endl;
        int size = line.getSize();

        // 40% chance serve first customer
        if (size > 0 && rand() % 100 < 40) {
            Customer served = line.getFrontCustomer();
            cout << "    " << served.getName() << " is served" << endl;
            line.pop_front();
            size--;
        }
        // 20% chance last customer leaves
        if (size > 0 && rand() % 100 < 20) {
            Customer left = line.getRearCustomer();
            cout << "    " << left.getName() << " exits the rear of the line" << endl;
            line.pop_back();
            size--;
        }

        // 60% chance a new customer joins line, VIP goes to front
        if (rand() % 100 < 60) {
            Customer newCust = getRandomCustomer(names);
            if (newCust.isVIPCustomer()) {
                line.push_front(newCust);
                cout << "    " << newCust.getName() << " (VIP) joins the front" << endl;
            } else {
                line.push_back(newCust);
                cout << "    " << newCust.getName() << " joins the line" << endl;
            }
        }

        cout << "    Resulting line:" << endl;
        line.printFormattedLine();
        cout << endl;
    }

}

int main() {
    srand(time(0));
    vector<string> names = readNames("names.txt");
    DoublyLinkedList coffeeLine;

    runSimulation(coffeeLine, names);

    
    return 0;
}