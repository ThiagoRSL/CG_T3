#include "CharacterBuilder.h"


CharacterBuilder::CharacterBuilder()
{
    //ctor
}

Character* CharacterBuilder::BuildShip(float x, float y, float* RGB, int ship_type_code)
{
    switch(ship_type_code)
    {
        case 1:
            return CreateSmallShip(x, y, RGB);
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;

    }
}

Character* CharacterBuilder::CreateSmallShip(float x, float y, float* RGB)
{
    Character* character = new Character(x, y, RGB);
    character->CreateWeaponSlot(Pnt2(0,0));

    ShipPart* body = CreateChassis(x, y, RGB);
    character->AppendPart(body);

    return character;
}

ShipPart* CharacterBuilder::CreateChassis(float x, float y, float* RGB)
{
    ShipPart* chassis = new ShipPart(x, y, RGB);
    chassis->AddVertex(-20,-25);
    chassis->AddVertex(-10,-40);
    chassis->AddVertex(10,-40);
    chassis->AddVertex(20,-25);
    chassis->AddVertex(20,25);
    chassis->AddVertex(-20,25);
    return chassis;
}
