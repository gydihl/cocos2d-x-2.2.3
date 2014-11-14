/********************************************************************
	created:	2014/08/18
	filename: 	IndicateLamp.h
	author:		底会雷
	purpose:	简单指示选择器
*********************************************************************/

#pragma once

#include "cocos2d.h"

class IndicateLamp
	: public cocos2d::CCNode
{
public:
	virtual ~IndicateLamp();

public:
	static IndicateLamp* create(int nCount);
	virtual bool init(int nCount);
	virtual void onExit();

public:
	bool select(int nIndex);

protected:
	cocos2d::CCArray *_pAryLamp;
	cocos2d::CCSprite *_pLightLamep;
};
