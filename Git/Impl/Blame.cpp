#include "../Blame.h"
namespace git {

Blame::Blame(const std::string& path, const git::RepoPtr& repo, const ObjectId& commit_oid)
: blame_(nullptr)
{
	git_blame_options blame_options = GIT_BLAME_OPTIONS_INIT;
	blame_options.newest_commit = commit_oid.Oid();
	check_lg2(git_blame_file(&blame_, repo->GetRepository(),
				path.c_str(), &blame_options),
			  "failed to blame", NULL);

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
	throw;
}

Blame::~Blame()
{
	git_blame_free(blame_);
}

BlameHunkVector Blame::Hunks() const
{
	return hunks_;
}

//////////////////////////////////////////////////////////////////////////////

BlameHunk::BlameHunk(const git_blame_hunk* hunk)
: commit_id_(ObjectId(hunk->final_commit_id))
, lines_num_(hunk->lines_in_hunk)
, start_line_number_(hunk->final_start_line_number)
, signature_(hunk->final_signature)
{
}

ObjectId BlameHunk::CommitId() const
{
	return commit_id_;
}

size_t BlameHunk::LinesNum() const
{
	return lines_num_;
}

size_t BlameHunk::StartLineNumber() const
{
	return start_line_number_;
}

GitSignature BlameHunk::Signature() const
{
	return signature_;
}

} // namespace git
