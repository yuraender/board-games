#include <iostream>
#include <windows.h>

using namespace std;

const int N = 8;

int board[N];
int queen = 0;

bool check();

void print();

int main_old() {
    //Set encoding to UTF-8 on Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    while (board[0] < N) {
        if (check()) {
            if (queen == N - 1) {
                print();
                board[queen]++;
            } else {
                queen++;
            }
            continue;
        }
        board[queen]++;
    }

    return 0;
}

bool check() {
    for (int i = 0; i < queen; i++) {
        if (board[queen] == board[i]
            || board[queen] - board[i] == queen - i
            || board[i] - board[queen] == queen - i) {
            return false;
        }
    }
    if (board[queen] > N - 1) {
        board[queen] = 0;
        queen--;
        return false;
    }
    return true;
}

void print() {
    for (int i : board) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
}
