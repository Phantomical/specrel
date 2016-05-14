
#include "FrameBuilder.h"

// Parser versions (Add includes here when new versions are created)
#include "parser-v0.1\GrammarFrameBuilder.h"

#include <iostream>

typedef FrameBuilderPtr(*FactoryFunc)(std::ostream&);
typedef std::map<std::string, FactoryFunc> FactoryMapType;

FactoryMapType CreateFactoryMap()
{
	FactoryMapType map;

	// Add new parser creation functions here for each version
	map["0.1"] = &grammar_v0_1::CreateFrameBuilder;

	return map;
}

FactoryMapType FactoryMap = CreateFactoryMap();

FrameBuilderPtr CreateFrameBuilder(const std::string& version)
{
	return CreateFrameBuilder(version, std::cout);
}
FrameBuilderPtr CreateFrameBuilder(const std::string& version, std::ostream& os)
{
	auto it = FactoryMap.find(version);

	if (it == FactoryMap.end())
		return nullptr;

	return it->second(os);
}

ParseErrorException::ParseErrorException(const char* msg) :
	exception(msg)
{

}
