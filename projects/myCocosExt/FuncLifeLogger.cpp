#include "FuncLifeLogger.h"
#include "Common/UnitKit.h"

USING_NS_CC;

CFuncLifeLogger::CFuncLifeLogger()
{

}

CFuncLifeLogger::CFuncLifeLogger(const std::string &msg)
	: _strMsg(msg)
{
	CCTime::gettimeofdayCocos2d(&_tmBegin, NULL);
	CCLOG("%s BEGIN at: %f!", _strMsg.c_str(), UnitKit::timeToSecond(this->_tmBegin));
}

CFuncLifeLogger::~CFuncLifeLogger()
{
	cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	CCLOG("%s END at: %f! after %f second", _strMsg.c_str(), UnitKit::timeToSecond(now), UnitKit::timeToSecond(now)-UnitKit::timeToSecond(_tmBegin));
}

