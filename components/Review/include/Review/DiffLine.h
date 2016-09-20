#pragma once
#include <QObject>
#include <Git/AnnotatedDiffLine.h>
#include <Review/Commit.h>

namespace review {

class DiffLine : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString text READ Text NOTIFY TextChanged)
	Q_PROPERTY(LineType lineType READ GetLineType NOTIFY LineTypeChanged)
	Q_PROPERTY(int lineNumber READ LineNumber NOTIFY LineNumberChanged)
	Q_PROPERTY(Commit* commit READ GetCommit NOTIFY CommitChanged)

public:
	DiffLine();
	DiffLine(git::AnnotatedDiffLinePtr& line);
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
	Commit* GetCommit() const;

Q_SIGNALS:
	void TextChanged();
	void LineTypeChanged();
	void LineNumberChanged();
	void CommitChanged();

private:
	git::AnnotatedDiffLinePtr line_;
	CommitPtr commit_;
};

typedef std::shared_ptr<DiffLine> DiffLinePtr;

} // namespace review
