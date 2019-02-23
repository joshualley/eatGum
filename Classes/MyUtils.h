#include "iostream"
#include "Windows.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;
using namespace std;
USING_NS_CC;

class MyUtils {
public:
	MyUtils(){}
	~MyUtils(){}
	static string gbk2utf8(const string text) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		wstring tes = [ = ]() {
			setlocale(LC_ALL, "chs");
			const char* _Source = text.c_str();
			size_t _Dsize = text.size() + 1;
			wchar_t * _Dest = new wchar_t[_Dsize];
			wmemset(_Dest, 0, _Dsize);
			std::wstring result = _Dest;
			delete[] _Dest;
			setlocale(LC_ALL, "C");
			return result;
		}();
		int asciSize = WideCharToMultiByte(CP_UTF8, 0, tes.c_str(), tes.size(), 
										NULL, 0, NULL, NULL);
		log("asciSize: %d", asciSize);
		log("tesSize: %d", tes.size());
		log("textSize: %d", text.size());
		if (asciSize == ERROR_NO_UNICODE_TRANSLATION || asciSize == 0) {
			return string();
		}
		char* resultString = new char[asciSize];
		int conveResult = WideCharToMultiByte(CP_UTF8, 0, tes.c_str(), tes.size(), 
											resultString, asciSize, NULL, NULL);
		if (conveResult != asciSize) {
			return string();
		}
		string buffer = "";
		buffer.append(resultString, asciSize);
		delete[] resultString;
		return buffer;
#else
		return text;
#endif
	}

	static void parserXml(const char* filename, ValueMap &vmap) {
		string filePath = FileUtils::getInstance()->fullPathForFilename(filename);
		log(filePath.c_str());
		tinyxml2::XMLDocument* pDoc = new tinyxml2::XMLDocument();
		tinyxml2::XMLError errorId = pDoc->LoadFile(filePath.c_str());
		//log("errorid: %d", errorId);
		
		if (errorId != 0)return;

		tinyxml2::XMLElement * rootElem = pDoc->RootElement();
		tinyxml2::XMLElement* dictElem = rootElem->FirstChildElement();
		
		while (dictElem) {
			tinyxml2::XMLElement* key = dictElem->FirstChildElement();
			//log("attribute_name = %s,attribute_value = %s", key->Name(), key->GetText());
			tinyxml2::XMLElement* value = key->NextSiblingElement();
			//log("attribute_name = %s,attribute_value = %s", value->Name(), value->GetText());
			vmap[key->GetText()] = Value(value->GetText());
			dictElem = dictElem->NextSiblingElement();
		}
	}

};