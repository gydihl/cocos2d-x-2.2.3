#include "IconNumberWidget.h"
#include "AssetLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

IconNumberWidget::IconNumberWidget()
{
	_pIcon = NULL;
	_pBk = NULL;
	_pNumber = NULL;
}

IconNumberWidget::~IconNumberWidget()
{

}

IconNumberWidget* IconNumberWidget::create(const char *szIcon, const char *szBk, const char *ttf)
{
	IconNumberWidget *pRet = new IconNumberWidget;
	if (pRet && pRet->init(szIcon, szBk, ttf))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool IconNumberWidget::init(const char *szIcon, const char *szBk, const char *ttf)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Widget::init());

		if (szBk && strlen(szBk) > 0)
		{
			_pBk = UIImageView::create();
			CC_BREAK_IF(!_pBk);
			AssetLoader::loadImageViewTexture(_pBk, szBk);
			this->addChild(_pBk);
		}
//		this->setContentSize(_pBk->getContentSize());

		_pIcon = UIImageView::create();
		CC_BREAK_IF(!_pIcon);
		AssetLoader::loadImageViewTexture(_pIcon, szIcon);
		this->addChild(_pIcon);
		if (_pBk)
			_pIcon->setPositionX(-_pBk->getContentSize().width*0.5f);
		else
			_pIcon->setPositionX(-_pIcon->getContentSize().width*0.5f);

		_pNumber = UILabel::create();
		_pNumber->setFontName(ttf);
		_pNumber->setFontSize(32);
 		_pNumber->setAnchorPoint(CCPointMake(0, 0.5f));
		if (_pBk)
 			_pNumber->setPositionX(-_pBk->getContentSize().width*0.5f+_pIcon->getContentSize().width*0.5f+10.0f);
		else
			_pNumber->setPositionX(0.0f);
		_pNumber->setText("0");
		CC_BREAK_IF(!_pNumber);
		this->addChild(_pNumber);
		
		bRet = true;
	} while (0);
	return bRet;
}

void IconNumberWidget::setNumber(int nNumber)
{
	if (!_pNumber)
		return;
	_pNumber->setText(CCString::createWithFormat("%d", nNumber)->getCString());
}
