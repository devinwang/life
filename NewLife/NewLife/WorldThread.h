#pragma once

#include "TheWorld.h"

// CWorldThread
class CTheWorld;
class CGlDraw;

class CWorldThread
{
protected:


public:
	CWorldThread(void);           // 动态创建所使用的受保护的构造函数
	virtual ~CWorldThread();

	virtual BOOL MainLoop(CGlDraw* pGlDraw);
	virtual int ExitInstance();

protected:
//	DECLARE_MESSAGE_MAP()
public:
	CTheWorld* m_pTheWorld;

};


