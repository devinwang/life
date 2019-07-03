// 生命类，生命个体。

#pragma once

#include "Field.h"

class CField;
class CLifeBody
{
public:
	CLifeBody(void);
	CLifeBody(const CLifeBody& thosLifeBody);
	~CLifeBody(void);


protected:

public:
	// 生命值(包括吃掉其它生命的能力)
	int m_hp;

	// 年龄
	int m_age;

	// 生命值最大值
	int m_hp_max;

	// 年龄最大值
	int m_age_max;

	// 生命体在世界中的位置
	int m_x, m_y, m_z;

	// 把一生命体的当前所有值赋给另一生命体
	CLifeBody& operator <=(const CLifeBody& thosLifeBody);
	// 把一生命体的当前可变值赋给另一生命体
	CLifeBody& operator =(const CLifeBody& thosLifeBody);

	// 指向位于同一草地的下一个生命体
	CLifeBody*	m_pNextBody;

	// 当前生命体所在草地
	CField*		m_pField;


	// // 生命体觅食
	int LookForFood(CField** ppField, CLifeBody** ppBody);

	// 寻找周围的草最多的草地
	CField* SearchAroundFood(void);

	// 找本地的生命体吃
	BOOL SearchLocalBody(CLifeBody** ppBody);

	// 寻找周围的生命体吃
	BOOL SearchAroundBody(CLifeBody** ppBody);

	// 吃掉一个生命体的所有生命值
	void EatLifeBody(CLifeBody* pBody);
	// // 生育小孩
	CLifeBody* Propagate(void);
};
