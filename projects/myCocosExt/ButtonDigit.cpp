#include "ButtonDigit.h"
#include "AssetLoader.h"

USING_NS_CC;
using namespace cocos2d::ui;

ButtonDigit* ButtonDigit::create()
{
	ButtonDigit *pRet = new ButtonDigit;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool ButtonDigit::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!UIButton::init());

		_pImageDigit = UIImageView::create();
		this->addChild(_pImageDigit, 0);

		_pLabelDigit = UILabelBMFont::create();
		_pImageDigit->addChild(_pLabelDigit, 1);

		this->setDigit(0);

		bRet = true;
	} while (0);
	return bRet;
}

void ButtonDigit::initButton(const char* normal,const char* selected,const char* disabled, float fBtnFrame /* = 0.0f */)
{
	AssetLoader::loadButtonTextures(this, normal, selected, disabled);
	this->setBtnFrame(fBtnFrame);

	this->setImagePosition();
}

void ButtonDigit::initImageDigit(const char* fileName, float fImageFrame /* = 0.0f */)
{
	if (!_pImageDigit)
		return;
	AssetLoader::loadImageViewTexture(_pImageDigit, fileName);
	this->setImageFrame(fImageFrame);

	this->setImagePosition();
}

void ButtonDigit::initLabelDigitFnt(const char* fileName)
{
	if (!_pImageDigit || !_pLabelDigit)
		return;
	_pLabelDigit->setFntFile(fileName);
	_pLabelDigit->setText(CCString::createWithFormat("%d", _nDigit)->getCString());

	const CCSize &szImage = _pImageDigit->getContentSize();
	if (szImage.height > 0.0f)
	{
		const CCSize &szLabel = _pLabelDigit->getContentSize();
		// 设置缩放比例
		float fScaleY = (szImage.height - 2*getImageFrame()) / szLabel.height;
		_pLabelDigit->setScale(fScaleY);
	}
}

void ButtonDigit::setLabelColor(const ccColor3B& color)
{
	if (!_pLabelDigit)
		return;
	_pLabelDigit->setColor(color);
}

void ButtonDigit::setDigit(int nDigit)
{
	_nDigit = nDigit;
	if (!_pLabelDigit || !_pImageDigit)
		return;

	if (0 == nDigit)
	{
		_pImageDigit->setVisible(false);
		_pLabelDigit->setVisible(false);
	}
	else
	{
		_pImageDigit->setVisible(true);
		_pLabelDigit->setVisible(true);
		_pLabelDigit->setText(CCString::createWithFormat("%d", nDigit)->getCString());
	}
}

void ButtonDigit::setImagePosition()
{
	if (!_pImageDigit)
		return;

	const CCSize &szBtnSize = this->getContentSize();
	// 放在右上角
	_pImageDigit->setPosition(CCPointMake(szBtnSize.width*0.5f-getBtnFrame(), szBtnSize.height*0.5f-getBtnFrame()));
}

