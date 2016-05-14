#pragma once

#include "..\PreDefs.h"
#include "..\Deserializer.h"

#include <map>
#include <string>
#include <vector>
#include <iosfwd>
#include <exception>

class ParseErrorException : public std::exception
{
public:
	ParseErrorException(const char*);
};

class FrameBuilder
{
public:
	virtual void Initialize(const std::string& filetext) = 0;
	virtual void FillFrames(std::vector<FramePtr>& frames) = 0;

	virtual const std::ostream& GetOutputLog() const = 0;

	FrameBuilder() = default;

	virtual ~FrameBuilder() = default;
};

typedef std::shared_ptr<FrameBuilder> FrameBuilderPtr;

FrameBuilderPtr CreateFrameBuilder(const std::string& version);
FrameBuilderPtr CreateFrameBuilder(const std::string& version, std::ostream& os);
