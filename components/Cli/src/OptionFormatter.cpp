#include <sstream>
#include <Cli/OptionFormatter.h>

namespace cli {

std::string OptionFormatter::Describe(const std::string& app_name,
	const std::string& caption,
	boost::program_options::options_description desc,
	boost::program_options::positional_options_description* positionals)
{
	OptionFormatter formatter(desc, positionals);
	std::stringstream description;
	description << formatter.Usage(app_name) << std::endl
				<< std::endl
				<< caption << std::endl
				<< std::endl
				<< formatter.PositionalsDetails() << std::endl
				<< formatter.ArgumentDetails() << std::endl;
	return description.str();
}

OptionFormatter::OptionFormatter(boost::program_options::options_description desc,
	boost::program_options::positional_options_description* positionals)
{
	for (const auto& option : desc.options())
	{
		AddOption(Option(option, positionals));
	}
}

std::string OptionFormatter::Usage(const std::string& app_name)
{
	std::stringstream usage;
	usage << "Usage: " << app_name << " ";
	usage << ShortOptionalOptions() << " ";
	for (auto& option : options_)
	{
		if (!option.has_short_name && !option.has_argument && !option.required)
		{
			usage << "[" << option.display_name << "] ";
		}
		if (option.has_argument && !option.required)
		{
			usage << "[" << option.display_name << " ARG] ";
		}
		if (option.has_argument && option.required)
		{
			usage << option.display_name << " ARG ";
		}
	}
	for (auto& option : positional_options_)
	{
		usage << option.display_name << " ";
	}
	auto usage_str = usage.str();
	usage_str.erase(usage_str.find_last_not_of(" ") + 1);
	return usage_str;
}

std::string OptionFormatter::ShortOptionalOptions()
{
	std::stringstream usage;
	for (auto& option : options_)
	{
		if (option.has_short_name && !option.has_argument && !option.required)
		{
			usage << option.display_name[1];
		}
	}
	auto short_options = usage.str();
	if (short_options.empty())
	{
		return short_options;
	}
	return "[-" + short_options + "]";
}

std::string OptionFormatter::PositionalsDetails()
{
	std::stringstream output;
	output << "Positional arguments:" << std::endl;
	for (auto& option : positional_options_)
	{
		output << option.Usage() << std::endl;
	}
	return output.str();
}

std::string OptionFormatter::ArgumentDetails()
{
	std::stringstream output;
	output << "Arguments:" << std::endl;
	for (auto& option : options_)
	{
		output << option.Usage() << std::endl;
	}
	return output.str();
}

void OptionFormatter::AddOption(const Option& option)
{
	option.positional ? positional_options_.push_back(option) : options_.push_back(option);
}

} //namespace cli
