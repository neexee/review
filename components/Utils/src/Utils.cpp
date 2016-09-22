#include <boost/filesystem.hpp>
#include <Utils/Utils.h>

namespace utils {

std::vector<std::string> SplitPath(const std::string& path)
{
	std::vector<std::string> result;
	auto boost_path = boost::filesystem::path(path);
	std::transform(boost_path.begin(),
		boost_path.end(),
		std::back_inserter(result),
		[](auto& path_part) -> std::string { return path_part.c_str(); });
	return result;
}

} // namespace utils
