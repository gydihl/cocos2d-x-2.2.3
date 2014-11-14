#include "AESCrypto.h"
#include "AES.h"

AESCrypto::AESCrypto()
{
	_pAES = NULL;
	unsigned char key[17] = "1234567980abcdef";
	resetKey(key, 16);
}

AESCrypto::~AESCrypto()
{
	CC_SAFE_DELETE(_pAES);
}

void AESCrypto::resetKey(unsigned char *key, unsigned int length /* = 16 */)
{
//	_strKey = key;
	if (!_pAES)
		_pAES = new AES;
	_pAES->resetKey(key);
}

// 加密函数应该不会用到游戏运行过程中
// 加密过程中涉及到了内存申请和是否
unsigned long AESCrypto::encode(unsigned char *&pBuff, unsigned long length)
{
	if (!_pAES || !pBuff || 0 == length)
		return length;
	const int count = 16;
	unsigned long bufSize = length;
	if (length % count > 0)
	{
		bufSize = count * (length / count + 1);
	}
	if (bufSize > length)
	{// 重新申请大内存
		unsigned char *pNewBuff = new unsigned char[bufSize];
		memset(pNewBuff, 0, bufSize);
		memcpy(pNewBuff, pBuff, length);
		delete []pBuff;
		pBuff = pNewBuff;
	}
	_pAES->encode(pBuff, bufSize);
	return bufSize;
}

unsigned long AESCrypto::decode(unsigned char *&pBuff, unsigned long length)
{
	if (!_pAES || !pBuff || 0 == length)
		return length;
	_pAES->decode(pBuff, length);

	while (0 == ((unsigned char*)pBuff)[length-1])
	{// 加密前不足16位，取消补充的0值
		--length;
	}
	return length;
}

