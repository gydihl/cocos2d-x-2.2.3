#include "AssetLoader.h"
#include "json/json.h"
#include "ResourceInfo.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

AssetLoader::~AssetLoader()
{
	CC_SAFE_RELEASE_NULL(this->_fileDict);
	CC_SAFE_RELEASE_NULL(this->_texturePlistDict);
	CC_SAFE_RELEASE_NULL(this->_textureImageDict);
}

CCSprite* AssetLoader::createSprite(const char *szName)
{
	if (!szName)
		return NULL;

	eAssetType type = AssetLoader::getInstance()->loadTexture(szName);

	if (kAssetTypeLocal == type)
	{
		return CCSprite::create(szName);
	}
	else if (kAssetTypePlist == type)
	{
		return CCSprite::createWithSpriteFrameName(szName);
	}
	return NULL;
}

bool AssetLoader::initSprite(cocos2d::CCSprite *pSprite, const char *szName)
{
	if (!pSprite || !szName)
		return false;

	eAssetType type = AssetLoader::getInstance()->loadTexture(szName);

	if (kAssetTypeLocal == type)
	{
		return pSprite->initWithFile(szName);
	}
	else if (kAssetTypePlist == type)
	{
		return pSprite->initWithSpriteFrameName(szName);
	}
	return false;
}

CCScale9Sprite* AssetLoader::createScale9Sprite(const char *szName)
{
	if (!szName)
		return NULL;

	eAssetType type = AssetLoader::getInstance()->loadTexture(szName);

	if (kAssetTypeLocal == type)
	{
		return CCScale9Sprite::create(szName);
	}
	else if (kAssetTypePlist == type)
	{
		return CCScale9Sprite::createWithSpriteFrameName(szName);
	}
	return NULL;
}

void AssetLoader::loadImageViewTexture(cocos2d::ui::UIImageView *pImageView, const char *szFileName)
{
	if (!pImageView || !szFileName)
		return;

	eAssetType type = AssetLoader::getInstance()->loadTexture(szFileName);

	if (kAssetTypeLocal == type)
	{
		pImageView->loadTexture(szFileName, UI_TEX_TYPE_LOCAL);
	}
	else if (kAssetTypePlist == type)
	{
		pImageView->loadTexture(szFileName, UI_TEX_TYPE_PLIST);
	}
}

void AssetLoader::loadButtonTextures(cocos2d::ui::UIButton *pButton, const char* normal,const char* selected,const char* disabled)
{
	if (!pButton)
		return;
	if (normal && strcmp(normal, "") != 0)
	{// normal
		eAssetType type = AssetLoader::getInstance()->loadTexture(normal);
		if (kAssetTypeLocal == type)
			pButton->loadTextureNormal(normal, UI_TEX_TYPE_LOCAL);
		else if (kAssetTypePlist == type)
			pButton->loadTextureNormal(normal, UI_TEX_TYPE_PLIST);
	}
	if (selected && strcmp(selected, "") != 0)
	{// selected
		eAssetType type = AssetLoader::getInstance()->loadTexture(selected);
		if (kAssetTypeLocal == type)
			pButton->loadTexturePressed(selected, UI_TEX_TYPE_LOCAL);
		else if (kAssetTypePlist == type)
			pButton->loadTexturePressed(selected, UI_TEX_TYPE_PLIST);
	}
	if (disabled && strcmp(disabled, "") != 0)
	{// disabled
		eAssetType type = AssetLoader::getInstance()->loadTexture(disabled);
		if (kAssetTypeLocal == type)
			pButton->loadTextureDisabled(disabled, UI_TEX_TYPE_LOCAL);
		else if (kAssetTypePlist == type)
			pButton->loadTextureDisabled(disabled, UI_TEX_TYPE_PLIST);
	}
}

static AssetLoader *s_assetLoader = NULL;

AssetLoader* AssetLoader::getInstance()
{
	if (!s_assetLoader)
	{
		s_assetLoader = new AssetLoader;
		s_assetLoader->init();
	}
	return s_assetLoader;
}

bool AssetLoader::init()
{
	std::string strPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(sjs_file_list);

	unsigned long size = 0;
	unsigned char *pBytes = NULL;
	pBytes = CCFileUtils::sharedFileUtils()->getFileData(strPath.c_str(), "rb", &size);

	std::string strDoc = (const char*)pBytes;
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(strDoc, root))
		return false;

	Json::Value &fileName = root[file_name];
	Json::Value &fileIndex = root[file_index];

	Json::ArrayIndex length = fileName.size();
	this->_fileDict = CCDictionary::create();
	this->_fileDict->retain();
	for (Json::ArrayIndex i = 0; i < length; ++i)
	{
		_fileDict->setObject(CCString::create(fileIndex[i].asString()), fileName[i].asCString());
	}

	Json::Value &textureName = root[texture_name];
	Json::Value &texturePlist = root[texture_plist];
	Json::Value &textureImg = root[texture_image];
	_texturePlistDict = CCDictionary::create();
	this->_texturePlistDict->retain();
	_textureImageDict = CCDictionary::create();
	this->_textureImageDict->retain();
	length = textureName.size();
	for (Json::ArrayIndex i = 0; i < length; ++i)
	{
		_texturePlistDict->setObject(CCString::create(texturePlist[i].asString()), textureName[i].asCString());
		_textureImageDict->setObject(CCString::create(textureImg[i].asString()), textureName[i].asCString());
	}

	CC_SAFE_DELETE_ARRAY(pBytes);
	return true;
}

bool AssetLoader::fileExists(const std::string &file)
{
	return _fileDict->objectForKey(file) != NULL;
}

const char* AssetLoader::getTexturePlist(const std::string &name)
{
	CCObject* objPd = _texturePlistDict->objectForKey(name);
	if (objPd != NULL)
	{
		std::string tt_idx = dynamic_cast<CCString*>(objPd)->getCString();
		CCDictElement* de = NULL;
		CCDICT_FOREACH(_fileDict, de)
		{
			if (de != NULL)
			{
				CCString* str = dynamic_cast<CCString*>(de->getObject());
				if (str->getCString() == tt_idx)
				{
					return de->getStrKey();
				}
			}
		}
	}
	return NULL;
}

const char* AssetLoader::getTextureImage(const std::string &name)
{
	CCObject* obj = _textureImageDict->objectForKey(name);
	if (obj != NULL)
	{
		std::string image = dynamic_cast<CCString*>(obj)->getCString();
		CCDictElement* de = NULL;
		CCDICT_FOREACH(_fileDict, de)
		{
			if (de != NULL)
			{
				CCString* str = dynamic_cast<CCString*>(de->getObject());
				if (str->getCString() == image)
				{
					return de->getStrKey();
				}
			}
		}
	}
	return NULL;
}

eAssetType AssetLoader::loadTexture(const char *szFile)
{
	if (!szFile)
		return kAssetTypeNone;
	if (this->fileExists(szFile))
	{
		return kAssetTypeLocal;
	}
//	CCLOG("create sprite: %s", szName);
	const char *szPlistFile = this->getTexturePlist(szFile);
	const char *szImageFile = this->getTextureImage(szFile);
//	CCLOG("plist: %s, image: %s", plistfile.c_str(), imagefile.c_str());
	if (szPlistFile && szImageFile)
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(szPlistFile, szImageFile);
		return kAssetTypePlist;
	}

	return kAssetTypeNone;
}
