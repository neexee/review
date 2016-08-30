#pragma once
#include <deque>
#include <memory>
#include <QList>
#include <QVariant>

namespace review {

class FileTreeItem;
typedef std::shared_ptr<FileTreeItem> FileTreeItemPtr;

class FileTreeItem: public std::enable_shared_from_this<FileTreeItem>
{
public:
	explicit FileTreeItem(const QString& data, const FileTreeItemPtr& parent = nullptr);
	~FileTreeItem();

	void AddChild(const FileTreeItemPtr& child);
	void AddChildrenRecursively(std::deque<QString> path_parts);
	const FileTreeItemPtr Child(int row);
	int ChildNumber() const;
	int ColumnNumber() const;
	QString Data() const;
	int Row() const;
	const FileTreeItemPtr Parent();

private:
	QList<FileTreeItemPtr> children_;
	QString file_name_;
	FileTreeItemPtr parent_;
};

} // namespace review
