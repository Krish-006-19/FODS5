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

Node* deleteNode(Node* root, int val) {
    if (!root) return nullptr;
    if (val < root->value) root->left = deleteNode(root->left, val);
    else if (val > root->value) root->right = deleteNode(root->right, val);
    else {
        if (!root->left) {
            Node* r = root->right;
            delete root;
            return r;
        }
        if (!root->right) {
            Node* l = root->left;
            delete root;
            return l;
        }
        Node* succ = root->right;
        while (succ->left) succ = succ->left;
        root->value = succ->value;
        root->right = deleteNode(root->right, succ->value);
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
