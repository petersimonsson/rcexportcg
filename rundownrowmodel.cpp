/**************************************************************************
  RCExportCG
  Copyright (C) 2017  Peter Simonsson <peter.simonsson@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/
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
    case Qt::DecorationRole:
        if(index.column() == 0 && row->preset().isEmpty())
            return QIcon(":/icons/error.png");
        break;
    case Qt::DisplayRole:
        switch(index.column())
        {
        case 1:
            return row->pageNumber();
        case 2:
            return row->storySlug();
        case 3:
            return attributesToString(row->attributes());
        }
        break;
    case Qt::ToolTipRole:
        switch(index.column())
        {
        case 0:
            if(row->preset().isEmpty())
                return tr("Missing preset");
            break;
        case 3:
            return attributesToString(row->attributes());
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
        case 1:
            return tr("Page");
        case 2:
            return tr("Story Slug");
        case 3:
            return tr("Attributes");
        }
    }

    return QVariant();
}

bool RundownRowModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!hasIndex(index.row(), index.column(), index.parent()))
        return false;

    RundownRow *row = m_rowList[index.row()];

    switch(role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        switch(index.column())
        {
        case 1:
            row->setPageNumber(value.toString());
            emit dataChanged(index, index);
            return true;
        case 2:
            row->setStorySlug(value.toString());
            emit dataChanged(index, index);
            return true;
        }
    case Qt::DecorationRole:
        row->setPreset(value.toString());
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

QString
RundownRowModel::attributesToString(const QVariantHash &attributes)
{
    QStringList attrString;
    QVariantHash::const_iterator it = attributes.begin();
    for(; it != attributes.end(); ++it)
        attrString.append(tr("%1 = %2").arg(it.key(), it.value().toString()));

    return attrString.join(", ");
}
