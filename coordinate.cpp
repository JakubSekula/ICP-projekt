#include "coordinate.h"

coordinate::coordinate( float x, float y ){
    this->x = x;
    this->y = y;
}

float coordinate::GetX(){
    return this->x;
}

float coordinate::GetY(){
    return this->y;
}
