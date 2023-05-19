#include "Slot.h"
#include "ShipPart.h"

Slot::Slot()
{
    //ctor
}

void Slot::Render()
{
    printf("Sou um slot.");
}

void Slot::SlotOf(ShipPart* part)
{
    AttachedTo = part;
}
ShipPart* Slot::SlotOf()
{
    return AttachedTo;
}
