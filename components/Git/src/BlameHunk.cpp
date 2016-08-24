#include "BlameHunk.h"

namespace git {

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

signature::Signature BlameHunk::Signature() const
{
	return signature_;
}

} // namespace git
