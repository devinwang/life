// 世界类，用于形成整个虚拟世界。

#include "StdAfx.h"
#include ".\theworld.h"


CTheWorld::CTheWorld(void)
{
	// 初始化草地指针
	for(int j = 0; j< WORLD_WIDE; j++)
		for(int i = 0; i < WORLD_WIDE; i++)
		{
			m_clsField[j][i].m_pESField = &m_clsField[j][(i+1) % WORLD_WIDE];
			m_clsField[j][i].m_pSOField = &m_clsField[(j+1) % WORLD_WIDE][i];
			m_clsField[j][i].m_pWEField = &m_clsField[j][(i+WORLD_WIDE-1) % WORLD_WIDE];
			m_clsField[j][i].m_pNOField  = &m_clsField[(j+WORLD_WIDE-1) % WORLD_WIDE][i];
		}
}

CTheWorld::~CTheWorld(void)
{
}
