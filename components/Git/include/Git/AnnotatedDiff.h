#pragma once
#include "AnnotatedDiffDelta.h"
#include "Diff.h"

namespace git {

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
