#include "modbus_server.h"

ModbusServer* ModbusServer::singleton = nullptr;

ModbusServer::ModbusServer(QObject *parent) : QObject(parent)
{
    settings = new QSettings("2B Technologies", "2B Touch");

    if (tcpServer.listen(QHostAddress::Any, 50200)) {
        qDebug()<<"Started Modbus Server!";
    } else {
        qDebug()<<"Could not start Modbus Server!";
    }

    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void ModbusServer::newConnection()
{
    QTcpSocket *client = tcpServer.nextPendingConnection();
    clients<<client;

    connect(client, SIGNAL(readyRead()), this, SLOT(readAvailable()));
}

void ModbusServer::readAvailable()
{
    QTcpSocket *client = (QTcpSocket *) sender();
    QByteArray data = client->readAll();

    QByteArray *resp = parseData(&data);

    if (resp != nullptr) {
        client->write(*resp);
    }
}

QByteArray* ModbusServer::parseData(QByteArray *data)
{
    modbus_request *req = new modbus_request(data);
    QByteArray *resp = nullptr;
    if (req->unitID == UNIT_ID) {
        switch (req->functionCode) {
            case READ_MULTIPLE_REG_FUNC:
                resp = read_multiple_registers(req, data);
                break;
            case WRITE_MULTIPLE_REG_FUNC:
                resp = write_multiple_register(req, data);
                break;
            default:
                resp = nullptr;
        }
    }
    return resp;
}

//QByteArray* ModbusServer::read_multiple_registers(modbus_request *req, QByteArray *data)
//{
//    QByteArray *resp = req->make_preamble();
//    int wordCount = ((data->at(10)>>8) + data->at(11)) * 2;
//    resp->replace(4, 1, QString((wordCount + 3)>>8).toLatin1().data(), 1);
//    resp->replace(5, 1, QString((wordCount + 3) & 0xFF).toLatin1().data(), 1);

//    resp->append(wordCount);
//    for (int i = 0; i < wordCount/2; i++) {
//        int index = req->startPos + i;
//        if (index >= registers.length()) {
//            resp->append('\0');//(index>>8);
//            resp->append('\0');//(index & 0xFF);
//        } else {
//            resp->append(registers[index]>>8);
//            resp->append(registers[index] & 0xFF);
//        }
//    }

//    return resp;
//}

// MODBUS_PROTOCOL
QByteArray* ModbusServer::read_multiple_registers(modbus_request *req, QByteArray *data)
{
    QByteArray *resp = req->make_preamble();
    int wordCount = ((data->at(10)<<8) + data->at(11)) * 2;
    resp->append(wordCount);

    bool added = false;
    for (int i = 0; i < wordCount/2; i++) {
        added = false;
        for (int j = 0; j < registers.length(); j++) {
            if (registers[j]->containsAddress(req->startPos + i)) {
                registers[j]->addByte(resp, req->startPos + i);
                added = true;
                break;
            }
        }
        if (!added) {
            modbus_register::copyEmpty(resp);
        }
    }
    return resp;
}

QByteArray* ModbusServer::write_multiple_register(modbus_request *req, QByteArray *data)
{
    QByteArray *resp = req->make_preamble();
    int wordCount = ((data->at(10)<<8) + data->at(11));
    for (int i = 0; i < wordCount; i++) {
        int a = static_cast<unsigned int>(static_cast<unsigned char>(data->at(13 + (i*2))));
        int b = static_cast<unsigned int>(static_cast<unsigned char>(data->at(13 + (i*2 + 1))));
        int value = (a << 8) + (b);
        int test = (unsigned int) data->at(13 + (i*2 + 1));
        updateRegister(req->startPos + i, value);
    }
    addByte(resp, req->startPos);
    addByte(resp, wordCount);
    return resp;
}

//1. Position = existing position
//      register will overwrite the data in that register
//2. Position is part of a different register
//      Nothing happens
//3. Part of data has addresses in another register
//      The register that was added first will be displayed
//      on the conflicting addresses
void ModbusServer::updateRegister(int position, QByteArray *value)
{
    modbus_register *reg = nullptr;
    for (int i = 0; i < registers.length(); i++) {
        if (registers.at(i)->startAddress == position) {
            reg = new modbus_register(position, value); //registers.at(i);
            registers.replace(i, reg);
            return;
        } else if (registers.at(i)->containsAddress(position)) {
            return;
        }
    }

    if (reg == nullptr) {
        reg = new modbus_register(position, value);
        registers.append(reg);
    }
}

void ModbusServer::updateRegister(int position, int value)
{
    modbus_register *reg = nullptr;
    for (int i = 0; i < registers.length(); i++) {
        if (registers.at(i)->startAddress == position) {
            reg = new modbus_register(position, value); //registers.at(i);
            registers.replace(i, reg);
            return;
        } else if (registers.at(i)->containsAddress(position)) {
            return;
        }
    }

    if (reg == nullptr) {
        reg = new modbus_register(position, value);
        registers.append(reg);
    }
}

void ModbusServer::updateRegister(int position, QString base)
{
    modbus_register *reg = nullptr;
    for (int i = 0; i < registers.length(); i++) {
        if (registers.at(i)->startAddress == position) {
            reg = new modbus_register(position, new QString(base)); //registers.at(i);
            registers.replace(i, reg);
            return;
        } else if (registers.at(i)->containsAddress(position)) {
            return;
        }
    }

    if (reg == nullptr) {
        reg = new modbus_register(position, new QString(base));
        registers.append(reg);
    }
}

void ModbusServer::deleteRegister(int address)
{
    for (int i = 0; i < registers.length(); i++) {
        if (registers[i]->startAddress == address) {
            registers.removeAt(i);
            return;
        }
    }
}
