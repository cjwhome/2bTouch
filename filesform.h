#ifndef FILESFORM_H
#define FILESFORM_H

#include <QWidget>

namespace Ui {
class FilesForm;
}

class FilesForm : public QWidget
{
    Q_OBJECT

public:
    explicit FilesForm(QWidget *parent = nullptr);
    ~FilesForm();

private:
    Ui::FilesForm *ui;
};

#endif // FILESFORM_H
