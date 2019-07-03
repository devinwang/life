// WorldThread.cpp : ʵ���ļ�
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
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	//MessageBox(NULL, "Helllo", "He", 0);
	SetThreadPriority(THREAD_PRIORITY_IDLE);

	srand( (unsigned)time( NULL ) );

	// ���翪ʼʱֻ��һ���͵�������
	CLifeBody *pInitBody;

	// ��������ʼ
	pInitBody = new CLifeBody();
	
	// ��ʼ�����������
	pInitBody->m_age = 0;
	pInitBody->m_age_max = CELL_AGE;
	pInitBody->m_hp = CELL_HP;
	pInitBody->m_hp_max = CELL_HP;
	pInitBody->m_pField = &m_pTheWorld->m_clsField[WORLD_WIDE/2][WORLD_WIDE/2];
	pInitBody->m_pNextBody = NULL;
	pInitBody->m_x = WORLD_WIDE/2;
	pInitBody->m_y = WORLD_WIDE/2;
	pInitBody->m_z = WORLD_WIDE/2;
	
	// ����������Ĳ���
	m_pTheWorld->m_clsField[WORLD_WIDE/2][WORLD_WIDE/2].m_pLifeBody = pInitBody;

	//while(1)
	//{
	//	m_pView->Render();
		//Sleep(1);

	//}

	// ������������
	int i, j;

begin:
	// ������������Ϊ��ʹÿ��ݵز���ʳ��
	//for(k = 0; k < WORLD_WIDE; k++)
		for(j = 0; j < WORLD_WIDE; j++)
			for(i = 0; i < WORLD_WIDE; i++)
			{
				// ÿ��ʹÿ��ݵز�����ʳ��
				m_pTheWorld->m_clsField [j][i].m_nFood += FIELD_FOOD_INC;

				// ���ÿ��ݵ�ʳ��ﵽ���ֵ
				if( m_pTheWorld->m_clsField [j][i].m_nFood > FIELD_FOOD_MAX)
					m_pTheWorld->m_clsField [j][i].m_nFood = FIELD_FOOD_MAX;

			}

	// ������������������壬���������ڵ�����������
	//for(k = 0; k < WORLD_WIDE; k++)
		for(j = 0; j < WORLD_WIDE; j++)
			for(i = 0; i < WORLD_WIDE; i++)
			{
				
				// �õ���ǰ�ݵ�ָ��
				CField*		pField = &m_pTheWorld->m_clsField [j][i];

				// ָ��ǰ�������ָ��
				CLifeBody*	pBody = pField->m_pLifeBody;

				// ָ���ŵ�ǰ������ָ��ĵ�ַ��ָ��
				CLifeBody** pPrevAddr = &pField->m_pLifeBody;

				// �������ݵ��ϵ�����������
				while(pBody)
				{
					// �����峤��һ��
					pBody->m_age++;
					
					// �����������������->����
					if(pBody->m_age >= pBody->m_age_max)
					{
						// ��ʱ���浱ǰ�������ָ��
						CLifeBody* pCurBody = pBody;

						// ����һ�����������һ������ָ��ָ�����������һ������
						*pPrevAddr = pBody->m_pNextBody;
						
						// ׼��������һ��������
						//pPrevAddr = &pBody->m_pNextBody;
						pBody = pBody->m_pNextBody;

						// ������������
						delete pCurBody;

						continue;
					}

					// ������ÿ�궼Ҫ��������ֵ
					// ���ĵ�����ֵΪ���������ֵ��һ���ٷֱ�
					int nDecHp = (pBody->m_hp_max * DEC_HP_PER)/100;
					// ���ٵ�����ֵ����Ϊһ��
					if(nDecHp <= 0)
						nDecHp = 1;

					pBody->m_hp -= nDecHp;

					// �������������ֵ���ٵ��޶�ֵ������������
					if(pBody->m_hp <= 0 || 
						pBody->m_hp <= (pBody->m_hp_max * DEAD_LINE)/100)
					{
						// ��ʱ���浱ǰ�������ָ��
						CLifeBody* pCurBody = pBody;

						// ����һ�����������һ������ָ��ָ�����������һ������
						*pPrevAddr = pBody->m_pNextBody;
						
						// ׼��������һ��������
						//pPrevAddr = &pBody->m_pNextBody;
						pBody = pBody->m_pNextBody;

						// ������������
						delete pCurBody;

						continue;
					}
					
					// ������һ��������
					pPrevAddr = &pBody->m_pNextBody;
					pBody = pBody->m_pNextBody;
				}

			}


	// ����������������������������ʳ
//	for(k = 0; k < WORLD_WIDE; k++)
		for(j = 0; j < WORLD_WIDE; j++)
			for(i = 0; i < WORLD_WIDE; i++)
			{
				// �õ���ǰ�ݵ�ָ��
				CField*		pField = &m_pTheWorld->m_clsField [j][i];

				// ָ��ǰ�������ָ��
				CLifeBody*	pBody = pField->m_pLifeBody;

				// ָ���ŵ�ǰ������ָ��ĵ�ַ��ָ��
				CLifeBody** pPrevAddr = &pField->m_pLifeBody;


				// ������ǰ�ݵ��ϵ�����������
				while(pBody)
				{ 
					// ��ҪǨ��ȥ�Ĳݵ�ָ��
					CField* pMoveField = NULL;
					
					// ��Ҫ���Ե���������ָ��
					CLifeBody* pEatBody = NULL;
					BOOL		bRet;

					// ��ʱ���浱ǰ�������ָ��
					CLifeBody* pCurBody = pBody;

					// Ѱ��ʳ��
					bRet = pBody->LookForFood(&pMoveField, &pEatBody);
					switch(bRet)
					{

						// ������Ҫ��Ǩ��
						case CL_MOVE:
							// �ӵ�ǰ�ݵص����������жϿ�
							// ����һ�����������һ������ָ��ָ�����������һ������
							*pPrevAddr = pBody->m_pNextBody;
						
							// �ѵ�ǰ������ҵ�ҪǨ��ȥ�ݵص�����������
							pCurBody->m_pNextBody = pMoveField->m_pLifeBody;
							pMoveField->m_pLifeBody = pCurBody;
							pCurBody->m_pField = pMoveField;

							// ׼��������һ��������
							goto	manual_next;
							break;
						
						// ������Ե����ص�һ��������
						case CL_EAT:
							{
								// ׼���ر��������������ڲݵص�����������
								CLifeBody* pReBody = pBody->m_pField->m_pLifeBody;
								// ָ�����ر���������ָ��ĵ�ַ��ָ��
								CLifeBody** pRePrevAddr = &pBody->m_pField->m_pLifeBody;
								while(pReBody)
								{
									// �����ǰ��������Ҫ���Ե���������
									if(pReBody == pEatBody)
									{
										// ���������������������жϿ�
										*pRePrevAddr = pReBody->m_pNextBody;
										// ɱ�����������
										delete pReBody;
										break;
									}
									// ׼��������һ��������
									pRePrevAddr = &pReBody->m_pNextBody;
									pReBody = pReBody->m_pNextBody;
								}
								// ��ִ�е����������Ե�����������Ѿ���������ɾ���ˣ��������������Ҫ�ر��ǡ�
								// 1���������ɾ��������������λ�ڱ��������Ϸ�ʱ,��Ϊ�䱻ɾ���ˣ�pPrevAddrָ����Ծ�
								// ��������Ѿ�ʧЧ��������ĳ�Ա����m_pNextBody��������pPrevAddr������ǰ���������
								// �����о��Բ������*pPrevAddr�����κβ�����
								// 2���������ɾ��������������λ�ڱ��������·�ʱ����Ϊ��ɾ�����Ĺ������Ѿ��Ա�������
								// ��m_pNextBodyָ���Ѿ����˸���(*pRePrevAddr = pReBody->m_pNextBody)��
								// �������Ժ�Ĳ����в��������⣬������һ�������ͬ��

							}
							break;
						
						case CL_MOVE_EAT:
							{
								// ׼���ر���׼���Ե������������ڲݵص�����������
								CLifeBody* pReBody = pEatBody->m_pField->m_pLifeBody;
								// ָ�����ر���������ָ��ĵ�ַ��ָ��
								CLifeBody** pRePrevAddr = &pEatBody->m_pField->m_pLifeBody;
								while(pReBody)
								{
									// �����ǰ��������Ҫ���Ե���������
									if(pReBody == pEatBody)
									{
										// �ѵ�ǰ������ȡ�����Ե���������λ��
										*pRePrevAddr = pBody;
										
										// �ѵ�ǰ������ӵ�ǰ�ݵ�����������ȡ����
										*pPrevAddr = pBody->m_pNextBody;

										// ���±��Ե������������������
										pBody->m_pNextBody = pReBody->m_pNextBody;

										// ���������ڲݵ�
										pBody->m_pField = pReBody->m_pField;

										// ɱ�����Ե���������
										delete pReBody;

										// ��ǰ�������Ѿ��뿪���ݵ�
										// ׼��������һ��������
										goto manual_next;

										break;
									}
									// ׼��������һ��������
									pRePrevAddr = &pReBody->m_pNextBody;
									pReBody = pReBody->m_pNextBody;
								}

							}
							break;
					
						case CL_FULL:
							// ������Ա��ˣ����粻��ҪΪ����ʲô��
							break;
					}

auto_next:
					// ׼��������һ��������
					pPrevAddr = &pBody->m_pNextBody;
manual_next:
					// Ϊ�˴���pBody�Ѿ�ʧЧ��������������嵽��Ĳݵ�ȥ��
					pBody = *pPrevAddr;

				}
			}


	// �������������������������������ֳ
	// for(k = 0; k < WORLD_WIDE; k++)
	for(j = 0; j < WORLD_WIDE; j++)
		for(i = 0; i < WORLD_WIDE; i++)
		{
			// �õ���ǰ�ݵ�ָ��
			CField*		pField = &m_pTheWorld->m_clsField [j][i];

			// ָ��ǰ�������ָ��
			CLifeBody*	pBody = pField->m_pLifeBody;


			// ��ǰ�ݵ�������С����
			CLifeBody* pChildrenBody = NULL;

			// ������ǰ�ݵ��ϵ�����������
			while(pBody)
			{
				// ��������ֳ
				CLifeBody* pChildBody = pBody->Propagate();

				// ���������С���������ǰ�������ʱ�ҵ�����С������
				if(pChildBody)
				{
					// ������С����������С����
					pChildBody->m_pNextBody  = pChildrenBody;

					pChildrenBody = pChildBody;
 
				}
				pBody = pBody->m_pNextBody;
			}

			// ������С�����ҵ���ǰ�ݵ�����������ȥ
			if(pChildrenBody)
			{
				// ԭ��������ָ��
				CLifeBody* pOldBody = pField->m_pLifeBody;
				
				// ����������ָ��
				pField->m_pLifeBody = pChildrenBody;
				
				// �ҵ�����������β
				CLifeBody* pBody = pChildrenBody;
				while(pBody->m_pNextBody)
				{
					pBody = pBody->m_pNextBody;
				}
				
				// ��ԭ���������ҵ�������������β
				pBody->m_pNextBody = pOldBody;
			}
		}


		Render();
	
		goto begin;

	return TRUE;
}

int CWorldThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CWorldThread, CWinThread)
END_MESSAGE_MAP()


// ��ʾ������

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
