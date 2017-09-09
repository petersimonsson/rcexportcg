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
#include "settingsdelegate.h"

#include <QComboBox>
#include <QCollator>

SettingsDelegate::SettingsDelegate(QWidget *parent) :
    QStyledItemDelegate(parent)
{

}

QWidget *SettingsDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    if(index.column() == 1)
    {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(m_presets);
        connect(editor, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this, &SettingsDelegate::commitAndCloseEditor);
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void SettingsDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() == 1)
    {
        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        combo->setCurrentText(index.data().toString());
    }
    else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void SettingsDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    if(index.column() == 1)
    {
        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        model->setData(index, combo->currentText());
    }
    else
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void SettingsDelegate::commitAndCloseEditor()
{
    QComboBox *editor = qobject_cast<QComboBox *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

void SettingsDelegate::setPresets(const QStringList &presets)
{
    m_presets = presets;

    QCollator collator;
    collator.setNumericMode(true);

    std::sort(m_presets.begin(), m_presets.end(),
              [&collator](const QString &preset1, const QString &preset2) {
                  return collator.compare(preset1, preset2) < 0;
              });
}
