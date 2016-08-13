#pragma once
#include <string>
#include <memory>
#include "Common.h"

namespace git {

class Repo
{
public:
	explicit Repo(const std::string& path);

	Repo(const Repo& other) = delete;
	Repo& operator=(const Repo&) = delete;

	git_repository* GetRepository();
	~Repo();

private:
	git_repository* repo;
};

typedef std::shared_ptr<Repo> RepoPtr;

} // namespace git
