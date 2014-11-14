/********************************************************************
	created:	2014/05/21
	filename: 	PositionBar.h
	author:		全晓洲
	purpose:	显示人物在地图中的位置比例
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

//USING_NS_CC;
//USING_NS_CC_EXT;
//using namespace ui;

class PositionBar : public cocos2d::CCLayer
{
public:
	PositionBar(void);
	~PositionBar(void);
	static PositionBar* CreateBar(const char* bottomImagename,const char* frontImagename,int length, int position);
//	virtual UISlider* init(char imagename[],int length, int position);  
	virtual bool init(const char* bottomImagename, const char* frontImagename, int length, int position);
	bool setPercent(int position);

protected:
	cocos2d::ui::UILayer* m_pUiLayer;
	cocos2d::ui::UISlider* slider;
};


