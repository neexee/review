#pragma once
#include "AnnotatedDiffLine.h"
#include "Common.h"
#include "Diff.h"

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
	AnnotatedDiff();
	AnnotatedDiff(const DiffPtr& diff, const RepoPtr& repo);
	AnnotatedDiffDeltas Deltas() const;

private:
	DiffPtr diff_;
	RepoPtr repo_;
	AnnotatedDiffDeltas deltas_;
};

typedef std::shared_ptr<AnnotatedDiff> AnnotatedDiffPtr;
} // namespace git