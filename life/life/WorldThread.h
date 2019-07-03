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
	CWorldThread(void);           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CWorldThread();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CTheWorld* m_pTheWorld;
	CChildView* m_pView;
	// ��ʾ������
	void Render(void);
};


