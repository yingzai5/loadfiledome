#include "TfileThread.h"
#include <QDir>
#include <QtDebug>
#include <QDateTime>
#include <qdiriterator.h>

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
    qDebug()<<"队列start ::"<< QDateTime::currentDateTime();
    queuegetFiles(m_path);
    qDebug()<<"队列end ::"<< QDateTime::currentDateTime();
    qDebug()<<"m_filelist.count::"<<m_filelist.count();
    m_filelist.clear();
    qDebug()<<"递归start ::"<< QDateTime::currentDateTime();
    getFiles(m_path);
    qDebug()<<"递归end ::"<< QDateTime::currentDateTime();
    qDebug()<<"m_filelist.count::"<<m_filelist.count();

    m_filelist.clear();
    qDebug()<<"迭代器start ::"<< QDateTime::currentDateTime();
    iteratorgetFile(m_path);
    qDebug()<<"迭代器end ::"<< QDateTime::currentDateTime();
    qDebug()<<"m_filelist.count::"<<m_filelist.count();

    //emit sigloadending(m_filelist.count());
}

void TfileThread::iteratorgetFile(const QString& path)
{
    QDirIterator dir_iterator(path,
                   QDir::Files | QDir::NoSymLinks,
                   QDirIterator::Subdirectories);
    while(dir_iterator.hasNext())
     {
        dir_iterator.next();
        QFileInfo file_info =dir_iterator.fileInfo();
        //QString absolute_file_path =file_info.absoluteFilePath();
        m_filelist<<file_info.absoluteFilePath();
     }
}
//队列实现文件的遍历
void TfileThread::queuegetFiles(const QString& path){
    QDir dir(m_path);
    QFileInfoList infolist = dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList infolist2;
    QFileInfo  info;
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
        }
    }
}

//递归实现文件的遍历
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
