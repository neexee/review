#include <Git/Object.h>
#include <Git/Tree.h>

namespace git {

Tree::Tree(const RepoPtr& repo, const Treeish& treeish)
: tree_(nullptr)
, repo_(repo)
, object_(std::make_shared<Object>())
{
	CheckSuccess("looking up object " + treeish,
		git_revparse_single, object_->Pointer(), repo->Pointer(), treeish.c_str());

	CheckSuccess("resolving object to tree " + treeish,
		git_object_peel,
		reinterpret_cast<git_object **>(&tree_), *object_->Pointer(), GIT_OBJ_TREE);
}

Tree::~Tree()
{
	git_tree_free(tree_);
}

RepoPtr Tree::Repo() const
{
	return repo_;
}

git_tree* Tree::Pointer() const
{
	return tree_;
}

ObjectId Tree::Id() const
{
	return ObjectId(*git_tree_id(tree_));
}

ObjectId Tree::CommitId() const
{
	return object_->Id();
}

} // namespace git
