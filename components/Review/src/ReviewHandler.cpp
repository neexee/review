#include <QtCore/QFileInfo>
#include <QtGui/QTextCursor>
#include <QtGui/QFontDatabase>

#include "Diff.h"
#include "Repo.h"
#include "DiffFormat.h"

#include "ReviewHandler.h"

ReviewHandler::ReviewHandler()
: target_(0)
, doc_(0)
, cursor_position_(-1)
, selection_start_(0)
, selection_end_(0)
{
}

void ReviewHandler::Init(const std::string& repo_path,
	const std::string& from_commitish, const std::string& to_commitish)
{
	repo_path_ = repo_path;
	from_commitish_ = from_commitish;
	to_commitish_ = to_commitish;

	auto diff = LoadDiff();
	namespace cd = cliutils::diff;
	cd::PrintOptions options{cd::Format::Patch, cd::Appearance::Plain};
	SetText(QString::fromStdString(ToString(diff, options)));
}

git::AnnotatedDiff ReviewHandler::LoadDiff()
{
	auto repo = std::make_shared<git::Repo>(repo_path_);
	auto diff = std::make_shared<git::Diff>(repo, from_commitish_,
											to_commitish_, git::DiffOptions());

	return git::AnnotatedDiff(diff, repo);
}

void ReviewHandler::SetTarget(QQuickItem *target)
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
		QQuickTextDocument *qqdoc = doc.value<QQuickTextDocument *>();
		if (qqdoc)
		{
			doc_ = qqdoc->textDocument();
		}
	}
	emit TargetChanged();
}

void ReviewHandler::SetText(const QString &arg)
{
	if (text_ != arg)
	{
		text_ = arg;
		emit TextChanged();
	}
}

QString ReviewHandler::Text() const
{
	return text_;
}

void ReviewHandler::SetCursorPosition(int position)
{
	if (position == cursor_position_)
	{
		return;
	}

	cursor_position_ = position;

	Reset();
}

void ReviewHandler::Reset()
{
	emit FontSizeChanged();
}

QTextCursor ReviewHandler::TextCursor() const
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

void ReviewHandler::MergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
	QTextCursor cursor = TextCursor();
	if (!cursor.hasSelection())
	{
		cursor.select(QTextCursor::WordUnderCursor);
	}
	cursor.mergeCharFormat(format);
}

void ReviewHandler::SetSelectionStart(int position)
{
	selection_start_ = position;
}

void ReviewHandler::SetSelectionEnd(int position)
{
	selection_end_ = position;
}

int ReviewHandler::CursorPosition() const
{
	return cursor_position_;
}

int ReviewHandler::SelectionStart() const
{
	return selection_start_;
}

int ReviewHandler::SelectionEnd() const
{
	return selection_end_;
}

int ReviewHandler::FontSize() const
{
	QTextCursor cursor = TextCursor();
	if (cursor.isNull())
	{
		return 0;
	}
	QTextCharFormat format = cursor.charFormat();
	return format.font().pointSize();
}

void ReviewHandler::SetFontSize(int arg)
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

QStringList ReviewHandler::DefaultFontSizes() const
{
	QStringList sizes;
	QFontDatabase db;
	for(int size: db.standardSizes())
	{
		sizes.append(QString::number(size));
	}
	return sizes;
}
