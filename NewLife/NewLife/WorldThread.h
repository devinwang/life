#pragma once

#include "TheWorld.h"

// CWorldThread
class CTheWorld;
class CGlDraw;

class CWorldThread
{
protected:


public:
	CWorldThread(void);           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CWorldThread();

	virtual BOOL MainLoop(CGlDraw* pGlDraw);
	virtual int ExitInstance();

protected:
//	DECLARE_MESSAGE_MAP()
public:
	CTheWorld* m_pTheWorld;

};


