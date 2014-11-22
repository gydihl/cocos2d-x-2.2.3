/********************************************************************
	created:	2014/09/28
	filename: 	IconNumberWidget.h
	author:		底会雷
	purpose:	显示图标和数字组合
		图标： 数字
		的组合样式
*********************************************************************/

#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

class IconNumberWidget
	: public cocos2d::ui::Widget
{
public:
	IconNumberWidget();
	virtual ~IconNumberWidget();

public:
	/*
		@purpose:	
		@access:	public static 
		@param:		const char * szIcon () : icon
		@param:		const char * szBk () : 背景图
		@param:		const char * ttf () : 数字的字体
		@return:	IconNumber* 
	*/
	static IconNumberWidget* create(const char *szIcon, const char *szBk, const char *ttf);
	virtual bool init(const char *szIcon, const char *szBk, const char *ttf);

public:
	void setNumber(int nNumber);

protected:
	cocos2d::ui::UIImageView *_pIcon;
	cocos2d::ui::UIImageView *_pBk;
	cocos2d::ui::UILabel *_pNumber;
};
