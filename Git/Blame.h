#pragma once
#include <vector>
#include "Common.h"
#include "Object.h"
#include "Repo.h"
#include "Signature.h"

namespace git {

class BlameHunk
{
public:
	explicit BlameHunk(const git_blame_hunk* hunk);

	ObjectId CommitId() const;
	size_t LinesNum() const;
	size_t StartLineNumber() const;
	GitSignature Signature() const;

private:
	ObjectId commit_id_;
	size_t lines_num_;
	size_t start_line_number_;
	GitSignature signature_;
};

//////////////////////////////////////////////////////////////////////////////
typedef std::vector<BlameHunk> BlameHunkVector;

class Blame
{
public:
	Blame(const std::string& path, const RepoPtr& repo, const ObjectId& commit_oid);

	Blame(const Blame& other) = delete;
	Blame& operator=(const Blame&) = delete;

	ObjectId FindCommitId(size_t line_number) const;
	BlameHunkVector Hunks() const;

	~Blame();

private:
	git_blame* blame_;
	BlameHunkVector hunks_;
};

} // namespace git
