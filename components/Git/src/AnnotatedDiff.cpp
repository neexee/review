#include "AnnotatedDiff.h"
#include "Blame.h"
#include "Callback.h"

namespace git {

AnnotatedDiff::AnnotatedDiff(const DiffPtr& diff, const RepoPtr& repo)
: diff_(diff)
, repo_(repo)
{
	const auto& deltas = diff_->Deltas();
	for (const auto& delta: deltas)
	{
		deltas_.emplace_back(delta, diff->NewTree(), diff->OldTree());
	}
}

AnnotatedDiffDeltas AnnotatedDiff::Deltas() const
{
	return deltas_;
}

//////////////////////////////////////////////////////////////////////////////

AnnotatedDiffDelta::AnnotatedDiffDelta(const DiffDelta& delta, const TreePtr& new_tree,
									   const TreePtr& old_tree)
: DiffDelta(delta)
{
	auto repo = new_tree->Repo();
	auto new_blame = std::make_shared<Blame>(delta.NewFile().Path(), repo, new_tree->CommitId());
	auto old_blame = std::make_shared<Blame>(delta.OldFile().Path(), repo, old_tree->CommitId());
	for (const auto& line: delta.Lines())
	{
		lines_.emplace_back(line, old_blame, new_blame);
	}
}

AnnotatedDiffLines AnnotatedDiffDelta::Lines() const
{
	return lines_;
}

} // namespace git
