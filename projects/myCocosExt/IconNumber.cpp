#include "IconNumber.h"
#include "AssetLoader.h"

USING_NS_CC;

IconNumber::IconNumber()
{
	_pIcon = NULL;
	_pBk = NULL;
	_pNumber = NULL;
}

IconNumber::~IconNumber()
{

}

IconNumber* IconNumber::create(const char *szIcon, const char *szBk, const char *ttf)
{
	IconNumber *pRet = new IconNumber;
	if (pRet && pRet->init(szIcon, szBk, ttf))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool IconNumber::init(const char *szIcon, const char *szBk, const char *ttf)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCNode::init());

		_pBk = AssetLoader::createSprite(szBk);
		CC_BREAK_IF(!_pBk);
		this->addChild(_pBk);
		this->setContentSize(_pBk->getContentSize());

		_pIcon = AssetLoader::createSprite(szIcon);
		CC_BREAK_IF(!_pIcon);
		this->addChild(_pIcon);
		_pIcon->setPositionX(-_pBk->getContentSize().width*0.5f);

		_pNumber = CCLabelTTF::create();
		_pNumber->setFontName(ttf);
		_pNumber->setFontSize(32);
 		_pNumber->setAnchorPoint(CCPointMake(0, 0.5f));
 		_pNumber->setPositionX(-_pBk->getContentSize().width*0.5f+_pIcon->getContentSize().width*0.5f+10.0f);
		_pNumber->setString("0");
		CC_BREAK_IF(!_pNumber);
		this->addChild(_pNumber);
		
		bRet = true;
	} while (0);
	return bRet;
}

void IconNumber::setNumber(int nNumber)
{
	if (!_pNumber)
		return;
	_pNumber->setString(CCString::createWithFormat("%d", nNumber)->getCString());
}
