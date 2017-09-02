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
