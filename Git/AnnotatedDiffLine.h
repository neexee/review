#include "Blame.h"
#include "DiffLine.h"

namespace git {

class AnnotatedDiffLine: public DiffLine
{
public:
	AnnotatedDiffLine(const DiffLine& diffline, const Blame& old_blame,
					  const Blame& new_blame);
	Oid CommitId() const;

private:
	Oid commit_id_;
};

} // namespace git
