/********************************************************************
	created:	2014/11/09
	filename: 	PopupTest.h
	author:		dihl
	purpose:	popup page test
*********************************************************************/

#pragma once

#include "PopupLayer.h"
#include "PopupMessage.h"
#include "PopupTouchGroup.h"

class TestPopupLayer
	: public PopupLayer
{
public:
	CREATE_FUNC(TestPopupLayer);

	virtual bool init();

protected:
	void onTestTouch(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType eventType);
};

class TestPopupTouchGroup
	: public PopupTouchGroup
{
public:
	CREATE_FUNC(TestPopupTouchGroup);

	virtual bool init();

protected:
	void onTestTouch(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType eventType);
};

class TestPopupMessage
	: public PopupMessage
{
public:
	CREATE_FUNC(TestPopupMessage);

	virtual bool init();

protected:
	void buttonCallback(cocos2d::CCNode* pSender);
};
