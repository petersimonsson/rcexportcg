#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class CasparCGVideoMetaData;
class CasparCGStillMetaData;

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    void setRundownCreatorUrl(const QString &url);
    QString rundownCreatorUrl() const;
    void setRundownCreatorApiKey(const QString &key);
    QString rundownCreatorApiKey() const;
    void setRundownCreatorApiToken(const QString &token);
    QString rundownCreatorApiToken() const;

    void setCasparCGRundownLocation(const QString &location);
    QString casparCGRundownLocation() const;

    void setCasparCGVideoMetadata(const CasparCGVideoMetaData &metadata);
    CasparCGVideoMetaData casparCGVideoMetadata() const;

    void setCasparCGStillMetadata(const CasparCGStillMetaData &metadata);
    CasparCGStillMetaData casparCGStillMetadata() const;

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
