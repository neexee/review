#pragma once
#include <string>
#include "Common.h"
#include "Repo.h"
#include "Diff.h"

namespace git
{
class Tree
{
public:
	Tree(const RepoPtr& repo, const std::string& treeish);
	Diff MakeDiff(Tree& another, const git_diff_options* diffopts);
	git_tree* GetTree();
	~Tree();
private:
	git_tree* tree;
	RepoPtr repo;
};

} // namespace git
