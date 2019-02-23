#pragma once
#include "cocos2d.h"
#include "iostream"

class XmlParser : public cocos2d::Ref, public cocos2d::SAXDelegator
{
	//声明返回数据属性
	CC_SYNTHESIZE(cocos2d::ValueVector, list, List);
private:
	std::string startElementName;
	cocos2d::ValueMap row;

public:
	
	bool initWithFile(const char* fileName) {
		cocos2d::SAXParser parser;
		if (!parser.init("UTF-8")) {
			cocos2d::log("Please use utf-8 format.");
			return false;
		}
		parser.setDelegator(this);
		auto sharedFileUtils = cocos2d::FileUtils::getInstance();
		std::string path = sharedFileUtils->fullPathForFilename(fileName);
		return parser.parse(path);
	}
	virtual void startElement(void * ctx, const char * name, const char ** atts) {
		CC_UNUSED_PARAM(ctx);
		startElementName = (char*)name;
		if (startElementName == "dict") {
			row = cocos2d::ValueMap();
			for (int i = 0; atts[i]; i += 2) {
				std::string key = (char*)atts[i + 1];
				std::string value = (char*)atts[i + 1];

				std::pair<std::string, cocos2d::Value> pair(key, cocos2d::Value(value));
				row.insert(pair);
			}
		}
	}
	virtual void endElement(void * ctx, const char * name) {
		CC_UNUSED_PARAM(ctx);
		std::string endElementName = (char*)name;
		if (endElementName == "dict") {
			list.push_back(cocos2d::Value(row));
		}
	}
	virtual void textHandler(void * ctx, const char * ch, int len) {
		CC_UNUSED_PARAM(ctx);
		std::string currentElementValue = std::string((char*)ch, 0, len);
		std::pair<std::string, cocos2d::Value> pair(startElementName, cocos2d::Value(currentElementValue));
		row.insert(pair);
	}

	static XmlParser * createWithFile(const char* fileName)
	{
		XmlParser* pRet = new XmlParser();
		if (pRet->initWithFile(fileName)) {
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
	
};