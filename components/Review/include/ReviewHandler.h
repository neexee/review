#pragma once
#include <string>
#include <QtCore/QTextCodec>
#include <QtGui/QTextCharFormat>
#include <QQuickTextDocument>
#include <qqmlfile.h>

#include "AnnotatedDiff.h"

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class ReviewHandler : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QQuickItem* target READ Target WRITE SetTarget NOTIFY TargetChanged)
	Q_PROPERTY(int cursorPosition READ CursorPosition WRITE SetCursorPosition NOTIFY CursorPositionChanged)
	Q_PROPERTY(int selectionStart READ SelectionStart WRITE SetSelectionStart NOTIFY SelectionStartChanged)
	Q_PROPERTY(int selectionEnd READ SelectionEnd WRITE SetSelectionEnd NOTIFY SelectionEndChanged)

	Q_PROPERTY(int fontSize READ FontSize WRITE SetFontSize NOTIFY FontSizeChanged)

	Q_PROPERTY(QStringList sefaultFontSizes READ DefaultFontSizes NOTIFY DefaultFontSizesChanged)

	Q_PROPERTY(QString text READ Text WRITE SetText NOTIFY TextChanged)

public:
	ReviewHandler();
	void Init(const std::string& repo_path,
			  const std::string& from_commitish, const std::string& to_commitish);

	QQuickItem* Target() { return target_; }
	void SetTarget(QQuickItem *Target);

	void SetCursorPosition(int position);
	void SetSelectionStart(int position);
	void SetSelectionEnd(int position);

	int CursorPosition() const;
	int SelectionStart() const;
	int SelectionEnd() const;

	QString FontFamily() const;

	int FontSize() const;

	QStringList DefaultFontSizes() const;
	QString Text() const;

public Q_SLOTS:
	void SetFontSize(int arg);
	void SetText(const QString &arg);

Q_SIGNALS:
	void TargetChanged();
	void CursorPositionChanged();
	void SelectionStartChanged();
	void SelectionEndChanged();

	void FontSizeChanged();
	void DefaultFontSizesChanged();

	void TextChanged();
	void DocumentTitleChanged();

private:
	void Reset();
	QTextCursor TextCursor() const;
	void MergeFormatOnWordOrSelection(const QTextCharFormat& format);
	git::AnnotatedDiff LoadDiff();

	QQuickItem* target_;
	QTextDocument* doc_;

	int cursor_position_;
	int selection_start_;
	int selection_end_;

	QFont font_;
	int font_size_;
	QString text_;

	std::string repo_path_;
	std::string from_commitish_;
	std::string to_commitish_;
};