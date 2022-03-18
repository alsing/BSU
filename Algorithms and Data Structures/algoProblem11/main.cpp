#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct lastValue {
    long value;
    int height;

    lastValue(long value, int height) : value(value), height(height) {}
};

struct Node {
    long data;
    Node* left;
    Node* right;
    int height;
    lastValue lastLeftValue;
    lastValue lastRightValue;
    int msl;

    Node(long data) : data(data), left(NULL), right(NULL), height(0), lastLeftValue(data, 0), lastRightValue(data, 0), msl(0) {}
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
        if (node != NULL) {
            s += to_string(node->data) + '\n';
            s += preOrderTraversal(node->left);
            s += preOrderTraversal(node->right);
        }
        return s;
    }

    string postOrderTraversal(Node* node) {
        string s = "";
        if (node != NULL) {
            s += postOrderTraversal(node->left);
            s += postOrderTraversal(node->right);
            s += to_string(node->data) + '\n';
        }
        return s;
    }

    string inOrderTraversal(Node* node) {
        string s = "";
        if (node != NULL) {
            s += inOrderTraversal(node->left);
            s += to_string(node->data) + '\n';
            s += inOrderTraversal(node->right);
        }
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

    void assignHeightsAndLastValues(Node* node) {
        if (node != NULL) {
            assignHeightsAndLastValues(node->left);
            assignHeightsAndLastValues(node->right);

            if (!node->left && !node->right)
                return;

            int right = 0;
            int left = 0;

            if (node->left) {
                left = node->left->height;
                node->msl += left + 1;
                node->lastLeftValue.height = left + 1;
                if (node->left->lastRightValue.height > node->left->lastLeftValue.height)
                    node->lastLeftValue.value = node->left->lastRightValue.value;
                else node->lastLeftValue.value = node->left->lastLeftValue.value;
            }

            if (node->right) {
                right += node->right->height;
                node->msl += right + 1;
                node->lastRightValue.height = right + 1;
                if (node->right->lastRightValue.height > node->right->lastLeftValue.height)
                    node->lastRightValue.value = node->right->lastRightValue.value;
                else node->lastRightValue.value = node->right->lastLeftValue.value;
            }

            node->height += max(left, right) + 1;
        }
    }

    Node* findMaxMsl(Node* node, Node* maxMslNode) {
        if (node != NULL) {
            if (node->msl > maxMslNode->msl)
                maxMslNode = node;
            else if (node->msl == maxMslNode->msl && (node->lastLeftValue.value + node->lastRightValue.value) < (maxMslNode->lastLeftValue.value + maxMslNode->lastRightValue.value))
                maxMslNode = node;

            maxMslNode = findMaxMsl(node->left, maxMslNode);
            maxMslNode = findMaxMsl(node->right, maxMslNode);
        }
        return maxMslNode;
    }
};

int main() {
    ifstream in("in.txt");
    string line;
    getline(in, line);

    Tree tree = *new Tree(stoll(line));

    while (getline(in, line)) {
        tree.insert(tree.getRoot(), stoll(line));
    }
    in.close();

    tree.assignHeightsAndLastValues(tree.getRoot());
    tree.deleteNode(tree.findMaxMsl(tree.getRoot(), tree.getRoot())->data);
    line = tree.preOrderTraversal(tree.getRoot());

    ofstream out("out.txt");
    out << line.substr(0, line.length() - 1);
    out.close();

    return 0;
}