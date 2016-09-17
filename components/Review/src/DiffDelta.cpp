#include <algorithm>
#include <Review/DiffDelta.h>

namespace review {

DiffDelta::DiffDelta(const git::AnnotatedDiffDelta& delta)
: delta_(delta)
{
	auto git_lines = delta_.Lines();
	std::transform(git_lines.begin(), git_lines.end(), std::back_inserter(lines_),
				   [](auto& line) { return std::make_shared<DiffLine>(line); });
}

QList<QObject*> DiffDelta::Lines()
{
	QList<QObject*> lines;
	std::transform(lines_.begin(), lines_.end(), std::back_inserter(lines),
				   [](auto& line) { return line.get(); });
	return lines;
}

int DiffDelta::CountLines(QQmlListProperty<DiffLine>* property)
{
	auto delta = static_cast<DiffDelta*>(property->data);
	return delta->lines_.size();
}

DiffLine* DiffDelta::At(QQmlListProperty<DiffLine>* property, int index)
{
	auto delta = static_cast<DiffDelta*>(property->data);
	return delta->lines_[index].get();
}

} // namespace review
