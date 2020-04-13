#include "coordinate.h"

coordinate::coordinate( int x, int y ){
    this->x = x;
    this->y = y;
}

int coordinate::GetX(){
    return this->x;
}

int coordinate::GetY(){
    return this->y;
}
