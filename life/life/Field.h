#pragma once

#include "LifeBody.h"

class CLifeBody;
class CField
{
public:
	CField(void);
	~CField(void);
	// ���ݵص�ʳ��ֵ
	int m_nFood;
	// �ڵ�ǰ���ݵ������������
	CLifeBody* m_pLifeBody;

	// ���ݵص����ܲݵ�ָ��
	CField* m_pESField, *m_pSOField, *m_pWEField, *m_pNOField;
};
