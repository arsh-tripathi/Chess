#include "coord.h"

Coord::Coord(int x, int y) : X{x}, Y{y}
{
}

Coord::Coord(Coord &other) : X{other.X}, Y{other.Y}
{
}

Coord::Coord(Coord &&other) : X{other.X}, Y{other.Y}
{
}

Coord &Coord::operator=(Coord &other)
{
    if (this == &other)
    {
        return *this;
    }
    X = other.X;
    Y = other.Y;
    return *this;
}

Coord &Coord::operator=(Coord &&other)
{
    X = other.X;
    Y = other.Y;
    return *this;
}

Coord::~Coord()
{
}

int Coord::x()
{
    return X;
}

int Coord::y()
{
    return Y;
}

bool Coord::checkBounds()
{
    return (X >= 0) && (X <= 7) && (Y >= 0) && (Y <= 7);
}

bool Coord::operator==(Coord &other)
{
    return (X == other.X) && (Y == other.Y);
}

Coord &Coord::operator+(Coord &other)
{
    X += other.X;
    Y += other.Y;
    return *this;
}

Coord &Coord::operator-(Coord &other)
{
    X -= other.X;
    Y -= other.Y;
    return *this;
}

Coord &Coord::operator*(int scale)
{
    X *= scale;
    Y *= scale;
    return *this;
}
