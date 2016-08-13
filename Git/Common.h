#pragma once
#include <stdexcept>
#include <git2.h>

namespace git {

typedef std::string Treeish;

class GitError: public std::runtime_error
{
public:
	explicit GitError(const std::string& error);
};

void check_lg2(int error, const char *message, const char *extra);

} // namespace git
