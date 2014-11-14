/********************************************************************
	created:	2014/06/25
	filename: 	BeAttackEffect.h
	author:		底会雷
	purpose:	主角被攻击的效果
*********************************************************************/

#ifndef _BE_ATTACK_EFFECT_H_
#define _BE_ATTACK_EFFECT_H_

#include "cocos2d.h"

class CBeAttackEffect
	: public cocos2d::CCSprite
{
public:
	static CBeAttackEffect* create(const char *pszFileName);
	virtual bool init(const char *pszFileName);

public:
	void Effect();
};

#endif	// _BE_ATTACK_EFFECT_H_
