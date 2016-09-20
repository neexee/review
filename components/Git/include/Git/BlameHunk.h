#pragma once
#include <vector>
#include "Commit.h"
#include "Repo.h"
#include "Signature.h"

namespace git {

class BlameHunk
{
public:
	BlameHunk(const git_blame_hunk* hunk, const RepoPtr& repo);
	BlameHunk(const git_blame_hunk* hunk, const CommitPtr& commit);
	CommitPtr Commit() const;
	size_t LinesNum() const;
	size_t StartLineNumber() const;
	signature::Signature Signature() const;

private:
	CommitPtr commit_;
	size_t lines_num_;
	size_t start_line_number_;
	signature::Signature signature_;
};

typedef std::shared_ptr<BlameHunk> BlameHunkPtr;
typedef std::vector<BlameHunkPtr> BlameHunkVector;

} // namespace git
