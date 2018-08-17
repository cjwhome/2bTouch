#ifndef MODBUS_SERVER_H
#define MODBUS_SERVER_H

#include <QObject>
#include <QtNetwork>
#include <QList>
#include <QSettings>
#include <QDebug>
#include <sstream>

#define PORT        (502)
#define UNIT_ID     (9)

#define READ_MULTIPLE_REG_FUNC  0x03
#define WRITE_MULTIPLE_REG_FUNC   0x10

class ModbusServer : public QObject
{
    Q_OBJECT

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
        modbus_register(int addr, float f) {
            static_assert(std::numeric_limits<float>::is_iec559, "Not An IEEE FLOAT!!!");
            union { float fval; std::uint32_t ival; };
            fval = f;

            std::uint32_t *testArr = &ival;
            std::uint8_t *test8_1 = (std::uint8_t *) testArr;
            std::uint8_t *test8_2 = (std::uint8_t *) testArr+1;
            std::uint8_t *test8_3 = (std::uint8_t *) testArr+2;
            std::uint8_t *test8_4 = (std::uint8_t *) testArr+3;

            QByteArray *array = new QByteArray();
            array->append(*test8_4);
            array->append(*test8_3);
            array->append(*test8_2);
            array->append(*test8_1);

            std::ostringstream stm;
            stm << std::hex << std::uppercase << ival;
            QString strVal = QString::fromStdString(stm.str());
            qDebug()<<strVal;

            init(addr, array);
        }
        modbus_register(int addr, QByteArray *val, bool interpolate=true) {
            if (interpolate) {
                QByteArray *array = new QByteArray();
                for (int i = 0; i < val->length(); i++) {
                    array->append('\0');
                    array->append(val->at(i));
                }
                init(addr, array);
            } else {
                init(addr, val);
            }
        }
        modbus_register(int addr, QString *str) {
            //init(addr, new QByteArray(str->toLatin1()));
            QByteArray *array = new QByteArray();
            for (int i = 0; i < str->length(); i++) {
                array->append('\0');
                array->append(str->at(i));
            }
            init(addr, array);
        }
        modbus_register(int addr, int val) {
            int count = 0;
            int temp = val;
            while (temp != 0) {
                temp >>= 8;
                count ++;
            }
            QByteArray *arr = new QByteArray();
            if (count % 2 == 1) {
                count ++;
            }
            for (int i = 0; i < count/2; i += 2) {
                arr->append((val >> (8 * (i+1))) & 0xFF);
                arr->append((val >> (8 * i)) & 0xFF);
            }
            init(addr, arr);
        }
        void init(int addr , QByteArray *val) {
            this->startAddress = addr;
            this->value = val;
        }

        int wordCount() {
            return (value->length() / 2);
        }

        bool containsAddress(int addr) {
            return ((startAddress <= addr) && (addr < (startAddress + wordCount())));
        }

        void addByte(QByteArray *message, int addr) {
            int currentLength = (message->at(4)<<8) + message->at(5);
            currentLength += 2;
            int byteIndex = addr - startAddress;
            message->append(value->at(byteIndex*2));
            message->append(value->at(byteIndex*2 + 1));
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

    static void addByte(QByteArray *data, int value) {
        int currentLength = (data->at(4)<<8) + data->at(5);
        currentLength += 2;
        data->replace(4, 1, QString(currentLength>>8).toLatin1().data(), 1);
        data->replace(5, 1, QString(currentLength & 0xFF).toLatin1().data(), 1);
        data->append(value>>8);
        data->append(value & 0xFF);
    }

signals:
    void sendMsg(QString msg);

public:
    enum Regs {
        MAIN_VALUE = 0
    };

public slots:
    static ModbusServer *getInstance() {
        if (singleton == nullptr)
        {
            singleton = new ModbusServer();
        }
        return singleton;
    }
    void newConnection();
    void readAvailable();
    QByteArray* parseData(QByteArray *data);
    QByteArray* read_multiple_registers(modbus_request *req, QByteArray *data);
    QByteArray* write_multiple_register(modbus_request *req, QByteArray *data);

    void updateRegister(int position, QByteArray *value);
    void updateRegister(int address, int value);
    void updateRegister(int address, QString value);
    void updateRegister(int address, float value);
    void deleteRegister(int address);
};

#endif // MODBUS_SERVER_H
