#include <memory>
#include <vector>
#include <QObject>
#include <QQmlListProperty>
#include <Git/AnnotatedDiff.h>
#include <Review/DiffLine.h>

namespace review {

class DiffDelta: public QObject
{
	Q_OBJECT
	Q_PROPERTY(QList<QObject*> diffLines READ Lines NOTIFY DiffLinesChanged)

public:
	DiffDelta(const git::AnnotatedDiffDelta& delta);
	QList<QObject*> Lines();

Q_SIGNALS:
	void DiffLinesChanged();

private:
	static int CountLines(QQmlListProperty<DiffLine>* property);
	static DiffLine* At(QQmlListProperty<DiffLine>* property, int index);
	git::AnnotatedDiffDelta delta_;
	std::vector<DiffLinePtr> lines_;
};

typedef std::shared_ptr<DiffDelta> DiffDeltaPtr;

} // namespace review
