#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{
    struct NODE {
        int data;
        NODE* next;
    };

    NODE *head = nullptr;
    int len = 0;

    void init() {
        head = nullptr;
        len = 0;
    }
    
    NODE* move(int i) {
        if (head == nullptr || i < 0) return nullptr;
        NODE* current = head;
        for (int j = 0; j < i; j++) {
            current = current->next;
        }
        return current;
    }
    
    void insert(int i, int x) {
        NODE* newNode = new NODE;
        newNode->data = x;
        
        if (head == nullptr) {
            // Empty list
            head = newNode;
            newNode->next = head;
            len = 1;
        } else if (i == 0) {
            // Insert at head
            NODE* tail = move(len - 1);
            newNode->next = head;
            head = newNode;
            tail->next = head;
            len++;
        } else {
            // Insert at position i (i > 0)
            NODE* prev = move(i - 1);
            newNode->next = prev->next;
            prev->next = newNode;
            len++;
        }
    }
    
    void remove(int i) {
        if (head == nullptr || i < 0 || i >= len) return;
        
        if (len == 1) {
            // Only one node
            delete head;
            head = nullptr;
            len = 0;
        } else if (i == 0) {
            // Remove head
            NODE* tail = move(len - 1);
            NODE* temp = head;
            head = head->next;
            tail->next = head;
            delete temp;
            len--;
        } else {
            // Remove at position i (i > 0)
            NODE* prev = move(i - 1);
            NODE* temp = prev->next;
            prev->next = temp->next;
            delete temp;
            len--;
        }
    }
    
    void remove_insert(int i) {
        if (head == nullptr || i < 0 || i >= len) return;
        
        if (len == 1) {
            // Only one node, nothing to do
            return;
        }
        
        // Get the value at position i
        NODE* nodeToMove = move(i);
        int value = nodeToMove->data;
        
        // Remove the node at position i
        remove(i);
        
        // Insert at the end (position len)
        insert(len, value);
    }
    
    void get_length() {
        cout << len << endl;
    }
    
    void query(int i) {
        if (i < 0 || i >= len) {
            cout << -1 << endl;
        } else {
            NODE* node = move(i);
            cout << node->data << endl;
        }
    }
    
    void get_max() {
        if (head == nullptr) {
            cout << -1 << endl;
            return;
        }
        
        int maxVal = head->data;
        NODE* current = head->next;
        for (int i = 1; i < len; i++) {
            if (current->data > maxVal) {
                maxVal = current->data;
            }
            current = current->next;
        }
        cout << maxVal << endl;
    }
    
    void clear() {
        if (head == nullptr) return;
        
        NODE* current = head;
        NODE* next;
        for (int i = 0; i < len; i++) {
            next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        len = 0;
    }
}

int n;
int main()
{
    cin >> n;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_)
    {
        cin >> op;
        switch(op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}
