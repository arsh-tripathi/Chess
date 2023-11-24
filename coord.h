#ifndef __COORD_H_
#define __COORD_H_

class Coord
{
    int X;
    int Y;

  public:
    Coord(int x, int y);
    Coord(Coord &other);
    Coord(Coord &&other);
    Coord &operator=(Coord &other);
    Coord &operator=(Coord &&other);
    ~Coord();

    int x();
    int y();

    bool checkBounds();
    bool operator==(Coord &other);
    Coord &operator+(Coord &other);
    Coord &operator-(Coord &other);
    Coord &operator*(int scale);
};

#endif
