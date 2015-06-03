#ifndef DISPLAYGRAPH_H
#define DISPLAYGRAPH_H

#include <QWidget>

namespace Ui {
class DisplayGraph;
}

class DisplayGraph : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayGraph(QWidget *parent = 0);
    ~DisplayGraph();

private:
    Ui::DisplayGraph *ui;
};

#endif // DISPLAYGRAPH_H
