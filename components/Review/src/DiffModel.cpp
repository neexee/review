#include <algorithm>
#include <Review/DiffModel.h>
#include <Git/AnnotatedDiff.h>
#include <Cli/DiffFormat.h>

namespace review {

DiffModel::DiffModel(const std::string& from, const std::string& to,
				  const std::string& repo_path)
{
	auto repo = std::make_shared<git::Repo>(repo_path);
	auto diff = std::make_shared<git::Diff>(repo, from,
											to, git::DiffOptions());
	adiff_ = std::make_shared<git::AnnotatedDiff>(diff, repo);

	auto git_deltas = adiff_->Deltas();
	std::transform(git_deltas.begin(), git_deltas.end(), std::back_inserter(deltas_),
				   [](auto& delta) { return std::make_shared<DiffDelta>(delta); });
}

QVector<QString> DiffModel::Paths() const
{
	QVector<QString> file_paths;
	auto deltas = adiff_->Deltas();
	std::transform(deltas.begin(), deltas.end(), std::back_inserter(file_paths),
				   [](auto& delta){ return QString::fromStdString(delta.NewFile().Path()); });
	return file_paths;
}

QString DiffModel::Text() const
{
	namespace cd = cliutils::diff;
	cd::PrintOptions options{cd::Format::Patch, cd::Appearance::Plain};

	auto text = cd::ToString(adiff_, options);
	return QString::fromStdString(text);
}

QList<QObject*> DiffModel::Deltas()
{
	QList<QObject*> deltas;
	std::transform(deltas_.begin(), deltas_.end(), std::back_inserter(deltas),
				   [](auto& delta) { return delta.get(); });
	return deltas;
}

int DiffModel::CountDeltas(QQmlListProperty<DiffDelta>* property)
{
	auto model = static_cast<DiffModel*>(property->data);
	return model->deltas_.size();
}

DiffDelta* DiffModel::At(QQmlListProperty<DiffDelta>* property, int index)
{
	auto model = static_cast<DiffModel*>(property->data);
	return model->deltas_[index].get();
}

} // namespace review
