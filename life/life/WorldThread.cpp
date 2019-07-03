// WorldThread.cpp : 实现文件
//

#include "stdafx.h"
#include "life.h"
#include "WorldThread.h"
#include ".\worldthread.h"
#include "MainFrm.h"


// CWorldThread

IMPLEMENT_DYNCREATE(CWorldThread, CWinThread)

CWorldThread::CWorldThread()
{

}

CWorldThread::~CWorldThread()
{
}

BOOL CWorldThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	//MessageBox(NULL, "Helllo", "He", 0);
	SetThreadPriority(THREAD_PRIORITY_IDLE);

	srand( (unsigned)time( NULL ) );

	// 世界开始时只有一个低等生命体
	CLifeBody *pInitBody;

	// 新生命开始
	pInitBody = new CLifeBody();
	
	// 初始化这个生命体
	pInitBody->m_age = 0;
	pInitBody->m_age_max = CELL_AGE;
	pInitBody->m_hp = CELL_HP;
	pInitBody->m_hp_max = CELL_HP;
	pInitBody->m_pField = &m_pTheWorld->m_clsField[WORLD_WIDE/2][WORLD_WIDE/2];
	pInitBody->m_pNextBody = NULL;
	pInitBody->m_x = WORLD_WIDE/2;
	pInitBody->m_y = WORLD_WIDE/2;
	pInitBody->m_z = WORLD_WIDE/2;
	
	// 在世界的中心产生
	m_pTheWorld->m_clsField[WORLD_WIDE/2][WORLD_WIDE/2].m_pLifeBody = pInitBody;

	//while(1)
	//{
	//	m_pView->Render();
		//Sleep(1);

	//}

	// 驱动整个世界
	int i, j;

begin:
	// 遍历整个世界为了使每块草地产生食物
	//for(k = 0; k < WORLD_WIDE; k++)
		for(j = 0; j < WORLD_WIDE; j++)
			for(i = 0; i < WORLD_WIDE; i++)
			{
				// 每年使每块草地产生的食物
				m_pTheWorld->m_clsField [j][i].m_nFood += FIELD_FOOD_INC;

				// 如果每块草地食物达到最大值
				if( m_pTheWorld->m_clsField [j][i].m_nFood > FIELD_FOOD_MAX)
					m_pTheWorld->m_clsField [j][i].m_nFood = FIELD_FOOD_MAX;

			}

	// 遍历整个世界的生命体，让寿命到期的生命体死亡
	//for(k = 0; k < WORLD_WIDE; k++)
		for(j = 0; j < WORLD_WIDE; j++)
			for(i = 0; i < WORLD_WIDE; i++)
			{
				
				// 得到当前草地指针
				CField*		pField = &m_pTheWorld->m_clsField [j][i];

				// 指向当前生命体的指针
				CLifeBody*	pBody = pField->m_pLifeBody;

				// 指向存放当前生命体指针的地址的指针
				CLifeBody** pPrevAddr = &pField->m_pLifeBody;

				// 遍历本草地上的所有生命体
				while(pBody)
				{
					// 生命体长了一岁
					pBody->m_age++;
					
					// 如果生命体寿命到期->死亡
					if(pBody->m_age >= pBody->m_age_max)
					{
						// 临时保存当前生命体的指针
						CLifeBody* pCurBody = pBody;

						// 让上一个生命体的下一生命体指针指向本生命体的下一生命体
						*pPrevAddr = pBody->m_pNextBody;
						
						// 准备遍历下一个生命体
						//pPrevAddr = &pBody->m_pNextBody;
						pBody = pBody->m_pNextBody;

						// 本生命体死亡
						delete pCurBody;

						continue;
					}

					// 生命体每年都要消耗生命值
					// 消耗的生命值为其最大生命值的一个百分比
					int nDecHp = (pBody->m_hp_max * DEC_HP_PER)/100;
					// 减少的生命值不能为一；
					if(nDecHp <= 0)
						nDecHp = 1;

					pBody->m_hp -= nDecHp;

					// 如果生命体生命值减少到限定值，它就死亡了
					if(pBody->m_hp <= 0 || 
						pBody->m_hp <= (pBody->m_hp_max * DEAD_LINE)/100)
					{
						// 临时保存当前生命体的指针
						CLifeBody* pCurBody = pBody;

						// 让上一个生命体的下一生命体指针指向本生命体的下一生命体
						*pPrevAddr = pBody->m_pNextBody;
						
						// 准备遍历下一个生命体
						//pPrevAddr = &pBody->m_pNextBody;
						pBody = pBody->m_pNextBody;

						// 本生命体死亡
						delete pCurBody;

						continue;
					}
					
					// 遍历下一个生命体
					pPrevAddr = &pBody->m_pNextBody;
					pBody = pBody->m_pNextBody;
				}

			}


	// 遍历整个世界驱动所有生命体觅食
//	for(k = 0; k < WORLD_WIDE; k++)
		for(j = 0; j < WORLD_WIDE; j++)
			for(i = 0; i < WORLD_WIDE; i++)
			{
				// 得到当前草地指针
				CField*		pField = &m_pTheWorld->m_clsField [j][i];

				// 指向当前生命体的指针
				CLifeBody*	pBody = pField->m_pLifeBody;

				// 指向存放当前生命体指针的地址的指针
				CLifeBody** pPrevAddr = &pField->m_pLifeBody;


				// 遍历当前草地上的所有生命体
				while(pBody)
				{ 
					// 将要迁徙去的草地指针
					CField* pMoveField = NULL;
					
					// 将要被吃掉的生命体指针
					CLifeBody* pEatBody = NULL;
					BOOL		bRet;

					// 临时保存当前生命体的指针
					CLifeBody* pCurBody = pBody;

					// 寻找食物
					bRet = pBody->LookForFood(&pMoveField, &pEatBody);
					switch(bRet)
					{

						// 生命体要求迁徙
						case CL_MOVE:
							// 从当前草地的生命体链中断开
							// 让上一个生命体的下一生命体指针指向本生命体的下一生命体
							*pPrevAddr = pBody->m_pNextBody;
						
							// 把当前生命体挂到要迁徙去草地的生命体链上
							pCurBody->m_pNextBody = pMoveField->m_pLifeBody;
							pMoveField->m_pLifeBody = pCurBody;
							pCurBody->m_pField = pMoveField;

							// 准备遍历下一个生命体
							goto	manual_next;
							break;
						
						// 生命体吃掉本地的一个生命体
						case CL_EAT:
							{
								// 准备重遍历本生命体所在草地的所有生命体
								CLifeBody* pReBody = pBody->m_pField->m_pLifeBody;
								// 指向存放重遍历生命体指针的地址的指针
								CLifeBody** pRePrevAddr = &pBody->m_pField->m_pLifeBody;
								while(pReBody)
								{
									// 如果当前生命体是要被吃掉的生命体
									if(pReBody == pEatBody)
									{
										// 把这个生命体从生命体链中断开
										*pRePrevAddr = pReBody->m_pNextBody;
										// 杀死这个生命体
										delete pReBody;
										break;
									}
									// 准备遍历下一个生命体
									pRePrevAddr = &pReBody->m_pNextBody;
									pReBody = pReBody->m_pNextBody;
								}
								// 当执行到这里，这个被吃掉的生命体就已经被从链中删掉了，但有两种情况需要特别考虑。
								// 1、当这个被删除的生命体正好位于本生命体上方时,因为其被删掉了，pPrevAddr指向的仍旧
								// 还是这个已经失效的生命体的成员变量m_pNextBody，所以在pPrevAddr更新以前，在下面的
								// 操作中绝对不允许对*pPrevAddr进行任何操作。
								// 2、当这个被删除的生命体正好位于本生命体下方时，因为在删除它的过程中已经对本生命体
								// 的m_pNextBody指针已经作了更新(*pRePrevAddr = pReBody->m_pNextBody)，
								// 所以在以后的操作中不会有问题，和其它一般情况相同。

							}
							break;
						
						case CL_MOVE_EAT:
							{
								// 准备重遍历准备吃掉的生命体所在草地的所有生命体
								CLifeBody* pReBody = pEatBody->m_pField->m_pLifeBody;
								// 指向存放重遍历生命体指针的地址的指针
								CLifeBody** pRePrevAddr = &pEatBody->m_pField->m_pLifeBody;
								while(pReBody)
								{
									// 如果当前生命体是要被吃掉的生命体
									if(pReBody == pEatBody)
									{
										// 把当前生命体取代被吃掉的生命体位置
										*pRePrevAddr = pBody;
										
										// 把当前生命体从当前草地生命体链中取下来
										*pPrevAddr = pBody->m_pNextBody;

										// 接下被吃掉的生命体的生命体链
										pBody->m_pNextBody = pReBody->m_pNextBody;

										// 更改其所在草地
										pBody->m_pField = pReBody->m_pField;

										// 杀死被吃掉的生命体
										delete pReBody;

										// 当前生命体已经离开本草地
										// 准备遍历下一个生命体
										goto manual_next;

										break;
									}
									// 准备遍历下一个生命体
									pRePrevAddr = &pReBody->m_pNextBody;
									pReBody = pReBody->m_pNextBody;
								}

							}
							break;
					
						case CL_FULL:
							// 生命体吃饱了，世界不需要为它做什么。
							break;
					}

auto_next:
					// 准备遍历下一个生命体
					pPrevAddr = &pBody->m_pNextBody;
manual_next:
					// 为了处理pBody已经失效的情况，如生命体到别的草地去了
					pBody = *pPrevAddr;

				}
			}


	// 遍历整个世界驱动所有生命体完成生殖
	// for(k = 0; k < WORLD_WIDE; k++)
	for(j = 0; j < WORLD_WIDE; j++)
		for(i = 0; i < WORLD_WIDE; i++)
		{
			// 得到当前草地指针
			CField*		pField = &m_pTheWorld->m_clsField [j][i];

			// 指向当前生命体的指针
			CLifeBody*	pBody = pField->m_pLifeBody;


			// 当前草地新生的小孩们
			CLifeBody* pChildrenBody = NULL;

			// 遍历当前草地上的所有生命体
			while(pBody)
			{
				// 生命体生殖
				CLifeBody* pChildBody = pBody->Propagate();

				// 如果新生了小孩，那我们把它们临时挂到新生小孩链上
				if(pChildBody)
				{
					// 把新生小孩加入新生小孩链
					pChildBody->m_pNextBody  = pChildrenBody;

					pChildrenBody = pChildBody;
 
				}
				pBody = pBody->m_pNextBody;
			}

			// 把新生小孩链挂到当前草地生命体链中去
			if(pChildrenBody)
			{
				// 原生命体链指针
				CLifeBody* pOldBody = pField->m_pLifeBody;
				
				// 现生命体链指针
				pField->m_pLifeBody = pChildrenBody;
				
				// 找到现生命体链尾
				CLifeBody* pBody = pChildrenBody;
				while(pBody->m_pNextBody)
				{
					pBody = pBody->m_pNextBody;
				}
				
				// 把原生命体链挂到现生命体链链尾
				pBody->m_pNextBody = pOldBody;
			}
		}


		Render();
	
		goto begin;

	return TRUE;
}

int CWorldThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CWorldThread, CWinThread)
END_MESSAGE_MAP()


// 显示生命体

void CWorldThread::Render(void)
{
	CChildView* pView = &((CMainFrame*)((ClifeApp*)AfxGetApp())->m_pMainWnd)->m_wndView;
	CClientDC dc(pView);

	for(int j = 0; j < WORLD_WIDE; j++)
		for(int i = 0; i < WORLD_WIDE; i++)
		{
			if(m_pTheWorld->m_clsField[j][i].m_pLifeBody)
			{
				dc.SetPixel(j, i, m_pTheWorld->m_clsField[j][i].m_pLifeBody->m_hp_max  *0x000000ff/HP_MAX );
			}
			else
				dc.SetPixel(j, i, RGB(255, 255, 255));
		}

}
