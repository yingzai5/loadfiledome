#include "fileloadThread.h"
#include <QDir>
#include <QtDebug>

TFileloadThread::TFileloadThread(QObject* parent) : QThread(parent)
{
   //this->wait();
}
TFileloadThread::~TFileloadThread()
{

}


void TFileloadThread::run()
{
    m_filelist.clear();
    QDir dir;
    dir.setPath(m_path);
    QFileInfoList infolist = dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList infolist2;

    foreach(const QFileInfo & info,infolist)
    {
        if(info.isDir())
        {
            dir.setPath(info.absoluteFilePath());
            infolist2 =dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
            infolist.append(infolist2);
        } else{
            m_filelist<< info.absoluteFilePath();
            qDebug()<< info.absoluteFilePath();
        }

    }
    emit sigloadending(m_filelist.count());
}


void TFileloadThread::startload(QString& path)
{
    m_path = path;
    this->start();
}

QList<QString>TFileloadThread::Getfilelist()
{
    return  m_filelist;
}

