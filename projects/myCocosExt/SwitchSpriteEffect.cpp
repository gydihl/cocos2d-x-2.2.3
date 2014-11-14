#include "SwitchSpriteEffect.h"
#include "Common/VisibleRect.h"
#include "GameInclude.h"

USING_NS_CC;

CSwitchSpriteEffect::CSwitchSpriteEffect(void)
{
}

CSwitchSpriteEffect::~CSwitchSpriteEffect(void)
{
}

CSwitchSpriteEffect* CSwitchSpriteEffect::Create(const char *szImg1,const char *szImg2)
{
	CSwitchSpriteEffect *pRet = new CSwitchSpriteEffect(); 
	if (pRet && pRet->init(szImg1, szImg2)) 
	{
		pRet->autorelease(); 
		return pRet; 
	}
	else 
	{
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	}
}

bool CSwitchSpriteEffect::init(const char *szImg1,const char *szImg2)
{
	if (!CCSprite::init())
		return false;
	m_nShowKey = 0;
	m_pSprite1 = AssetLoader::createSprite(szImg1);
	m_pSprite1->setVisible(true);
	m_pSprite1->setOpacity(255);
	this->addChild(m_pSprite1, 2);
//	this->initWithSpriteFrameName(szImg1);

	m_pSprite2 = AssetLoader::createSprite(szImg2);
	m_pSprite2->setVisible(true);
	m_pSprite2->setOpacity(100);
	this->addChild(m_pSprite2, 1);

	this->CalcDis();
	return true;
}

void CSwitchSpriteEffect::SwitchEffect()
{
	CCActionInterval* actiono = CCFadeOut::create(0.2f);
	CCActionInterval* actioni = CCFadeIn::create(0.2f);
	CCActionInterval* action = CCFadeTo::create(0.2f, 100);
	CCActionInterval* moveup = CCMoveTo::create(0.2f, ccp(0, 0+m_fSpriteDis));
	CCActionInterval* movedown = CCMoveTo::create(0.2f, ccp(0, 0));

	if (1 == m_nShowKey)
	{
		m_pSprite2->runAction(action);
		m_pSprite2->runAction(moveup);
		m_pSprite1->runAction(actioni);
		m_pSprite1->runAction(movedown);
		m_nShowKey = 0;
	}
	else
	{
 		m_pSprite1->runAction(action);
 		m_pSprite1->runAction(moveup);
		m_pSprite2->runAction(actioni);
		m_pSprite2->runAction(movedown);
		m_nShowKey = 1;
	}
	if (0 == m_nShowKey)
	{
		this->reorderChild(m_pSprite1, 2);
		this->reorderChild(m_pSprite2, 1);
	}
	else
	{
		this->reorderChild(m_pSprite1, 1);
		this->reorderChild(m_pSprite2, 2);
	}
}

void CSwitchSpriteEffect::CalcDis()
{
	if (!m_pSprite1 || !m_pSprite2)
		return;
	CCRect rcBox = m_pSprite1->boundingBox();
	m_fSpriteDis = rcBox.size.height * m_fScaleY * 2 / 7;
	if (0 == m_nShowKey)
	{
		m_pSprite2->setPosition(ccp(0, 0+m_fSpriteDis));
	}
	else
	{
		m_pSprite1->setPosition(ccp(0, 0+m_fSpriteDis));
	}
	this->setContentSize(CCSizeMake(rcBox.size.width * m_fScaleX, 
		rcBox.size.height * m_fScaleY));
}

void CSwitchSpriteEffect::setScale(float fScale)
{
	CCSprite::setScale(fScale);
	this->CalcDis();
}

void CSwitchSpriteEffect::setScaleX(float fScaleX)
{
	CCSprite::setScaleX(fScaleX);
//	this->CalcDis();
}

void CSwitchSpriteEffect::setScaleY(float fScaleY)
{
	CCSprite::setScaleY(fScaleY);
	this->CalcDis();
}




