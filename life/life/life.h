// life.h : life Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


#include "TheWorld.h"
#include "WorldThread.h"

// ClifeApp:
// �йش����ʵ�֣������ life.cpp
//

class ClifeApp : public CWinApp
{
public:
	ClifeApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	
	// ָ��ָ��һ��Ψһ����������
	CTheWorld *m_pTheWorld;

	CWorldThread	*m_pThread;
};

extern ClifeApp theApp;
