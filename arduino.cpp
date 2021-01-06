#include "arduino.h"
#include <QDebug>

arduino::arduino()
{

}

int arduino::connect_arduino()
{

    serial=new QSerialPort;
    foreach(const QSerialPortInfo &serial_port_info,QSerialPortInfo::availablePorts()){
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
            if(serial_port_info.vendorIdentifier()==arduino_uno_vendor_id && serial_port_info.productIdentifier()==arduino_uno_producy_id ){
                arduino_is_available=true;
                arduino_port_name=serial_port_info.portName();


            }
        }
        }

        if(arduino_is_available){
            qDebug()<<"arduino port name is :"<<arduino_port_name;
                serial->setPortName(arduino_port_name);
             if(serial->open(QSerialPort::ReadWrite))
             {
                 serial->open(QIODevice::ReadWrite);

                serial->setBaudRate(QSerialPort::Baud9600);
                serial->setDataBits(QSerialPort::Data8);
                serial->setParity(QSerialPort::NoParity);
                serial->setStopBits(QSerialPort::OneStop);
                serial->setFlowControl(QSerialPort::NoFlowControl);

                return 0;
             }
            return  1;
        }

}
int arduino::close_arduino()
{
    if(serial->isOpen())
    {
        serial->close();
        return 0;
    }
    return 1;
}
QByteArray arduino::read_from_arduino()
{
    QByteArray data="";
    serial->bytesAvailable();
    data=serial->readLine();
    return data;


}
int arduino::write_to_arduino(QByteArray d)
{

    if(serial->isWritable())
    {
        serial->write(d);
    }else qDebug()<<"couldn't write to serial ";
}
QSqlQueryModel *  arduino ::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select to_char(DATE_MESURE,'dd/mm/yyyy hh24:mi:ss'),temp,hum from historique_temp order by date_mesure desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("DATE_MESURE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("temp"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("hum"));
    return model;
}
