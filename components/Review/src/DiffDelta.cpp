#include <algorithm>
#include <QQmlEngine>
#include <Review/DiffDelta.h>
#include <Review/DiffLine.h>

namespace review {

DiffDelta::DiffDelta(const git::AnnotatedDiffDeltaPtr& delta)
: QAbstractTableModel(nullptr)
, delta_(delta)
{
	role_name_mapping_[static_cast<int>(Roles::RowNumber)] = "rowNumber";
	role_name_mapping_[static_cast<int>(Roles::CommitInfo)] = "commitInfo";
	role_name_mapping_[static_cast<int>(Roles::Text)] = "text";
	auto git_lines = delta_->Lines();
	std::transform(
		git_lines.begin(), git_lines.end(), std::back_inserter(lines_), [this](auto& line) {
			auto diff_line = std::make_shared<DiffLine>(line);
			QQmlEngine::setObjectOwnership(diff_line.get(), QQmlEngine::CppOwnership);
			return diff_line;
		});
}

QString DiffDelta::Path() const
{
	return QString::fromStdString(delta_->NewFile().Path());
}

QVariant DiffDelta::Line(int line_index) const
{
	if (line_index < 0 || static_cast<size_t>(line_index) > lines_.size())
	{
		return QVariant();
	}
	return QVariant::fromValue(lines_[line_index].get());
}

int DiffDelta::columnCount(const QModelIndex& /*parent*/) const
{
	return 3;
}

QVariant DiffDelta::data(const QModelIndex& index, int role_index) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	auto row = index.row();
	auto role = static_cast<Roles>(role_index);
	switch (role)
	{
	case Roles::RowNumber:
		return QVariant::fromValue(lines_[row]->LineNumber());
	case Roles::CommitInfo:
		return lines_[row]->GetCommit()->Summary();
	case Roles::Text:
		return lines_[row]->Text();
	}
	return QVariant();
}

int DiffDelta::rowCount(const QModelIndex& /*parent*/) const
{
	return lines_.size();
}

QHash<int, QByteArray> DiffDelta::roleNames() const
{
	return role_name_mapping_;
}

} // namespace review
