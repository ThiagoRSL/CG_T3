#include "Renderable.h"

Renderable::Renderable()
{
    CameraOffsetRef = CameraManager::shared_instance().GetCameraOffsetRef();
    Static(false);
}
