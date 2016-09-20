#include <Git/Common.h>
#include <Git/Repo.h>

namespace git {

Repo::Repo(const std::string& path)
: repo_(nullptr)
{
	CheckSuccess("could not open repository " + path,
	    git_repository_open_ext,
	    &repo_,
	    path.c_str(),
	    0,
	    nullptr);
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
