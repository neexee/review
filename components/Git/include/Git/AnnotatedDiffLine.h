#pragma once
#include <vector>
#include "DiffLine.h"

namespace git {

class AnnotatedDiffLine : public DiffLine
{
public:
	AnnotatedDiffLine(const DiffLine& diffline, const CommitPtr& commit);
	CommitPtr Commit() const;

private:
	CommitPtr commit_;
};

typedef std::shared_ptr<AnnotatedDiffLine> AnnotatedDiffLinePtr;
typedef std::vector<AnnotatedDiffLinePtr> AnnotatedDiffLines;

} // namespace git
