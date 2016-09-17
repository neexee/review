#include <QtCore/QFileInfo>
#include <QtGui/QTextCursor>
#include <QtGui/QFontDatabase>

#include "DiffView.h"

namespace review {

DiffView::DiffView()
: target_(0)
, doc_(0)
, cursor_position_(-1)
, selection_start_(0)
, selection_end_(0)
{
}

void DiffView::SetTarget(QQuickItem* target)
{
	doc_ = 0;
	target_ = target;
	if (!target_)
	{
		return;
	}

	QVariant doc = target_->property("textDocument");
	if (doc.canConvert<QQuickTextDocument *>())
	{
		QQuickTextDocument* qqdoc = doc.value<QQuickTextDocument*>();
		if (qqdoc)
		{
			doc_ = qqdoc->textDocument();
		}
	}
	emit TargetChanged();
}

void DiffView::SetCursorPosition(int position)
{
	if (position == cursor_position_)
	{
		return;
	}

	cursor_position_ = position;

	Reset();
}

void DiffView::Reset()
{
	emit FontSizeChanged();
}

QTextCursor DiffView::TextCursor() const
{
	QTextCursor cursor = QTextCursor(doc_);
	if (selection_start_ != selection_end_)
	{
		cursor.setPosition(selection_start_);
		cursor.setPosition(selection_end_, QTextCursor::KeepAnchor);
	}
	else
	{
		cursor.setPosition(cursor_position_);
	}
	return cursor;
}

void DiffView::MergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
	QTextCursor cursor = TextCursor();
	if (!cursor.hasSelection())
	{
		cursor.select(QTextCursor::WordUnderCursor);
	}
	cursor.mergeCharFormat(format);
}

void DiffView::SetSelectionStart(int position)
{
	selection_start_ = position;
}

void DiffView::SetSelectionEnd(int position)
{
	selection_end_ = position;
}

int DiffView::CursorPosition() const
{
	return cursor_position_;
}

int DiffView::SelectionStart() const
{
	return selection_start_;
}

int DiffView::SelectionEnd() const
{
	return selection_end_;
}

int DiffView::FontSize() const
{
	QTextCursor cursor = TextCursor();
	if (cursor.isNull())
	{
		return 0;
	}
	QTextCharFormat format = cursor.charFormat();
	return format.font().pointSize();
}

void DiffView::SetFontSize(int arg)
{
	QTextCursor cursor = TextCursor();
	if (cursor.isNull())
	{
		return;
	}
	QTextCharFormat format;
	format.setFontPointSize(arg);
	MergeFormatOnWordOrSelection(format);
	emit FontSizeChanged();
}

QStringList DiffView::DefaultFontSizes() const
{
	QStringList sizes;
	QFontDatabase db;
	for(int size: db.standardSizes())
	{
		sizes.append(QString::number(size));
	}
	return sizes;
}

} // namespace review
