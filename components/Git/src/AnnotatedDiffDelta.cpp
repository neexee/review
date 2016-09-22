#include <Git/AnnotatedDiffDelta.h>
#include <Git/Blame.h>
#include <Git/DiffDelta.h>

namespace git {

AnnotatedDiffDelta::AnnotatedDiffDelta(const DiffDelta& delta,
	const TreePtr& new_tree,
	const TreePtr& old_tree)
: DiffDelta(delta)
{
	auto repo = new_tree->Repo();
	auto old_blame = std::make_shared<Blame>(OldFile(), repo, old_tree->CommitId());
	auto new_blame = std::make_shared<Blame>(NewFile(), repo, new_tree->CommitId());

	for (const auto& line : delta.Lines())
	{
		auto commit = FindCommit(line, old_blame, new_blame);
		lines_.push_back(std::make_shared<AnnotatedDiffLine>(line, commit));
	}
}

CommitPtr AnnotatedDiffDelta::FindCommit(const DiffLine& line,
	const BlamePtr& old_blame,
	const BlamePtr& new_blame)
{
	auto line_type = line.LineType();

	if (line_type == DiffLineType::Deletion || line_type == DiffLineType::DeletionEOF)
	{
		return old_blame->FindCommitByLine(line.OldNumber());
	}
	return new_blame->FindCommitByLine(line.NewNumber());
}

AnnotatedDiffLines AnnotatedDiffDelta::Lines() const
{
	return lines_;
}

} // namespace git
