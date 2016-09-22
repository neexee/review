#include <Utils/Callback.h>

#include <Git/AnnotatedDiff.h>
#include <Git/Blame.h>

namespace git {

AnnotatedDiff::AnnotatedDiff(const DiffPtr& diff, const RepoPtr& repo)
: diff_(diff)
, repo_(repo)
{
	const auto& deltas = diff_->Deltas();
	for (const auto& delta : deltas)
	{
		deltas_.push_back(
			std::make_shared<AnnotatedDiffDelta>(delta, diff->NewTree(), diff->OldTree()));
	}
}

AnnotatedDiffDeltas AnnotatedDiff::Deltas() const
{
	return deltas_;
}

} // namespace git
