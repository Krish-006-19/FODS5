#include <iostream>
#include <cctype>
#include <string>
#include <limits>
using namespace std;

struct Node {
    Node *left, *right;
    int value;
    Node(int val) {
        value = val;
        left = right = nullptr;
    }
};

class Queue {
    static const int SIZE = 100;
    Node* arr[SIZE];
    int frontIdx, rear;
public:
    Queue() : frontIdx(0), rear(0) {}

    bool empty() { return frontIdx == rear; }

    void push(Node* x) {
        if (rear == SIZE) {
            cout << "Queue Overflow\n";
            return;
        }
        arr[rear++] = x;
    }

    Node* pop() {
        if (empty()) {
            cout << "Queue Underflow\n";
            return nullptr;
        }
        return arr[frontIdx++];
    }

    Node* front() {
        if (empty()) {
            cout << "Queue Empty\n";
            return nullptr;
        }
        return arr[frontIdx];
    }
};

class Stack {
    static const int SIZE = 100;
    Node* arr[SIZE];
    int topidx;
public:
    Stack() : topidx(-1) {}

    bool empty() { return topidx == -1; }

    void push(Node* x) {
        if (topidx == SIZE - 1) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++topidx] = x;
    }

    Node* pop() {
        if (empty()) {
            cout << "Stack Underflow\n";
            return nullptr;
        }
        return arr[topidx--];
    }

    Node* top() {
        if (empty()) return nullptr;
        return arr[topidx];
    }
};

Node* insertNode(Node* &root, int val) {
    Node* node = new Node(val);
    if (!root) {
        root = node;
        return root;
    }

    Queue q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.pop();

        if (!curr->left) {
            curr->left = node;
            return root;
        } else q.push(curr->left);

        if (!curr->right) {
            curr->right = node;
            return root;
        } else q.push(curr->right);
    }

    return root;
}

void Update(Node *root, int oldValue, int newValue) {
    if (!root) return;

    Queue q;
    q.push(root);

    while (!q.empty()) {
        Node *current = q.pop();
        if (current->value == oldValue) {
            current->value = newValue;
            return;
        }
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

Node* deleteNode(Node* root, int val) {
    if (!root) return nullptr;

    Node* target = nullptr;
    Node* last = nullptr;
    Node* parentOfLast = nullptr;

    Queue q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.pop();

        if (current->value == val)
            target = current;

        if (current->left) {
            parentOfLast = current;
            q.push(current->left);
        }

        if (current->right) {
            parentOfLast = current;
            q.push(current->right);
        }
        last = current;
    }

    if (target) {
        target->value = last->value;

        if (parentOfLast) {
            if (parentOfLast->left == last)
                parentOfLast->left = nullptr;
            else if (parentOfLast->right == last)
                parentOfLast->right = nullptr;
        } else {
            root = nullptr; 
        }
        delete last;
    }
    return root;
}

void Preorder(Node *root) {
    if (!root) return;
    Stack st;
    st.push(root);
    while (!st.empty()) {
        Node *current = st.pop();
        cout << current->value << " ";
        if (current->right) st.push(current->right);
        if (current->left) st.push(current->left);
    }
}

void Inorder(Node *root) {
    Stack st;
    Node *current = root;
    while (current || !st.empty()) {
        while (current) {
            st.push(current);
            current = current->left;
        }
        current = st.pop();
        cout << current->value << " ";
        current = current->right;
    }
}

void Postorder(Node *root) {
    if (!root) return;
    Stack st1, st2;
    st1.push(root);
    while (!st1.empty()) {
        Node* current = st1.pop();
        st2.push(current);
        if (current->left) st1.push(current->left);
        if (current->right) st1.push(current->right);
    }
    while (!st2.empty()) {
        cout << st2.pop()->value << " ";
    }
}

void LevelOrder(Node* root) {
    if (!root) return;
    Queue q;
    q.push(root);
    while (!q.empty()) {
        Node* current = q.pop();
        cout << current->value << " ";
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

bool isValidInteger(const string& str) {
    if (str.empty()) return false;

    int start = 0;
    if (str[0] == '+' || str[0] == '-')
        start = 1;

    if (start == str.size()) return false;

    for (int i = start; i < str.size(); i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

int getValidInteger(const string& prompt) {
    string input;
    int val;

    while (true) {
        cout << prompt;
        cin >> input;

        if (!isValidInteger(input)) {
            cout << "invalid input. Please enter a valid integer.\n";
            continue;
        }

        try {
            val = stoi(input);
            return val;
        } catch (const out_of_range&) {
            cout << "Number out of range. Try again.\n";
        } catch (...) {
            cout << "Unexpected error. Try again.\n";
        }
    }
}

int main() {
    Node* root = nullptr;
    string choice;
    int val, newVal;
    while(true) {
        cout << "\n\n==== Binary Tree Menu ====\n";
        cout << "1. Insert Node\n";
        cout << "2. Delete Node\n";
        cout << "3. Update Node\n";
        cout << "4. Preorder Traversal\n";
        cout << "5. Inorder Traversal\n";
        cout << "6. Postorder Traversal\n";
        cout << "7. Level Order Traversal\n";
        cout << "8. Exit\n";
        cout << "choose a num: ";
        cin >> choice;
        if (choice.size() != 1 || choice[0] < '1' || choice[0] > '8') {
            cout << "Invalid choice. Please enter a number between 1–8.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice[0]) {
            case '1':
                val = getValidInteger("Enter value to insert: ");
                insertNode(root, val);
                break;
            
            case '2':
                val = getValidInteger("Enter value to delete: ");
                root = deleteNode(root, val);
                break;
            
            case '3':
                val = getValidInteger("Enter old value to update: ");
                newVal = getValidInteger("Enter new value: ");
                Update(root, val, newVal);
                break;

            case '4':
                cout << "Preorder Traversal: ";
                Preorder(root);
                cout << endl;
                break;

            case '5':
                cout << "Inorder Traversal: ";
                Inorder(root);
                cout << endl;
                break;

            case '6':
                cout << "Postorder Traversal: ";
                Postorder(root);
                cout << endl;
                break;

            case '7':
                cout << "Level Order Traversal: ";
                LevelOrder(root);
                cout << endl;
                break;

            case '8':
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    }

    return 0;
}
