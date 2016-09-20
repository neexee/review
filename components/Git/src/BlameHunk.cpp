#include <memory>
#include <Git/BlameHunk.h>
#include <Git/Commit.h>
#include <Git/Object.h>

namespace git {

BlameHunk::BlameHunk(const git_blame_hunk* hunk, const RepoPtr& repo)
: commit_(std::make_shared<git::Commit>(ObjectId(hunk->final_commit_id), repo))
, lines_num_(hunk->lines_in_hunk)
, start_line_number_(hunk->final_start_line_number)
, signature_(hunk->final_signature)
{
}

BlameHunk::BlameHunk(const git_blame_hunk* hunk, const CommitPtr& commit)
: commit_(commit)
, lines_num_(hunk->lines_in_hunk)
, start_line_number_(hunk->final_start_line_number)
, signature_(hunk->final_signature)
{
}

CommitPtr BlameHunk::Commit() const
{
	return commit_;
}

size_t BlameHunk::LinesNum() const
{
	return lines_num_;
}

size_t BlameHunk::StartLineNumber() const
{
	return start_line_number_;
}

signature::Signature BlameHunk::Signature() const
{
	return signature_;
}

} // namespace git
