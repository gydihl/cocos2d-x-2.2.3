/********************************************************************
	created:	2014/09/21
	filename: 	SingletonNode.h
	author:		底会雷
	purpose:	单例Node
*********************************************************************/

#pragma once

#include "cocos2d.h"
#include "Singleton.h"

template <typename T>
class SingletonNode
	: public cocos2d::CCNode
	, public Singleton<T>
{
	friend class Singleton<SingletonNode>;

protected:
	SingletonNode() {};
	virtual bool init();

public:
	virtual void addToParent(cocos2d::CCNode *pParent);
};

template <typename T>
bool SingletonNode<T>::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCNode::init());
		CC_SAFE_RETAIN(this);

		bRet = true;
	} while (0);
	return bRet;
}

template <typename T>
void SingletonNode<T>::addToParent(CCNode *pParent)
{
	this->removeFromParent();
	if (pParent)
		pParent->addChild(this);
}
