#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct bstNode {
    long data;
    long leftBorder;
    long rightBorder;
};

int main() {
    ifstream in("bst.in");

    long number;
    long data;
    int line;
    char position;
    string s = "YES";

    in >> number;
    bstNode* bstArray = new bstNode[number];

    in >> data;
    bstArray[0].data = data;
    bstArray[0].leftBorder = LONG_MIN;
    bstArray[0].rightBorder = LONG_MAX;

    for (int i = 1; i < number; i++) {
        in >> data;
        in >> line;
        in >> position;

        bstNode parent = bstArray[line - 1];

        if (position == 'L') {
            if (data >= parent.leftBorder && data < parent.data) {
                bstArray[i].data = data;
                bstArray[i].leftBorder = parent.leftBorder;
                bstArray[i].rightBorder = parent.data - 1;
            }
            else {
                s = "NO";
                break;
            }
        }
        else {
            if (data >= parent.data && data <= parent.rightBorder) {
                bstArray[i].data = data;
                bstArray[i].leftBorder = parent.data;
                bstArray[i].rightBorder = parent.rightBorder;
            } else {
                s = "NO";
                break;
            }
        }
    }
    in.close();

    ofstream out("bst.out");
    out << s;
    out.close();

    return 0;
}