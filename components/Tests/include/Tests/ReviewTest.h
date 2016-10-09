#pragma once
#include <memory>
#include <string>
#include <Review/DiffModel.h>
#include <gtest/gtest.h>

namespace tests {

class ReviewTest : public ::testing::Test
{
protected:
	ReviewTest();

	std::string repo_path_;
	std::unique_ptr<review::DiffModel> file_added_;
};

} // namespace tests
