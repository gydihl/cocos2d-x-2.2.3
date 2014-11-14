#include "GladmanAESCrypto.h"
#include "GladmanAES.h"

GladmanAESCrypto::GladmanAESCrypto()
{
	_pAES = NULL;
	unsigned char key[65] = "6bead6bf16b9d120fde23bc36e8fbc046bead6bf16b9d120fde23bc36e8fbc04";
	resetKey(key, 64);
}

GladmanAESCrypto::~GladmanAESCrypto()
{
	CC_SAFE_DELETE(_pAES);
}

void GladmanAESCrypto::resetKey(unsigned char *key, unsigned int length /* = 16 */)
{
//	_strKey = key;
	if (!_pAES)
		_pAES = new GladmanAES;
	_pAES->setkey(key, length);
}

// 加密函数应该不会用到游戏运行过程中
// 加密过程中涉及到了内存申请和释放
unsigned long GladmanAESCrypto::encode(unsigned char *&pBuff, unsigned long length)
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
	bufSize =_pAES->encode((unsigned char*)pBuff, bufSize, (unsigned char*)pBuff);
	return bufSize;
}

unsigned long GladmanAESCrypto::decode(unsigned char *&pBuff, unsigned long length)
{
	if (!_pAES || !pBuff || 0 == length)
		return length;
	length = _pAES->decode((unsigned char*)pBuff, length, (unsigned char*)pBuff);
	
	while (0 == ((unsigned char*)pBuff)[length-1])
	{// 加密前不足16位，取消补充的0值
		--length;
	}
	
	return length;
}

