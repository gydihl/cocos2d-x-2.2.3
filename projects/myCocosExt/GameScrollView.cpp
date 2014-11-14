#include "GameScrollView.h"

USING_NS_CC;
USING_NS_CC_EXT;

CGameScrollView::CGameScrollView()
	: m_fAdjustSpeed(ADJUST_ANIM_VELOCITY)
	, m_bSetDirection(false)
	, m_nCurPage(0)
{

}

CGameScrollView::~CGameScrollView()
{

}

bool CGameScrollView::init()
{
	if (!CCScrollView::init())
	{
		return false;
	}

	return true;
}

bool CGameScrollView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	m_BeginOffset = getContentOffset();
	bool bRet = CCScrollView::ccTouchBegan(pTouch, pEvent);
	if (bRet)
	{
		// 滑动开始的回调
		CGameScrollViewDelegate *pDele = (CGameScrollViewDelegate *)m_pDelegate;
		pDele->scrollViewScrollBegin(m_pContainer->getChildByTag(m_nCurPage), m_nCurPage);
	}
	return bRet;
}

void CGameScrollView::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CGameScrollViewDelegate *pDele = (CGameScrollViewDelegate *)m_pDelegate;
	pDele->scrollViewScrolling(m_pContainer->getChildByTag(m_nCurPage), m_nCurPage);
	CCScrollView::ccTouchMoved(pTouch, pEvent);
}

void CGameScrollView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint touchPoint = pTouch->getLocation();

	CCScrollView::ccTouchEnded(pTouch, pEvent);

	CCPoint m_EndOffset = getContentOffset();

	//点击Page的功能
	if (m_BeginOffset.equals(m_EndOffset))
	{
		int nPage = -1;
		if (m_eDirection == kCCScrollViewDirectionHorizontal)
		{
			nPage = abs(m_EndOffset.x / (int)m_CellSize.width);
		}
		else
		{
			nPage = abs(m_EndOffset.y / (int)m_CellSize.height);
		}

		CGameScrollViewDelegate *pDele = (CGameScrollViewDelegate *)m_pDelegate;
		CCNode *pPgae = m_pContainer->getChildByTag(nPage);
		if (!pPgae)
			return;
		CCRect rcContent;
		rcContent.origin = pPgae->getPosition();
		rcContent.size = pPgae->getContentSize();
		rcContent.origin.x -= rcContent.size.width / 2;
		rcContent.origin.y -= rcContent.size.height / 2;
//		CCRect rcNew = pPgae->boundingBox();

		CCPoint pos = touchPoint;
		if (m_eDirection == kCCScrollViewDirectionHorizontal)
		{
			pos.x += nPage * m_CellSize.width;
		}
		else
		{
			pos.y -= nPage * m_CellSize.height;
		}

		if (rcContent.containsPoint(pos))
		{
			pDele->scrollViewClick(m_EndOffset, touchPoint, pPgae, nPage);
		}
		// 滑动结束后的回调
		pDele->scrollViewScrollEnd(m_pContainer->getChildByTag(m_nCurPage), m_nCurPage);
		return ;
	}

	//自动调整
	adjustScrollView(m_BeginOffset, m_EndOffset);
}

void CGameScrollView::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCScrollView::ccTouchCancelled(pTouch, pEvent);

	CCPoint m_EndOffset = getContentOffset();
	adjustScrollView(m_BeginOffset, m_EndOffset);
}

void CGameScrollView::adjustScrollView( const cocos2d::CCPoint &oBegin, const cocos2d::CCPoint &oEnd)
{
	int nPage = 0;
	int nAdjustPage = 0;

	if (m_eDirection == kCCScrollViewDirectionHorizontal)
	{
		nPage = abs(oBegin.x / (int)m_CellSize.width);
		int nDis = oEnd.x - oBegin.x;

		if (nDis < -getViewSize().width / 5)
		{
			nAdjustPage = nPage + 1;
		}
		else if (nDis > getViewSize().width / 5)
		{
			nAdjustPage = nPage - 1;
		}
		else
		{
			nAdjustPage = nPage;
		}
	}
	else
	{
		nPage = abs(oBegin.y / (int)m_CellSize.height);
		int nDis = oEnd.y - oBegin.y;

		if (nDis < -getViewSize().height / 5)
		{
			nAdjustPage = nPage - 1;
		}
		else if (nDis > getViewSize().height / 5)
		{
			nAdjustPage = nPage + 1;
		}
		else
		{
			nAdjustPage = nPage;
		}
	}

	nAdjustPage = MIN(nAdjustPage, m_nPageCount - 1);
	nAdjustPage = MAX(nAdjustPage, 0);

	scrollToPage(nAdjustPage);
	// 滑动结束后的回调
	CGameScrollViewDelegate *pDele = (CGameScrollViewDelegate *)m_pDelegate;
	pDele->scrollViewScrollEnd(m_pContainer->getChildByTag(m_nCurPage), m_nCurPage);
}

void CGameScrollView::scrollToPage( int nPage )
{
	// 关闭CCScrollView中的自调整
	unscheduleAllSelectors();

	CCPoint oOffset = getContentOffset();
	// 调整位置
	CCPoint adjustPos;
	if (m_eDirection == kCCScrollViewDirectionHorizontal)
	{
		adjustPos = ccp(-m_CellSize.width * nPage, 0);
	}
	else
	{
		adjustPos = ccp(0, m_CellSize.height * nPage);
	}
	// 调整动画时间
	float adjustAnimDelay = ccpDistance(adjustPos, oOffset) / m_fAdjustSpeed;

	// 调整位置
	setContentOffsetInDuration(adjustPos, adjustAnimDelay);

	if (nPage != m_nCurPage)
	{
		m_nCurPage = nPage;
		scheduleOnce(schedule_selector(CGameScrollView::onScrollEnd), adjustAnimDelay);
	}
}

void CGameScrollView::onScrollEnd(float fDelay)
{
	CGameScrollViewDelegate *pDele = (CGameScrollViewDelegate *)m_pDelegate;
	pDele->scrollViewEndChangePage(m_pContainer->getChildByTag(m_nCurPage), m_nCurPage);
}

void CGameScrollView::scrollToNextPage()
{
	int nCurPage = getCurPage();
	if (nCurPage >= m_nPageCount - 1)
	{
		return ;
	}
	scrollToPage(nCurPage + 1);
}

void CGameScrollView::scrollToPrePage()
{
	int nCurPage = getCurPage();
	if (nCurPage <= 0)
	{
		return ;
	}
	scrollToPage(nCurPage - 1);
}

bool CGameScrollView::createContainer(CGameScrollViewDelegate *pDele, int nCount, const cocos2d::CCSize &oSize )
{
	CCAssert(m_bSetDirection, "must call setDirection first!!!");
	m_nPageCount = nCount;
	m_CellSize = oSize;
	setDelegate(pDele);

	CCLayer *pContainer = CCLayer::create();

//	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
//	CCSize winSize = CCSizeMake(420, 700);
	for (int i = 0; i < nCount; ++i)
	{
		CCNode *pNode = CCNode::create();
		pDele->scrollViewInitPage(this, pNode, i);

		CCObject *pObj = NULL;

		if (m_eDirection == kCCScrollViewDirectionHorizontal)
		{
			pNode->setPosition(ccp(m_tViewSize.width / 2 + i * oSize.width, m_tViewSize.height / 2));
		}
		else
		{
			pNode->setPosition(ccp(m_tViewSize.width / 2, m_tViewSize.height / 2 - i * oSize.height));
		}
		CCSize oMaxSize;
		CCARRAY_FOREACH(pNode->getChildren(), pObj)
		{
			CCNode *pNode = (CCNode *)pObj;
			oMaxSize.width = MAX(oMaxSize.width, pNode->getContentSize().width);
			oMaxSize.height = MAX(oMaxSize.height, pNode->getContentSize().height);
		}
		pNode->setContentSize(oMaxSize);
		pNode->setTag(i);
		pContainer->addChild(pNode);
	}

	setContainer(pContainer);

	return true;
}

int CGameScrollView::getCurPage()
{
	return m_nCurPage;
}

void CGameScrollView::setCurPage( int nPage )
{
	CCAssert(m_nCurPage >= 0 && m_nCurPage < m_nPageCount, "");

	if (m_eDirection == kCCScrollViewDirectionHorizontal)
	{
		setContentOffset(ccp(-nPage * m_CellSize.width, 0));
	}
	else
	{
		setContentOffset(ccp(0, nPage * m_CellSize.height));
	}
	m_nCurPage = nPage;
}

int CGameScrollView::getPageCount()
{
	return m_nPageCount;
}

CCNode *CGameScrollView::getPage( int nPage )
{
	return m_pContainer->getChildByTag(nPage);
}

void CGameScrollView::setDirection( CCScrollViewDirection eDirection )
{
	CCAssert(eDirection != kCCScrollViewDirectionBoth, "Does not suppost kCCScrollViewDirectionBoth!!!");
	CCScrollView::setDirection(eDirection);
	m_bSetDirection = true;
}
/*
void CGameScrollView::setContentOffsetInDuration(CCPoint offset, float dt)
{
	CCFiniteTimeAction *expire;

	CCActionInterval *scroll = CCMoveTo::create(dt, offset);
	expire = CCCallFuncN::create(this, callfuncN_selector(CGameScrollView::stoppedAnimatedScroll));
	m_pContainer->runAction(CCSequence::create(CCEaseSineIn::create(scroll), expire, NULL));
	this->schedule(schedule_selector(CGameScrollView::performedAnimatedScroll));
}
*/
