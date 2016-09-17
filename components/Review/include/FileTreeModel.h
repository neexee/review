#pragma once
#include <string>
#include <vector>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "FileTreeItem.h"

namespace review {

class FileTreeModel : public QAbstractItemModel
{
	Q_OBJECT
	Q_PROPERTY(QVector<QString> paths READ Paths WRITE SetPaths)
public:
	enum class Roles
	{
		FileName = Qt::UserRole + 1,
		FileDescription
	};

	FileTreeModel(QObject* parent = nullptr);
	QVector<QString> Paths() const;

	QVariant data(const QModelIndex& index, int role) const Q_DECL_OVERRIDE;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
	Qt::ItemFlags flags(const QModelIndex& index) const Q_DECL_OVERRIDE;
	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QModelIndex parent(const QModelIndex& index) const Q_DECL_OVERRIDE;
	int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QHash<int, QByteArray> roleNames() const override;

public Q_SLOTS:
	void SetPaths(QVector<QString> paths);

private:
	FileTreeItem* ParentItem(const QModelIndex& parent) const;
	FileTreeItemPtr root_;
	QHash<int, QByteArray> role_name_mapping_;
};

} // namespace review
