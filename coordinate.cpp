#include "coordinate.h"

/**
 * @brief coordinate::coordinate Nastavenie suradnice
 * @param x Suradnica X
 * @param y Suradnica Y
 */
coordinate::coordinate( float x, float y ){
    this->x = x;
    this->y = y;
}

/**
 * @brief coordinate::GetX
 * @return Vrati suradnicu X
 */
float coordinate::GetX(){
    return this->x;
}

/**
 * @brief coordinate::GetY
 * @return Vrati suradnicu Y
 */
float coordinate::GetY(){
    return this->y;
}
