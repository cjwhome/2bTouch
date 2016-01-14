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

    QString getCom_port() const;
    void setCom_port(const QString &value);

    QString getDiagnosticA_units() const;
    void setDiagnosticA_units(const QString &value);

    QString getDiagnosticB_units() const;
    void setDiagnosticB_units(const QString &value);

    QString getDiagnosticC_units() const;
    void setDiagnosticC_units(const QString &value);

    QString getMain_display_name() const;
    void setMain_display_name(const QString &value);

    QString getDiagnosticA_name() const;
    void setDiagnosticA_name(const QString &value);

    QString getDiagnosticB_name() const;
    void setDiagnosticB_name(const QString &value);

    QString getDiagnosticC_name() const;
    void setDiagnosticC_name(const QString &value);

    int getDiagnosticA_position() const;
    void setDiagnosticA_position(int value);

    int getDiagnosticB_position() const;
    void setDiagnosticB_position(int value);

    int getDiagnosticC_position() const;
    void setDiagnosticC_position(int value);



private:
    QString device_name;
    QString main_display_name;
    QString main_display_units;
    QString diagnosticA_units;
    QString diagnosticB_units;
    QString diagnosticC_units;
    QString diagnosticA_name;
    QString diagnosticB_name;
    QString diagnosticC_name;
    QString com_port;
    int main_display_position;      //this tells where the main (ozone, NO2, yada yada yada) is located in the qlist
    int diagnosticA_position;
    int diagnosticB_position;
    int diagnosticC_position;
    int date_position;          //this tells where the date/time is located in the qlist
    int time_position;
    int number_of_columns;
};

#endif // DEVICEPROFILE_H
