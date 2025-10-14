#include <iostream>
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

int main() {
    Node *root = nullptr;
    insertNode(root, 1);
    insertNode(root, 2);
    insertNode(root, 3);
    insertNode(root, 4);
    insertNode(root, 5);
    insertNode(root, 6);
    insertNode(root, 7);

    cout << "Preorder: ";
    Preorder(root);

    cout << "\nInorder: ";
    Inorder(root);

    cout << "\nPostorder: ";
    Postorder(root);

    cout << "\nLevelOrder: ";
    LevelOrder(root);

    cout << "\n\nAfter Update (4→8): ";
    Update(root, 4, 8);
    Inorder(root);

    cout << "\nAfter Delete (7): ";
    deleteNode(root, 7);
    Inorder(root);

    return 0;
}
