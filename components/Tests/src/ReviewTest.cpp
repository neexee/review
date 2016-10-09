#include <algorithm>
#include <string>
#include <type_traits>
#include <vector>

#include <boost/filesystem.hpp>

#include <Review/Application.h>
#include <Tests/ReviewTest.h>

namespace tests {

namespace {
const std::string file_addition_parent = "8f5a9de";
const std::string file_addition = "4f4e729";
}

ReviewTest::ReviewTest()
: repo_path_(boost::filesystem::current_path().c_str())
, file_added_(
	  std::make_unique<review::DiffModel>(file_addition_parent, file_addition, repo_path_))
{
}

TEST_F(ReviewTest, WrongCommitsOrRepoPath)
{
	ASSERT_THROW(review::DiffModel(file_addition_parent, file_addition, "/"), git::GitError);
	ASSERT_THROW(review::DiffModel("", file_addition, repo_path_), git::GitError);
	ASSERT_THROW(review::DiffModel(file_addition_parent, "", repo_path_), git::GitError);
}
TEST_F(ReviewTest, PathGeneration)
{
	auto paths = file_added_->Paths();
	ASSERT_EQ(paths.size(), 1);
	auto path = paths[0];
	ASSERT_EQ(path.toStdString(), "Test/Sample.txt");
}

TEST_F(ReviewTest, DeltaGeneration)
{
	auto deltas = file_added_->Deltas();
	ASSERT_EQ(deltas.size(), 1);
}

TEST_F(ReviewTest, DeltaInfo)
{
	auto deltas = file_added_->Deltas();
	auto delta = static_cast<review::DiffDelta*>(deltas[0]);
	ASSERT_EQ(delta->Path().toStdString(), "Test/Sample.txt");
	ASSERT_GE(delta->rowCount(), 0);
	ASSERT_EQ(delta->columnCount(), 3);
}

TEST_F(ReviewTest, DeltaLineTypes)
{
	using LineType = std::underlying_type<review::DiffLine::LineType>::type;
	auto deltas = file_added_->Deltas();
	auto delta = static_cast<review::DiffDelta*>(deltas[0]);

	ASSERT_GE(delta->rowCount(), 0);

	unsigned int row_count = delta->rowCount();
	std::vector<LineType> expected_line_types(row_count, review::DiffLine::Addition);
	std::vector<LineType> line_types;

	std::vector<LineType> expected_line_numbers(row_count);
	std::iota(expected_line_numbers.begin(), expected_line_numbers.end(), 0);
	for (int i = 0; i < row_count; i++)
	{
		auto line = delta->Line(i).value<review::DiffLine*>();
		line_types.push_back(line->GetLineType());
	}
	ASSERT_EQ(expected_line_types, line_types);
}

TEST_F(ReviewTest, DeltaLineNumbers)
{
	auto deltas = file_added_->Deltas();
	auto delta = static_cast<review::DiffDelta*>(deltas[0]);

	ASSERT_GE(delta->rowCount(), 0);

	unsigned int row_count = delta->rowCount();

	std::vector<int> expected_line_numbers(row_count);
	std::iota(expected_line_numbers.begin(), expected_line_numbers.end(), 1);

	std::vector<int> line_numbers;
	for (int i = 0; i < row_count; i++)
	{
		auto line = delta->Line(i).value<review::DiffLine*>();
		line_numbers.push_back(line->LineNumber());
	}
	ASSERT_EQ(expected_line_numbers, line_numbers);
}

TEST_F(ReviewTest, DeltaLineCommits)
{
	auto deltas = file_added_->Deltas();
	auto delta = static_cast<review::DiffDelta*>(deltas[0]);

	ASSERT_GE(delta->rowCount(), 0);

	unsigned int row_count = delta->rowCount();

	std::vector<std::string> line_commits;

	for (int i = 0; i < row_count; i++)
	{
		auto line = delta->Line(i).value<review::DiffLine*>();
		line_commits.push_back(line->GetCommit()->ShortHex().toStdString());
	}
	auto commit_hex = line_commits[0];
	ASSERT_EQ(commit_hex, file_addition);

	std::vector<std::string> expected_line_commits(row_count, commit_hex);

	ASSERT_EQ(expected_line_commits, line_commits);

	auto commit = delta->Line(0).value<review::DiffLine*>()->GetCommit();
	ASSERT_EQ("Add sample commit for testing", commit->Summary().toStdString());
}

TEST_F(ReviewTest, ModelLoads)
{
	std::vector<const char*> argv = {
		"review", file_addition_parent.c_str(), file_addition.c_str()};
	review::Application application{
		static_cast<int>(argv.size()), const_cast<char**>(argv.data())};
	application.Init();
	auto review = application.Review();
	auto diff_model = review->Diff();
	auto paths = diff_model->Paths();

	ASSERT_EQ(paths.size(), 1);
	auto path = paths[0];
	ASSERT_EQ(path.toStdString(), "Test/Sample.txt");
}

} // namespace tests
