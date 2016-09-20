#pragma once
#include <memory>
#include <vector>
#include <QList>
#include <QObject>
#include <Git/AnnotatedDiff.h>
#include <Review/DiffLine.h>

namespace review {

class DiffDelta : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QList<QObject*> diffLines READ Lines NOTIFY DiffLinesChanged)
	Q_PROPERTY(QString path READ Path NOTIFY PathChanged)

public:
	DiffDelta(const git::AnnotatedDiffDeltaPtr& delta);
	QList<QObject*> Lines();
	QString Path() const;

Q_SIGNALS:
	void DiffLinesChanged();
	void PathChanged();

private:
	git::AnnotatedDiffDeltaPtr delta_;
	std::vector<DiffLinePtr> lines_;
};

typedef std::shared_ptr<DiffDelta> DiffDeltaPtr;

} // namespace review
