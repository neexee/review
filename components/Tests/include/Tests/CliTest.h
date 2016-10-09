#pragma once
#include <gtest/gtest.h>

namespace tests {

class CliTest : public ::testing::Test
{
protected:
	CliTest();

	std::string repo_path_;
};

} // namespace tests
