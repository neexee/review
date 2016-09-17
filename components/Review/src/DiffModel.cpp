#include "DiffModel.h"
#include "AnnotatedDiff.h"
#include "DiffFormat.h"

namespace review {

DiffModel::DiffModel(const std::string& from, const std::string& to,
				  const std::string& repo_path)
{
	auto repo = std::make_shared<git::Repo>(repo_path);
	auto diff = std::make_shared<git::Diff>(repo, from,
											to, git::DiffOptions());
	adiff_ = std::make_shared<git::AnnotatedDiff>(diff, repo);
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

} // namespace review