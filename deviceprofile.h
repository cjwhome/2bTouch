#ifndef DEVICEPROFILE_H
#define DEVICEPROFILE_H
#include <QString>

class DeviceProfile
{
public:
    DeviceProfile();

    QString getDevice_name() const;
    void setDevice_name(const QString &value);

    int getMain_display_position() const;
    void setMain_display_position(int value);

    int getDatetime_position() const;
    void setDatetime_position(int value);

private:
    QString device_name;
    int main_display_position;      //this tells where the main (ozone, NO2, yada yada yada) is located in the qlist
    int datetime_position;          //this tells where the date/time is located in the qlist
};

#endif // DEVICEPROFILE_H
