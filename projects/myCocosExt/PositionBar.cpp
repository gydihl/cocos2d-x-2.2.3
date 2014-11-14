#include "PositionBar.h"
#include "Common/VisibleRect.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;

PositionBar::PositionBar(void)
{
}

PositionBar::~PositionBar(void)
{
}

PositionBar* PositionBar::CreateBar(const char* bottomImagename,const char* frontImagename,int length, int position)
{
	PositionBar *pRet = new PositionBar(); 	

	if (pRet && pRet->init(bottomImagename, frontImagename,length, position)) 
	{ 
		pRet->autorelease(); 
		return pRet;//->init(bottomImagename, frontImagename,length, position); 
	} 
	else
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}

bool PositionBar::init(const char* bottomImagename, const char* frontImagename, int length, int position)
{
	if (!CCLayer::create())
		return false;

	CCPoint ptCenter = VisibleRect::center();

	slider = UISlider::create();
	slider->setTouchEnabled(false);
	slider->loadBarTexture(bottomImagename);
	slider->setScaleX(length / slider->getSize().width);
	slider->setScaleY(length / slider->getSize().width);
	slider->loadProgressBarTexture(frontImagename);
	slider->setPercent(position);

	this->addChild(slider);
	//return slider;
	return true;
}

bool PositionBar::setPercent(int position)
{
	slider->setPercent(position);
	return true;
}
