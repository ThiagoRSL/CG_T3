#include "ShipPart.h"

ShipPart::ShipPart(float x, float y, float* RGB)
    :Poly(x, y, RGB)
{
    //ctor
}
void ShipPart::AddModifier(int modifier_id)
{
    this->modifiers.push_back(modifier_id);
}
void ShipPart::AddWeaponSlot(int modifier_id)
{
    this->modifiers.push_back(modifier_id);
}
