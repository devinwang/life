
// 一些常量文件定义

#pragma once

// 世界本身的限制

// 世界的大小
// 世界是由一个WORLD_WIDE*WORLD_WIDE组成的平面FIELD
#define	WORLD_WIDE		200

// 每块草地的最大食物值
#define	FIELD_FOOD_MAX		50

// 阳光每年使每块草地产生的食物值
#define FIELD_FOOD_INC		10


// 世界对生命体的一些限制

// 生命体繁殖能力最大值(最大一次能生几个儿子)
#define PROPAGATE_ABILITY_MAX	10
// 生命体繁殖年龄
#define PROPAGATE_AGE			30 // 30%

// 一生命体每年消耗的生命值比上其最大生命值的比值
#define DEC_HP_PER		10 // 10%

// 当生命体生命值达到其最大生命的百分之多少时会死去
#define DEAD_LINE		10 // 10%

// 一生命体吃掉另一生命体时可获得对方百分之多少生命值
#define GET_HP_PER		30 // 30%

#define	HP_MAX			200

// 当生命值达到最大生命值多少时，将无法吃草（变成肉食生命体）
//#define HP_MA

#define	AGE_MAX			50

// 微生物的初始值
#define CELL_HP						10
#define CELL_AGE					5
#define CELL_PROPAGATE_ABILITY_MAX	1

// CLifeBody::LookForFood  返回值定义
#define CL_FULL		0	// 吃饱了
#define CL_MOVE		1	// 迁徙到周围
#define CL_EAT		2	// 吃掉本地生命体
#define CL_MOVE_EAT	3	// 吃掉周围生命体
