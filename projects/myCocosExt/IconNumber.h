/********************************************************************
	created:	2014/09/28
	filename: 	IconNumber.h
	author:		底会雷
	purpose:	显示图标和数字组合
		图标： 数字
		的组合样式
*********************************************************************/

#pragma once

#include "cocos2d.h"

class IconNumber
	: public cocos2d::CCNode
{
public:
	IconNumber();
	virtual ~IconNumber();

public:
	/*
		@purpose:	
		@access:	public static 
		@param:		const char * szIcon () : icon
		@param:		const char * szBk () : 背景图
		@param:		const char * ttf () : 数字的字体
		@return:	IconNumber* 
	*/
	static IconNumber* create(const char *szIcon, const char *szBk, const char *ttf);
	virtual bool init(const char *szIcon, const char *szBk, const char *ttf);

public:
	void setNumber(int nNumber);

protected:
	cocos2d::CCSprite *_pIcon;
	cocos2d::CCSprite *_pBk;
	cocos2d::CCLabelTTF *_pNumber;
};
