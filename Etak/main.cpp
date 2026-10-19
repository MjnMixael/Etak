/*
 * Copyright (C) Mike Nelson
 *
 * All source code herein is subject to the GPL license included.
 *
*/

#include "Etak.h"

#include <QApplication>
#include <QColor>
#include <QElapsedTimer>
#include <QFont>
#include <QGuiApplication>
#include <QIcon>
#include <QLinearGradient>
#include <QPainter>
#include <QPixmap>
#include <QScreen>
#include <QSharedMemory>
#include <QSplashScreen>
#include <QThread>

namespace {

// Long enough to read, so a fast start does not just flash the splash.
constexpr int MinimumSplashMs = 800;

// Composed splash: the app logo on the left, title and subtitle on the right.
QPixmap splashPixmap()
{
    const QSize size(480, 270);
    const qreal ratio = QGuiApplication::primaryScreen() ? QGuiApplication::primaryScreen()->devicePixelRatio() : 1.0;

    QPixmap pixmap(size * ratio);
    pixmap.setDevicePixelRatio(ratio);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QLinearGradient background(0, 0, size.width(), size.height());
    background.setColorAt(0, QColor(28, 36, 52));
    background.setColorAt(1, QColor(12, 16, 26));
    painter.fillRect(QRect(QPoint(0, 0), size), background);

    const QPixmap logo(":/Etak/icon.png");
    const int s = 180;
    painter.drawPixmap(QRect(26, (size.height() - s) / 2, s, s), logo);

    QFont title = painter.font();
    title.setPixelSize(54);
    title.setBold(true);
    painter.setFont(title);
    painter.setPen(Qt::white);
    painter.drawText(QRect(214, 72, 250, 66), Qt::AlignLeft | Qt::AlignVCenter, "Etak");

    QFont subtitle = painter.font();
    subtitle.setPixelSize(15);
    subtitle.setBold(false);
    painter.setFont(subtitle);
    painter.setPen(QColor(170, 182, 200));
    painter.drawText(QRect(216, 140, 236, 40), Qt::AlignLeft | Qt::TextWordWrap,
        QCoreApplication::translate("main", "Translation tool for FreeSpace Open"));

    return pixmap;
}

} // namespace

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Etak");
    QCoreApplication::setApplicationName("Etak");
    a.setWindowIcon(QIcon(":/Etak/icon.png"));

    QSharedMemory sharedMemory;
    sharedMemory.setKey("EtakRunning");

    if (!sharedMemory.create(1)) {
        // Another instance is already running so end here
        return 1;
    }

    QElapsedTimer shown;
    shown.start();
    QSplashScreen splash(splashPixmap());
    splash.show();
    splash.showMessage(QCoreApplication::translate("main", "Starting..."),
        Qt::AlignLeft | Qt::AlignBottom, QColor(170, 182, 200));
    a.processEvents();

    Etak w;

    const qint64 remaining = MinimumSplashMs - shown.elapsed();
    if (remaining > 0)
        QThread::msleep(quint64(remaining));

    w.show();
    splash.finish(&w);
    return a.exec();
}
