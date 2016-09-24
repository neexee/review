#pragma once
#include <memory>
#include <vector>

#include <QAbstractTableModel>
#include <QList>
#include <QObject>

#include <Git/AnnotatedDiff.h>
#include <Review/DiffLine.h>

namespace review {

class DiffDelta : public QAbstractTableModel
{
	Q_OBJECT

public:
	DiffDelta(const git::AnnotatedDiffDeltaPtr& delta);

	Q_INVOKABLE QString Path() const;
	Q_INVOKABLE QVariant Line(int line_index) const;

	QVariant data(const QModelIndex& index, int role) const Q_DECL_OVERRIDE;
	int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QHash<int, QByteArray> roleNames() const override;

private:
	enum class Roles
	{
		RowNumber = Qt::UserRole + 1,
		CommitInfo,
		Text
	};

	git::AnnotatedDiffDeltaPtr delta_;
	std::vector<DiffLinePtr> lines_;
	QHash<int, QByteArray> role_name_mapping_;
};

typedef std::shared_ptr<DiffDelta> DiffDeltaPtr;

} // namespace review
