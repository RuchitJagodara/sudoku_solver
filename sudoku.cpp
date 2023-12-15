#include <bits/stdc++.h>

typedef struct {
    int b[9][9];
} sudoku;

void clear(bool seen[10])
{
    for (int i = 0; i < 10; ++i) {
        seen[i] = false;
    }
}

int is_valid(const sudoku& s)
{
    bool seen[10];
    for (int row = 0; row < 9; ++row) {
        clear(seen);
        for (int col = 0; col < 9; ++col) {
            int v = s.b[row][col];
            if (v && seen[v]) { return false; }
            seen[v] = true;
        }
    }
    for (int col = 0; col < 9; ++col) {
        clear(seen);
        for (int row = 0; row < 9; ++row) {
            int v = s.b[row][col];
            if (v && seen[v]) { return false; }
            seen[v] = true;
        }
    }
    int boxrow = 0;
    int boxcol = 0;
    while (boxrow < 9) {
        while (boxcol < 9) {
            clear(seen);
            for (int r = 0; r < 3; ++r) {
                for (int c = 0; c < 3; ++c) {
                    int v = s.b[boxrow+r][boxcol+c];
                    if (v && seen[v]) { return false; }
                    seen[v] = true;
                }
            }
            boxcol += 3;
        }
        boxrow += 3;
        boxcol = 0;
    }
    return true;
}

sudoku place(const sudoku& s, int i, int j, int v)
{
    sudoku t = s;
    assert(t.b[i][j] == 0);
    t.b[i][j] = v;
    return t;
}

void print_board(const sudoku& s)
{
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            int v = s.b[r][c];
            if (v) std::cout << v << " ";
            else std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

void read_board(sudoku& s)
{
    int v;
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            std::cin >> v;
            s.b[r][c] = v;
        }
    }
}

bool is_full(const sudoku& s)
{
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (s.b[r][c] == 0) return false;
        }
    }
    return true;
}

std::pair<int, int> find_first_blank(const sudoku& s)
{
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (s.b[r][c] == 0) return { r, c };
        }
    }
    assert(0);
}

sudoku solve(const sudoku& s)
{
    std::stack<sudoku> st;
    st.push(s);
    while (!st.empty()) {
        sudoku v = st.top();
        st.pop();
        if (is_full(v)) {
            return v;
        }
        auto pos = find_first_blank(v);
        for (int val = 1; val <= 9; ++val) {
            sudoku u = place(v, pos.first, pos.second, val);
            if (is_valid(u)) {
                st.push(u);
            }
        }
    }
    assert(0);
}

int main()
{
    sudoku s;
    read_board(s);
    print_board(s);
    std::cout << "===\n";
    sudoku t = solve(s);
    print_board(t);

    return 0;
}
