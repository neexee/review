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

template <typename Function, typename... Args>
void CheckSuccess(std::string message, Function libgit2_function, Args&&...);

} // namespace git

#include "Impl/Common.inl"
