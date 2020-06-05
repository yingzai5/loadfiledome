#include "TfileThread.h"
#include <QDir>
#include <QtDebug>

TfileThread::TfileThread(QObject* parent) : QThread(parent)
{
   //this->wait();
}
TfileThread::~TfileThread()
{

}


void TfileThread::run()
{
    m_filelist.clear();
    QDir dir;
    dir.setPath(m_path);
    QFileInfoList infolist = dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList infolist2;
     qDebug()<<infolist;
    QFileInfo  info;
    //foreach(const QFileInfo & info,infolist)
    for(int i=0; i < infolist.count(); i++)
    {
        info =infolist.at(i);
        if(info.isDir())
        {
            dir.setPath(info.absoluteFilePath());
            infolist2 =dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
            infolist.append(infolist2);
        } else{
            m_filelist<<info.absoluteFilePath();
            qDebug()<<"file:" << info.absoluteFilePath();
        }
    }
    emit sigloadending(m_filelist.count());
}


void TfileThread::startload(QString& path)
{
    m_path = path;
    this->start();
}

QList<QString>TfileThread::Getfilelist()
{
    return  m_filelist;
}
