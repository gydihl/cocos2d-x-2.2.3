/********************************************************************
	created:	2014/09/13
	filename: 	Singleton.h
	author:		底会雷
	purpose:	单例模板
*********************************************************************/

#pragma once

template <typename T>
class Singleton
{
protected:
	Singleton() {}
	virtual bool init();

public:
	// 获得单例对象
	static T* getInstance();
	// 释放单例对象
	void freeInstance();

protected:
	static T *_pInstance;
};

template <typename T>
T* Singleton<T>::_pInstance = NULL;

template <typename T>
bool Singleton<T>::init()
{
	bool bRet = false;
	do 
	{
		
		bRet = true;
	} while (0);
	return bRet;
}

template <typename T>
T* Singleton<T>::getInstance()
{
	if (!_pInstance)
	{
		_pInstance = new T();
		_pInstance->init();
	}
	return _pInstance;
}

template <typename T>
void Singleton<T>::freeInstance()
{
	if (_pInstance)
	{
		delete _pInstance;
		_pInstance = NULL;
	}
}

