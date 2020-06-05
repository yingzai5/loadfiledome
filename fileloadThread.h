#ifndef FILELOADTHREAD_H
#define FILELOADTHREAD_H

#include <QThread>

class TFileloadThread : public QThread
{
    Q_OBJECT
public:
    TFileloadThread(QObject* parent);
    ~TFileloadThread() override;
    Q_INVOKABLE void startload(QString& path);
    Q_INVOKABLE QList<QString> Getfilelist();

protected:
    void run() override;

signals:
   void sigloadending(int cout);

private:
    QString m_path;
    QStringList m_dirs;
    QList<QString> m_filelist ;
};

#endif // FILELOADTHREAD_H
