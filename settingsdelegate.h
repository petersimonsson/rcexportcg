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
#ifndef SETTINGSDELEGATE_H
#define SETTINGSDELEGATE_H

#include <QStyledItemDelegate>

class SettingsDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit SettingsDelegate(QWidget *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void setPresets(const QStringList &presets);
    void setObjects(const QStringList &objects);

private slots:
    void commitAndCloseEditor();

private:
    QStringList m_presets;
    QStringList m_objects;
};

#endif // SETTINGSDELEGATE_H
