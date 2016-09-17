#include <QStringList>
#include "Utils.h"
#include "FileTreeModel.h"

namespace review {

FileTreeModel::FileTreeModel(QObject* parent)
: QAbstractItemModel(parent)
, root_(std::make_shared<FileTreeItem>("Title"))
{
	role_name_mapping_[static_cast<int>(Roles::FileName)] = "fileName";
}

QVector<QString> FileTreeModel::Paths() const
{
	return QVector<QString>();
}

void FileTreeModel::SetPaths(QVector<QString> paths)
{
	for(const auto& path: paths)
	{
		auto path_parts = utils::SplitPath(path.toStdString());
		std::deque<QString> q_path_parts;
		std::transform(path_parts.begin(), path_parts.end(), std::back_inserter(q_path_parts),
					   [](auto& part) { return QString::fromStdString(part); });
		root_->AddChildrenRecursively(q_path_parts);
	}
	emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

int FileTreeModel::columnCount(const QModelIndex& parent) const
{
	if (parent.isValid())
	{
		return static_cast<FileTreeItem*>(parent.internalPointer())->ColumnNumber();
	}
	return root_->ColumnNumber();
}

QVariant FileTreeModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}
	if (role != static_cast<int>(Roles::FileName))
	{
		return QVariant();
	}
	FileTreeItem* item = static_cast<FileTreeItem*>(index.internalPointer());
	return item->Data();
}

QVariant FileTreeModel::headerData(int /*section*/, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return root_->Data();
	return QVariant();
}

Qt::ItemFlags FileTreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return QAbstractItemModel::flags(index);
}

QModelIndex FileTreeModel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	FileTreeItem* parent_item = ParentItem(parent);
	FileTreeItem* child_item = parent_item->Child(row).get();
	if (child_item)
	{
		return createIndex(row, column, child_item);
	}
	return QModelIndex();
}

FileTreeItem* FileTreeModel::ParentItem(const QModelIndex& parent) const
{
	if (!parent.isValid())
	{
		return root_.get();
	}
	return static_cast<FileTreeItem*>(parent.internalPointer());
}

QModelIndex FileTreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	FileTreeItem* child_item = static_cast<FileTreeItem*>(index.internalPointer());
	FileTreeItem* parent_item = child_item->Parent().get();

	if (parent_item == root_.get())
	{
		return QModelIndex();
	}
	return createIndex(parent_item->Row(), 0, parent_item);
}

int FileTreeModel::rowCount(const QModelIndex& parent) const
{

	if (parent.column() > 0)
	{
		return 0;
	}
	return ParentItem(parent)->ChildNumber();
}

QHash<int, QByteArray> FileTreeModel::roleNames() const
{
	return role_name_mapping_;
}

} // namespace review
