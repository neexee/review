#include <string>
#include <vector>
#include <Tests/UtilsTest.h>
#include <Utils/Utils.h>

namespace tests {

UtilsTest::UtilsTest()
{
}

TEST_F(UtilsTest, SplitPathSimleSplit)
{
	std::string input = "some_dir/any_file.cpp";
	std::vector<std::string> expected_result{"some_dir", "any_file.cpp"};
	auto result = utils::SplitPath(input);
	EXPECT_EQ(result, expected_result);
}

} // namespace tests
