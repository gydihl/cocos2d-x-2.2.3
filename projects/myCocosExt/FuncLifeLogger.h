/********************************************************************
	created:	2014/07/09
	filename: 	FuncLifeLogger.h
	author:		底会雷
	purpose:	测量函数的生命周期
*********************************************************************/

#pragma once

#include "cocos2d.h"

class CFuncLifeLogger
{
public:
	CFuncLifeLogger();
	CFuncLifeLogger(const std::string &msg);

	~CFuncLifeLogger();

protected:
	std::string _strMsg;					// 函数信息
	struct cocos2d::cc_timeval _tmBegin;	// 开始时间
};

#ifdef _DEBUG
#define LOG_FUNC_LIFE_TIMER		CFuncLifeLogger __log__(__FUNCTION__)
#else
#define LOG_FUNC_LIFE_TIMER		
#endif


