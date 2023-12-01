#include <iostream>
#include <vector>

using namespace std;

const int ROWS = 5;
const int COLS = 5;

void floodFillDFS(vector<vector<int>>& image, int sr, int sc, int newColor, int originalColor) {
    if (sr < 0 || sr >= ROWS || sc < 0 || sc >= COLS || image[sr][sc] != originalColor || image[sr][sc] == newColor) {
        return;
    }

    image[sr][sc] = newColor;

    floodFillDFS(image, sr - 1, sc, newColor, originalColor);
    floodFillDFS(image, sr + 1, sc, newColor, originalColor);
    floodFillDFS(image, sr, sc - 1, newColor, originalColor);
    floodFillDFS(image, sr, sc + 1, newColor, originalColor);
}

void floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
    if (image[sr][sc] == newColor) {
        return;
    }

    int originalColor = image[sr][sc];
    floodFillDFS(image, sr, sc, newColor, originalColor);
}

void printImage(const vector<vector<int>>& image) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> image = {
        {1, 1, 1, 1, 0},
        {1, 1, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0}
    };

    printImage(image);
    floodFill(image, 2, 2, 2);
    printImage(image);

    return 0;
}
