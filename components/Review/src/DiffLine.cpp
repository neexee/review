#include <Git/DiffLine.h>
#include <Review/Commit.h>
#include <Review/DiffDelta.h>
#include <Review/DiffLine.h>
#include <Review/DiffModel.h>

namespace review {

DiffLine::DiffLine()
{
}

DiffLine::DiffLine(git::AnnotatedDiffLinePtr& line)
: line_(line)
, commit_(std::make_shared<Commit>(line->Commit()))
{
}

DiffLine::LineType DiffLine::GetLineType() const
{
	using LT = git::DiffLineType;
	static auto line_type_map = std::map<LT, LineType>{
		{LT::Context, Context}, {LT::Addition, Addition}, {LT::Deletion, Deletion}};

	auto type = line_type_map.find(line_->LineType());
	if (type != line_type_map.end())
	{
		return type->second;
	}
	return Context;
}

int DiffLine::LineNumber() const
{
	if (line_->LineType() == git::DiffLineType::Deletion)
	{
		return line_->OldNumber();
	}
	return line_->NewNumber();
}

Commit* DiffLine::GetCommit() const
{
	return commit_.get();
}

QString DiffLine::Text() const
{
	return QString::fromStdString(line_->Content());
}

} // namespace review
