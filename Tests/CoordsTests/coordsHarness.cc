#include "../../coord.h"
#include <iostream>

using namespace std;

istream& operator>>(istream &in, Coord &myC) {
    
    return in;  
}

ostream& operator<<(ostream &out, Coord &myC) {

    out << "[" << myC.x() << "," << myC.y() << "]";

    return out;

}

int main () {
    char c;
    while (cin >> c) {

        // 1x 1y 2x 2y
        // q - quit 
        // a - add 
        // m - minus
        // e - equality
        // s - scale 

        if (c == 'q') {
            break;
        } else if (c == 'a') {
            int x1, y1, x2, y2;
            cin >> x1;
            cin >> y1;

            cin >> x2;
            cin >> y2;

            Coord one {x1, y1};
            Coord two {x2, y2};
            cout << one << " + ";       
            one = one + two;
            cout << two << " = ";
            cout << one << endl;

        } else if (c == 'm') {

            int x1, y1, x2, y2;
            cin >> x1;
            cin >> y1;

            cin >> x2;
            cin >> y2;

            Coord one {x1, y1};
            Coord two {x2, y2};
            cout << one << " - ";       
            one = one - two;
            cout << two << " = ";
            cout << one << endl;
        }  else if (c == 'e') {

            bool result;
            int x1, y1, x2, y2;
            cin >> x1;
            cin >> y1;

            cin >> x2;
            cin >> y2;

            Coord one {x1, y1};
            Coord two {x2, y2};
            cout << one << " == ";       
            result = one == two;
            cout << two << " ? ";
            if(result) {
                cout << "TRUE" << endl;
            } else {
                cout << "FALSE" << endl;               
            }

        }  else if (c == 's') {
            // takes x1 y1 integer
            int x1, y1, scale;

            cin >> x1;
            cin >> y1;

            cin >> scale;

            Coord one {x1, y1};

            cout << one << " * ";
            cout << scale << " = ";
            cout << one * scale << endl;
        }
    }
}
