#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <sstream>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;

vector<vector<bool>> out;

int unicode(int x, int y) {
    int track = 1, ret = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            if (out[(1 - i) + x][(2 - j) + y]) {
                ret += track;
            }
            track *= 2;
        }
    }
    return ret;
}

int main() {

    _setmode(_fileno(stdout), _O_U16TEXT);

    srand(time(NULL));

    const char fill = '0', white = '.';
    const String image = "che.png", output = "out.txt";
    const int thresh = 50, xSquish = 6, ySquish = 16;

    Image img;
    if (!img.loadFromFile(image)) cerr << "yike";

    wofstream of;
    of.open(output);
    cout << of.fail();


    Vector2u s = img.getSize();

    for (int i = 0; i < s.y; i += ySquish) {
        vector<bool> ph;
        for (int j = 0; j < s.x; j += xSquish) {
            if (img.getPixel(j, i).r < thresh + (rand() % (255 - thresh))) {
                ph.push_back(true);
            } else {
                ph.push_back(false);
            }
        }
        out.push_back(ph);
    }


    int c = 0;
    for (int i = 0; i < out.size() - 1; i += 2) {
        if (c > 1800) {
            wcout << endl << endl;
            c = 0;
        }
        for (int j = 0; j < out[0].size() - 1; j += 3) {
            c++;
            wchar_t ph = 10240 + unicode(i, j);
            wcout << ph;
//            of << ph;
        }
        wcout << L"\u000A";
//        of << L"\u000A ";
    }

    of.close();

    return EXIT_SUCCESS;
}
