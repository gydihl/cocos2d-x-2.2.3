#include "ScrollNumber.h"
#include "NumberLabel.h"

USING_NS_CC;

ScrollNumber* ScrollNumber::create(int nFigureCount, int nNumber /* = 0 */)
{
	ScrollNumber *pRet = new ScrollNumber;
	if (pRet && pRet->init(nFigureCount, nNumber))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool ScrollNumber::init(int nFigureCount, int nNumber)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCNode::init());

		this->setFigureCount(0);
		this->setMaxNumber(0);
		for (int i = 0; i < nFigureCount; ++i)
		{
			this->addFigureLabel();
		}
/*
		_nFigureCount = nFigureCount;
		int nFontSize = 36;

		const int nCount = 10;


		for (int i = 0; i < nFigureCount; ++i)
		{
			CCArray *pAryLabel = CCArray::createWithCapacity(nCount);
			for (int j = 0; j < nCount; ++j)
			{
				CCLabelTTF *pLabel = CCLabelTTF::create(CCString::createWithFormat("%d", j)->getCString(), "Thonburi", nFontSize);
				pAryLabel->addObject(pLabel);
			}
			NumberLabel *pNumberLabel = NumberLabel::create(pAryLabel);
			pNumberLabel->setPosition(CCPointMake(nFontSize*0.75*i, 0));
			this->addChild(pNumberLabel, 0, i);
		}
*/
		this->setNumber(nNumber);

		bRet = true;
	} while (0);
	return bRet;
}
/*
void ScrollNumber::setNumber(int nNumber, int nCeiling / * = 999999 * /)
{
	nNumber = MIN(nNumber, nCeiling);
	nNumber = MAX(nNumber, 0);
	_nNumber = nNumber;
	for (int i = 0; i < s_nNumberFigure; ++i)
	{
		NumberLabel *pLabel = (NumberLabel*)this->getChildByTag(i);
		int nDigit = _nNumber / (int)(pow(10.0, 6-i-1)) % 10;
//		pLabel->setDigit(nDigit, pLabel->getDigit());
		pLabel->setDigit(nDigit, nDigit);
	}
}
*/
void ScrollNumber::setNumber(int nNumber, eScrollNumberActionType type /* = kScrollNumberActionNone */, float fDelta /* = 0.0f */)
{
	if (nNumber < 0)
		nNumber *= -1;
	if (nNumber >= getMaxNumber())
	{
		// 添加一位
		this->addFigureLabel();
		setNumber(nNumber, type, fDelta);
		return;
	}
	_nNumber = nNumber;
	for (int i = 0; i < this->getFigureCount(); ++i)
	{
		NumberLabel *pLabel = (NumberLabel*)this->getChildByTag(i);
		int nDigit = _nNumber / (int)(pow(10.0, this->getFigureCount()-i-1)) % 10;
		switch (type)
		{
		case kScrollNumberActionNone:
			pLabel->setDigit(nDigit, nDigit, fDelta);
			break;
		case kScrollNumberActionNormal:
			pLabel->setDigit(nDigit, 0, fDelta);
			break;
		case kScrollNumberActionFromLast:
			pLabel->setDigit(nDigit, pLabel->getDigit(), fDelta);
			break;
		case kScrollNumberActionRand:
		case kScrollNumberActionFast:
		default:
			CCAssert(false, "");
			break;
		}
	}
}

void ScrollNumber::addFigureLabel()
{
	const int nFontSize = 36;
	const int nCount = 10;
	CCArray *pAryLabel = CCArray::createWithCapacity(nCount);
	for (int i = 0; i < nCount; ++i)
	{
		CCLabelTTF *pLabel = CCLabelTTF::create(CCString::createWithFormat("%d", i)->getCString(), "Thonburi", nFontSize);
		pAryLabel->addObject(pLabel);
	}
	NumberLabel *pNumberLabel = NumberLabel::create(pAryLabel);
	pNumberLabel->setPosition(CCPointMake(nFontSize*0.75*getFigureCount(), 0));
	this->addChild(pNumberLabel, 0, getFigureCount());
	setFigureCount(getFigureCount()+1);
	setMaxNumber(pow(10.0, getFigureCount())-1);
}


