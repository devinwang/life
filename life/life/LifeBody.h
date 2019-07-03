// �����࣬�������塣

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
	// ����ֵ(�����Ե���������������)
	int m_hp;

	// ����
	int m_age;

	// ����ֵ���ֵ
	int m_hp_max;

	// �������ֵ
	int m_age_max;

	// �������������е�λ��
	int m_x, m_y, m_z;

	// ��һ������ĵ�ǰ����ֵ������һ������
	CLifeBody& operator <=(const CLifeBody& thosLifeBody);
	// ��һ������ĵ�ǰ�ɱ�ֵ������һ������
	CLifeBody& operator =(const CLifeBody& thosLifeBody);

	// ָ��λ��ͬһ�ݵص���һ��������
	CLifeBody*	m_pNextBody;

	// ��ǰ���������ڲݵ�
	CField*		m_pField;


	// // ��������ʳ
	int LookForFood(CField** ppField, CLifeBody** ppBody);

	// Ѱ����Χ�Ĳ����Ĳݵ�
	CField* SearchAroundFood(void);

	// �ұ��ص��������
	BOOL SearchLocalBody(CLifeBody** ppBody);

	// Ѱ����Χ���������
	BOOL SearchAroundBody(CLifeBody** ppBody);

	// �Ե�һ�����������������ֵ
	void EatLifeBody(CLifeBody* pBody);
	// // ����С��
	CLifeBody* Propagate(void);
};
