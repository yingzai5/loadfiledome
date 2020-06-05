#include "TfileThread.h"
#include <QDir>
#include <QtDebug>
#include <QDateTime>

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
    qDebug()<<"start ::"<< QDateTime::currentDateTime();
    for(int i=0; i < infolist.count(); i++)
    {
        if (this->isInterruptionRequested())
            return;
        info =infolist.at(i);
        if(info.isDir())
        {
            dir.setPath(info.absoluteFilePath());
            infolist2 =dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
            infolist.append(infolist2);
        } else{
            m_filelist<<info.absoluteFilePath();
            //qDebug()<<"file:" << info.absoluteFilePath();
        }
    }
    qDebug()<<"end ::"<< QDateTime::currentDateTime();
    m_filelist.clear();
    qDebug()<<"start222 ::"<< QDateTime::currentDateTime();
    getFiles(m_path);
    qDebug()<<"end222 ::"<< QDateTime::currentDateTime();
    //emit sigloadending(m_filelist.count());
}

void TfileThread::getFiles(const QString& path)
{
    if (this->isInterruptionRequested())
        return;

    QDir dir;
    dir.setPath(path);
    QFileInfoList infolist = dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);

    foreach(const QFileInfo & info, infolist)
    {
        if (this->isInterruptionRequested())
            break;

        if (info.isDir())
            getFiles(info.absoluteFilePath());
        else
            m_filelist << info.absoluteFilePath();
    }
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
