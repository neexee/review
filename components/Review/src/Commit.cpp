#include <Git/Object.h>
#include <Review/Commit.h>

namespace review {

Commit::Commit(const git::CommitPtr& commit)
: commit_(commit)
{
}

QString Commit::Summary() const
{
	return QString::fromStdString(commit_->Summary());
}

QString Commit::ShortHex() const
{
	return QString::fromStdString(commit_->Id().ShortHex());
}

} // namespace review
