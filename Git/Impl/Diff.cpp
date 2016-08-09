#include "Utils/Utils.h"
#include "../Diff.h"
#include "../Tree.h"

namespace git
{

DiffOptions::DiffOptions(const std::string& from, const std::string& to, const std::string& dir)
: diffopts(GIT_DIFF_OPTIONS_INIT)
, findopts(GIT_DIFF_FIND_OPTIONS_INIT)
, from(from)
, to(to)
, dir(dir)
{
}

Diff::Diff(const RepoPtr& repo)
: diff_(nullptr)
, repo_(repo)
{
}

git_diff** Diff::GetPointerToDiff()
{
	return &diff_;
}

Diff::~Diff()
{
	git_diff_free(diff_);
}

static const char *colors[] = {
	"\033[m", /* reset */
	"\033[1m", /* bold */
	"\033[31m", /* red */
	"\033[32m", /* green */
	"\033[36m" /* cyan */
};

void PrintDiff(Diff& diff, const PrintOptions& options)
{
	if (options.color >= 0)
		fputs(colors[0], stdout);
	auto stuff = *diff.GetPointerToDiff();
	check_lg2(git_diff_print(stuff, options.format,
							 color_printer, const_cast<int*>(&(options.color))),
				"displaying diff", NULL);

	if (options.color >= 0)
		fputs(colors[0], stdout);
}

const Diff MakeDiff(const DiffOptions& o)
{
	auto repo = std::make_shared<Repo>(o.dir);
	Tree from{repo, o.from};
	Tree to{repo, o.to};
	auto d = from.MakeDiff(to, &o.diffopts);

	return d;
}

int diff_output(
	const git_diff_delta *d,
	const git_diff_hunk *h,
	const git_diff_line *l,
	void *p)
{
	FILE *fp = (FILE*)p;

	(void)d; (void)h;

	if (!fp)
		fp = stdout;

	if (l->origin == GIT_DIFF_LINE_CONTEXT ||
		l->origin == GIT_DIFF_LINE_ADDITION ||
		l->origin == GIT_DIFF_LINE_DELETION)
		fputc(l->origin, fp);

	fwrite(l->content, 1, l->content_len, fp);

	return 0;
}

int color_printer(
		const git_diff_delta *delta,
		const git_diff_hunk *hunk,
		const git_diff_line *line,
		void *data)
{
	int *last_color = (int*)data, color = 0;

	(void)delta; (void)hunk;

	if (*last_color >= 0) {
		switch (line->origin) {
		case GIT_DIFF_LINE_ADDITION:  color = 3; break;
		case GIT_DIFF_LINE_DELETION:  color = 2; break;
		case GIT_DIFF_LINE_ADD_EOFNL: color = 3; break;
		case GIT_DIFF_LINE_DEL_EOFNL: color = 2; break;
		case GIT_DIFF_LINE_FILE_HDR:  color = 1; break;
		case GIT_DIFF_LINE_HUNK_HDR:  color = 4; break;
		default: break;
		}

		if (color != *last_color) {
			if (*last_color == 1 || color == 1)
				fputs(colors[0], stdout);
			fputs(colors[color], stdout);
			*last_color = color;
		}
	}

	return diff_output(delta, hunk, line, stdout);
}

} // namespace git
