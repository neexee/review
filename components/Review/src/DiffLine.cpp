#include <Git/DiffLine.h>
#include <Review/DiffLine.h>

namespace review {

DiffLine::DiffLine()
{
}

DiffLine::DiffLine(git::AnnotatedDiffLine& line)
: line_(line)
{
}

DiffLine::LineType DiffLine::GetLineType() const
{
	using LT = git::DiffLineType;
	static auto line_type_map = std::map<LT, LineType>
	{
		{ LT::Context,   Context  },
		{ LT::Addition,  Addition },
		{ LT::Deletion,  Deletion }
	};

	auto type = line_type_map.find(line_.LineType());
	if (type != line_type_map.end())
	{
		return type->second;
	}
	return Context;
}

int DiffLine::LineNumber() const
{
	if (line_.LineType() == git::DiffLineType::Deletion)
	{
		return line_.OldNumber();
	}
	return line_.NewNumber();
}

QString DiffLine::Text() const
{
	return QString::fromStdString(line_.Content());
}

} // namespace review
