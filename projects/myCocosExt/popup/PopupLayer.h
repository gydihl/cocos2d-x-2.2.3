/********************************************************************
	created:	2014/11/06
	filename: 	PopupLayer.h
	author:		dihl
	purpose:	popup layer
*********************************************************************/

#pragma once

#include "cocos2d.h"

class PopupLayer
	: public cocos2d::CCLayer
{
	typedef cocos2d::CCLayer	SupperPopupLayer;

public:
	CREATE_FUNC(PopupLayer);

	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};
