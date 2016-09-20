#pragma once
#include <memory>
#include <string>
#include <git2.h>

namespace git {

class Repo
{
public:
	explicit Repo(const std::string& path);

	Repo(const Repo& other) = delete;
	Repo& operator=(const Repo&) = delete;

	git_repository* Pointer();
	~Repo();

private:
	git_repository* repo_;
};

typedef std::shared_ptr<Repo> RepoPtr;

} // namespace git
