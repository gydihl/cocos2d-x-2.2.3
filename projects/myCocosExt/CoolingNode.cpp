#include "CoolingNode.h"
#include "AssetLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

CoolingNode::CoolingNode()
{
	_fCD = 0.0f;
	_pTouchNode = NULL;
	_pCover = NULL;
	_pProgressTimer = NULL;
	_pAction = NULL;
	_touchEventListener = NULL;
	_touchEventSelector = NULL;
	_bTouchEnabled = true;
}

CoolingNode::~CoolingNode()
{
	CC_SAFE_RELEASE_NULL(_pAction);
}

CoolingNode* CoolingNode::create(float fCD, const char *szImageName, const char *szCoolingName)
{
	CoolingNode *pRet = new CoolingNode;
	if (pRet && pRet->init(fCD, szImageName, szCoolingName))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CoolingNode::init(float fCD, const char *szImageName, const char *szCoolingName)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCNode::init());

		// 冷却时间不能小于0
		CC_BREAK_IF(fCD < 0.0f);

		// 冷却时间
		this->setCD(fCD);

		_pTouchNode = AssetLoader::createSprite(szImageName);
		CC_BREAK_IF(!_pTouchNode);
		this->addChild(_pTouchNode);

		_pCover = AssetLoader::createSprite(szCoolingName);
		_pProgressTimer = CCProgressTimer::create(_pCover);
		_pProgressTimer->setOpacity(125);
		_pProgressTimer->setType(kCCProgressTimerTypeRadial);		// 设置为扇形
		// CCProgressTo的startWithTarget()函数会认为100为0
		// 所以这里不设置100
		_pProgressTimer->setPercentage(99.9f);
		_pProgressTimer->setReverseProgress(true);
		this->addChild(_pProgressTimer);

		if (fCD > 0.0f)
		{
			_pAction = CCSequence::create(
				CCProgressTo::create(fCD, 0.0f),
				CCCallFunc::create(this, callfunc_selector(CoolingNode::allowTouch)),
				NULL);
			_pAction->retain();
		}

		this->setContentSize(_pTouchNode->getContentSize());
//		this->setAnchorPoint(CCPointMake(0.5, 0.5));

		bRet = true;
	} while (0);
	return bRet;
}

void CoolingNode::onEnter()
{
	if (_bTouchEnabled)
	{
		this->registerWithTouchDispatcher();
	}
	CCNode::onEnter();
}

void CoolingNode::onExit()
{
	if (_bTouchEnabled )
	{
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getTouchDispatcher()->removeDelegate(this);
	}
	CCNode::onExit();
}

void CoolingNode::registerWithTouchDispatcher()
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();

	pDispatcher->addTargetedDelegate(this, 0, true);
}

bool CoolingNode::isTouchEnabled()
{
	return _bTouchEnabled;
}

void CoolingNode::setTouchEnabled(bool enabled)
{
	if (_bTouchEnabled != enabled)
	{
		_bTouchEnabled = enabled;
		if (m_bRunning)
		{
			if (enabled)
			{
				this->registerWithTouchDispatcher();
			}
			else
			{
				// have problems?
				CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
			}
		}
	}
}

bool CoolingNode::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint location = pTouch->getLocation();
	CCPoint nsp = _pTouchNode->convertToNodeSpace(location);
	const CCSize &szSize = _pTouchNode->getContentSize();
	CCRect bb = CCRect(-szSize.width * m_obAnchorPoint.x, 
		-szSize.height * m_obAnchorPoint.y, 
		szSize.width, 
		szSize.height);
	if (nsp.x >= bb.origin.x 
		&& nsp.x <= bb.origin.x + bb.size.width 
		&& nsp.y >= bb.origin.y 
		&& nsp.y <= bb.origin.y + bb.size.height)
	{
		if (_touchEventListener && _touchEventSelector)
		{
			(_touchEventListener->*_touchEventSelector)(this, TOUCH_EVENT_BEGAN);
		}
		return true;
	}
	return false;
}

void CoolingNode::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (_touchEventListener && _touchEventSelector)
	{
		(_touchEventListener->*_touchEventSelector)(this, TOUCH_EVENT_MOVED);
	}
}

void CoolingNode::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	this->setTouchEnabled(false);
	_pProgressTimer->stopAllActions();
	// CCProgressTo的startWithTarget()函数会认为100为0
	// 所以这里不设置100
	_pProgressTimer->setPercentage(99.9f);
	if (_pAction)
		_pProgressTimer->runAction(_pAction);
	if (_touchEventListener && _touchEventSelector)
	{
		(_touchEventListener->*_touchEventSelector)(this, TOUCH_EVENT_ENDED);
	}
}

void CoolingNode::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	if (_touchEventListener && _touchEventSelector)
	{
		(_touchEventListener->*_touchEventSelector)(this, TOUCH_EVENT_CANCELED);
	}
}

void CoolingNode::allowTouch()
{
	this->setTouchEnabled(true);
}

void CoolingNode::addTouchEventListener(cocos2d::CCObject* target, cocos2d::ui::SEL_TouchEvent selector)
{
	this->_touchEventListener = target;
	this->_touchEventSelector = selector;
}

