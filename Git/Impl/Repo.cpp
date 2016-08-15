#include "../Repo.h"
namespace git {

Repo::Repo(const std::string& path)
: repo_(nullptr)
{
	check_lg2(git_repository_open_ext(&repo_, path.c_str(), 0, NULL),
			  "Could not open repository", path.c_str());
}

git_repository* Repo::Pointer()
{
	return repo_;
}

Repo::~Repo()
{
	git_repository_free(repo_);
}

} // namespace git
