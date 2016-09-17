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

QString DiffLine::Text() const
{
	return QString::fromStdString(line_.Content());
}

} // namespace review
