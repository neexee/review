#include "../Common.h"
#include "Utils/Utils.h"

namespace git {
namespace {

struct LibGitInitializer
{
	LibGitInitializer()
	{
		git_libgit2_init();
	}
	~LibGitInitializer()
	{
		git_libgit2_shutdown();
	}
};

static LibGitInitializer libGit;

} // namespace

GitError::GitError(const std::string& error)
: std::runtime_error(error)
{
}

} //namespace git
