#include "PointGrade.h"
#include "AssetLoader.h"

USING_NS_CC;
using namespace cocos2d::ui;

PointGrade* PointGrade::create(const char *szPointBk, const char *szPointSel, int nMaxPoint /* = 10 */, float fInset/* = 0.0f*/)
{
	PointGrade *pRet = new PointGrade;
	if (pRet && pRet->init(szPointBk, szPointSel, nMaxPoint, fInset))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool PointGrade::init(const char *szPointBk, const char *szPointSel, int nMaxPoint /* = 10 */, float fInset/* = 0.0f*/)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Widget::init());

		_strPointBk = szPointBk;
		_strPointSel = szPointSel;
		CC_BREAK_IF(_strPointBk.empty());
		CC_BREAK_IF(_strPointSel.empty());
		_fInset = fInset;

		CC_BREAK_IF(nMaxPoint <= 0);

		_pAryMaxPoint = CCArray::createWithCapacity(nMaxPoint);
		CC_SAFE_RETAIN(_pAryMaxPoint);
		_pAryScorePoint = CCArray::createWithCapacity(nMaxPoint);;
		CC_SAFE_RETAIN(_pAryScorePoint);

		CC_BREAK_IF(!this->initPointScore(nMaxPoint));

		bRet = true;
	} while (0);
	return bRet;
}

bool PointGrade::initPointScore(int nMaxPoint)
{
	bool bRet = false;
	do 
	{
		CCPoint position;
		int nMid = nMaxPoint / 2;
		UIImageView *pImage = NULL;
		for (int i = 0; i < nMaxPoint; ++i)
		{
			pImage = UIImageView::create();
			AssetLoader::loadImageViewTexture(pImage, _strPointBk.c_str());

			position.x = (pImage->getContentSize().width-_fInset)*(i-nMid);
			position.y = 0.0f;
//			UnitKit::calcWinPoint(position);

			pImage->setPosition(position);
			this->addChild(pImage);
			_pAryMaxPoint->addObject(pImage);

			pImage = UIImageView::create();
			AssetLoader::loadImageViewTexture(pImage, _strPointSel.c_str());
			pImage->setPosition(position);
			pImage->setVisible(false);
			this->addChild(pImage);
			_pAryScorePoint->addObject(pImage);
		}
		CC_BREAK_IF((int)_pAryMaxPoint->count() < nMaxPoint);
		CC_BREAK_IF((int)_pAryScorePoint->count() < nMaxPoint);
		bRet = true;
	} while (0);
	return bRet;
}

void PointGrade::setScore(int nScore)
{
	if (nScore < 0)
		nScore = 0;
	if (nScore > (int)_pAryMaxPoint->count())
		nScore = (int)_pAryMaxPoint->count();
	for (unsigned int index = 0; index < _pAryScorePoint->count(); ++index)
	{
		CCSprite *pSprite = static_cast<CCSprite*>(_pAryScorePoint->objectAtIndex(index));
		if ((int)index < nScore)
			pSprite->setVisible(true);
		else
			pSprite->setVisible(false);
	}
}

