#include "gincu/gspritesheet.h"
#include "gincu/gerrorhandler.h"
#include "gincu/gresourcemanager.h"
#include "gincu/ginputstream.h"
#include "gincu/gapplication.h"
#include "cpgf/goutmain.h"

#include <cstring>

namespace gincu {

GImage GSpriteSheetData::getImage(const std::string & name) const
{
	auto it = this->indexMap.find(name);
	if(it != this->indexMap.end()) {
		return GImage(this->imageData, this->rectList[it->second]);
	}
	else {
		return GImage();
	}
}

int GSpriteSheetData::getIndex(const std::string & name) const
{
	auto it = this->indexMap.find(const_cast<std::string &>(name));
	if(it != this->indexMap.end()) {
		return it->second;
	}
	else {
		return -1;
	}
}

void GSpriteSheetData::load(const std::string & resourceName, const GSpriteSheetFormat format)
{
	const GSpriteSheet::LoaderMap * loaderMap = GSpriteSheet::getLoaderMap();
	auto it = loaderMap->find(format);
	if(it == loaderMap->end()) {
		handleFatal("Can't find sprite sheet loader.");
		return;
	}

	it->second(resourceName,this);

	this->imageData = GResourceManager::getInstance()->getImage(this->imageName).getData();

	for(std::size_t i = 0; i < this->nameList.size(); ++i) {
		this->indexMap.insert(std::make_pair(std::reference_wrapper<const std::string>(this->nameList[i]), i));
	}
}

void GSpriteSheetData::appendSubImage(const std::string & name, const GRect & rect)
{
	this->nameList.push_back(name);
	this->rectList.push_back(rect);
}

void GSpriteSheetData::setImageName(const std::string & imageName)
{
	this->imageName = imageName;
}

GSpriteSheet::LoaderMap * GSpriteSheet::getLoaderMap()
{
	static LoaderMap loaderMap;
	
	return &loaderMap;
}

void GSpriteSheet::registerLoader(const GSpriteSheetFormat format, const LoaderCallback & loader)
{
	getLoaderMap()->insert(std::make_pair(format, loader));
}

GSpriteSheet::GSpriteSheet()
{
}

GSpriteSheet::GSpriteSheet(const std::shared_ptr<GSpriteSheetData> & data)
	: data(data)
{
}


char * skipSpaces(char * p, char * end)
{
	while(p < end && isspace(*p)) {
		++p;
	}

	return p;
}

char * backSkipSpaces(char * p, char * begin)
{
	while(p > begin && isspace(*p)) {
		--p;
	}

	return p;
}

std::string getNextToken(char * & buffer, char * end, const char delimiter)
{
	buffer = skipSpaces(buffer, end);
	char * p = buffer;
	while(p < end && *p != delimiter) {
		++p;
	}

	if(p == buffer) {
		return std::string();
	}

	char * tokenEnd = backSkipSpaces(p - 1, buffer);
	std::string result(buffer, tokenEnd + 1 - buffer);
	buffer = p + 1;
	return result;
}

void spriteSheetLoader_spritePackText(const std::string & resourceName, GSpriteSheetData * spriteSheet)
{
	spriteSheet->setImageName(resourceName + ".png");
	
	GFileInputStream stream = GResourceManager::getInstance()->getFileStream(resourceName + ".txt");
	
	const std::size_t size = (std::size_t)stream.getSize();
	std::unique_ptr<char[]> buffer(new char[size + 2]);
	stream.read(buffer.get(), size);
	buffer[size] = '\n';
	buffer[size + 1] = 0;

	char * bufferEnd = buffer.get() + size;

	char * ptr = buffer.get();
	for(;;) {
		ptr = skipSpaces(ptr, bufferEnd);
		if(ptr >= bufferEnd) {
			break;
		}

		char * endLine = strchr(ptr, '\n');
		if(endLine == nullptr) {
			break;
		}

		for(;;) {
			const std::string resourceName = getNextToken(ptr, endLine, '=');
			if(resourceName.empty()) break;
			const std::string x = getNextToken(ptr, endLine, ' ');
			if(x.empty()) break;
			const std::string y = getNextToken(ptr, endLine, ' ');
			if(y.empty()) break;
			const std::string width = getNextToken(ptr, endLine, ' ');
			if(width.empty()) break;
			const std::string height = getNextToken(ptr, endLine, ' ');
			if(height.empty()) break;

			spriteSheet->appendSubImage(resourceName, GRect{
				(GCoord)std::stoi(x),
				(GCoord)std::stoi(y),
				(GCoord)std::stoi(width),
				(GCoord)std::stoi(height),
			});

			break;
		}

		ptr = endLine + 1;
	}
}

G_AUTO_RUN_BEFORE_MAIN()
{
	GSpriteSheet::registerLoader(GSpriteSheetFormat::spritePackText, &spriteSheetLoader_spritePackText);
}


} //namespace gincu

