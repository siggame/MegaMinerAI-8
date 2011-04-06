#include "../manager/manager.h"
#include "../gameobject/gameobject.h"

typedef int ObjIdType;

class ObjectManager : public Manager<ObjIdType,GameObject>
{

};
