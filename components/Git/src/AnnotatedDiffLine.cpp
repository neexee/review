#include <Git/AnnotatedDiffLine.h>

namespace git {

AnnotatedDiffLine::AnnotatedDiffLine(const DiffLine& diffline, const CommitPtr& commit)
: DiffLine(diffline)
, commit_(commit)
{
}
CommitPtr AnnotatedDiffLine::Commit() const
{
	return commit_;
}

} // namespace git
