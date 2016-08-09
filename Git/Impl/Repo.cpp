#include "../Repo.h"
namespace git
{

Repo::Repo(const std::string& path)
 : repo(nullptr)
{
	check_lg2(git_repository_open_ext(&repo, path.c_str(), 0, NULL),
			  "Could not open repository", path.c_str());
}

git_repository* Repo::GetRepository()
{
	return repo;
}

Repo::~Repo()
{
	git_repository_free(repo);
}

} // namespace git
