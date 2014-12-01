#include "PopupTest.h"
#include "AssetLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

//////////////////////////////////////////////////////////////////////////
// TestPopupLayer
bool TestPopupLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!PopupLayer::init());

		TouchGroup *pUI = TouchGroup::create();
		this->addChild(pUI);
		// 比TestPopupLayer的优先级要高
		pUI->setTouchPriority(kCCMenuHandlerPriority-1);

		UIButton *pBtn = AssetLoader::createUIButton("jump.png", "jump_2.png", "", 
			this, toucheventselector(TestPopupLayer::onTestTouch));
		pUI->addWidget(pBtn);

		bRet = true;
	} while (0);
	return bRet;
}

void TestPopupLayer::onTestTouch(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType eventType)
{
	switch (eventType)
	{
	case TOUCH_EVENT_BEGAN:
		CCLOG("test popuplayer touch began");
		break;
	case TOUCH_EVENT_MOVED:
		CCLOG("test popuplayer touch moved");
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("test popuplayer touch ended");
		break;
	case TOUCH_EVENT_CANCELED:
		CCLOG("test popuplayer touch canceled");
		break;
	default:
		CCLOG("test popuplayer touch default");
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// TestPopupTouchGroup
bool TestPopupTouchGroup::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!PopupTouchGroup::init());

		UIButton *pBtn = AssetLoader::createUIButton("jump.png", "jump_2.png", "", 
			this, toucheventselector(TestPopupTouchGroup::onTestTouch));
		this->addWidget(pBtn);

		bRet = true;
	} while (0);
	return bRet;
}

void TestPopupTouchGroup::onTestTouch(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType eventType)
{
	switch (eventType)
	{
	case TOUCH_EVENT_BEGAN:
		CCLOG("test popuptouchgroup touch began");
		break;
	case TOUCH_EVENT_MOVED:
		CCLOG("test popuptouchgroup touch moved");
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("test popuptouchgroup touch ended");
		break;
	case TOUCH_EVENT_CANCELED:
		CCLOG("test popuptouchgroup touch canceled");
		break;
	default:
		CCLOG("test popuptouchgroup touch default");
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// TestPopupMessage
bool TestPopupMessage::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!PopupMessage::init());

		this->setBackgroundImg("BackGround.png");
		this->setContentSize(CCSizeMake(400, 350));
		this->setTitle("dihl");
		this->setContentText("fdjasklfdjakslfdjsalk", 20, 60, 250);
		this->setCallbackFunc(this, callfuncN_selector(TestPopupMessage::buttonCallback));
		this->addButton("pop_button.png", "pop_button.png", "ok", 0);
		this->addButton("pop_button.png", "pop_button.png", "cancel", 1);

		bRet = true;
	} while (0);
	return bRet;
}

void TestPopupMessage::buttonCallback(CCNode* pSender)
{
	CCLOG("button callback tag: %d", pSender->getTag());
}
