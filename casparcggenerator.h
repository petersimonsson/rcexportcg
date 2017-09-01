#ifndef CASPARCGGENERATOR_H
#define CASPARCGGENERATOR_H

#include <QObject>

class RundownRow;

class QIODevice;

class CasparCGGenerator : public QObject
{
    Q_OBJECT
public:
    explicit CasparCGGenerator(QObject *parent = nullptr);

    void setDevice (const QString &device) { m_deviceName = device; }

    void convert(const QList<RundownRow*> &rowList, QIODevice *output);

private:
    QString m_deviceName;
};

#endif // CASPARCGGENERATOR_H
