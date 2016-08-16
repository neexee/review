#pragma once
#include <vector>
#include "BlameHunk.h"
#include "Common.h"
#include "Object.h"
#include "Repo.h"

namespace git {

class Blame
{
public:
	Blame(const std::string& path, const RepoPtr& repo, const ObjectId& commit_oid);

	Blame(const Blame& other) = delete;
	Blame& operator=(const Blame&) = delete;

	ObjectId FindCommitId(size_t line_number) const;
	BlameHunkVector Hunks() const;
	RepoPtr Repo() const;

	~Blame();

private:
	git_blame* blame_;
	BlameHunkVector hunks_;
	RepoPtr repo_;
};

typedef std::shared_ptr<Blame> BlamePtr;

} // namespace git
