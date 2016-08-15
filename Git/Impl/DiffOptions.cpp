#include "../DiffOptions.h"

namespace git {

DiffOptions::DiffOptions()
{
	git_diff_init_options(&diffopts_, GIT_DIFF_OPTIONS_VERSION);
	git_diff_find_init_options(&findopts_, GIT_DIFF_FIND_OPTIONS_VERSION);
}

} // namespace git
