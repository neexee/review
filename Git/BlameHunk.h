#pragma once
#include <vector>
#include "Common.h"
#include "Object.h"
#include "Signature.h"

namespace git {

class BlameHunk
{
public:
	explicit BlameHunk(const git_blame_hunk* hunk);

	ObjectId CommitId() const;
	size_t LinesNum() const;
	size_t StartLineNumber() const;
	signature::Signature Signature() const;

private:
	ObjectId commit_id_;
	size_t lines_num_;
	size_t start_line_number_;
	signature::Signature signature_;
};

typedef std::vector<BlameHunk> BlameHunkVector;

} // namespace git
