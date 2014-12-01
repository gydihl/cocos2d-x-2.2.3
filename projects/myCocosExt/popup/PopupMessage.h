/********************************************************************
	created:	2014/11/09
	filename: 	PopupMessage.h
	author:		dihl
	purpose:	popup message
*********************************************************************/

#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PopupLayer.h"

class PopupMessage
	: // public cocos2d::CCLayer
	public PopupLayer
{
	typedef PopupLayer	SupperPopupMessage;
public:
	PopupMessage();
	virtual ~PopupMessage();

public:
	CREATE_FUNC(PopupMessage);
	static PopupMessage* create(const char *szBackgroundImg);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

// 	virtual void registerWithTouchDispatcher();
// 
// 	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

public:
	void setTitle(const char *szTitle, int nFontSize = 20);
	void setContentText(const char *szText, int nFontSize = 20, 
		int nPadding = 50, int nPaddingTop = 100);

	void setCallbackFunc(cocos2d::CCObject *pTarget, cocos2d::SEL_CallFuncN callFunc);

	bool addButton(const char *normalImg, const char *selectedImg, const char *title, int tag = 0);

protected:
	void buttonCallback(cocos2d::CCObject *pSender);

protected:
	CC_SYNTHESIZE_PASS_BY_REF(std::string, _strBackgroundImg, BackgroundImg);

	CC_SYNTHESIZE_RETAIN(cocos2d::CCLabelTTF*, _pLabelTitle, LabelTitle);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCLabelTTF*, _pLabelContentText, LabelContentText);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCMenu*, _pMenu, MenuButton);
	CC_SYNTHESIZE(int, _nContentPadding, ContentPadding);
	CC_SYNTHESIZE(int, _nContentPaddingTop, ContentPaddingTop);

protected:
	cocos2d::CCObject *_pCallbackListener;
	cocos2d::SEL_CallFuncN _callFunc;
};

