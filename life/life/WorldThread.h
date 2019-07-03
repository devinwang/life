#pragma once

#include "TheWorld.h"
#include "ChildView.h"

// CWorldThread
class CTheWorld;

class CWorldThread : public CWinThread
{
	DECLARE_DYNCREATE(CWorldThread)

protected:


public:
	CWorldThread(void);           // 动态创建所使用的受保护的构造函数
	virtual ~CWorldThread();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CTheWorld* m_pTheWorld;
	CChildView* m_pView;
	// 显示生命体
	void Render(void);
};


