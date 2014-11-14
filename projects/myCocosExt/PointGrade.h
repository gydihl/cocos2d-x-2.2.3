/********************************************************************
	created:	2014/08/21
	filename: 	PointGrade.h
	author:		底会雷
	purpose:	点数区分好坏
*********************************************************************/

#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

class PointGrade
	: public cocos2d::ui::Widget
{
public:
	static PointGrade* create(const char *szPointBk, const char *szPointSel, int nMaxPoint = 10, float fInset = 0.0f);
	virtual bool init(const char *szPointBk, const char *szPointSel, int nMaxPoint = 10, float fInset = 0.0f);

protected:
	bool initPointScore(int nMaxPoint);

public:
	void setScore(int nScore);

protected:
//	void createScore(int nScore);

protected:
	cocos2d::CCArray *_pAryMaxPoint;		// 最大分点
	cocos2d::CCArray *_pAryScorePoint;		// 得分点

	std::string _strPointBk;
	std::string _strPointSel;
	float _fInset;
	int _nScorePoint;						// 得分数
};
