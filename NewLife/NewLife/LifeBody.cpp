// 生命类，生命个体。


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


// 把一生命体的当前所有值赋给另一生命体
CLifeBody& CLifeBody::operator <=(const CLifeBody& thosLifeBody)
{
	//TODO: return statement

	// 如果是同一生命体就没有必要赋值了
	if(&thosLifeBody == this)
		return *this;

	m_hp = thosLifeBody.m_hp ;
	m_hp_max = thosLifeBody.m_hp_max ;

	return *this;

}

// 把一生命体的当前可变值赋给另一生命体
CLifeBody& CLifeBody::operator =(const CLifeBody& thosLifeBody)
{
	//TODO: return statement

	// 如果是同一生命体就没有必要赋值了
	if(&thosLifeBody == this)
		return *this;

	m_hp = thosLifeBody.m_hp ;

	return *this;

}


// 生命体觅食
int CLifeBody::LookForFood(CField** ppField, CLifeBody** ppBody)
{

	// 吃过了或吃饱了
	if(m_hp_max - m_hp <= 0)
	{	
		m_hp = m_hp_max;
		return CL_FULL;
	}
	// 吃本地的草，如果本地有草吃的话
	if(m_pField->m_nFood > 0)
	{
		// 如果本地草够吃了
		if(m_pField->m_nFood - (m_hp_max-m_hp) >= 0)
		{
			m_pField->m_nFood -= (m_hp_max-m_hp);
			// 吃饱了
			m_hp = m_hp_max;
			return CL_FULL;
		}
		// 如果不够吃

		// 先把草吃光
		m_hp += m_pField->m_nFood;
		m_pField->m_nFood = 0;
	}

	// 本地草吃光了，去周围看看有草吃没有，准备去草最多的那一个方向吃
	
	// 如果周围有草吃，就准备迁徙过去
	if(*ppField = SearchAroundFood())
	{
		// 发现周围有草吃，并准备迁徙过去（现在还属于本草地）
		// 告诉世界“我要迁徙”
		return CL_MOVE;
	}

	// 如果周围没有草吃了,就看看有没有本地的生命体可以吃
	// 如果有就告诉世界“我吃了一个本地生命体”
	if(SearchLocalBody( ppBody))
		return CL_EAT;

	// 如果本地没有本地的生命体可以吃，就看看周围有没有生命体可以吃
	// 如果有就告诉世界“我吃了一个周围生命体”
	if(SearchAroundBody(ppBody))
		return CL_MOVE_EAT;


	// 什么吃的都没有了，或者我吃不了:(
	// 不管那么多，乱找个方向碰碰运气
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

	// 不会执行到这里的
	return CL_FULL;
}


// 寻找周围的草吃，如果有的话，找到中间的草最多的草地，以准备迁徙过去
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
		// 先找东边
		if(m_pField->m_pESField->m_nFood > nMaxFood)
		{
			pGoodField = m_pField->m_pESField;
			nMaxFood = pGoodField->m_nFood;
		}
		break;

	case 1:
		// 再找南边
		if(m_pField->m_pSOField->m_nFood > nMaxFood)
		{
			pGoodField = m_pField->m_pSOField;
			nMaxFood = pGoodField->m_nFood;
		}
		break;

	case 2:
		// 再找西边
		if(m_pField->m_pWEField->m_nFood > nMaxFood)
		{
			pGoodField = m_pField->m_pWEField;
			nMaxFood = pGoodField->m_nFood;
		}
		break;

	case 3:
		// 最后找北面
		if(m_pField->m_pNOField->m_nFood > nMaxFood)
		{
			pGoodField = m_pField->m_pNOField;
			nMaxFood = pGoodField->m_nFood;
		}
		break;
	}
	// 如果pGoodField为零的话，那就是周围也没有草了
	// 如果pGoodField不为零的话，那一定有草吃了而且是草最多的
	return pGoodField;	

}

// 寻找本地生命体吃，如果有的吃的话，就吃掉它
BOOL CLifeBody::SearchLocalBody(CLifeBody** ppBody)
{
	// 本草地的第一个生命体指针
	CLifeBody* pBody = 	m_pField->m_pLifeBody;
	*ppBody = NULL;

	while(pBody){
		// 不能是自己
		if(pBody == this)
		{
			pBody = pBody->m_pNextBody;
			break;
		}
		
		// 对方的最大生命值低于我
		if(pBody->m_hp_max < m_hp_max)
		{
			// 如果曾经找到过最大生命值比自己小的生命体
			if(*ppBody != NULL)
			{
				// 找最肥的吃
				if((*ppBody)->m_hp_max < pBody->m_hp_max)
					*ppBody = pBody;
			}
			else // 这是第一个找到的可以吃的生命体
			{
				*ppBody = pBody;
			}
		}
		pBody = pBody->m_pNextBody;
	}
	
	// 找到吃的了
	if(*ppBody != NULL)
	{
		// 把找到的生命体吃掉（但世界还不知道它被吃掉了）
		EatLifeBody(*ppBody);
		return TRUE;
	}
	return FALSE;
}

// 吃掉一个生命体的所有生命值
void CLifeBody::EatLifeBody(CLifeBody* pBody)
{
	// 虽然整个吃掉了，但只能吸收一定的百分比
	m_hp += ((pBody->m_hp * GET_HP_PER)/100 );

	// 不能把自己吃撑
	if(m_hp > m_hp_max)
		m_hp = m_hp_max;
}

// 寻找周围的生命体吃，如果有的吃的话，就吃掉它
BOOL CLifeBody::SearchAroundBody(CLifeBody** ppBody)
{
	CLifeBody* pBody = 	NULL;
		
	*ppBody = NULL;

	int dir = rand()%4;
	

	switch(dir)
	{
	case 0:
		// 东边草地的第一个生命体指针
		pBody = m_pField->m_pESField->m_pLifeBody;

		while(pBody){
			// 对方的最大生命值低于我
			if(pBody->m_hp_max < m_hp_max)
			{
				// 如果曾经找到过最大生命值比自己小的生命体
				if(*ppBody != NULL)
				{
					// 找最肥的吃
					if((*ppBody)->m_hp_max < pBody->m_hp_max)
						*ppBody = pBody;
				}
				else // 这是第一个找到的可以吃的生命体
				{
					*ppBody = pBody;
				}
			}
			pBody = pBody->m_pNextBody;
		}
		break;
	
	case 1:
		// 南边草地的第一个生命体指针
		pBody = 	m_pField->m_pSOField->m_pLifeBody;
		while(pBody){
			// 对方的最大生命值低于我
			if(pBody->m_hp_max < m_hp_max)
			{
				// 如果曾经找到过最大生命值比自己小的生命体
				if(*ppBody != NULL)
				{
					// 找最肥的吃
					if((*ppBody)->m_hp_max < pBody->m_hp_max)
						*ppBody = pBody;
				}
				else // 这是第一个找到的可以吃的生命体
				{
					*ppBody = pBody;
				}
			}
			pBody = pBody->m_pNextBody;
		}
		break;

	case 2:
		// 西边草地的第一个生命体指针
		pBody = 	m_pField->m_pWEField->m_pLifeBody;
		while(pBody){
			// 对方的最大生命值低于我
			if(pBody->m_hp_max < m_hp_max)
			{
				// 如果曾经找到过最大生命值比自己小的生命体
				if(*ppBody != NULL)
				{
					// 找最肥的吃
					if((*ppBody)->m_hp_max < pBody->m_hp_max)
						*ppBody = pBody;
				}
				else // 这是第一个找到的可以吃的生命体
				{
					*ppBody = pBody;
				}
			}
			pBody = pBody->m_pNextBody;
		}
		break;

	case 3:
		// 北边草地的第一个生命体指针
		pBody = 	m_pField->m_pNOField->m_pLifeBody;
		while(pBody){
			// 对方的最大生命值低于我
			if(pBody->m_hp_max < m_hp_max)
			{
				// 如果曾经找到过最大生命值比自己小的生命体
				if(*ppBody != NULL)
				{
					// 找最肥的吃
					if((*ppBody)->m_hp_max < pBody->m_hp_max)
						*ppBody = pBody;
				}
				else // 这是第一个找到的可以吃的生命体
				{
					*ppBody = pBody;
				}
			}
			pBody = pBody->m_pNextBody;
		}
		break;
	}
	// 找到吃的了
	if(*ppBody != NULL)
	{
		// 把找到的生命体吃掉（但世界还不知道它被吃掉了）
		EatLifeBody(*ppBody);
		return TRUE;
	}

	// 找不到吃的
	return FALSE;
}

// 生育小孩
CLifeBody* CLifeBody::Propagate(void)
{
	CLifeBody* pChild = NULL;
	
	// 如果没到生殖年龄
	if(m_age < (m_age_max*PROPAGATE_AGE)/100)
		return pChild;

	// 如果不符合生殖条件（吃不饱）
	if(m_hp < (m_hp_max*DEAD_LINE*2)/100)
		return pChild;

	// 所有条件都符合，可以生一个小孩
	pChild = new CLifeBody();
	if(pChild == NULL)
		MessageBox(NULL, "新生生命体失败！", "没空间了", 0);

	pChild->m_age = 0;
	pChild->m_hp = m_hp/2;
	// 生在当前草地上
	pChild->m_pField = m_pField;
	// 坐标当然一样
	pChild->m_x = m_x;
	pChild->m_y = m_y;
	pChild->m_z = m_z;
	
	// 有千分之一的机会发生变异
	pChild->m_age_max = (rand()%AGE_CHANGE_PRE == 1)?
				(  AGE_MAX * rand()/ RAND_MAX ):m_age_max;
//	pChild->m_age_max = (( AGE_CHANGE_PRE * rand())/RAND_MAX == 187)?
//				(  AGE_MAX * rand()/ RAND_MAX ):m_age_max;
	// 有千分之一的机会发生变异
//	pChild->m_hp_max = ((HP_CHANGE_PER * rand())/RAND_MAX == 249)?
//				(  HP_MAX * rand()/ RAND_MAX ):m_hp_max;
	pChild->m_hp_max = (rand()%HP_CHANGE_PER == 1)?
				(  HP_MAX * rand()/ RAND_MAX ):m_hp_max;

	// 保证不会把小宝宝撑死
	if (pChild->m_hp_max < pChild->m_hp)
		pChild->m_hp = pChild->m_hp_max;
	
	// 本生命体要分一半的生命值给对方
	m_hp /= 2;

	return pChild;
}
