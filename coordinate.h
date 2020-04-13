#ifndef COORDINATE_H
#define COORDINATE_H


class coordinate
{
public:
    coordinate( int x, int y );
    int GetX();
    int GetY();

private:
    int x, y;
};

#endif // COORDINATE_H
