
// һЩ�����ļ�����

#pragma once

// ���籾�������

// ����Ĵ�С
// ��������һ��WORLD_WIDE*WORLD_WIDE��ɵ�ƽ��FIELD
#define	WORLD_WIDE		200

// ÿ��ݵص����ʳ��ֵ
#define	FIELD_FOOD_MAX		50

// ����ÿ��ʹÿ��ݵز�����ʳ��ֵ
#define FIELD_FOOD_INC		10


// ������������һЩ����

// �����己ֳ�������ֵ(���һ��������������)
#define PROPAGATE_ABILITY_MAX	10
// �����己ֳ����
#define PROPAGATE_AGE			30 // 30%

// һ������ÿ�����ĵ�����ֵ�������������ֵ�ı�ֵ
#define DEC_HP_PER		10 // 10%

// ������������ֵ�ﵽ����������İٷ�֮����ʱ����ȥ
#define DEAD_LINE		10 // 10%

// һ������Ե���һ������ʱ�ɻ�öԷ��ٷ�֮��������ֵ
#define GET_HP_PER		30 // 30%

#define	HP_MAX			200

// ������ֵ�ﵽ�������ֵ����ʱ�����޷��Բݣ������ʳ�����壩
//#define HP_MA

#define	AGE_MAX			50

// ΢����ĳ�ʼֵ
#define CELL_HP						10
#define CELL_AGE					5
#define CELL_PROPAGATE_ABILITY_MAX	1

// CLifeBody::LookForFood  ����ֵ����
#define CL_FULL		0	// �Ա���
#define CL_MOVE		1	// Ǩ�㵽��Χ
#define CL_EAT		2	// �Ե�����������
#define CL_MOVE_EAT	3	// �Ե���Χ������
