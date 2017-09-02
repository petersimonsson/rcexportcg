#ifndef RUNDOWNROWMODEL_H
#define RUNDOWNROWMODEL_H

#include <QAbstractItemModel>
#include <QList>

class RundownRow;

class RundownRowModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit RundownRowModel(QObject *parent = nullptr);
    virtual ~RundownRowModel();

    void clear();
    void appendRow(RundownRow* row);
    QList<RundownRow*> rowList() const { return m_rowList; }

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    QList<RundownRow*> m_rowList;
};

#endif // RUNDOWNROWMODEL_H
