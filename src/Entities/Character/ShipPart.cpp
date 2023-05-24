#include "ShipPart.h"
#include "Character.h"

ShipPart::ShipPart(float x, float y, float* RGB)
    :Poly(x, y, RGB)
{
    this->part_type_id = part_type_id;
}


void ShipPart::AddModifier(int modifier_id)
{
    //this->modifiers.push_back(modifier_id);
}

void ShipPart::AddWeaponSlot(Pnt2 offset)
{
    WeaponSlot* ws = new WeaponSlot();
    ws->EquippedWeapon = nullptr;
    ws->SetPosition(offset.x + this->Offset.x, offset.y + this->Offset.y);
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

void ShipPart::SetOffset(float x, float y)
{
    Poly::SetOffset(x, y);
    int i;
    for(i = 0; i < WeaponSlots.size(); i++)
    {
        WeaponSlots.at(i)->SetPosition(WeaponSlots.at(i)->GetPosition().x + this->Offset.x, WeaponSlots.at(i)->GetPosition().y + this->Offset.y);
    }
}
