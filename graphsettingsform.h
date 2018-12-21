#ifndef GRAPHSETTINGSFORM_H
#define GRAPHSETTINGSFORM_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class GraphSettingsForm;
}

class GraphSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit GraphSettingsForm(QWidget *parent = nullptr);
    ~GraphSettingsForm();

signals:
    void applyGraphSettings();

private:
    Ui::GraphSettingsForm *ui;

    QString m_sSettingsFile;

    void loadSettings();
    void saveSettings();
    bool autoscalex;
    bool autoscaley;

private slots:
    void apply();
};

#endif // GRAPHSETTINGSFORM_H
