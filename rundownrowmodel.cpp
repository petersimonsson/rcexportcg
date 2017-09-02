#include "rundownrowmodel.h"
#include "rundownrow.h"

RundownRowModel::RundownRowModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

RundownRowModel::~RundownRowModel()
{
    qDeleteAll(m_rowList);
    m_rowList.clear();
}

void RundownRowModel::clear()
{
    beginResetModel();
    qDeleteAll(m_rowList);
    m_rowList.clear();
    endResetModel();
}

void RundownRowModel::appendRow(RundownRow* row)
{
    beginInsertRows(QModelIndex(), m_rowList.count(), m_rowList.count());
    m_rowList.append(row);
    endInsertRows();
}

QModelIndex RundownRowModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    return createIndex(row, column, m_rowList[row]);
}

QModelIndex RundownRowModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)

    return QModelIndex();
}

int RundownRowModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return m_rowList.count();
}

int RundownRowModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 4;
}

QVariant RundownRowModel::data(const QModelIndex &index, int role) const
{
    if(!hasIndex(index.row(), index.column(), index.parent()))
        return QVariant();

    RundownRow *row = m_rowList[index.row()];

    switch(role)
    {
    case Qt::DisplayRole:
        switch(index.column())
        {
        case 0:
            return row->pageNumber();
        case 1:
            return row->storySlug();
        case 2:
            return row->type();
        case 3:
            return row->file();
        }
        break;
    }

    return QVariant();
}

QVariant RundownRowModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation != Qt::Horizontal)
        return QVariant();

    switch(role)
    {
    case Qt::DisplayRole:
        switch(section)
        {
        case 0:
            return tr("Page");
        case 1:
            return tr("Story Slug");
        case 2:
            return tr("Type");
        case 3:
            return tr("File");
        }
    }

    return QVariant();
}
