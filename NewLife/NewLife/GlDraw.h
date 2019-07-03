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
	// ≥ı ºªØGlDraw
	int InitGlDraw(void);
	int CGlDraw::Render(CTheWorld* pWorld);
};
