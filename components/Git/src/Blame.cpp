#include <algorithm>
#include <Git/Blame.h>
#include <Git/Common.h>
#include <Git/DiffFile.h>

namespace git {

Blame::Blame(const DiffFile& file, const git::RepoPtr& repo, const ObjectId& commit_oid)
: blame_(nullptr)
, repo_(repo)
, commit_id_(commit_oid)
{
	if (file.Exists())
	{
		return;
	}
	git_blame_options blame_options = GIT_BLAME_OPTIONS_INIT;
	blame_options.newest_commit = commit_oid.Oid();
	CheckSuccess("failed to blame " + file.Path(),
		git_blame_file,
		&blame_,
		repo->Pointer(),
		file.Path().c_str(),
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
	if (iter == hunks_.end())
	{
		return std::make_shared<Commit>(commit_id_, repo_);
	}
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
