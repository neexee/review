#include <Git/Commit.h>
#include <Git/Common.h>
#include <Git/Object.h>

namespace git {

Commit::Commit(const ObjectId& id, const RepoPtr& repo)
: commit_(nullptr)
{
	auto oid = id.Oid();
	CheckSuccess("failed to lookup commit " + id.Hex(),
		git_commit_lookup,
		&commit_,
		repo->Pointer(),
		&oid);
}

Commit::~Commit()
{
	git_commit_free(commit_);
}

git_commit* Commit::Pointer()
{
	return commit_;
}

std::string Commit::Message() const
{
	return std::string(git_commit_message(commit_));
}

std::string Commit::Summary() const
{
	return std::string(git_commit_summary(commit_));
}

std::string Commit::Body() const
{
	return std::string(git_commit_body(commit_));
}

ObjectId Commit::Id() const
{
	return ObjectId(*git_commit_id(commit_));
}

} // namespace git
