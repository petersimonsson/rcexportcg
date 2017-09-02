#ifndef CASPARCGGENERATOR_H
#define CASPARCGGENERATOR_H

#include <QObject>
#include <QHash>

class RundownRowModel;
class CasparCGMetaData;

class QIODevice;

class CasparCGGenerator : public QObject
{
    Q_OBJECT
public:
    explicit CasparCGGenerator(QObject *parent = nullptr);

    void convert(RundownRowModel *rowModel, QIODevice *output);

    void insertMetadata(const QString &type, CasparCGMetaData *metadata) { m_metadata.insert(type, metadata); }

private:
    QHash<QString, CasparCGMetaData*> m_metadata;
};

#endif // CASPARCGGENERATOR_H
