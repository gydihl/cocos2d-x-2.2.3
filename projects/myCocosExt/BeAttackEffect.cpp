#include "BeAttackEffect.h"
#include "AssetLoader.h"

USING_NS_CC;

CBeAttackEffect* CBeAttackEffect::create(const char *pszFileName)
{
	CBeAttackEffect *pSprite = new CBeAttackEffect();
	if (pSprite && pSprite->init(pszFileName))
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool CBeAttackEffect::init(const char *pszFileName)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!AssetLoader::initSprite(this, pszFileName));
		this->setOpacity(0);

		bRet = true;
	} while (0);
	return bRet;
}

void CBeAttackEffect::Effect()
{
	CCFadeIn* pAction1 = CCFadeIn::create(0.1f);
	CCFadeOut* pAction2 = CCFadeOut::create(0.1f);
	stopAllActions();
	runAction(CCSequence::create(pAction1, pAction2, pAction1, pAction2, NULL));
}

