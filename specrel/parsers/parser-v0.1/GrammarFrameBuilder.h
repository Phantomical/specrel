#pragma once

#include "..\FrameBuilder.h"

namespace grammar_v0_1
{
	class GrammarFrameBuilder : public FrameBuilder
	{
	private:
		std::vector<TypeInfo> Types;
		std::ostream& OutputLog;
		std::vector<const char*> Strings;

	public:
		void Initialize(const std::string& filetext);
		void FillFrame(FramePtr frame);
		void FillFrames(std::vector<FramePtr>& frames);

		const std::ostream& GetOutputLog() const;

		// Initializes the output log to std::cout
		GrammarFrameBuilder();
		// Initializes the output log with the given std::ostream
		GrammarFrameBuilder(std::ostream&);
		// Initializes the output log with the given std::ostream
		// and automatically calls Initialize with the given file
		GrammarFrameBuilder(std::ostream&, const std::string& filetext);

		~GrammarFrameBuilder();
	};

	FrameBuilderPtr CreateFrameBuilder(std::ostream& os);
}
