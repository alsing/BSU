#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Node {
protected:
    long data;
    Node* left;
    Node* right;
public:
    Node(long data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }

    void insert(long data) {
        if (data < this->data) {
            if (this->left == NULL)
                this->left = new Node(data);
            else this->left->insert(data);
        } else if (data > this->data) {
            if (this->right == NULL)
                this->right = new Node(data);
            else this->right->insert(data);

        }
    }

    string preOrderTraversal() {
        string s = "";
        s = s + to_string(this->data) + '\n';
        if (this->left != NULL)
            s += this->left->preOrderTraversal();
        if (this->right != NULL)
            s += this->right->preOrderTraversal();
        return s;
    }

};

int main() {
    ifstream in("input.txt");
    string line;
    getline(in, line);

    if (line != "") {
        Node tree = *new Node(stoll(line));

        while (getline(in, line)) {
            tree.insert(stoll(line));
        }
        in.close();

        line = tree.preOrderTraversal();

        ofstream out("output.txt");
        out << line.substr(0, line.length() - 1);
        out.close();
    }
    else {
        ofstream out("output.txt");
        out.close();
    }

    return 0;
}
