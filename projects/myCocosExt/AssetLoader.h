/********************************************************************
	created:	2014/06/19
	filename: 	AssetLoader.h
	author:		底会雷
	purpose:	
*********************************************************************/

#ifndef _RESMGR_ASSETLOADER_H_
#define _RESMGR_ASSETLOADER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

enum eAssetType
{
	kAssetTypeNone,
	kAssetTypeLocal,
	kAssetTypePlist,
};

class AssetLoader
	: public cocos2d::CCObject
{
protected:
	AssetLoader()		{}
	~AssetLoader();

public:
	static cocos2d::CCSprite* createSprite(const char *szName);
	static bool initSprite(cocos2d::CCSprite *pSprite, const char *szName);
	// CCScale9Sprite
	static cocos2d::extension::CCScale9Sprite* createScale9Sprite(const char *szName);
	// 加载UIImageView资源
	static cocos2d::ui::UIImageView* createUIImageView(const char *szFileName);
	static void loadImageViewTexture(cocos2d::ui::UIImageView *pImageView, const char *szFileName);
	// 加载UIButton资源
	static cocos2d::ui::UIButton* createUIButton(const char *normal, const char *selected, const char *disabled, 
		cocos2d::CCObject *target = NULL, cocos2d::ui::SEL_TouchEvent selector = NULL);
	static void loadButtonTextures(cocos2d::ui::UIButton *pButton, const char* normal,const char* selected,const char* disabled);
	
protected:
	static AssetLoader* getInstance();
	bool init();

	bool fileExists(const std::string &file);
	const char* getTexturePlist(const std::string& name);
	const char* getTextureImage(const std::string& name);

	eAssetType loadTexture(const char *szFile);

protected:
	cocos2d::CCDictionary *_fileDict;
	cocos2d::CCDictionary *_texturePlistDict;
	cocos2d::CCDictionary *_textureImageDict;
};

#endif	// _RESMGR_ASSETLOADER_H_
