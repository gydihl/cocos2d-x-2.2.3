/********************************************************************
	created:	2014/07/29
	filename: 	NumberLabel.h
	author:		底会雷
	purpose:	实现遮罩效果的数字标签
*********************************************************************/

#pragma once

#include "cocos2d.h"

class NumberLabel
	: public cocos2d::CCNode
{
public:
	virtual ~NumberLabel();

	/*
		@purpose:	
		@access:	public static 
		@param:		cocos2d::CCArray * pAryLabel () : 标签
		@param:		int nDigit () : 默认显示的数字
		@return:	NumberLabel* 
	*/
	static NumberLabel* create(cocos2d::CCArray *pAryLabel, int nDigit = 0);

	virtual bool init(cocos2d::CCArray *pAryLabel, int nDigit = 0);
	virtual void visit(void);

public:
	/*
		@purpose:	
		@access:	virtual public 
		@param:		int nDigit () : 新数字
		@param:		int nLast () : 开始数字
		@return:	void 
	*/
	void setDigit(int nDigit, int nLast, float fDelta);
	// 设置数字，立即显示
	void setDigitAndCommit(int nDigit);

protected:
	// 改变数字时播放滚动动画
	void animation(int nDigit);
	// 计算label位置
	void calcLabelPosition(int nDigit);

protected:
	CC_SYNTHESIZE_READONLY(int, _nDigit, Digit);

protected:
	cocos2d::CCNode *_pLabelContainer;
	cocos2d::CCArray *_pAryLabel;
};

