#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

class BST {
public:
    Node* root;

    BST() { root = NULL; }

    Node* insert(Node* node, int val) {
        if (node == NULL) return new Node(val);

        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);

        return node;
    }

    void insert(int val) {
        root = insert(root, val);
    }

    void inorder(Node* node) {
        if (node == NULL) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // largest value strictly smaller than key
    int findPredecessor(int key) {
        Node* curr = root;
        int pred = -1;

        while (curr != NULL) {
            if (key > curr->data) {
                pred = curr->data;
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        return pred;
    }

    // smallest value strictly greater than key
    int findSuccessor(int key) {
        Node* curr = root;
        int succ = -1;

        while (curr != NULL) {
            if (key < curr->data) {
                succ = curr->data;
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return succ;
    }

    void rangeQueryRecursive(Node* node, int low, int high, int& comparisons) {
        if (node == NULL) return;

        comparisons++;

        if (node->data > low)
            rangeQueryRecursive(node->left, low, high, comparisons);

        if (node->data >= low && node->data <= high)
            cout << node->data << " ";

        if (node->data < high)
            rangeQueryRecursive(node->right, low, high, comparisons);
    }

    void rangeQueryIterative(int low, int high, int& comparisons) {
        vector<Node*> stack;
        Node* curr = root;

        while (curr != NULL || !stack.empty()) {
            while (curr != NULL) {
                comparisons++;
                if (curr->data > low)
                    curr = curr->left;
                else
                    break;
            }

            if (curr == NULL) {
                curr = stack.back();
                stack.pop_back();
            }

            comparisons++;
            if (curr->data >= low && curr->data <= high)
                cout << curr->data << " ";

            curr = curr->right;
        }
    }
};

int main() {
    int values[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85};
    int n = sizeof(values) / sizeof(values[0]);

    BST tree;
    for (int i = 0; i < n; i++)
        tree.insert(values[i]);

    cout << "Inorder Traversal: ";
    tree.inorder(tree.root);
    cout << endl;

    int key = 40;
    cout << "\nKey = " << key << endl;
    cout << "Predecessor: " << tree.findPredecessor(key) << endl;
    cout << "Successor:   " << tree.findSuccessor(key) << endl;

    int low = 30, high = 70;
    cout << "\nRange Query [" << low << ", " << high << "]" << endl;

    int recComp = 0;
    cout << "Recursive: ";
    tree.rangeQueryRecursive(tree.root, low, high, recComp);
    cout << "\nComparisons (recursive): " << recComp << endl;

    int iterComp = 0;
    cout << "Iterative: ";
    tree.rangeQueryIterative(low, high, iterComp);
    cout << "\nComparisons (iterative): " << iterComp << endl;

    return 0;
}