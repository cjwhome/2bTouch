#ifndef FILEWRITER_H
#define FILEWRITER_H
#include <QFile>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QDir>
//creates a csv file
class FileWriter
{
public:
    FileWriter();
    void writeHeader();
    void appendRow();
    bool checkIfUsbMounted();
    QString getUsbPath() const;
    void setUsbPath(const QString &value);

    bool createDataFolder(QString deviceName);

    QString getFull_data_path() const;
    void setFull_data_path(const QString &value);

private:
    QString usbPath;
    QString usb_device_root;
    QString local_path;
    QString full_data_path;
    bool usbMounted;

};

#endif // FILEWRITER_H
