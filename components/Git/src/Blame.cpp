#include <algorithm>
#include <Git/Blame.h>
#include <Git/Common.h>

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
		auto hunk = git_blame_get_hunk_byindex(blame_, hunk_number);
		auto hunk_commit = std::make_shared<Commit>(ObjectId(hunk->final_commit_id), repo);
		hunks_.emplace_back(std::make_shared<BlameHunk>(hunk, hunk_commit));
	}
}

CommitPtr Blame::FindCommitByLine(size_t line_number) const
{
	auto iter = std::find_if(hunks_.begin(), hunks_.end(), [line_number](const auto& hunk) {
		auto left_bound = hunk->StartLineNumber();
		auto right_bound = left_bound + hunk->LinesNum();
		return line_number >= left_bound && line_number < right_bound;
	});
	return (*iter)->Commit();
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
