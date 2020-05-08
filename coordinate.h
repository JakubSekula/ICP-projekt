#ifndef COORDINATE_H
#define COORDINATE_H


class coordinate
{
public:

    /**
     * @brief coordinate::coordinate Nastavenie suradnice
     * @param x Suradnica X
     * @param y Suradnica Y
     */
    coordinate( float x, float y );

    /**
     * @brief coordinate::GetX
     * @return Vrati suradnicu X
     */
    float GetX();

    /**
     * @brief coordinate::GetY
     * @return Vrati suradnicu Y
     */
    float GetY();

private:
    float x, y; //!< x a y suradnica bodu
};

#endif // COORDINATE_H
