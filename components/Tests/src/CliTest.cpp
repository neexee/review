#include <string>
#include <vector>
#include <boost/filesystem.hpp>

#include <Cli/OptionFormatter.h>
#include <Cli/Options.h>
#include <Tests/CliTest.h>

namespace tests {

CliTest::CliTest()
: repo_path_(boost::filesystem::current_path().c_str())
{
}

TEST_F(CliTest, NormalRun)
{
	std::vector<const char*> argv = {"executable-name", "-p", "/", "master", "feature-branch"};
	auto options = cli::Options(argv.size(), const_cast<char**>(argv.data()));
	ASSERT_EQ("master", options.CommitFrom());
	ASSERT_EQ("feature-branch", options.CommitTo());
	ASSERT_EQ("/", options.RepoPath());
}

TEST_F(CliTest, NormalRunNoCommitTo)
{
	std::vector<const char*> argv = {"executable-name", "-p", "/", "master"};
	auto options = cli::Options(argv.size(), const_cast<char**>(argv.data()));
	ASSERT_EQ("master", options.CommitFrom());
	ASSERT_EQ("HEAD", options.CommitTo());
	ASSERT_EQ("/", options.RepoPath());
}

TEST_F(CliTest, NormalRunNoPath)
{
	std::vector<const char*> argv = {"executable-name", "master"};
	auto options = cli::Options(argv.size(), const_cast<char**>(argv.data()));
	ASSERT_EQ(repo_path_, options.RepoPath());
}

TEST_F(CliTest, NoStartCommit)
{
	std::vector<const char*> argv = {"executable-name"};
	ASSERT_THROW(
		cli::Options(argv.size(), const_cast<char**>(argv.data())), cli::OptionParseError);
}

TEST_F(CliTest, RandomOption)
{
	std::vector<const char*> argv = {"executable-name", "-s", "file"};
	ASSERT_THROW(
		cli::Options(argv.size(), const_cast<char**>(argv.data())), cli::OptionParseError);
}

TEST_F(CliTest, UsualHelpRun)
{
	namespace bpo = boost::program_options;
	namespace bfs = boost::filesystem;

	bpo::options_description desc("");

	std::string empty;
	// clang-format off
	desc.add_options()
	("help,h", "Display help")
	("path,p", bpo::value<std::string>(&empty), "Repository path.")
	("commit-from", bpo::value<std::string>(&empty)->required(), "Start commit")
	("commit-to", bpo::value<std::string>(&empty), "Final commit");
	// clang-format on

	bpo::positional_options_description positionals;
	positionals.add("commit-from", 1);
	positionals.add("commit-to", 1);

	auto formatter = cli::OptionFormatter(desc, &positionals);
	ASSERT_EQ(
		"Usage: appname [-h] [-p ARG] commit-from commit-to", formatter.Usage("appname"));
	ASSERT_EQ("[-h]", formatter.ShortOptionalOptions());
	ASSERT_EQ("Positional arguments:\n\tcommit-from         \tStart commit\n\tcommit-to       "
			  "    \tFinal commit\n",
		formatter.PositionalsDetails());
	ASSERT_EQ("Arguments:\n\t-h [ --help ]       \tDisplay help\n\t-p [ --path ]       "
			  "\tRepository path.\n",
		formatter.ArgumentDetails());
}

} // namespace tests
