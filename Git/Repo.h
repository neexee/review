#pragma once
#include <string>
#include <memory>
#include "Common.h"

namespace git
{

class Repo
{
public:
	explicit Repo(const std::string& path);
	Repo(const Repo& other) = delete;
	Repo& operator=(const Repo&) = delete;
	~Repo();

	git_repository* GetRepository();

private:
	git_repository* repo;
};

typedef std::shared_ptr<Repo> RepoPtr;

} // namespace git
