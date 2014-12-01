#include "PopupTouchGroup.h"
#include "AssetLoader.h"

USING_NS_CC;

bool PopupTouchGroup::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!SupperPopupTouchGroup::init());

		bRet = true;
	} while (0);
	return bRet;
}

void PopupTouchGroup::onEnter()
{
	this->setTouchEnabled(true);
	SupperPopupTouchGroup::onEnter();

	// 弹出效果
	CCAction *popupLayer = CCSequence::create(CCScaleTo::create(0.0f, 0.0f),
		CCScaleTo::create(0.06f, 1.05f),
		CCScaleTo::create(0.08f, 0.95f),
		CCScaleTo::create(0.08f, 1.0f), NULL);
	this->runAction(popupLayer);
}

void PopupTouchGroup::onExit()
{
	SupperPopupTouchGroup::onExit();
}

void PopupTouchGroup::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 
		kCCMenuHandlerPriority, true);
}

bool PopupTouchGroup::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	SupperPopupTouchGroup::ccTouchBegan(pTouch, pEvent);
	return true;
}

void PopupTouchGroup::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	SupperPopupTouchGroup::ccTouchMoved(pTouch, pEvent);
}

void PopupTouchGroup::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	SupperPopupTouchGroup::ccTouchEnded(pTouch, pEvent);
}

void PopupTouchGroup::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	SupperPopupTouchGroup::ccTouchCancelled(pTouch, pEvent);
}


