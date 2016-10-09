#pragma once
#include <string>
#include <boost/program_options.hpp>
#include "Option.h"

namespace cli {

class OptionFormatter
{
public:
	static std::string Describe(const std::string& app_name,
		const std::string& caption,
		boost::program_options::options_description desc,
		boost::program_options::positional_options_description* positionals = nullptr);

	OptionFormatter(boost::program_options::options_description desc,
		boost::program_options::positional_options_description* positionals = nullptr);

	std::string Usage(const std::string& app_name);
	std::string PositionalsDetails();
	std::string ArgumentDetails();
	std::string ShortOptionalOptions();

private:
	void AddOption(const Option& option);

	std::vector<Option> options_;
	std::vector<Option> positional_options_;
};

} // namespace cli
