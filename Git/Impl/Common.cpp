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

void check_lg2(int error, const char *message, const char *extra)
{
	if (!error)
		return;

	const git_error* libgit2err;
	const char* libgit2msg = "";
	const char* libgit2spacer = "";
	if ((libgit2err = giterr_last()) != NULL && libgit2err->message != NULL)
	{
		libgit2msg = libgit2err->message;
		libgit2spacer = " - ";
	}

	if (extra)
	{
		throw GitError(utils::string_format("%s '%s' [%d]%s%s\n",
							message, extra, error, libgit2spacer, libgit2msg));
	}
	throw GitError(utils::string_format("%s [%d]%s%s\n",
						message, error, libgit2spacer, libgit2msg));
}

} //namespace git
