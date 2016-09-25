#pragma once
#include <string>
#include <boost/program_options.hpp>

namespace cli {

struct Option
{
	Option(boost::shared_ptr<boost::program_options::option_description> option,
		const boost::program_options::positional_options_description* positionals);

	std::string Usage();

	std::string id;
	std::string display_name;
	std::string description;
	std::string format_name;

	bool required;
	bool has_short_name;
	bool has_argument;
	bool positional;
};

} // namespace cli
