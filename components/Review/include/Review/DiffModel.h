#pragma once
#include <memory>
#include <vector>
#include <QAbstractItemModel>
#include <QString>
#include <QVector>
#include <Git/AnnotatedDiff.h>
#include <Review/Commit.h>
#include <Review/DiffDelta.h>

namespace review {

class DiffModel : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QVector<QString> paths READ Paths NOTIFY PathsChanged)
	Q_PROPERTY(QList<QObject*> deltas READ Deltas NOTIFY DeltasChanged)

public:
	DiffModel();
	DiffModel(const std::string& from, const std::string& to, const std::string& repo);
	DiffModel(DiffModel&& another) = default;

	QVector<QString> Paths() const;
	QList<QObject*> Deltas();

Q_SIGNALS:
	void PathsChanged();
	void DeltasChanged();

private:
	git::AnnotatedDiffPtr adiff_;
	QList<DiffDeltaPtr> deltas_;
	CommitPtr from_commit_;
	CommitPtr to_commit_;
};

typedef std::shared_ptr<DiffModel> DiffModelPtr;

} // namespace review
