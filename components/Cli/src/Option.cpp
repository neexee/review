#include <iomanip>
#include <Cli/Option.h>

namespace cli {

namespace {
// See http://www.boost.org/doc/libs/1_58_0/doc/html/boost/program_options/option_description.html#idp202461808-bb
const size_t PREFIXED_SHORT_NAME = 0;
const size_t PREFIXED_LONG_NAME = 1;
const size_t UNPREFIXED_NAME = 4;

const size_t SHORT_NAME_LENGTH = 2; // -x
const size_t ADEQUATE_NAME_LENGTH = 20;

} // namespace

Option::Option(boost::shared_ptr<boost::program_options::option_description> option,
	const boost::program_options::positional_options_description* positionals)
: required(false)
, has_short_name(false)
, has_argument(false)
, positional(false)
{
	if ((option->canonical_display_name(UNPREFIXED_NAME).size() == SHORT_NAME_LENGTH))
	{
		has_short_name = true;
		id = option->canonical_display_name(UNPREFIXED_NAME);
		display_name = option->canonical_display_name(UNPREFIXED_NAME);
	}
	else
	{
		has_short_name = false;
		id = option->canonical_display_name(PREFIXED_SHORT_NAME);
		display_name = option->canonical_display_name(PREFIXED_LONG_NAME);
	}

	const auto& semantic = option->semantic();
	required = semantic->is_required();
	has_argument = semantic->max_tokens() > 0 ? true : false;

	description = option->description();
	format_name = option->format_name();

	if (!positionals)
	{
		return;
	}

	for (size_t i = 0; i < positionals->max_total_count(); ++i)
	{
		if (id == positionals->name_for_position(i))
		{
			display_name.erase(0, display_name.find_first_not_of('-'));
			positional = true;
			break;
		}
	}
}

std::string Option::Usage()
{
	std::stringstream usage;
	if (positional)
	{
		usage << "\t" << std::setw(ADEQUATE_NAME_LENGTH) << std::left << display_name << "\t"
			  << description;
	}
	else
	{
		usage << "\t" << std::setw(ADEQUATE_NAME_LENGTH) << std::left << format_name << "\t"
			  << description;
	}
	return usage.str();
}

} // namespace cli
