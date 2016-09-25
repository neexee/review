#include <Git/Diff.h>
#include <Git/Repo.h>

#include <Review/Review.h>

namespace review {

Review::Review()
{
}

Review::Review(const cli::Options& options)
: diff_(std::make_shared<DiffModel>(options.CommitFrom(),
	  options.CommitTo(),
	  options.RepoPath()))
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
