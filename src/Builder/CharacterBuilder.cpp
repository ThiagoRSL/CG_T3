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
            return CreateMediumShip(x, y, RGB);
        case 3:
            break;
        case 4:
            break;

    }
}

Character* CharacterBuilder::CreateSmallShip(float x, float y, float* RGB)
{
    Character* character = new Character(x, y, RGB);
    ShipPart* body = CreateChassis(x, y, RGB);
    body->AddWeaponSlot(Pnt2(0,0));
    character->AppendPart(body);

    return character;
}

Character* CharacterBuilder::CreateMediumShip(float x, float y, float* RGB)
{
    Character* character = new Character(x, y, RGB);
    //character->CreateWeaponSlot(Pnt2(0,0));

    ShipPart* body = CreateChassis(x, y, RGB);
    body->AddWeaponSlot(Pnt2(0,0));
    character->AppendPart(body);


    ShipPart* rightWing = CreateRightWing(x, y, RGB);
    rightWing->AddWeaponSlot(Pnt2(30,5));
    character->AppendPart(rightWing);
    ShipPart* leftWing = CreateLeftWing(x, y, RGB);
    leftWing->AddWeaponSlot(Pnt2(-30,5));
    character->AppendPart(leftWing);


    return character;
}

ShipPart* CharacterBuilder::CreateChassis(float x, float y, float* RGB)
{
    ShipPart* part = new ShipPart(x, y, RGB);
    part->AddVertex(-20,-25);
    part->AddVertex(-10,-40);
    part->AddVertex(10,-40);
    part->AddVertex(20,-25);
    part->AddVertex(20,25);
    part->AddVertex(-20,25);
    return part;
}

ShipPart* CharacterBuilder::CreateLeftWing(float x, float y, float* RGB)
{
    ShipPart* leftWing = new ShipPart(x, y, RGB);
    leftWing->AddVertex(10, -25);
    leftWing->AddVertex(-10, -10);
    leftWing->AddVertex(-10, 30);
    leftWing->AddVertex(10, 30);
    leftWing->SetOffset(-30, 0);
    return leftWing;
}

ShipPart* CharacterBuilder::CreateRightWing(float x, float y, float* RGB)
{
    ShipPart* rightWing = new ShipPart(x, y, RGB);
    rightWing->AddVertex(10, -10);
    rightWing->AddVertex(-10, -25);
    rightWing->AddVertex(-10, 30);
    rightWing->AddVertex(10, 30);
    rightWing->SetOffset(30, 0);
    return rightWing;
}
