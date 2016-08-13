#pragma once
#include <string>
#include "Common.h"
#include "Repo.h"
#include "Object.h"

namespace git
{
class Tree
{
public:
	Tree(const RepoPtr& repo_, const Treeish& treeish);

	Tree(const Tree&) = delete;
	Tree& operator=(const Tree&) = delete;

	git_tree* GetTree() const;
	Oid GetOid() const;
	ObjectPtr GetObject() const;
	Oid CommitOid() const;
	~Tree();
	RepoPtr Repo() const;

private:
	git_tree* tree_;
	RepoPtr repo_;
	ObjectPtr object_;
};

typedef std::shared_ptr<Tree> TreePtr;

} // namespace git
