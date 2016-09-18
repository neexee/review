#include <QObject>
#include <Git/AnnotatedDiffLine.h>

namespace review {

class DiffLine: public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString text READ Text NOTIFY TextChanged)
	Q_PROPERTY(LineType lineType READ GetLineType NOTIFY LineTypeChanged)
	Q_PROPERTY(int lineNumber READ LineNumber NOTIFY LineNumberChanged)

public:
	DiffLine();
	DiffLine(git::AnnotatedDiffLine& line);
	enum LineType
	{
		Addition,
		Deletion,
		Context
	};
	Q_ENUM(LineType)

	LineType GetLineType() const;
	int LineNumber() const;
	QString Text() const;

Q_SIGNALS:
	void TextChanged();
	void LineTypeChanged();
	void LineNumberChanged();

private:
	git::DiffLine line_;
};

typedef std::shared_ptr<DiffLine> DiffLinePtr;

}// namespace review
