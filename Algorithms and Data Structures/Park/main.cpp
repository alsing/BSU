#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int CalculateArea(int right, int left, int top, int bottom) {
    return (right - left) * (top - bottom);
}

bool TreeComparator (vector <int> first, vector <int> second) {
    return first[0] < second[0];
}

int main() {
    fstream input_file("input.txt");

    int n_trees, width, height;
    input_file >> n_trees >> width >> height;

    vector<vector<int>> trees(n_trees, vector(2, 0));
    set<int> unique_y;

    int x, y;
    for (int i = 0; i < n_trees; ++i) {
        input_file >> x >> y;
        trees[i][0] = x;
        trees[i][1] = y;
        unique_y.insert(y);
    }
    unique_y.insert(0);
    unique_y.insert(height);

    vector<int> unique_y_vector(unique_y.begin(), unique_y.end());

    sort(trees.begin(), trees.end(), TreeComparator);
    sort(unique_y_vector.begin(), unique_y_vector.end());

    int area = 0;

    int left_border = 0;
    int right_border = 0;
    for (int i = unique_y_vector.size() - 1; i >= 0; --i) {
        for (int j = unique_y_vector.size() - 1; j > i; --j) {
            for (int k = 0; k < n_trees; ++k) {
                if (trees[k][1] > unique_y_vector[i] && trees[k][1] < unique_y_vector[j] && right_border != trees[k][0]) {
                    right_border = trees[k][0];
                    area = max(area, CalculateArea(right_border, left_border, unique_y_vector[j], unique_y_vector[i]));
                    left_border = right_border;

                }
            }
            right_border = width;
            area = max(area, CalculateArea(right_border, left_border, unique_y_vector[j], unique_y_vector[i]));
        }
    }

    ofstream output_file("output.txt");
    output_file << area;

    input_file.close();
    output_file.close();
}