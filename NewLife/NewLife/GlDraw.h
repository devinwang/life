#pragma once

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

class CTheWorld;

class CGlDraw
{
public:
	CGlDraw(void);
	~CGlDraw(void);
	// ��ʼ��GlDraw
	int InitGlDraw(void);
	int CGlDraw::Render(CTheWorld* pWorld);
};
