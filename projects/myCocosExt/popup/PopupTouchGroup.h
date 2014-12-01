/********************************************************************
	created:	2014/11/06
	filename: 	PopupTouchGroup.h
	author:		dihl
	purpose:	popup touch group layer
*********************************************************************/

#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

class PopupTouchGroup
	: public cocos2d::ui::TouchGroup
{
	typedef cocos2d::ui::TouchGroup		SupperPopupTouchGroup;

public:
	CREATE_FUNC(PopupTouchGroup);

	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};
