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
private:
    QString usbPath;
    QString usb_device_root;
    QString full_data_path;
};

#endif // FILEWRITER_H
