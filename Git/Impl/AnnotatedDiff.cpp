#include "Utils/Callback.h"
#include "../AnnotatedDiff.h"
#include "../Blame.h"

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
	Blame new_blame {delta.NewFile().Path(), repo, new_tree->CommitOid()};
	Blame old_blame {delta.OldFile().Path(), repo, old_tree->CommitOid()};
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
