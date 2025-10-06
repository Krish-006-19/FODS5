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

void Preorder(Node *root) {
    if (!root) return;
    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* current = st.top();
        st.pop();
        cout << current->value << " ";
        if (current->right) st.push(current->right);
        if (current->left) st.push(current->left);
    }
}

void Inorder(Node* root) {
    stack<Node*> st;
    Node* current = root;
    while(true){
        if(current){
            st.push(current);
            current = current->left;
        } else {
            if(st.empty()) break;
            current = st.top();
            st.pop();
            cout << current->value << " ";
            current = current->right;
        }
    }
}

void Postorder(Node* root) {
    if (!root) return;
    stack<Node*> st1, st2;
    st1.push(root);

    while (!st1.empty()) {
        Node* current = st1.top();
        st1.pop();
        st2.push(current);

        if (current->left) st1.push(current->left);
        if (current->right) st1.push(current->right);
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
    Node* root = nullptr;
    insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 70);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 60);
    insertNode(root, 80);

    cout << "Preorder: ";
    Preorder(root);

    cout << "\nInorder: ";
    Inorder(root);

    cout << "\nPostorder: ";
    Postorder(root);

    cout << "\nLevel-order (BFS): ";
    LevelOrder(root);

    return 0;
}
