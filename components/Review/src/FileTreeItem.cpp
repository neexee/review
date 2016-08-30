#include <QStringList>
#include "FileTreeItem.h"

namespace review {

FileTreeItem::FileTreeItem(const QString& file_name, const FileTreeItemPtr& parent)
: file_name_(file_name)
, parent_(parent)
{
}

FileTreeItem::~FileTreeItem()
{
}

void FileTreeItem::AddChild(const FileTreeItemPtr& item)
{
	children_.append(item);
}

void FileTreeItem::AddChildrenRecursively(std::deque<QString> path_parts)
{
	if (path_parts.size() == 0)
	{
		return;
	}
	QString root = path_parts.front();
	auto child_iterator = std::find_if(children_.begin(), children_.end(),
			  [root](FileTreeItemPtr& child) { return child->Data() == root; });

	if (child_iterator == children_.end())
	{
		children_.append(std::make_shared<FileTreeItem>(root, shared_from_this()));
		child_iterator = std::prev(children_.end());
	}

	path_parts.pop_front();
	(*child_iterator)->AddChildrenRecursively(path_parts);
}

const FileTreeItemPtr FileTreeItem::Child(int row)
{
	return children_.value(row);
}

int FileTreeItem::ChildNumber() const
{
	return children_.count();
}

int FileTreeItem::ColumnNumber() const
{
	return 1;
}

QString FileTreeItem::Data() const
{
	return file_name_;
}

const FileTreeItemPtr FileTreeItem::Parent()
{
	return parent_;
}

int FileTreeItem::Row() const
{
	if (parent_)
	{
		auto& parent_children = parent_->children_;
		auto iter = std::find_if(parent_children.begin(), parent_children.end(),
								 [this](auto& child) { return child.get() == this; });

		return std::distance(parent_children.begin(), iter);
	}
	return 0;
}

} // namespace review
