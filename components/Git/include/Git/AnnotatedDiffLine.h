#pragma once
#include "Blame.h"
#include "DiffLine.h"

namespace git {

class AnnotatedDiffLine : public DiffLine
{
public:
	AnnotatedDiffLine(const DiffLine& diffline,
	    const BlamePtr& old_blame,
	    const BlamePtr& new_blame);
	ObjectId CommitId() const;
	BlamePtr Blame() const;

private:
	ObjectId commit_id_;
	BlamePtr blame_;
};

} // namespace git
