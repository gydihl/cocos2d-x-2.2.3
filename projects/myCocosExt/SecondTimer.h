/********************************************************************
	created:	2014/09/12
	filename: 	SecondTimer.h
	author:		底会雷
	purpose:	按照秒计时，保存运行时间
*********************************************************************/

#pragma once

#include "cocos2d.h"

class ISecondTimerDelegate
{
public:
	// 更新时间的回调
	virtual void updateSecondTimer(float fTime) = 0;
};

class SecondTimer
	: public cocos2d::CCNode
{
public:
	CREATE_FUNC(SecondTimer);
	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

protected:
	void calcTimer(float delta);

protected:
	CC_SYNTHESIZE_READONLY(float, _fRunTime, RunTime);
	CC_SYNTHESIZE(ISecondTimerDelegate*, _pDelegate, Delegate);
};
