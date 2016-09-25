#include <cstdlib>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <Cli/OptionFormatter.h>
#include <Cli/Options.h>

namespace cli {

Options::Options(int argc, char** argv)
{
	namespace bpo = boost::program_options;
	namespace bfs = boost::filesystem;

	const std::string caption = "Display diff alongside blame info";
	bpo::options_description desc(caption);

	// clang-format off
	desc.add_options()
		("help,h", "Display this help and exit")
		("path,p", bpo::value<std::string>(&repo_path_), "Git repository path. Default: current working directory")
		("commit-from", bpo::value<std::string>(&commit_from_)->required(), "Review start commit")
		("commit-to", bpo::value<std::string>(&commit_to_), "Review final commit. Default: HEAD");
	// clang-format on

	bpo::positional_options_description positionals;
	positionals.add("commit-from", 1);
	positionals.add("commit-to", 1);

	bpo::variables_map vm;
	try
	{
		bpo::parsed_options parsed_options =
			bpo::command_line_parser(argc, argv).options(desc).positional(positionals).run();
		store(parsed_options, vm);
		if (vm.count("help"))
		{
			std::string app_name = bfs::basename(argv[0]);
			std::cout << OptionFormatter::Describe(app_name, caption, desc, &positionals);
			exit(EXIT_SUCCESS);
		}
		notify(vm);
	}
	catch (bpo::required_option& err)
	{
		FormatRequiredOptionError(err);
		throw OptionParseError(err.what());
	}
	catch (bpo::error& err)
	{
		throw OptionParseError(err.what());
	}

	if (!vm.count("path"))
	{
		repo_path_ = bfs::initial_path().string();
	}

	if (!vm.count("commit-from"))
	{
		throw OptionParseError("commit-from is required");
	}
	if (!vm.count("commit-to"))
	{
		commit_to_ = "HEAD";
	}
}

std::string Options::RepoPath() const
{
	return repo_path_;
}

std::string Options::CommitFrom() const
{
	return commit_from_;
}

std::string Options::CommitTo() const
{
	return commit_to_;
}

void Options::FormatRequiredOptionError(boost::program_options::required_option& error)
{
	std::string option_name = error.get_option_name();
	option_name.erase(0, option_name.find_first_not_of('-'));
	error.set_option_name(option_name);
}

//////////////////////////////////////////////////////////////////////////////

OptionParseError::OptionParseError(const std::logic_error& err)
: std::logic_error(err)
{
}

OptionParseError::OptionParseError(const std::string& message)
: std::logic_error(message)
{
}

} //namespace cli
