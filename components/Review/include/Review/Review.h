#pragma once
#include <QtQuick/QQuickItem>
#include <Git/AnnotatedDiff.h>
#include <Review/DiffModel.h>

namespace review {

class Review : public QQuickItem
{
	Q_OBJECT
	Q_PROPERTY(DiffModel* diff READ Diff WRITE SetDiff NOTIFY DiffChanged)

public:
	Review();
	Review(const std::string& from, const std::string& to, const std::string& repo);

	DiffModel* Diff() const;

public Q_SLOTS:
	void SetDiff(DiffModel* diff);

Q_SIGNALS:
	void DiffChanged(DiffModel* diff);

private:
	QDiffPtr diff_;
};

} // namespace review
