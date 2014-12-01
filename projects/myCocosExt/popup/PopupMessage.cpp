#include "PopupMessage.h"
#include "AssetLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

PopupMessage::PopupMessage()
	: _pLabelTitle(NULL)
	, _pLabelContentText(NULL)
	, _pMenu(NULL)
	, _nContentPadding(0)
	, _nContentPaddingTop(0)
	, _pCallbackListener(NULL)
	, _callFunc(NULL)
{
}

PopupMessage::~PopupMessage()
{
	CC_SAFE_RELEASE_NULL(_pMenu);
	CC_SAFE_RELEASE_NULL(_pLabelTitle);
	CC_SAFE_RELEASE_NULL(_pLabelContentText);
}

PopupMessage* PopupMessage::create(const char *szBackgroundImg)
{
	PopupMessage *pRet = PopupMessage::create();
	if (pRet)
	{
		pRet->setBackgroundImg(szBackgroundImg);
	}
	return pRet;
}

bool PopupMessage::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!SupperPopupMessage::init());

		this->setContentSize(CCSizeZero);

		// 初始化menu
		CCMenu *pMenu = CCMenu::create();
		pMenu->setPosition(CCPointZero);
		this->setMenuButton(pMenu);

		bRet = true;
	} while (0);
	return bRet;
}

void PopupMessage::onEnter()
{
	SupperPopupMessage::onEnter();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint ptCenter = CCPointMake(winSize.width*0.5f, winSize.height*0.5f);

	CCSize szContent;
	CCNode *pBackground = NULL;
	if (getContentSize().equals(CCSizeZero))
	{
		CCSprite *pSprite = AssetLoader::createSprite(_strBackgroundImg.c_str());
		pSprite->setPosition(ptCenter);
		this->addChild(pSprite, 0, 0);
		szContent = pSprite->getTexture()->getContentSize();
		pBackground = pSprite;
	}
	else
	{
		CCScale9Sprite *pSprite = AssetLoader::createScale9Sprite(_strBackgroundImg.c_str());
		pSprite->setContentSize(getContentSize());
		pSprite->setPosition(ptCenter);
		this->addChild(pSprite, 0, 0);
		szContent = this->getContentSize();
		pBackground = pSprite;
	}
	// 添加按钮，并设置位置
	_pMenu->setPosition(CCPointMake(szContent.width*0.5f, szContent.height*0.5f));
	pBackground->addChild(_pMenu);
	float fBtnWidth = szContent.width / (getMenuButton()->getChildrenCount()+1);

	CCArray *pAryMenuItem = _pMenu->getChildren();
	for (unsigned int index = 0; index < pAryMenuItem->count(); ++index)
	{
		CCNode *pNode = dynamic_cast<CCNode*>(pAryMenuItem->objectAtIndex(index));
		pNode->setPosition(CCPointMake(-szContent.width*0.5f+fBtnWidth*(index+1),
			-szContent.height/3));
	}

	// 显示对话框标题
	if (getLabelTitle())
	{
		getLabelTitle()->setPosition(
			ccpAdd(CCPointMake(szContent.width*0.5f, szContent.height*0.5f), 
				CCPointMake(0, szContent.height*0.5f - 35.0f)));
		pBackground->addChild(getLabelTitle());
	}

	// 显示文本内容
	if (getLabelContentText())
	{
		CCLabelTTF* ltf = getLabelContentText();
		ltf->setPosition(ccp(szContent.width / 2, szContent.height / 2));
		ltf->setDimensions(CCSizeMake(szContent.width - _nContentPadding * 2, szContent.height - _nContentPaddingTop));
		ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
		pBackground->addChild(ltf);
	}
}

void PopupMessage::onExit()
{
	SupperPopupMessage::onExit();
}

// void PopupMessage::registerWithTouchDispatcher()
// {
// 	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,
// 		kCCMenuHandlerPriority, true);
// }
// 
// bool PopupMessage::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
// {
// 	return true;
// }

void PopupMessage::setTitle(const char *szTitle, int nFontSize /* = 20 */)
{
	CCLabelTTF *pLabelTitle = CCLabelTTF::create(szTitle, "", nFontSize);
	this->setLabelTitle(pLabelTitle);
}

void PopupMessage::setContentText(const char *szText, int nFontSize /* = 20 */, int nPadding /* = 50 */, int nPaddingTop /* = 100 */)
{
	CCLabelTTF *pLabelText = CCLabelTTF::create(szText, "", nFontSize);
	this->setLabelContentText(pLabelText);

	this->setContentPadding(nPadding);
	this->setContentPaddingTop(nPaddingTop);
}

void PopupMessage::setCallbackFunc(cocos2d::CCObject *pTarget, cocos2d::SEL_CallFuncN callFunc)
{
	_pCallbackListener = pTarget;
	_callFunc = callFunc;
}

bool PopupMessage::addButton(const char *normalImg, const char *selectedImg, const char *title, int tag /* = 0 */)
{
	// 创建图片菜单按钮
	CCMenuItemImage *pMenuItem = CCMenuItemImage::create(normalImg,
		selectedImg, this, menu_selector(PopupMessage::buttonCallback));
	pMenuItem->setTag(tag);

	// 添加文字说明并设置位置
	const CCSize &szMenu = pMenuItem->getContentSize();
	CCLabelTTF *ttf = CCLabelTTF::create(title, "", 20);
	ttf->setColor(ccc3(0, 0, 0));
	ttf->setPosition(CCPointMake(szMenu.width*0.5f, szMenu.height*0.5f));
	pMenuItem->addChild(ttf);

	getMenuButton()->addChild(pMenuItem);
	return true;
}

void PopupMessage::buttonCallback(CCObject* pSender)
{
	CCNode *node = dynamic_cast<CCNode*>(pSender);
	if (_pCallbackListener && _callFunc)
	{
		(_pCallbackListener->*_callFunc)(node);
	}
	this->removeFromParent();
}
