#include <map>
#include <git2.h>
#include "DiffLine.h"

namespace git {

namespace {

const std::map<char, DiffLineType> line_type_map =
{
	{ GIT_DIFF_LINE_CONTEXT,       DiffLineType::Context      },
	{ GIT_DIFF_LINE_ADDITION,      DiffLineType::Addition     },
	{ GIT_DIFF_LINE_DELETION,      DiffLineType::Deletion     },
	{ GIT_DIFF_LINE_CONTEXT_EOFNL, DiffLineType::ContextNoEOF },
	{ GIT_DIFF_LINE_ADD_EOFNL,     DiffLineType::AdditionEOF  },
	{ GIT_DIFF_LINE_DEL_EOFNL,     DiffLineType::DeletionEOF  }
};

} // namespace

DiffLine::DiffLine(const git_diff_line* line)
: old_lineno_(line->old_lineno)
, new_lineno_(line->new_lineno)
, line_type_(ToLineType(line->origin))
, content_(line->content, line->content_len)
{
}

int DiffLine::OldNumber() const
{
	return old_lineno_;
}

int DiffLine::NewNumber() const
{
	return new_lineno_;
}

DiffLineType DiffLine::LineType() const
{
	return line_type_;
}

std::string DiffLine::Content() const
{
	return content_;
}

DiffLineType ToLineType(char line_type)
{
	return line_type_map.at(line_type);
}

char ToChar(DiffLineType line_type)
{
	for (const auto& kv: line_type_map)
	{
		if (kv.second == line_type)
		{
			return kv.first;
		}
	}
	return ' ';
}

} // namespace git
