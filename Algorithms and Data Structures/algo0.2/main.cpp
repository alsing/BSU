#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Node {
    long data;
    Node* left;
    Node* right;

    Node(long data) : data(data), left(NULL), right(NULL) {}
};


class Tree {
protected:
    Node* root;
public:
    Tree(long data) {
        this->root = new Node(data);
    }

    Node *getRoot() const {
        return root;
    }

    void insert(Node* node, long data) {
        if (data < node->data) {
            if (node->left == NULL)
                node->left = new Node(data);
            else return insert(node->left, data);
        } else if (data > node->data) {
            if (node->right == NULL)
                node->right = new Node(data);
            else return insert(node->right, data);
        }
    }

    string preOrderTraversal(Node* node) {
        string s = "";
        s = s + to_string(node->data) + '\n';
        if (node->left != NULL)
            s += preOrderTraversal(node->left);
        if (node->right != NULL)
            s += preOrderTraversal(node->right);
        return s;
    }

    Node* findNode(Node* current, long value) {
        Node* node = current;
        if (current->data > value && current->left != NULL)
            node = findNode(current->left, value);
        if (current->data < value && current->right != NULL)
            node = findNode(current->right, value);
        if (node->data != value)
            return NULL;
        return node;
    }

    void deleteNode(long value) {
        Node* current = this->root;
        Node* parent = NULL;
        while (current && current->data != value) {
            parent = current;
            if (current->data > value)
                current = current->left;
            else
                current = current->right;
        }
        if (!current)
            return;

        if (!current->left) {
            if (!parent)
                root = current->right;
            else {
                if (parent && parent->left == current)
                    parent->left = current->right;
                if (parent && parent->right == current)
                    parent->right = current->right;
            }
            delete current;
            return;
        }

        if (!current->right) {
            if (!parent)
                root = current->left;
            else {
                if (parent && parent->left == current)
                    parent->left = current->left;
                if (parent && parent->right == current)
                    parent->right = current->left;
            }
            delete current;
            return;
        }

        Node* minNode = current->right;
        Node* minNodeParent = current;
        while (minNode->left) {
            minNodeParent = minNode;
            minNode = minNode->left;
        }
        current->data = minNode->data;
        if (!minNodeParent->left || minNodeParent->left->data == minNode->data)
            minNodeParent->left = minNode->right;
        else minNodeParent->right = minNode->right;
        delete minNode;
        return;
    }
};

int main() {
    ifstream in("input.txt");
    string line;
    getline(in, line);

    long value = stoll(line);
    getline(in, line);
    getline(in, line);

    Tree tree = *new Tree(stoll(line));

    while (getline(in, line)) {
        tree.insert(tree.getRoot(), stoll(line));
    }
    in.close();

    tree.deleteNode(value);

    line = tree.preOrderTraversal(tree.getRoot());

    ofstream out("output.txt");
    out << line.substr(0, line.length() - 1);
    out.close();

    return 0;
}