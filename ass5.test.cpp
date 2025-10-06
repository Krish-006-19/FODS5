#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct Node {
    Node *left;
    Node *right;
    int value;
    Node(int val) {
        value = val;
        left = right = nullptr;
    }
};

Node* insertNode(Node* &root, int val) {
    Node* node = new Node(val);
    if (!root) {
        root = node;
        return root;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (!curr->left) {
            curr->left = node;
            return root;
        } else {
            q.push(curr->left);
        }

        if (!curr->right) {
            curr->right = node;
            return root;
        } else {
            q.push(curr->right);
        }
    }

    return root;
}

void Update(Node *root, int oldValue, int newValue) {
    if (!root)
        return;
    queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        Node *current = q.front();
        q.pop();
        if (current->value == oldValue) {
            current->value = newValue;
            return;
        }
        if (current->left)
            q.push(current->left);
        if (current->right)
            q.push(current->right);
    }
}

Node *deleteNode(Node *&root, int value) {
    if (!root)
        return root;
    Node *parent = nullptr;
    Node *curr = root;
    while (curr && curr->value != value) {
        parent = curr;
        if (value < curr->value)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (!curr)
        return root;

    if (!curr->left && !curr->right) {
        if (curr != root) {
            if (parent->left == curr)
                parent->left = nullptr;
            else
                parent->right = nullptr;
        } else
            root = nullptr;
        delete curr;
    }
    else if (!curr->left || !curr->right) {
        Node *child = (curr->left) ? curr->left : curr->right;
        if (curr != root) {
            if (curr == parent->left)
                parent->left = child;
            else
                parent->right = child;
        } else
            root = child;
        delete curr;
    }
    else {
        Node *succParent = curr;
        Node *succ = curr->right;
        while (succ->left) {
            succParent = succ;
            succ = succ->left;
        }
        curr->value = succ->value;
        if (succParent->left == succ)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;
        delete succ;
    }
    return root;
}

void Preorder(Node *root) {
    if (!root)
        return;
    stack<Node *> st;
    st.push(root);
    while (!st.empty()) {
        Node *current = st.top();
        st.pop();
        cout << current->value << " ";
        if (current->right)
            st.push(current->right);
        if (current->left)
            st.push(current->left);
    }
}

void Inorder(Node *root) {
    stack<Node *> st;
    Node *current = root;
    while (current || !st.empty()) {
        while (current) {
            st.push(current);
            current = current->left;
        }
        current = st.top();
        st.pop();
        cout << current->value << " ";
        current = current->right;
    }
}

void Postorder(Node *root) {
    if (!root)
        return;
    stack<Node *> st1, st2;
    st1.push(root);
    while (!st1.empty()) {
        Node *current = st1.top();
        st1.pop();
        st2.push(current);
        if (current->left)
            st1.push(current->left);
        if (current->right)
            st1.push(current->right);
    }
    while (!st2.empty()) {
        cout << st2.top()->value << " ";
        st2.pop();
    }
}

void LevelOrder(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
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

    cout << "\nlevelOrder: ";
    LevelOrder(root);

    cout << "\n\n";

    Update(root, 4, 8);
    Inorder(root);

    cout << "\n\n";

    deleteNode(root, 7);
    Inorder(root);

    return 0;
}
