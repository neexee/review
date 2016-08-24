#pragma once
#include <git2.h>

namespace git {

struct DiffOptions
{
	DiffOptions();
	git_diff_options diffopts_;
	git_diff_find_options findopts_;
};

} // namespace git
