#include "Slot.h"
#include "ShipPart.h"

Slot::Slot()
{
    //ctor
}

void Slot::SlotOf(ShipPart* part)
{
    AttachedTo = part;
}

ShipPart* Slot::SlotOf()
{
    return AttachedTo;
}
