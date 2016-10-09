#include <algorithm>
#include <Git/AnnotatedDiff.h>
#include <Review/DiffDelta.h>
#include <Review/DiffModel.h>

namespace review {

DiffModel::DiffModel()
{
}

DiffModel::DiffModel(const std::string& from,
	const std::string& to,
	const std::string& repo_path)
{
	auto repo = std::make_shared<git::Repo>(repo_path);
	auto diff = std::make_shared<git::Diff>(repo, from, to, git::DiffOptions());
	adiff_ = std::make_shared<git::AnnotatedDiff>(diff, repo);

	auto git_deltas = adiff_->Deltas();
	std::transform(
		git_deltas.begin(), git_deltas.end(), std::back_inserter(deltas_), [](auto& delta) {
			return std::make_shared<DiffDelta>(delta);
		});
}

QVector<QString> DiffModel::Paths() const
{
	QVector<QString> file_paths;
	const auto& deltas = adiff_->Deltas();
	std::transform(
		deltas.begin(), deltas.end(), std::back_inserter(file_paths), [](auto& delta) {
			return QString::fromStdString(delta->NewFile().Path());
		});
	return file_paths;
}

QList<QObject*> DiffModel::Deltas()
{
	QList<QObject*> deltas;
	std::transform(
		deltas_.begin(), deltas_.end(), std::back_inserter(deltas), [](auto& delta) {
			return delta.get();
		});
	return deltas;
}

} // namespace review
