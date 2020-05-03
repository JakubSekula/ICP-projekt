#ifndef COORDINATE_H
#define COORDINATE_H


class coordinate
{
public:
    coordinate( float x, float y );
    float GetX();
    float GetY();

private:
    float x, y;
};

#endif // COORDINATE_H
