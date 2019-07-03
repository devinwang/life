#include "StdAfx.h"
#include ".\field.h"

CField::CField(void)
: m_nFood(FIELD_FOOD_MAX/2), m_pLifeBody(NULL)
{
	// 每一块草地产生时都有充足的食物
}

CField::~CField(void)
{
}
