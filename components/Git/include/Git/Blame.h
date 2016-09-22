#pragma once
#include <vector>
#include "BlameHunk.h"
#include "Object.h"
#include "Repo.h"

namespace git {

class DiffFile;

class Blame
{
public:
	Blame(const DiffFile& file, const RepoPtr& repo, const ObjectId& commit_oid);

	Blame(const Blame& other) = delete;
	Blame& operator=(const Blame&) = delete;
	~Blame();

	CommitPtr FindCommitByLine(size_t line_number) const;
	BlameHunkVector Hunks() const;
	RepoPtr Repo() const;

private:
	git_blame* blame_;
	BlameHunkVector hunks_;
	RepoPtr repo_;
	ObjectId commit_id_;
};

typedef std::shared_ptr<Blame> BlamePtr;

} // namespace git
