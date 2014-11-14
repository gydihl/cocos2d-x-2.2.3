/********************************************************************
	created:	2014/10/23
	filename: 	AESCrypto.h
	author:		底会雷
	purpose:	MyCrypto接口的实现
*********************************************************************/

#pragma once

#include "cocos2d.h"
#include "support/crypto/MyCrypto.h"

class AES;

class AESCrypto
	: public cocos2d::MyCrypto
{
public:
	AESCrypto();
	virtual ~AESCrypto();

public:
	/*
		@purpose:	加密函数
		@access:	virtual public 
		@param:		void * & pBuff (in/out) : 待加密的原始数据/加密后的数据
		@param:		unsigned long length (in) : pBuff的长度
		@return:	unsigned long 加密后数据的长度
	*/
	virtual unsigned long encode(unsigned char *&pBuff, unsigned long length);
	/*
		@purpose:	解密函数
		@access:	virtual public 
		@param:		void * & pBuff (in/out) : 待解密的数据/解密后的数据
		@param:		unsigned long length (in) : pBuff的长度
		@return:	unsigned long 解密后数据的长度
	*/
	virtual unsigned long decode(unsigned char *&pBuff, unsigned long length);
	/*
		@purpose:	设置密码key
		@access:	virtual public 
		@param:		unsigned char * key (in) : 密码
		@param:		unsigned int length (in) : 密码长度
		@return:	void 
	*/
	virtual void resetKey(unsigned char *key, unsigned int length = 16);

protected:
	AES *_pAES;
	std::string _strKey;
};
