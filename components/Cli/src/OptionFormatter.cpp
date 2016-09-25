#include <Cli/OptionFormatter.h>

namespace cli {

std::string OptionFormatter::Describe(const std::string& app_name,
	const std::string& caption,
	boost::program_options::options_description desc,
	boost::program_options::positional_options_description* positionalDesc)
{
	OptionFormatter option_printer;
	for (const auto& option : desc.options())
	{
		option_printer.AddOption(Option(option, positionalDesc));
	}

	std::stringstream description;
	description << "Usage: " << app_name << " " << option_printer.Usage() << std::endl
				<< std::endl
				<< caption << std::endl
				<< std::endl
				<< option_printer.PositionalsDetails() << std::endl
				<< option_printer.ArgumentDetails() << std::endl;
	return description.str();
}

void OptionFormatter::AddOption(const Option& option)
{
	option.positional ? positional_options_.push_back(option) : options_.push_back(option);
}

std::string OptionFormatter::Usage()
{
	std::stringstream usage;
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
	return usage.str();
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

} //namespace cli
