#pragma once
#include <memory>
#include <QObject>
#include <QString>

#include <Git/Commit.h>

namespace review {

class Commit : public QObject
{
	Q_OBJECT

public:
	Commit();
	Commit(const git::CommitPtr& commit);

	Q_INVOKABLE QString Summary() const;
	Q_INVOKABLE QString ShortHex() const;

private:
	git::CommitPtr commit_;
};

typedef std::shared_ptr<Commit> CommitPtr;

} // namespace review
