#pragma once
#include <string>
#include <git2.h>

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
	int old_lineno_;
	int new_lineno_;
	DiffLineType line_type_;
	std::string content_;
};

DiffLineType ToLineType(char line_type);
char ToChar(DiffLineType line_type);

} // namespace git
