/********************************************************************
	created:	2014/06/09
	filename: 	ScrollView.h
	author:		底会雷
	purpose:	血条控件
*********************************************************************/

#ifndef _BLOOD_CTRL_H_
#define _BLOOD_CTRL_H_

#include "cocos2d.h"

class BloodCtrl
	: public cocos2d::CCLayer
{
public:
	CREATE_FUNC(BloodCtrl);

	static BloodCtrl* CreateCtrl();

public:
	virtual bool init();

public:
	void SetPosition(const cocos2d::CCPoint &position);
	void SetPercentage(float fPercentage);

protected:
	cocos2d::CCSprite *m_pBloodBkImg;			// 血条的背景图片
	cocos2d::CCProgressTimer *m_pBloodCtrl;		// 血条
};

#endif	// _BLOOD_CTRL_H_

