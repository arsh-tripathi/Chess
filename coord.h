#ifndef __COORD_H_
#define __COORD_H_

class Coord
{
    int X;
    int Y;

  public:
    Coord(int x, int y);
    Coord(const Coord &other);
    Coord(Coord &&other);
    Coord &operator=(const Coord &other);
    Coord &operator=(Coord &&other);
    ~Coord();

    int x() const;
    int y() const;

    bool checkBounds() const;
    bool operator==(const Coord &other) const;
    Coord operator+(const Coord &other);
    Coord operator-(const Coord &other);
    Coord operator*(int scale);
};

#endif
