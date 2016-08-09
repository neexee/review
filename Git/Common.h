#pragma once
#include <stdexcept>
#include <git2.h>

namespace git
{

class GitError: public std::runtime_error
{
public:
	GitError(const std::string& error);
};

void check_lg2(int error, const char *message, const char *extra);

} // namespace git
