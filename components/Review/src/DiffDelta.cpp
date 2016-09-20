#include <algorithm>
#include <Review/DiffDelta.h>
#include <Review/DiffLine.h>

namespace review {

DiffDelta::DiffDelta(const git::AnnotatedDiffDeltaPtr& delta)
: delta_(delta)
{
	auto git_lines = delta_->Lines();
	std::transform(
	    git_lines.begin(), git_lines.end(), std::back_inserter(lines_), [this](auto& line) {
		    return std::make_shared<DiffLine>(line);
		});
}

QList<QObject*> DiffDelta::Lines()
{
	QList<QObject*> lines;
	std::transform(lines_.begin(), lines_.end(), std::back_inserter(lines), [](auto& line) {
		return static_cast<QObject*>(line.get());
	});
	return lines;
}

QString DiffDelta::Path() const
{
	return QString::fromStdString(delta_->NewFile().Path());
}

} // namespace review
