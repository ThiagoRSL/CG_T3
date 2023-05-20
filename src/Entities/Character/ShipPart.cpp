#include "ShipPart.h"
#include "Character.h"

ShipPart::ShipPart(float x, float y, float* RGB)
    :Poly(x, y, RGB)
{
    //ctor
}


void ShipPart::AddModifier(int modifier_id)
{
    //this->modifiers.push_back(modifier_id);
}

void ShipPart::AddWeaponSlot(Pnt2 offset)
{
    WeaponSlot* ws = new WeaponSlot();
    ws->EquippedWeapon = nullptr;
    ws->SetOffset(offset.x, offset.y);
    WeaponSlots.push_back(ws);
    ws->SlotOf(this);
}

void ShipPart::AddMotorSlot(Pnt2 offset)
{
    /*
    WeaponSlot* ws = new WeaponSlot();
    ws->EquippedWeapon = nullptr;
    ws->SetOffset(offset.x, offset.y);
    WeaponSlots.push_back(ws);*/
}

void ShipPart::AppendToCharacter(Character* character)
{
    this->AttachedTo = character;
    this->Anchor = character->GetAnchor();
}
