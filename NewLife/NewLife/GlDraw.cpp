#include "StdAfx.h"
#include ".\gldraw.h"

#include <stdio.h>

#include "condef.h"
#include "TheWorld.h"
#include "LifeBody.h"

CGlDraw::CGlDraw(void)
{
}

CGlDraw::~CGlDraw(void)
{
}

static void CALLBACK GLReflashFun(GLsizei x, GLsizei y)
{
//	AfxMessageBox("Win");
	return;
}

static void CALLBACK GLMouseFun(AUX_EVENTREC * pEvent)
{
//	AfxMessageBox("Mouse");
	return;
}

void CALLBACK display(void)
{
	glColor3f(1.0,1.0,0.0);
	//DrawMyObjects();
	glFlush();
}

// 初始化GlDraw
int CGlDraw::InitGlDraw(void)
{
	//AUXRESHAPEPROC
	auxInitDisplayMode(AUX_DOUBLE |AUX_RGBA);
	//auxInitDisplayMode(AUX_SINGLE |AUX_RGBA);
	auxInitPosition(0,0,600,600);
	auxInitWindow("simple");


	//auxReshapeFunc(GLReflashFun);
	//auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, GLMouseFun);

	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//glViewport(0, 0, 100,100);
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glRotatef(30, 1, 0, 0);
	glRotatef(30, 0, 1, 0);
	glTranslatef(-0.7, -0.3, 0);
	//glViewport(-20, -20, 400, 400);
	//glFrustum(-20, 20, -20, 20, 5, 30); 
	//glTranslatef(0.0, 0.0, 0.0);
	//glScalef(1.0, 2.0, 1.0);

	//glColor3f(1.0,0.0,0.0);
	//glRectf(-0.5,-0.5,0.5,0.5);

	glFlush();


	return 0;
}

// 
int CGlDraw::Render(CTheWorld* pWorld)
{
	int nBodyNum = 0;	
	//hglrc = wglCreateContext(hdc); 
	//GetDC(
	//GetCurrentDc
	//DrawText(



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	



	//glRotatef(20, 1, 1, 1);
	// 画坐标
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();


	for(int j = 0; j < WORLD_WIDE; j++)
		for(int i = 0; i < WORLD_WIDE; i++)
		{
			CLifeBody* pBody = pWorld->m_clsField[j][i].m_pLifeBody;
			int nPos = 0;
			//glBegin(GL_LINES);
			//glBegin(GL_TRIANGLES);
			glBegin(GL_POINTS);
			if(pBody != NULL)
			{
				//glBegin(GL_LINES);

				do{

					UINT nColor = pBody->m_hp_max*0x00ffffff/HP_MAX;
					glColor3b(nColor >>16, nColor, nColor >> 8);
					glVertex3f(((GLfloat)i)/WORLD_WIDE, (GLfloat)(nPos)/40, ((GLfloat)j)/WORLD_WIDE);
					nPos++;
					pBody= pBody->m_pNextBody;
					nBodyNum++;

				}while(pBody != NULL);

				//glEnd();
			}
			//glColor3d(0xff, 0, 0);
			//glVertex3f(0.1, 0.2, 0);
			//glVertex3f(0.0, 0.0, 0);
			//glVertex3f(0.2, 0.0, 0);
			glEnd();
		}
	//TextOut(hDC, 0, 0, "Hello", 5);
	//glBegin(GL_TEXTS);
	//glColor3d(0xff, 0, 0);
	//auxCreateFont();
	//auxDrawStr("Hello");
	//glEnd();

	glFlush();
	auxSwapBuffers();

	// 输出文字
	HDC hDC = auxGetHDC();
	char szBuff[48];
	sprintf(szBuff, "当前生命体个数: %d", nBodyNum);
	TextOut(hDC, 0, 0, szBuff, strlen(szBuff));


	return 0;
}
