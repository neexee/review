#pragma once
#include <memory>
#include "Common.h"
#include "Object.h"
#include "Repo.h"

namespace git {

class Tree
{
public:
	Tree(const RepoPtr& repo_, const Treeish& treeish);

	Tree(const Tree&) = delete;
	Tree& operator=(const Tree&) = delete;

	git_tree* Pointer() const;
	ObjectId Id() const;
	ObjectId CommitId() const;
	~Tree();
	RepoPtr Repo() const;

private:
	git_tree* tree_;
	RepoPtr repo_;
	ObjectPtr object_;
};

typedef std::shared_ptr<Tree> TreePtr;

} // namespace git
