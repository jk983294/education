#include <unistd.h>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;


struct Board {
    std::vector<int8_t> board;

    Board() {
        board.resize(9 * 9, 0);
    }
    int get_index(int row, int col) const { return row * 9 + col; }
    int get_val(int row, int col) const { return board[get_index(row, col)]; }
    void set_val(int row, int col, int val) { board[get_index(row, col)] = val; }

    bool feasible(int row, int col) const {
        return check(row, col, true) && check(row, col, false) && check_small_box(row, col);
    }
    void print_board() const {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                printf("%d\t", get_val(i, j));
            }
            printf("\n");
        }
    }
    std::pair<int, int> next_pos() {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                auto v = get_val(i, j);
                if (v <= 0 || v > 9) return {i, j};
            }
        }
        return {-1, -1};
    }
    bool all_good() {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                auto v = get_val(i, j);
                if (v <= 0 || v > 9) return false;
            }
        }
        return true;
    }

private:
    bool check(int row, int col, bool is_row) const {
        vector<bool> good(10, false);
        for (int i = 0; i < 9; ++i) {
            int idx = get_val(row, i);
            if (!is_row) idx = get_val(i, col);
            if (idx > 0) {
                if (good[idx]) {
                    return false;
                } else {
                    good[idx] = true;
                }
            }
        }
        return true;
    }
    bool check_small_box(int row, int col) const {
//        if (row == 1) {
//            printf("h");
//        }
        vector<bool> good(10, false);
        int small_row = row / 3;
        int small_col = col / 3;
        for (int i = 0; i < 3; ++i) {
            int row_curr = small_row * 3 + i;
            for (int j = 0; j < 3; ++j) {
                int col_curr = small_col * 3 + j;
                int idx = get_val(row_curr, col_curr);
                if (idx > 0) {
                    if (good[idx]) {
                        return false;
                    } else {
                        good[idx] = true;
                    }
                }
            }
        }
        return true;
    }
};

struct Item {
    Board m_board;
    int row{-1}, col{-1};
};

struct SudoKuSolution {
    bool input(int row, int col, int val) {
        int val_old = m_board.get_val(row, col);
        if (val_old <= 0) {
            m_board.set_val(row, col, val);
            return m_board.feasible(row, col);
        }
        return false;
    }
    bool solve() {
        if (m_board.all_good()) return true;
        bool last_push = true;
        auto pos_ = m_board.next_pos();
        auto b = m_board;
        b.set_val(pos_.first, pos_.second, 1);
        s.push({b, pos_.first, pos_.second});
        printf("push %d,%d,%d\n", pos_.first, pos_.second, 1);
        while (!s.empty()) {
            Item curr = s.top();
            s.pop();
            if (last_push) {
                if (curr.m_board.feasible(curr.row, curr.col)) {
                    if (curr.m_board.all_good()) {
                        m_result = curr.m_board;
                        printf("total %d steps\n", m_steps);
                        return true;
                    }
                    pos_ = curr.m_board.next_pos();
                    if (pos_.first >= 0) {
                        s.push(curr);
                        b = curr.m_board;
                        b.set_val(pos_.first, pos_.second, 1);
                        s.push({b, pos_.first, pos_.second});
                        printf("push %d,%d,%d\n", pos_.first, pos_.second, 1);
                        ++m_steps;
                        last_push = true;
                    } else {
                        printf("pop %d,%d,%d\n", curr.row, curr.col, 1);
                        ++m_steps;
                        last_push = false;
                    }
                } else {
                    last_push = pop_out(curr);
                }
            } else { // pop
                last_push = pop_out(curr);
            }
            //sleep(1);
        }
        return false;
    }

    bool pop_out(Item& curr) {
        int val = curr.m_board.get_val(curr.row, curr.col);
        ++m_steps;
        printf("pop %d,%d,%d\n", curr.row, curr.col, val);
        if (val >= 9) { // continue pop
            return false;
        } else {
            curr.m_board.set_val(curr.row, curr.col, val + 1);
            s.push(curr);
            ++m_steps;
            printf("push %d,%d,%d\n", curr.row, curr.col, val + 1);
            return true;
        }
    }
    Board m_board, m_result;
    std::stack<Item> s;
    int m_steps{0};
};

int main(int argc, char** argv) {
    SudoKuSolution solution;
//    cout << "question:\n";
//    int row, col, val;
//    while (true) {
//        cin >> row >> col >> val;
//        if (row < 0) {
//            cout << "input end\n";
//            break;
//        } else {
//            if (!solution.input(row, col, val)) {
//                cout << "position not good\n";
//                exit(0);
//            }
//        }
//    }
//    solution.input(0, 0, 1);
    solution.m_board.board = {8, 0, 0, 0, 5, 9, 0, 0, 0,
                              0, 4, 5, 0, 8, 7, 9, 6, 0,
                              0, 9, 0, 2, 0, 4, 5, 8, 7,
                              0, 0, 9, 0, 0, 6, 8, 4, 1,
                              4, 1, 0, 0, 0, 0, 6, 0, 0,
                              6, 2, 8, 4, 0, 0, 3, 7, 5,
                              0, 7, 1, 9, 6, 2, 4, 3, 8,
                              0, 8, 4, 7, 0, 3, 2, 5, 0,
                              0, 0, 2, 8, 0, 5, 7, 0, 9};
    solution.solve();
    solution.m_result.print_board();
    return 0;
}
