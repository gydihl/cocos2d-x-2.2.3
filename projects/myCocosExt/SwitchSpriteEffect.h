/********************************************************************
	created:	2014/06/14
	filename: 	SwitchSpriteEffect.h
	author:		全晓洲
	purpose:	切换效果
*********************************************************************/
#pragma once
#include "cocos2d.h"

class CSwitchSpriteEffect 
	: public cocos2d::CCSprite
{
public:
	CSwitchSpriteEffect(void);
	~CSwitchSpriteEffect(void);

	static CSwitchSpriteEffect* Create(const char *szImg1,const char *szImg2);
	bool init(const char *szImg1,const char *szImg2);  

public:
	virtual void setScale(float fScale);
	virtual void setScaleX(float fScaleX);
	virtual void setScaleY(float fScaleY);

	void SwitchEffect();

protected:
	void CalcDis();

protected:
	float m_fSpriteDis;
	int m_nShowKey;
	cocos2d::CCSprite *m_pSprite1;
	cocos2d::CCSprite *m_pSprite2;

};

