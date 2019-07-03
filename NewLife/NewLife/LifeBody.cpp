// �����࣬�������塣


#include "StdAfx.h"

#include "condef.h"
#include ".\lifebody.h"


CLifeBody::CLifeBody(void)
:m_hp(0), m_hp_max(0)
{

}


CLifeBody::CLifeBody(const CLifeBody& thosLifeBody)
{
	m_hp = thosLifeBody.m_hp ;
	m_hp_max = thosLifeBody.m_hp_max ;
}

CLifeBody::~CLifeBody(void)
{
}


// ��һ������ĵ�ǰ����ֵ������һ������
CLifeBody& CLifeBody::operator <=(const CLifeBody& thosLifeBody)
{
	//TODO: return statement

	// �����ͬһ�������û�б�Ҫ��ֵ��
	if(&thosLifeBody == this)
		return *this;

	m_hp = thosLifeBody.m_hp ;
	m_hp_max = thosLifeBody.m_hp_max ;

	return *this;

}

// ��һ������ĵ�ǰ�ɱ�ֵ������һ������
CLifeBody& CLifeBody::operator =(const CLifeBody& thosLifeBody)
{
	//TODO: return statement

	// �����ͬһ�������û�б�Ҫ��ֵ��
	if(&thosLifeBody == this)
		return *this;

	m_hp = thosLifeBody.m_hp ;

	return *this;

}


// ��������ʳ
int CLifeBody::LookForFood(CField** ppField, CLifeBody** ppBody)
{

	// �Թ��˻�Ա���
	if(m_hp_max - m_hp <= 0)
	{	
		m_hp = m_hp_max;
		return CL_FULL;
	}
	// �Ա��صĲݣ���������вݳԵĻ�
	if(m_pField->m_nFood > 0)
	{
		// ������زݹ�����
		if(m_pField->m_nFood - (m_hp_max-m_hp) >= 0)
		{
			m_pField->m_nFood -= (m_hp_max-m_hp);
			// �Ա���
			m_hp = m_hp_max;
			return CL_FULL;
		}
		// ���������

		// �ȰѲݳԹ�
		m_hp += m_pField->m_nFood;
		m_pField->m_nFood = 0;
	}

	// ���زݳԹ��ˣ�ȥ��Χ�����вݳ�û�У�׼��ȥ��������һ�������
	
	// �����Χ�вݳԣ���׼��Ǩ���ȥ
	if(*ppField = SearchAroundFood())
	{
		// ������Χ�вݳԣ���׼��Ǩ���ȥ�����ڻ����ڱ��ݵأ�
		// �������硰��ҪǨ�㡱
		return CL_MOVE;
	}

	// �����Χû�вݳ���,�Ϳ�����û�б��ص���������Գ�
	// ����о͸������硰�ҳ���һ�����������塱
	if(SearchLocalBody( ppBody))
		return CL_EAT;

	// �������û�б��ص���������Գԣ��Ϳ�����Χ��û����������Գ�
	// ����о͸������硰�ҳ���һ����Χ�����塱
	if(SearchAroundBody(ppBody))
		return CL_MOVE_EAT;


	// ʲô�ԵĶ�û���ˣ������ҳԲ���:(
	// ������ô�࣬���Ҹ�������������
	int rand_dir =  rand()%4;
	switch(rand_dir)
	{
		case 0:
			*ppField = m_pField->m_pESField;
			return CL_MOVE;
			break;
		case 1:
			*ppField = m_pField->m_pSOField;
			return CL_MOVE;
			break;
		case 2:
			*ppField = m_pField->m_pWEField;
			return CL_MOVE;
			break;
		case 3:
			*ppField = m_pField->m_pNOField;
			return CL_MOVE;
			break;
	}

	// ����ִ�е������
	return CL_FULL;
}


// Ѱ����Χ�Ĳݳԣ�����еĻ����ҵ��м�Ĳ����Ĳݵأ���׼��Ǩ���ȥ
CField* CLifeBody::SearchAroundFood(void)
{

	CField* pGoodField = NULL;
	int nMaxFood = 0;
	int nDir;
	//int nDirUse[4] = {0, 0, 0, 0};

	nDir = rand()%4;

	
	switch(nDir)
	{
	case 0:
		// ���Ҷ���
		if(m_pField->m_pESField->m_nFood > nMaxFood)
		{
			pGoodField = m_pField->m_pESField;
			nMaxFood = pGoodField->m_nFood;
		}
		break;

	case 1:
		// �����ϱ�
		if(m_pField->m_pSOField->m_nFood > nMaxFood)
		{
			pGoodField = m_pField->m_pSOField;
			nMaxFood = pGoodField->m_nFood;
		}
		break;

	case 2:
		// ��������
		if(m_pField->m_pWEField->m_nFood > nMaxFood)
		{
			pGoodField = m_pField->m_pWEField;
			nMaxFood = pGoodField->m_nFood;
		}
		break;

	case 3:
		// ����ұ���
		if(m_pField->m_pNOField->m_nFood > nMaxFood)
		{
			pGoodField = m_pField->m_pNOField;
			nMaxFood = pGoodField->m_nFood;
		}
		break;
	}
	// ���pGoodFieldΪ��Ļ����Ǿ�����ΧҲû�в���
	// ���pGoodField��Ϊ��Ļ�����һ���вݳ��˶����ǲ�����
	return pGoodField;	

}

// Ѱ�ұ���������ԣ�����еĳԵĻ����ͳԵ���
BOOL CLifeBody::SearchLocalBody(CLifeBody** ppBody)
{
	// ���ݵصĵ�һ��������ָ��
	CLifeBody* pBody = 	m_pField->m_pLifeBody;
	*ppBody = NULL;

	while(pBody){
		// �������Լ�
		if(pBody == this)
		{
			pBody = pBody->m_pNextBody;
			break;
		}
		
		// �Է����������ֵ������
		if(pBody->m_hp_max < m_hp_max)
		{
			// ��������ҵ����������ֵ���Լ�С��������
			if(*ppBody != NULL)
			{
				// ����ʵĳ�
				if((*ppBody)->m_hp_max < pBody->m_hp_max)
					*ppBody = pBody;
			}
			else // ���ǵ�һ���ҵ��Ŀ��ԳԵ�������
			{
				*ppBody = pBody;
			}
		}
		pBody = pBody->m_pNextBody;
	}
	
	// �ҵ��Ե���
	if(*ppBody != NULL)
	{
		// ���ҵ���������Ե��������绹��֪�������Ե��ˣ�
		EatLifeBody(*ppBody);
		return TRUE;
	}
	return FALSE;
}

// �Ե�һ�����������������ֵ
void CLifeBody::EatLifeBody(CLifeBody* pBody)
{
	// ��Ȼ�����Ե��ˣ���ֻ������һ���İٷֱ�
	m_hp += ((pBody->m_hp * GET_HP_PER)/100 );

	// ���ܰ��Լ��Գ�
	if(m_hp > m_hp_max)
		m_hp = m_hp_max;
}

// Ѱ����Χ��������ԣ�����еĳԵĻ����ͳԵ���
BOOL CLifeBody::SearchAroundBody(CLifeBody** ppBody)
{
	CLifeBody* pBody = 	NULL;
		
	*ppBody = NULL;

	int dir = rand()%4;
	

	switch(dir)
	{
	case 0:
		// ���߲ݵصĵ�һ��������ָ��
		pBody = m_pField->m_pESField->m_pLifeBody;

		while(pBody){
			// �Է����������ֵ������
			if(pBody->m_hp_max < m_hp_max)
			{
				// ��������ҵ����������ֵ���Լ�С��������
				if(*ppBody != NULL)
				{
					// ����ʵĳ�
					if((*ppBody)->m_hp_max < pBody->m_hp_max)
						*ppBody = pBody;
				}
				else // ���ǵ�һ���ҵ��Ŀ��ԳԵ�������
				{
					*ppBody = pBody;
				}
			}
			pBody = pBody->m_pNextBody;
		}
		break;
	
	case 1:
		// �ϱ߲ݵصĵ�һ��������ָ��
		pBody = 	m_pField->m_pSOField->m_pLifeBody;
		while(pBody){
			// �Է����������ֵ������
			if(pBody->m_hp_max < m_hp_max)
			{
				// ��������ҵ����������ֵ���Լ�С��������
				if(*ppBody != NULL)
				{
					// ����ʵĳ�
					if((*ppBody)->m_hp_max < pBody->m_hp_max)
						*ppBody = pBody;
				}
				else // ���ǵ�һ���ҵ��Ŀ��ԳԵ�������
				{
					*ppBody = pBody;
				}
			}
			pBody = pBody->m_pNextBody;
		}
		break;

	case 2:
		// ���߲ݵصĵ�һ��������ָ��
		pBody = 	m_pField->m_pWEField->m_pLifeBody;
		while(pBody){
			// �Է����������ֵ������
			if(pBody->m_hp_max < m_hp_max)
			{
				// ��������ҵ����������ֵ���Լ�С��������
				if(*ppBody != NULL)
				{
					// ����ʵĳ�
					if((*ppBody)->m_hp_max < pBody->m_hp_max)
						*ppBody = pBody;
				}
				else // ���ǵ�һ���ҵ��Ŀ��ԳԵ�������
				{
					*ppBody = pBody;
				}
			}
			pBody = pBody->m_pNextBody;
		}
		break;

	case 3:
		// ���߲ݵصĵ�һ��������ָ��
		pBody = 	m_pField->m_pNOField->m_pLifeBody;
		while(pBody){
			// �Է����������ֵ������
			if(pBody->m_hp_max < m_hp_max)
			{
				// ��������ҵ����������ֵ���Լ�С��������
				if(*ppBody != NULL)
				{
					// ����ʵĳ�
					if((*ppBody)->m_hp_max < pBody->m_hp_max)
						*ppBody = pBody;
				}
				else // ���ǵ�һ���ҵ��Ŀ��ԳԵ�������
				{
					*ppBody = pBody;
				}
			}
			pBody = pBody->m_pNextBody;
		}
		break;
	}
	// �ҵ��Ե���
	if(*ppBody != NULL)
	{
		// ���ҵ���������Ե��������绹��֪�������Ե��ˣ�
		EatLifeBody(*ppBody);
		return TRUE;
	}

	// �Ҳ����Ե�
	return FALSE;
}

// ����С��
CLifeBody* CLifeBody::Propagate(void)
{
	CLifeBody* pChild = NULL;
	
	// ���û����ֳ����
	if(m_age < (m_age_max*PROPAGATE_AGE)/100)
		return pChild;

	// �����������ֳ�������Բ�����
	if(m_hp < (m_hp_max*DEAD_LINE*2)/100)
		return pChild;

	// �������������ϣ�������һ��С��
	pChild = new CLifeBody();
	if(pChild == NULL)
		MessageBox(NULL, "����������ʧ�ܣ�", "û�ռ���", 0);

	pChild->m_age = 0;
	pChild->m_hp = m_hp/2;
	// ���ڵ�ǰ�ݵ���
	pChild->m_pField = m_pField;
	// ���굱Ȼһ��
	pChild->m_x = m_x;
	pChild->m_y = m_y;
	pChild->m_z = m_z;
	
	// ��ǧ��֮һ�Ļ��ᷢ������
	pChild->m_age_max = (rand()%AGE_CHANGE_PRE == 1)?
				(  AGE_MAX * rand()/ RAND_MAX ):m_age_max;
//	pChild->m_age_max = (( AGE_CHANGE_PRE * rand())/RAND_MAX == 187)?
//				(  AGE_MAX * rand()/ RAND_MAX ):m_age_max;
	// ��ǧ��֮һ�Ļ��ᷢ������
//	pChild->m_hp_max = ((HP_CHANGE_PER * rand())/RAND_MAX == 249)?
//				(  HP_MAX * rand()/ RAND_MAX ):m_hp_max;
	pChild->m_hp_max = (rand()%HP_CHANGE_PER == 1)?
				(  HP_MAX * rand()/ RAND_MAX ):m_hp_max;

	// ��֤�����С��������
	if (pChild->m_hp_max < pChild->m_hp)
		pChild->m_hp = pChild->m_hp_max;
	
	// ��������Ҫ��һ�������ֵ���Է�
	m_hp /= 2;

	return pChild;
}
