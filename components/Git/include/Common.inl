#include "Utils.h"

namespace git {

template <typename Function, typename... Args>
void CheckSuccess(std::string message, Function libgit2_function, Args&&... args)
{
	int error = libgit2_function(std::forward<Args>(args)...);
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
	auto error_message = utils::string_format(
		"%s [%d]%s%s\n", message.c_str(), error, libgit2spacer, libgit2msg);
	throw GitError(error_message);
}

} //namespace git
