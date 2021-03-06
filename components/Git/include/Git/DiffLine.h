#pragma once
#include <string>
#include <git2.h>

#include <Git/Commit.h>

namespace git {

enum class DiffLineType
{
	Context,
	Addition,
	Deletion,
	ContextNoEOF,
	AdditionEOF,
	DeletionEOF
};

class DiffLine
{
public:
	DiffLine();
	explicit DiffLine(const git_diff_line* diff);
	int OldNumber() const;
	int NewNumber() const;
	DiffLineType LineType() const;
	std::string Content() const;

private:
	DiffLineType ToLineType(char line_type);
	char ToChar(DiffLineType line_type);

	int old_lineno_;
	int new_lineno_;
	DiffLineType line_type_;
	std::string content_;
};

} // namespace git
