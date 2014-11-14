/********************************************************************
	created:	2014/09/18
	filename: 	ButtonDigit.h
	author:		底会雷
	purpose:	右上角带数字的按钮
		初始化顺序
			initButton()
			initImageDigit()
			initLabelDigit()
*********************************************************************/

#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

class ButtonDigit
	: public cocos2d::ui::UIButton
{
public:
	static ButtonDigit* create();
	virtual bool init();

public:
	//////////////////////////////////////////////////////////////////////////
	// 初始化函数
	virtual void initButton(const char* normal,const char* selected,const char* disabled, float fBtnFrame = 0.0f);
	virtual void initImageDigit(const char* fileName, float fImageFrame = 0.0f);
	// 设置文本fnt文件
	virtual void initLabelDigitFnt(const char* fileName);
	// 设置文本颜色
	virtual void setLabelColor(const cocos2d::ccColor3B& color);

	//////////////////////////////////////////////////////////////////////////
	// 数字操作
	virtual void setDigit(int nDigit);
protected:
	// 设置_pImageDigit位置
	virtual void setImagePosition();

protected:
	CC_SYNTHESIZE(cocos2d::ui::UIImageView*, _pImageDigit, ImageDigit);
	CC_SYNTHESIZE(cocos2d::ui::UILabelBMFont*, _pLabelDigit, LabelDigit);

	CC_SYNTHESIZE(float, _fBtnFrame, BtnFrame);
	CC_SYNTHESIZE(float, _fImageFrame, ImageFrame);
	CC_SYNTHESIZE_READONLY(int, _nDigit, Digit);
};

