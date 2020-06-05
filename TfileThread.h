#ifndef TFILETHREAD_H
#define TFILETHREAD_H
#include <QThread>

class TfileThread : public QThread
{
    Q_OBJECT
public:
    TfileThread(QObject* parent);
    ~TfileThread() override;
    Q_INVOKABLE void startload(QString& path);
    Q_INVOKABLE QList<QString> Getfilelist();
    void getFiles(const QString& path);

protected:
    void run() override;

signals:
   void sigloadending(int cout);

private:
    QString m_path;
    QStringList m_dirs;
    QList<QString> m_filelist ;
};
#endif // TFILETHREAD_H
