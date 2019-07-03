// life.h : life 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h” 
#endif

#include "resource.h"       // 主符号


#include "TheWorld.h"
#include "WorldThread.h"

// ClifeApp:
// 有关此类的实现，请参阅 life.cpp
//

class ClifeApp : public CWinApp
{
public:
	ClifeApp();


// 重写
public:
	virtual BOOL InitInstance();

// 实现

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	
	// 指针指向一个唯一的虚拟世界
	CTheWorld *m_pTheWorld;

	CWorldThread	*m_pThread;
};

extern ClifeApp theApp;
