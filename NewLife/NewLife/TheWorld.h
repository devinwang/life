
// 世界类，用于形成整个虚拟世界。

#pragma once
#include "condef.h"
#include "field.h"
#include "WorldThread.h"

class CTheWorld
{
public:
	CTheWorld(void);
	~CTheWorld(void);
	// 世界中的这块草地
	CField m_clsField[WORLD_WIDE][WORLD_WIDE];

};
