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
		boost::program_options::positional_options_description* positionals = 0);

private:
	void AddOption(const Option& option);
	std::string Usage();
	std::string PositionalsDetails();
	std::string ArgumentDetails();
	std::string ShortOptionalOptions();

	std::vector<Option> options_;
	std::vector<Option> positional_options_;
};

} // namespace cli
