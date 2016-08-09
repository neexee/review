#pragma once
#include <string>
#include "Common.h"
#include "Repo.h"

namespace git
{

struct DiffOptions
{
	DiffOptions(const std::string& from, const std::string& to, const std::string& dir);
	git_diff_options diffopts;
	git_diff_find_options findopts;
	std::string from;
	std::string to;
	std::string dir;
};

class Diff
{
public:
	explicit Diff(const RepoPtr& repo);
	git_diff** GetPointerToDiff();
	~Diff();
private:
	git_diff* diff_;
	RepoPtr repo_;
};

const Diff MakeDiff(const DiffOptions& o);

struct PrintOptions
{
public:
	git_diff_format_t format;
	int color;
};

void PrintDiff(Diff& diff, const PrintOptions& options);

int diff_output(const git_diff_delta *d, const git_diff_hunk *h, const git_diff_line *l, void *p);
int color_printer(const git_diff_delta *delta, const git_diff_hunk *hunk, const git_diff_line *line, void *data);

} // namespace git
