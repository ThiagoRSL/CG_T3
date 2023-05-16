#ifndef CHARACTERBUILDER_H
#define CHARACTERBUILDER_H

#include "Character.h"

class CharacterBuilder
{
    public:
        CharacterBuilder();

        static Character* BuildShip(float x, float y, float* RGB, int ship_type_code);

    protected:

    private:
        static Character* CreateSmallShip(float x, float y, float* RGB);
        static ShipPart* CreateChassis(float x, float y, float* RGB);
};

#endif // CHARACTERBUILDER_H
