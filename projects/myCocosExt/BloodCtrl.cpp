#include "BloodCtrl.h"
#include "GameInclude.h"

USING_NS_CC;

BloodCtrl* BloodCtrl::CreateCtrl()
{
	return BloodCtrl::create();
}

bool BloodCtrl::init()
{
	if (!CCLayer::init())
		return false;

	// 添加血条的背景图片
	m_pBloodBkImg =	AssetLoader::createSprite(si_monster_blood_frame);
	this->addChild(m_pBloodBkImg);
	// 添加进度条
	CCSprite *pBlood = AssetLoader::createSprite(si_monster_blood);
	this->m_pBloodCtrl = CCProgressTimer::create(pBlood);
	// 设置成横向的
	this->m_pBloodCtrl->setType(kCCProgressTimerTypeBar);
	// 可以看作是按矩形显示效果的进度条类型
	this->m_pBloodCtrl->setMidpoint(CCPointMake(0, 0));
	// 用来设定进度条横向前进的方向从左向右或是从右向左
	this->m_pBloodCtrl->setBarChangeRate(CCPointMake(1, 0));
	this->m_pBloodCtrl->setPercentage(100.0f);
	this->addChild(m_pBloodCtrl);

	return true;
}

void BloodCtrl::SetPosition(const cocos2d::CCPoint &position)
{
	if (m_pBloodBkImg)
	{
		m_pBloodBkImg->setPosition(position);
	}
	if (m_pBloodCtrl)
	{
		m_pBloodCtrl->setPosition(position);
	}
}

void BloodCtrl::SetPercentage(float fPercentage)
{
	if (!m_pBloodCtrl)
		return;
	m_pBloodCtrl->setPercentage(fPercentage);
}
