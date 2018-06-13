#ifndef MODBUS_SERVER_H
#define MODBUS_SERVER_H

#include <QObject>
#include <QtNetwork>
#include <QList>
#include <QSettings>
#include <QDebug>

#define PORT        (502)
#define UNIT_ID     (9)

class ModbusServer : public QObject
{
    Q_OBJECT
public:
    enum Regs {
        MAIN_VALUE = 0
    };

private:
    static ModbusServer *singleton;
    explicit ModbusServer(QObject *parent = nullptr);

    QTcpServer tcpServer;
    QList<QTcpSocket *> clients;

    QSettings *settings;

    struct modbus_request
    {
        int transactionID;
        int unitID;
        int functionCode;
        int startPos;

        modbus_request() {}
        modbus_request(QByteArray *data) {
            qDebug()<<data;

            transactionID = (data->at(0)<<8) + data->at(1);
            unitID = data->at(6);
            functionCode = data->at(7);
            startPos = (data->at(8)<<8) + data->at(9);
        }

        QByteArray* make_preamble(){
            QByteArray *preamble = new QByteArray();
            //Transaction ID
            preamble->append(transactionID>>8);
            preamble->append(transactionID & 0xFF);
            //Protocol
            preamble->append('\0');
            preamble->append('\0');
            //Size: 4, 5
            preamble->append('\0');
            preamble->append('\3');
            //Unit ID
            preamble->append(UNIT_ID);
            //Func Code
            preamble->append(functionCode);

            return preamble;
        }
    };

    struct modbus_register
    {
        int startAddress;
        QByteArray *value;

        modbus_register() {}
        modbus_register(int addr, QByteArray *val) {
            startAddress = addr;
            value = val;
        }

        int wordCount() {
            return value->length();
        }

        bool containsAddress(int addr) {
            return ((startAddress <= addr) && (addr < (startAddress + wordCount())));
        }

        void addByte(QByteArray *message, int addr) {
            int currentLength = (message->at(4)<<8) + message->at(5);
            currentLength += 2;
            int byteIndex = addr - startAddress;
            message->append(value->at(byteIndex)>>8);
            message->append(value->at(byteIndex) & 0xFF);
            int a = currentLength>>8;
            int b = currentLength & 0xFF;
            message->replace(4, 1, QString(currentLength>>8).toLatin1().data(), 1);
            message->replace(5, 1, QString(currentLength & 0xFF).toLatin1().data(), 1);
        }

        static void copyEmpty(QByteArray *message) {
            int currentLength = (message->at(4)<<8) + message->at(5);
            currentLength += 2;
            message->append('\0');
            message->append('\0');
            message->replace(4, 1, QString(currentLength>>8).toLatin1().data(), 1);
            message->replace(5, 1, QString(currentLength & 0xFF).toLatin1().data(), 1);
        }
    };
    QList<modbus_register *> registers;

signals:

public slots:
    static ModbusServer *getInstance() {
        if (singleton == nullptr) {
            singleton = new ModbusServer();
        }
        return singleton;
    }
    void newConnection();
    void readAvailable();
    QByteArray* parseData(QByteArray *data);
    QByteArray* read_multiple_registers(modbus_request *req, QByteArray *data);

    void updateRegister(int position, QByteArray *value);
    void deleteRegister(int address);
};

#endif // MODBUS_SERVER_H
