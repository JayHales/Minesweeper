#include <iostream>
#include <string>
#include <cstring>

int left = 0;
bool won = 0;

const int size = 10;
const int bombs = 10;

char m[size][size];

int rndint() {
    return rand() % size;
}
void p(std::string s) {
    std::cout << s;
}
void c(int w, int z) {
    m[w][z] += 2;
    left--;
    for (int x = -(w >= 1); x < (w > 8 ? 1 : 2); x++) {
        for (int y = -(z >= 1); y < (z > 8 ? 1 : 2); y++) {
            if (m[x + w][y + z] & 2 || m[x + w][y + z] & 4) continue;
            if (m[x + w][y + z] >> 3 == 0) c(x + w, y + z);
            else {
                m[x + w][y + z] += 2;
                left--;
            }
        }
    }
}
void r() {
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#endif
    p("    0 1 2 3 4 5 6 7 8 9\n\n");
    for (int y = 0; y < size; y++) {
        std::cout << y << "   ";
        for (int x = 0; x < size; x++) {
            if (m[x][y] & 4)
                p("f ");
            else if (m[x][y] & 2)
                if (m[x][y] & 1)
                    p("x ");
                else if (m[x][y] >> 3 == 0)
                    p("  ");
                else
                    std::cout << ((int)(m[x][y]) >> 3) << " ";
            else
                p("# ");
        }
        p("\n");
    }
}
int main()
{
    srand(time(0));
    left = size * size;
    memset(m, 0, sizeof(m));
    for (int i = 0; i < bombs; i++) {
        int w = rndint();
        int z = rndint();
        if (m[w][z] & 1) {
            i--;
            continue;
        }
        m[w][z] = 1;
        for (int x = -(w >= 1); x < (w > 8 ? 1 : 2); x++) {
            for (int y = -(z >= 1); y < (z > 8 ? 1 : 2); y++) {
                if (x == 0 && y == 0) continue;
                m[x + w][y + z] = m[x + w][y + z] + 8;
            }
        }
    }
    r();
    while (1) {
        std::string j;
        std::getline(std::cin, j);
        std::string g = j.substr(0, 1);
        if (g == "r") {
            int x = stoi(j.substr(1, 1));
            int y = stoi(j.substr(2, 1));
            if (m[x][y] & 2 || m[x][y] & 4)continue;
            if (m[x][y] & 1) {
                m[x][y] += 2;
                break;
            }
            if (m[x][y] >> 3 == 0) {
                char(*p)[size][size] = &m;
                c(x, y);
            }
            else {
                m[x][y] = m[x][y] + 2;
                left--;
            }
        }
        if (g == "f") {
            int x = stoi(j.substr(1, 1));
            int y = stoi(j.substr(2, 1));
            if (m[x][y] & 2) continue;
            if (m[x][y] & 4) {
                m[x][y] -= 4;
                continue;
            }
            m[x][y] += 4;
        }
        if (left == bombs) {
            won = 1;
            break;
        }
        r();
    }
    r();
    p((won ? "You win!" : "You lose!"));
    return 0;
}

