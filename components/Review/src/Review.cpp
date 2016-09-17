#include "Review.h"

#include "Diff.h"
#include "Repo.h"
#include "DiffFormat.h"

namespace review {

Review::Review()
{
}

Review::Review(const std::string& from, const std::string& to,
					  const std::string& repo)
: diff_(std::make_shared<DiffModel>(from, to, repo))
{
	emit DiffChanged(diff_.get());
}

DiffModel* Review::Diff() const
{
	return diff_.get();
}

void Review::SetDiff(DiffModel* diff)
{
	diff_.reset(diff);
}

} // namespace review
