#ifndef SCANNETWORKSVIEW_H
#define SCANNETWORKSVIEW_H

#include <QWidget>
#include <QStringListModel>
#include <QListView>

namespace Ui {
class ScanNetworksView;
}

class ScanNetworksView : public QWidget
{
    Q_OBJECT

public:
    explicit ScanNetworksView(QWidget *parent = 0);
    ~ScanNetworksView();

private slots:
    void scanNetworks(void);

private:
    Ui::ScanNetworksView *ui;

    QStringListModel *networkListModel;
    QListView *networkListView;
    QString extractString(QString text);
};

#endif // SCANNETWORKSVIEW_H
