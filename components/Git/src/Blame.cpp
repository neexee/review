#include <Git/Blame.h>

namespace git {

Blame::Blame(const git::RepoPtr& repo, const ObjectId& commit_id)
: blame_(nullptr)
, repo_(repo)
, commit_id_(commit_id)
{
}

Blame::Blame(const std::string& path, const git::RepoPtr& repo, const ObjectId& commit_oid)
: blame_(nullptr)
, repo_(repo)
, commit_id_(commit_oid)
{
	git_blame_options blame_options = GIT_BLAME_OPTIONS_INIT;
	blame_options.newest_commit = commit_oid.Oid();
	CheckSuccess("failed to blame " + path,
	    git_blame_file,
	    &blame_,
	    repo->Pointer(),
	    path.c_str(),
	    &blame_options);

	auto hunk_count = git_blame_get_hunk_count(blame_);
	for (decltype(hunk_count) hunk_number = 0; hunk_number < hunk_count; ++hunk_number)
	{
		hunks_.emplace_back(git_blame_get_hunk_byindex(blame_, hunk_number));
	}
}

ObjectId Blame::FindCommitId(size_t line_number) const
{
	for (const auto& hunk : hunks_)
	{
		auto left_bound = hunk.StartLineNumber();
		auto right_bound = left_bound + hunk.LinesNum();
		if (line_number >= left_bound && line_number < right_bound)
		{
			return hunk.CommitId();
		}
	}
	return commit_id_;
}

RepoPtr Blame::Repo() const
{
	return repo_;
}

Blame::~Blame()
{
	git_blame_free(blame_);
}

} // namespace git
