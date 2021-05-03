#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int rem = 0;
bool won = 0;

const int dim = 10;
const int bombs = 10;

char m[dim][dim];

int rndint() {
    return rand() % dim;
}
void p(string s) {
    cout << s;
}
void c(int w, int z) {
    m[w][z] += 2;
    rem--;
    for (int x = -(w >= 1); x < (w > 8 ? 1 : 2); x++) {
        for (int y = -(z >= 1); y < (z > 8 ? 1 : 2); y++) {
            if (m[x + w][y + z] & 2 || m[x + w][y + z] & 4) continue;
            if (m[x + w][y + z] >> 3 == 0) c(x + w, y + z);
            else {
                m[x + w][y + z] += 2;
                rem--;
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
    p("          _)                                                    \n");
    p(" __ `__ \\  | __ \\   _ \\  __|\\ \\  \\   / _ \\  _ \\ __ \\   _ \\  __| \n");
    p(" |   |   | | |   |  __/\\__ \\ \\ \\  \\ /  __/  __/ |   |  __/ |    \n");
    p("_|  _|  _|_|_|  _|\\___|____/  \\_/\\_/ \\___|\\___| .__/ \\___|_|    \n");
    p("                                               _|               \n");
    
    p("rxy to reveal x,y, fxy to place flag on x,y\n\n    0 1 2 3 4 5 6 7 8 9\n\n");
    for (int y = 0; y < dim; y++) {
        cout << y << "   ";
        for (int x = 0; x < dim; x++) {
            if (m[x][y] & 4)
                p("f ");
            else if (m[x][y] & 2)
                if (m[x][y] & 1)
                    p("x ");
                else if (m[x][y] >> 3 == 0)
                    p("  ");
                else
                    cout << ((int)(m[x][y]) >> 3) << " ";
            else
                p("# ");
        }
        p("\n");
    }
}
int main()
{
    srand(time(0));
    rem = dim * dim;
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
        string j;
        getline(cin, j);
        string g = j.substr(0, 1);
        if (g == "r") {
            int x = stoi(j.substr(1, 1));
            int y = stoi(j.substr(2, 1));
            if (m[x][y] & 2 || m[x][y] & 4)continue;
            if (m[x][y] & 1) {
                m[x][y] += 2;
                break;
            }
            if (m[x][y] >> 3 == 0) {
                char(*p)[dim][dim] = &m;
                c(x, y);
            }
            else {
                m[x][y] = m[x][y] + 2;
                rem--;
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
        if (rem == bombs) {
            won = 1;
            break;
        }
        r();
    }
    r();
    p((won ? "You win!\n" : "You lose!\n"));
    return 0;
}


