#include "../Object.h"
#include "../Tree.h"

namespace git
{

Tree::Tree(const RepoPtr& repo, const std::string& treeish)
 : tree(nullptr), repo(repo)
{
	Object object;
	check_lg2(git_revparse_single(object.GetPointerToObject(),
								  repo->GetRepository(), treeish.c_str()),
			  "looking up object", treeish.c_str());
	check_lg2(git_object_peel(reinterpret_cast<git_object **>(&tree),
							  *object.GetPointerToObject(), GIT_OBJ_TREE),
			  "resolving object to tree", treeish.c_str());
}

Tree::~Tree()
{
	git_tree_free(tree);
}

Diff Tree::MakeDiff(Tree& another, const git_diff_options* diffopts)
{
	Diff diff(repo);
	check_lg2(git_diff_tree_to_tree(diff.GetPointerToDiff(), repo->GetRepository(),
									tree, another.tree, diffopts),
			  "diff trees", NULL);
	return diff;
}

git_tree* Tree::GetTree()
{
	return tree;
}

} // namespace git
