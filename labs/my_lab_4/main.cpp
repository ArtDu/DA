#include <iostream>
#include <vector>
#include <queue>

void z_func(std::vector<uint32_t> &z, const std::vector<uint64_t> &string);

void prefix_func(std::vector<uint32_t> &sp, const std::vector<uint32_t> &z);

void failure_func(std::vector<uint32_t> &F, const std::vector<uint32_t> &sp);

void kmp(const std::vector<uint64_t> &string, const std::vector<uint32_t> &F);

uint64_t read_number(bool &EOF_status, uint32_t &column, uint32_t &row, bool &newline);

int main() {

    std::vector<uint64_t> string;
    std::vector<uint32_t> z;
    std::vector<uint32_t> sp;
    std::vector<uint32_t> F;

    int32_t c;
    uint64_t num = 0;
    bool last = true;
    do {
        c = getchar();
    } while (c == ' ');
    if (c == EOF) {
        return 0;
    }
    do {

        if (c == ' ' || c == '\n') {
            last = false;
            string.push_back(num);
            num = 0;
            do {
                c = getchar();
            } while (c == ' ');
            if (c == EOF) {
                return 0;
            }
            continue;
        } else {
            last = true;
            num = (num * 10) + c - '0';
        }
        c = getchar();
        if (c == EOF) {
            return 0;
        }
    } while (c != '\n');

    if (num != 0 || last) {
        string.push_back(num);
    }

    z_func(z, string);
    prefix_func(sp, z);
    failure_func(F, sp);
    kmp(string, F);
    return 0;
}

void z_func(std::vector<uint32_t> &z, const std::vector<uint64_t> &string) {
    size_t string_size = string.size();
    z.resize(string_size, 0);
    uint32_t l = 0, r = 0;
    for (uint32_t k = 1; k < string_size; ++k) {
        if (k > r) {
            uint32_t i = 0, j = k;
            while (string[i] == string[j]) {
                i++;
                j++;
            }
            z[k] = i;
            if (z[k] > 0) {
                r = k + z[k] - 1;
                l = k;
            }
        } else {
            uint32_t k_ = k - l;
            if (z[k_] < r - k + 1) {
                z[k] = z[k_];
            } else {
                uint32_t i = z[l] + 1, j = r + 1;
                while (string[i] == string[j]) {
                    i++;
                    j++;
                }
                z[k] = j - k;
                r = j - 1;
                l = k;
            }
        }
    }

}

void prefix_func(std::vector<uint32_t> &sp, const std::vector<uint32_t> &z) {
    size_t z_size = z.size();
    sp.resize(z_size, 0);
    for (uint64_t j = z_size - 1; j > 1; --j) {
        uint64_t i = j + z[j] - 1;
        if (i < z_size)
            sp[i] = z[j];
    }
}

void failure_func(std::vector<uint32_t> &F, const std::vector<uint32_t> &sp) {
    size_t sp_size = sp.size();
    F.resize(sp_size, 0);
    for (int i = 1; i < sp_size; ++i) {
        F[i] = sp[i - 1];
    }
}

uint64_t read_number(bool &EOF_status, uint32_t &column, uint32_t &row, bool &newline) {
    int32_t c;
    uint64_t num = 0;
    do {
        c = getchar();
        if (c == '\n') {
            row++;
        }
    } while (c == ' ' || c == '\n');
    do {

        if (c == EOF) {
            EOF_status = true;
            break;
        } else if (c == ' ' || c == '\n') {
            if (c == '\n') {
                column++;
                newline = true;
            } else {
                column++;
            }

            break;
        } else {
            num = (num * 10) + c - '0';
        }
        c = getchar();
    } while (true);
    return num;
}

void kmp(const std::vector<uint64_t> &string, const std::vector<uint32_t> &F) {
    std::queue<std::pair<uint32_t, uint32_t >> pos;
    std::pair<uint32_t, uint32_t> pos_pair;
    uint32_t column = 0, row = 1;
    uint64_t t;
    uint64_t p = 0, n = string.size();
    bool exit = false;
    bool new_line = false;
    bool skip = false;
    t = read_number(exit, column, row, new_line);
    if (exit)
        return;
    pos_pair = std::make_pair(row, column);
    pos.push(pos_pair);
    if (new_line) {
        column = 0;
        row++;
        new_line = false;
    }

    while (true) {

        while (string[p] == t && p < n) {
            p++;
            if (exit) {
                break;
            }
            t = read_number(exit, column, row, new_line);
            pos_pair = std::make_pair(row, column);
            if (p == n) {
                skip = true;
                std::cout << pos.front().first << ", " << pos.front().second << std::endl;
            }
            if (pos.size() == n) {
                pos.pop();
            }
            pos.push(pos_pair);
            if (new_line) {
                column = 0;
                row++;
                new_line = false;
            }
        }

        if (p == n && skip == false) {
            std::cout << pos.front().first << ", " << pos.front().second << std::endl;
        }
        skip = false;
        if (exit)
            break;

        if (p == 0) {
            t = read_number(exit, column, row, new_line);
            pos_pair = std::make_pair(row, column);
            if (pos.size() == n) {
                pos.pop();
            }
            pos.push(pos_pair);
            if (new_line) {
                column = 0;
                row++;
                new_line = false;
            }
        }

        p = F[p];
    }
}