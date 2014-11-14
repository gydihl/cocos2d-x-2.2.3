#include "SecondTimer.h"

USING_NS_CC;

bool SecondTimer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCNode::init());

		this->_fRunTime = 0.0f;
		this->_pDelegate = NULL;

		bRet = true;
	} while (0);
	return bRet;
}

void SecondTimer::onEnter()
{
	// 计算运行时间
	this->schedule(schedule_selector(SecondTimer::calcTimer), 1.0f);
	CCNode::onEnter();
}

void SecondTimer::onExit()
{
	this->unschedule(schedule_selector(SecondTimer::calcTimer));
	CCNode::onExit();
}

void SecondTimer::calcTimer(float delta)
{
	_fRunTime += delta;
	if (getDelegate())
		getDelegate()->updateSecondTimer(_fRunTime);
}
