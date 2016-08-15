#include "../AnnotatedDiffLine.h"

namespace git {

AnnotatedDiffLine::AnnotatedDiffLine(const DiffLine& diffline, const Blame& old_blame,
									 const Blame& new_blame)
: DiffLine(diffline)
{
	auto line_type = diffline.LineType();
	if (line_type == DiffLineType::Deletion || line_type == DiffLineType::DeletionEOF)
	{
		commit_id_ = old_blame.FindCommitId(diffline.OldNumber());
	}
	else
	{
		commit_id_ = new_blame.FindCommitId(diffline.NewNumber());
	}
}

ObjectId AnnotatedDiffLine::CommitId() const
{
	return commit_id_;
}

} // namespace git
