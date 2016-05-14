#include "Frame.h"
#include "parsers\FrameBuilder.h"
#include <iostream>
#include <fstream>

char v[] = "version 0.1";

int main(int argc, char** argv)
{
	try
	{
		if (argc < 2)
		{
			std::cout << "usage: specrel <input file>" << std::endl;
			return 1;
		}

		FrameBuilderPtr builder = CreateFrameBuilder("0.1", std::cout);

		std::string buffer;
		{
			std::ifstream t(argv[1]);
			t.seekg(0, std::ios::end);
			size_t size = t.tellg();
			buffer.resize(size);
			t.seekg(0);
			t.read(&buffer[0], size);
		}

		builder->Initialize(buffer);

		std::vector<FramePtr> frames;
		builder->FillFrames(frames);

		FramePtr frame = frames[0];

		frame->TraceFrame();

		frame->Save("output.bmp");

		return 0;
	}
	catch (ParseErrorException e)
	{
		return 1;
	}
}
