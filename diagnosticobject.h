#ifndef DIAGNOSTICOBJECT_H
#define DIAGNOSTICOBJECT_H

#include <QObject>
#include <QString>

class DiagnosticObject : public QObject
{
    Q_OBJECT
public:
    explicit DiagnosticObject(QObject *parent = 0);

    int position;
    QString name;
    QString type;
    int priority;
    QString units;
    bool error_available;
    double min;
    double max;
    QString value;

signals:

public slots:
};

#endif // DIAGNOSTICOBJECT_H
