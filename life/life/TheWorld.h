
// �����࣬�����γ������������硣

#pragma once
#include "field.h"
#include "WorldThread.h"

class CTheWorld
{
public:
	CTheWorld(void);
	~CTheWorld(void);
	// �����е����ݵ�
	CField m_clsField[WORLD_WIDE][WORLD_WIDE];

};
