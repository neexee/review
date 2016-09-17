#pragma once
#include <memory>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QVector>

#include "AnnotatedDiff.h"

namespace review {

class DiffModel: public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString text READ Text NOTIFY TextChanged)
	Q_PROPERTY(QVector<QString> paths READ Paths NOTIFY PathsChanged)
public:
	DiffModel(const std::string& from, const std::string& to,
		  const std::string& repo);
	QString Text() const;
	QVector<QString> Paths() const;

Q_SIGNALS:
	void TextChanged();
	void PathsChanged();

private:
	git::AnnotatedDiffPtr adiff_;
};

typedef std::shared_ptr<DiffModel> QDiffPtr;

} // namespace review

//Q_DECLARE_METATYPE(review::QDiff*)
