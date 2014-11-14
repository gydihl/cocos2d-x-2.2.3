#include "NumberLabel.h"

USING_NS_CC;

enum{
	kCounterAction = 0
};

NumberLabel::~NumberLabel()
{
	CC_SAFE_RELEASE_NULL(_pAryLabel);
}

NumberLabel* NumberLabel::create(cocos2d::CCArray *pAryLabel, int nDigit /* = 0 */)
{
	NumberLabel *pRet = new NumberLabel;
	if (pRet && pRet->init(pAryLabel, nDigit))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool NumberLabel::init(cocos2d::CCArray *pAryLabel, int nDigit /* = 0 */)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCNode::init());

		CC_BREAK_IF(!pAryLabel);

		_pAryLabel = CCArray::create();
		CC_BREAK_IF(!_pAryLabel);
		CC_SAFE_RETAIN(_pAryLabel);

		_pLabelContainer = CCNode::create();
		CC_BREAK_IF(!_pLabelContainer);

		this->calcLabelPosition(0);

		for (unsigned int index = 0; index < pAryLabel->count(); ++index)
		{
			CCNode *pNode = (CCNode*)pAryLabel->objectAtIndex(index);
			if (!pNode)
				continue;
			float y = pNode->getContentSize().height * index;
			pNode->setPosition(CCPointMake(0, y));
			_pLabelContainer->addChild(pNode, 0, index);
			_pAryLabel->addObject(pAryLabel->objectAtIndex(index));
		}

		this->addChild(_pLabelContainer);
		this->setDigit(nDigit, nDigit, 0.0f);

		bRet = true;
	} while (0);
	return bRet;
}

void NumberLabel::calcLabelPosition(int nDigit)
{
	if (!_pAryLabel || !_pLabelContainer)
		return;
	_pLabelContainer->setPosition(CCPointZero);
	for (unsigned int index = nDigit; index < _pAryLabel->count(); ++index)
	{
		CCNode *pNode = (CCNode*)_pAryLabel->objectAtIndex(index);
		if (!pNode)
			continue;
		float y = pNode->getContentSize().height * (index-nDigit);
		pNode->setPosition(CCPointMake(0, y));
	}
	for (int index = 0; index < nDigit; ++index)
	{
		CCNode *pNode = (CCNode*)_pAryLabel->objectAtIndex(index);
		if (!pNode)
			continue;
		float y = pNode->getContentSize().height * (_pAryLabel->count()-nDigit+index);
		pNode->setPosition(CCPointMake(0, y));
	}
}

void NumberLabel::animation(int nDigit)
{
	CCNode *pLabel = _pLabelContainer->getChildByTag(nDigit);
	const CCPoint &ptDest = pLabel->getPosition();
//	this->stopActionByTag(kCounterAction);
	this->_pLabelContainer->stopAllActions();
	CCMoveTo *moveToAction = CCMoveTo::create(0.2f, CCPointMake(0, -ptDest.y));
//	moveToAction->setTag(kCounterAction);
	_pLabelContainer->runAction(moveToAction);
}

void NumberLabel::visit()
{
// 	CCNode::visit();
// 	return;

	// 启动遮罩效果
	glEnable(GL_SCISSOR_TEST);

	CCNode *pNode = _pLabelContainer->getChildByTag(_nDigit);
	const CCSize &size = pNode->getContentSize();

	float fScaleX = CCEGLView::sharedOpenGLView()->getScaleX();
	float fScaleY = CCEGLView::sharedOpenGLView()->getScaleY();
	CCPoint location = getParent()->convertToWorldSpace(CCPointMake(getPosition().x-size.width*0.5f, getPosition().y-size.height*0.5f));

	// 设置遮罩效果
	glScissor(location.x*fScaleX, location.y*fScaleY, size.width*fScaleX, size.height*fScaleY);
	CCNode::visit();
	// 关闭遮罩效果
	glDisable(GL_SCISSOR_TEST);
}

void NumberLabel::setDigit(int nDigit, int nLast, float fDelta)
{
	if (nDigit == nLast)
	{
		this->setDigitAndCommit(nDigit);
		return;
	}
	this->calcLabelPosition(nLast);
	
	CCNode *pLabel = _pLabelContainer->getChildByTag(nDigit);
	const CCPoint &ptDest = pLabel->getPosition();
	_pLabelContainer->stopAllActions();
	_pLabelContainer->runAction(
		CCMoveTo::create(fDelta, CCPointMake(0, -ptDest.y))
		);

	_nDigit = nDigit;
}

void NumberLabel::setDigitAndCommit(int nDigit)
{
	this->calcLabelPosition(nDigit);
	CCNode *pLabel = _pLabelContainer->getChildByTag(nDigit);
	_pLabelContainer->stopAllActions();
	_pLabelContainer->setPosition(CCPointMake(0, -pLabel->getPosition().y));
	_nDigit = nDigit;
}
