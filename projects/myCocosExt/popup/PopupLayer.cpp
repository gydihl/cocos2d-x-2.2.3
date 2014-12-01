#include "PopupLayer.h"
#include "AssetLoader.h"

USING_NS_CC;

bool PopupLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!SupperPopupLayer::init());

		bRet = true;
	} while (0);
	return bRet;
}

void PopupLayer::onEnter()
{
	this->setTouchEnabled(true);
	SupperPopupLayer::onEnter();
}

void PopupLayer::onExit()
{
	SupperPopupLayer::onExit();

	// 弹出效果
	CCAction* popupLayer = CCSequence::create(CCScaleTo::create(0.0, 0.0),
		CCScaleTo::create(0.06, 1.05),
		CCScaleTo::create(0.08, 0.95),
		CCScaleTo::create(0.08, 1.0), NULL);
	this->runAction(popupLayer);
}

void PopupLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool PopupLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void PopupLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	SupperPopupLayer::ccTouchMoved(pTouch, pEvent);
}

void PopupLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	SupperPopupLayer::ccTouchEnded(pTouch, pEvent);
}

void PopupLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	SupperPopupLayer::ccTouchCancelled(pTouch, pEvent);
}


