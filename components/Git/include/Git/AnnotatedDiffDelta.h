#pragma once
#include <vector>
#include "AnnotatedDiffLine.h"
#include "Blame.h"
#include "Commit.h"
#include "DiffDelta.h"
#include "Tree.h"

namespace git {

class AnnotatedDiffDelta : public DiffDelta
{
public:
	AnnotatedDiffDelta(const DiffDelta& delta,
		const TreePtr& new_tree,
		const TreePtr& old_tree);
	AnnotatedDiffLines Lines() const;

private:
	CommitPtr FindCommit(const DiffLine& line,
		const BlamePtr& old_blame,
		const BlamePtr& new_blame);
	AnnotatedDiffLines lines_;
};

typedef std::shared_ptr<AnnotatedDiffDelta> AnnotatedDiffDeltaPtr;
typedef std::vector<AnnotatedDiffDeltaPtr> AnnotatedDiffDeltas;

} // namespace git
