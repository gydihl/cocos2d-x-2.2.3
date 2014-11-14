/********************************************************************
	created:	2014/09/17
	filename: 	CoolingNode.h
	author:		底会雷
	purpose:	技能冷却按钮
*********************************************************************/

#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

class CoolingNode
	: public cocos2d::CCNode
	, public cocos2d::CCTouchDelegate
{
public:
	CoolingNode();
	virtual ~CoolingNode();

public:
	static CoolingNode* create(float fCD, const char *szImageName, const char *szCoolingName);
	virtual bool init(float fCD, const char *szImageName, const char *szCoolingName);

	virtual void onEnter();
	virtual void onExit();

	virtual void registerWithTouchDispatcher(void);

	virtual bool isTouchEnabled();
	virtual void setTouchEnabled(bool value);

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	// optional
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);


public:
	void addTouchEventListener(cocos2d::CCObject* target, cocos2d::ui::SEL_TouchEvent selector);

protected:
	void allowTouch();

protected:
	CC_SYNTHESIZE(float, _fCD, CD);		// 冷却时间
	CC_SYNTHESIZE(cocos2d::CCSprite*, _pTouchNode, TouchNode);
	CC_SYNTHESIZE(cocos2d::CCSprite*, _pCover, Cover);
	CC_SYNTHESIZE(cocos2d::CCProgressTimer*, _pProgressTimer, ProgressTimer);
	CC_SYNTHESIZE(cocos2d::CCFiniteTimeAction*, _pAction, Action);

protected:
	cocos2d::CCObject*       _touchEventListener;
	cocos2d::ui::SEL_TouchEvent    _touchEventSelector;

	bool _bTouchEnabled;		// 是否允许触摸
};

