#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_LEVEL = 5;

struct Node{
    int data;
    Node* right;
    Node* down;
};

Node* createNode(int value){
    Node* newNode = new Node;
    newNode->data = value;
    newNode->right = NULL;
    newNode->down = NULL;
    return newNode;
}

int randomLevel(){
    int level = 0;
    while ((rand() % 2) && level < MAX_LEVEL)
        level++;
    return level;
}

void insert(Node* head[], int value){
    Node* update[MAX_LEVEL + 1];
    Node* current = head[MAX_LEVEL];
    for (int i = MAX_LEVEL; i >= 0; i--){
        while (current->right->data < value)
            current = current->right;
        update[i] = current;
        current = current->down;
    }
    int level = randomLevel();
    Node* lower = NULL;
    for (int i = 0; i <= level; i++){
        Node* newNode = createNode(value);
        newNode->down = lower;
        newNode->right = update[i]->right;
        update[i]->right = newNode;
        lower = newNode;
    }
    cout << value << " inserted successfully.\n";
}

bool search(Node* head[], int value){
    Node* current = head[MAX_LEVEL];
    for (int i = MAX_LEVEL; i >= 0; i--){
        while (current->right->data < value)
            current = current->right;
        if (current->right->data == value)
            return true;
        current = current->down;
    }
    return false;
}

bool deleteNode(Node* head[], int value){
    Node* current = head[MAX_LEVEL];
    bool found = false;
    for (int i = MAX_LEVEL; i >= 0; i--){
        while (current->right->data < value)
            current = current->right;
        if (current->right->data == value){
            Node* temp = current->right;
            current->right = temp->right;
            delete temp;
            found = true;
        }
        current = current->down;
    }
    return found;
}

void display(Node* head[]){
    cout << "\nSkip List:\n\n";
    for (int i = MAX_LEVEL; i >= 0; i--){
        Node* current = head[i];
        cout << "Level " << i << ": ";
        while (current != NULL){
            if (current->data == -999999)
                cout << "-INF ";
            else if (current->data == 999999)
                cout << "+INF ";
            else
                cout << current->data << " ";
            current = current->right;
        }
        cout << endl;
    }
}

int main(){
    srand(time(0));
    Node* head[MAX_LEVEL + 1];
    Node* tail[MAX_LEVEL + 1];
    for (int i = 0; i <= MAX_LEVEL; i++){
        head[i] = createNode(-999999);
        tail[i] = createNode(999999);
        head[i]->right = tail[i];
    }
    for (int i = 1; i <= MAX_LEVEL; i++){
        head[i]->down = head[i - 1];
        tail[i]->down = tail[i - 1];
    }
    int n;
    cout << "Enter number of initial elements: ";
    cin >> n;
    cout << "\nEnter elements: ";
    for (int i = 0; i < n; i++){
        int value;
        cin >> value;
        insert(head, value);
    }
    int choice, value;
    do{
        cout << "\n--- Skip List Menu ---\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Delete\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice){
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                insert(head, value);
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                if (search(head, value))
                    cout << value << " found in Skip List.\n";
                else
                    cout << value << " not found in Skip List.\n";
                break;
            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                if (deleteNode(head, value))
                    cout << value << " deleted successfully.\n";
                else
                    cout << value << " not found in Skip List.\n";
                break;
            case 4:
                display(head);
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);
    return 0;
}