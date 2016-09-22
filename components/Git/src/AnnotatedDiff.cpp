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

//////////////////////////////////////////////////////////////////////////////

AnnotatedDiffDelta::AnnotatedDiffDelta(const DiffDelta& delta,
	const TreePtr& new_tree,
	const TreePtr& old_tree)
: DiffDelta(delta)
{
	auto repo = new_tree->Repo();

	std::shared_ptr<Blame> old_blame;
	if (delta.Status() == DeltaStatus::Added)
	{
		old_blame = std::make_shared<Blame>(repo, old_tree->CommitId());
	}
	else
	{
		old_blame =
			std::make_shared<Blame>(delta.OldFile().Path(), repo, old_tree->CommitId());
	}

	std::shared_ptr<Blame> new_blame;
	if (delta.Status() == DeltaStatus::Deleted)
	{
		new_blame = std::make_shared<Blame>(repo, new_tree->CommitId());
	}
	else
	{
		new_blame =
			std::make_shared<Blame>(delta.NewFile().Path(), repo, new_tree->CommitId());
	}

	for (const auto& line : delta.Lines())
	{
		auto line_type = line.LineType();
		CommitPtr commit;
		if (line_type == DiffLineType::Deletion || line_type == DiffLineType::DeletionEOF)
		{
			commit = old_blame->FindCommitByLine(line.OldNumber());
		}
		else
		{
			commit = new_blame->FindCommitByLine(line.NewNumber());
		}
		lines_.push_back(std::make_shared<AnnotatedDiffLine>(line, commit));
	}
}

AnnotatedDiffLines AnnotatedDiffDelta::Lines() const
{
	return lines_;
}

} // namespace git
