/********************************************************************
	created:	2014/10/23
	filename: 	MyCrypto.h
	author:		底会雷
	purpose:	加密解密基类
*********************************************************************/

#pragma once

#include "CCPlatformDefine.h"
#include "platform/CCPlatformConfig.h"

NS_CC_BEGIN

class MyCrypto
{
public:
	/*
		@purpose:	加密函数
		@access:	virtual public 
		@param:		void * & pBuff (in/out) : 待加密的原始数据/加密后的数据
		@param:		unsigned long length (in) : pBuff的长度
		@return:	unsigned long 加密后数据的长度
	*/
	virtual unsigned long encode(unsigned char *&pBuff, unsigned long length) = 0;
	/*
		@purpose:	解密函数
		@access:	virtual public 
		@param:		void * & pBuff (in/out) : 待解密的数据/解密后的数据
		@param:		unsigned long length (in) : pBuff的长度
		@return:	unsigned long 解密后数据的长度
	*/
	virtual unsigned long decode(unsigned char *&pBuff, unsigned long length) = 0;
	/*
		@purpose:	设置密码key
		@access:	virtual public 
		@param:		unsigned char * key (in) : 密码
		@param:		unsigned int length (in) : 密码长度
		@return:	void 
	*/
	virtual void resetKey(unsigned char *key, unsigned int length = 16) = 0;
};

NS_CC_END