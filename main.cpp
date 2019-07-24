#include <QCoreApplication>
#include <QDebug>
#include <qthread.h>

#include "config.pb.h"

rpcmethod::MethodRegist testdata;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testdata.Clear();
    testdata.set_id( 1 );
    testdata.set_method("update");
    testdata.set_optional1(9);

    int size = testdata.ByteSize();
    char *buff;
    buff = (char *)malloc(size);
    testdata.SerializeToArray(buff, size);

    char *recvBuf;
    recvBuf=(char *)malloc(size);
    for(int i = 0; i < size; i++){
        recvBuf[i] = buff[i];
    }

    rpcmethod::MethodRegist t;
    t.ParseFromArray( recvBuf,size );

    qDebug("%d", t.id());
    qDebug("%d", t.optional1());
    qDebug() << QString::fromStdString(t.method());
    QThread::sleep(10000);
    return 0;
}
