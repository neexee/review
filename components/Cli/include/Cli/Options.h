#pragma once
#include <stdexcept>
#include <string>
#include <boost/program_options.hpp>
namespace cli {

class Options
{
public:
	Options(int argc, char** argv);
	std::string RepoPath() const;
	std::string CommitFrom() const;
	std::string CommitTo() const;

private:
	void FormatRequiredOptionError(boost::program_options::required_option& error);

	std::string repo_path_;
	std::string commit_from_;
	std::string commit_to_;
};

class OptionParseError : public std::logic_error
{
public:
	OptionParseError(const std::logic_error& err);
	OptionParseError(const std::string& message);
};

} // namespace cli
