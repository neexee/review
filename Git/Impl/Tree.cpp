#include "../Object.h"
#include "../Tree.h"

namespace git {

Tree::Tree(const RepoPtr& repo, const Treeish& treeish)
: tree_(nullptr)
, repo_(repo)
, object_(std::make_shared<Object>())
{
	check_lg2(git_revparse_single(object_->GetPointerToObject(),
								  repo->GetRepository(), treeish.c_str()),
			  "looking up object", treeish.c_str());

	check_lg2(git_object_peel(reinterpret_cast<git_object **>(&tree_),
							  *object_->GetPointerToObject(), GIT_OBJ_TREE),
			  "resolving object to tree", treeish.c_str());
}

Tree::~Tree()
{
	git_tree_free(tree_);
}

RepoPtr Tree::Repo() const
{
	return repo_;
}

git_tree* Tree::GetTree() const
{
	return tree_;
}

ObjectId Tree::Id() const
{
	return ObjectId(*git_tree_id(tree_));
}

ObjectPtr Tree::GetObject() const
{
	return object_;
}

ObjectId Tree::CommitId() const
{
	return object_->Id();
}

} // namespace git
