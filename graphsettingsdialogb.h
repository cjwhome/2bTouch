#ifndef GRAPHSETTINGSDIALOGB_H
#define GRAPHSETTINGSDIALOGB_H

#include <QDialog>

namespace Ui {
class GraphSettingsDialogB;
}

class GraphSettingsDialogB : public QDialog
{
    Q_OBJECT

public:
    explicit GraphSettingsDialogB(QWidget *parent = nullptr);
    ~GraphSettingsDialogB();

signals:
    void applyGraphSettings();

private:
    Ui::GraphSettingsDialogB *ui;

    QString m_sSettingsFile;

    void loadSettings();
    void saveSettings();
    bool autoscalex;
    bool autoscaley;

private slots:
    void apply();
};

#endif // GRAPHSETTINGSDIALOGB_H
