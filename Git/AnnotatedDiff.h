#pragma once
#include "Common.h"
#include "Diff.h"
#include "AnnotatedDiffLine.h"

namespace git {

typedef std::vector<AnnotatedDiffLine> AnnotatedDiffLines;

class AnnotatedDiffDelta : public DiffDelta
{
public:
	AnnotatedDiffDelta(const DiffDelta& delta, const TreePtr& new_tree,
					   const TreePtr& old_tree);
	AnnotatedDiffLines Lines() const;
private:
	AnnotatedDiffLines lines_;
};

//////////////////////////////////////////////////////////////////////////////
typedef std::vector<AnnotatedDiffDelta> AnnotatedDiffDeltas;

class AnnotatedDiff
{
public:
	AnnotatedDiff(const DiffPtr& diff, const RepoPtr& repo);
	AnnotatedDiffDeltas Deltas() const;

private:
	DiffPtr diff_;
	RepoPtr repo_;
	AnnotatedDiffDeltas deltas_;
};

} // namespace git
