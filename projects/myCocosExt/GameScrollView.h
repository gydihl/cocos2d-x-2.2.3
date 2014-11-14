
#ifndef _GAME_SCROLL_VIEW_H_
#define _GAME_SCROLL_VIEW_H_

#include "cocos2d.h"
#include "cocos-ext.h"

// 校正滑动动画速度
#define ADJUST_ANIM_VELOCITY 2000

class CGameScrollViewDelegate
	: public cocos2d::extension::CCScrollViewDelegate
{
public:
	// 滚动触发
//	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) = 0;
	// 缩放触发
//	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) = 0;
	// 初始化每个单独页面,pPage为这个页面的容器,nPage是这个页面的ID
	virtual bool scrollViewInitPage(cocos2d::CCNode *pScroll, cocos2d::CCNode *pPage, int nPage) = 0;
	// 点击某个页面处理
	virtual void scrollViewClick(const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint , cocos2d::CCNode *pPage, int nPage ) = 0;
	// 每一次滑动开始是的回调
	virtual void scrollViewScrollBegin(cocos2d::CCNode *pPage, int nPage) = 0;
	// 滑动过程中的回调
	virtual void scrollViewScrolling(cocos2d::CCNode *pPage, int nPage) = 0;
	// 每一次滑动结束后的回调
	virtual void scrollViewScrollEnd(cocos2d::CCNode *pPage, int nPage) = 0;
	// 每一次滑动结束后，如果页数有改变的回调,可以在这里处理一些事情
	virtual void scrollViewEndChangePage(cocos2d::CCNode *pPage, int nPage) = 0;
};

class CGameScrollView
	: public cocos2d::extension::CCScrollView
{
public:
	CGameScrollView();
	~CGameScrollView();
public:
	CREATE_FUNC(CGameScrollView);

	bool init();

	bool createContainer(CGameScrollViewDelegate *pDele, int nCount, const cocos2d::CCSize &oSize );

//	void setContentOffsetInDuration(cocos2d::CCPoint offset, float dt); 

	virtual bool ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );

	virtual void ccTouchMoved( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );

	virtual void ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );

	virtual void ccTouchCancelled( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );

	virtual void setDirection(cocos2d::extension::CCScrollViewDirection eDirection);

	void setCurPage(int nPage);
	void scrollToPage(int nPage);
	void scrollToNextPage();
	void scrollToPrePage();
	int getPageCount();
	int getCurPage();
	CCNode *getPage(int nPage);

protected:
	void adjustScrollView(const cocos2d::CCPoint &oBegin, const cocos2d::CCPoint &oEnd);

	virtual void onScrollEnd(float fDelay);
protected:
	int m_nPageCount;
	int m_nPrePage;
	cocos2d::CCPoint m_BeginOffset;
	cocos2d::CCSize m_CellSize;
	float m_fAdjustSpeed;
	bool m_bSetDirection;
	int m_nCurPage;
};


#endif	// _GAME_SCROLL_VIEW_H_

