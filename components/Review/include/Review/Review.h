#pragma once
#include <QtQuick/QQuickItem>
#include <Cli/Options.h>
#include <Git/AnnotatedDiff.h>
#include <Review/DiffModel.h>

namespace review {

class Review : public QQuickItem
{
	Q_OBJECT
	Q_PROPERTY(DiffModel* diff READ Diff WRITE SetDiff NOTIFY DiffChanged)

public:
	Review();
	Review(const cli::Options& options);

	DiffModel* Diff() const;

public Q_SLOTS:
	void SetDiff(DiffModel* diff);

Q_SIGNALS:
	void DiffChanged(DiffModel* diff);

private:
	DiffModelPtr diff_;
};

} // namespace review
