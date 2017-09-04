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

#include <QIcon>

RundownRowModel::RundownRowModel(QObject *parent) :
    QAbstractItemModel(parent), m_videoIcon(":/icons/Movie.png"),
    m_imageIcon(":/icons/Still.png")
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

    return 3;
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
            return row->attributes().value("file").toString();
        }
        break;
    case Qt::DecorationRole:
        if(index.column() == 0)
        {
            if(row->type() == "video")
                return m_videoIcon;
            else if(row->type() == "image")
                return m_imageIcon;
        }
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
            return tr("File");
        }
    }

    return QVariant();
}
