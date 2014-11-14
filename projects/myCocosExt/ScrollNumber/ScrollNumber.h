/********************************************************************
	created:	2014/07/29
	filename: 	ScrollNumberLayer.h
	author:		底会雷
	purpose:	滚动数字
*********************************************************************/

#pragma once

#include "cocos2d.h"

typedef enum {
	ZCWScrollNumAnimationTypeNone,
	ZCWScrollNumAnimationTypeNormal,
	ZCWScrollNumAnimationTypeFromLast,
	ZCWScrollNumAnimationTypeRand,
	ZCWScrollNumAnimationTypeFast
} ZCWScrollNumAnimationType;

enum eScrollNumberActionType
{
	kScrollNumberActionNone,		// 没有切换效果，直接显示结果
	kScrollNumberActionNormal,		// 从0滚动到目标数字
	kScrollNumberActionFromLast,	// 当前数字滚动到目标数字
	// 下面两个暂时没有实现
	kScrollNumberActionRand,
	kScrollNumberActionFast,		// 快速切换
};

class ScrollNumber
	: public cocos2d::CCNode
{
public:
	static ScrollNumber* create(int nFigureCount, int nNumber = 0);
	virtual bool init(int nFigureCount, int nNumber = 0);

public:
	void setNumber(int nNumber, eScrollNumberActionType type = kScrollNumberActionNone, float fDelta = 0.0f);

protected:
	/*
		@purpose:	添加一个标签
		@access:	protected 
		@return:	void 
	*/
	void addFigureLabel();
	void getNumAtPos(int pos);

protected:
	CC_SYNTHESIZE_READONLY(int, _nNumber, Number);

protected:
	// 最大表示的位数
	CC_SYNTHESIZE(int, _nFigureCount, FigureCount);
	CC_SYNTHESIZE(int, _nMaxNumber, MaxNumber);
// public:
// 	static GoldCounterLayer* create(int number = 0);
// 	bool init(int number = 0);
// 	void setNumber(int number,int ceiling = 999999);
// 	CC_SYNTHESIZE_READONLY(int, _number, Number);
// protected:
// 	void getNumAtPos(int pos);
};

