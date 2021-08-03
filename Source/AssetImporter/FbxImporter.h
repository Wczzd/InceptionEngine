#pragma once


#include <string>

namespace inceptionengine::fbximport
{
	float constexpr SampleRate = 30.0f;

	void Import(std::string const& filePath, std::string const& outputFolder);

}