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

    int getDate_position() const;
    void setDate_position(int value);

    int getTime_position() const;
    void setTime_position(int value);

    QString getMain_display_units() const;
    void setMain_display_units(const QString &value);

    int getNumber_of_columns() const;
    void setNumber_of_columns(int value);

private:
    QString device_name;
    QString main_display_units;
    int main_display_position;      //this tells where the main (ozone, NO2, yada yada yada) is located in the qlist
    int date_position;          //this tells where the date/time is located in the qlist
    int time_position;
    int number_of_columns;
};

#endif // DEVICEPROFILE_H
