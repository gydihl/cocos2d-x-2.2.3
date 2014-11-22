#include "IndicateLamp.h"
#include "GameInclude.h"

USING_NS_CC;

IndicateLamp::~IndicateLamp()
{
	CC_SAFE_RELEASE_NULL(_pAryLamp);
}

IndicateLamp* IndicateLamp::create(int nCount)
{
	IndicateLamp *pRet = new IndicateLamp;
	if (pRet && pRet->init(nCount))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool IndicateLamp::init(int nCount)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCNode::init());
		CC_BREAK_IF(0 == nCount);

		_pLightLamep = NULL;
		_pAryLamp = CCArray::createWithCapacity(nCount);
		_pAryLamp->retain();
		CCPoint position;
		int nMid = nCount / 2;
		for (int i = 0; i < nCount; ++i)
		{
			CCSprite *pSprite =	AssetLoader::createSprite(si_passPointNormal);
			position.x = pSprite->getContentSize().width*1.3f * (i-nMid);
			position.y = 0.0f;
			UnitKit::calcWinPoint(position);
			pSprite->setPosition(position);
			this->addChild(pSprite);
			_pAryLamp->addObject(pSprite);
		}

		_pLightLamep = AssetLoader::createSprite(si_passPointSelect);
		this->addChild(_pLightLamep);
		this->select(0);

		bRet = true;
	} while (0);
	return bRet;
}

void IndicateLamp::onExit()
{
	CCNode::onExit();
}

bool IndicateLamp::select(int nIndex)
{
	if (nIndex < 0 || nIndex >= (int)_pAryLamp->count())
		return false;
	if (!_pLightLamep)
		return false;
	CCSprite *pSprite = (CCSprite*)_pAryLamp->objectAtIndex(nIndex);
	if (!pSprite)
		return false;
	_pLightLamep->setPosition(pSprite->getPosition());
	return true;
//	_pLightLamep->setPosition(((CCSprite*)_pAryLamp->objectAtIndex(0))->getPosition());
}
