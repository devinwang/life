#pragma once

#include "LifeBody.h"

class CLifeBody;
class CField
{
public:
	CField(void);
	~CField(void);
	// 本草地的食物值
	int m_nFood;
	// 在当前这块草地生活的生命体
	CLifeBody* m_pLifeBody;

	// 这块草地的四周草地指针
	CField* m_pESField, *m_pSOField, *m_pWEField, *m_pNOField;
};
