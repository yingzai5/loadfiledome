#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "TfileThread.h"
//#include <QString>

class TfileThread;
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    TfileThread* m_dsad = new TfileThread(nullptr);
    QString path = "D:\\";
    m_dsad->startload(path);
    return app.exec();
}
