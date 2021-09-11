#include "screen.h"

#include <QApplication>
#include <QScreen>

#if QT_VERSION < QT_VERSION_CHECK(5,11,0)
#   include <QDesktopWidget>
#endif

namespace {

QScreen *screenFromNumber(int i)
{
    const auto screens = QGuiApplication::screens();
    if (i < 0 || i >= screens.size())
        return nullptr;
    return screens[i];
}

} // namespace

int screenCount()
{
    return QGuiApplication::screens().size();
}

int screenNumberAt(const QPoint &pos)
{
#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
    auto screen = QGuiApplication::screenAt(pos);
    if (screen == nullptr)
        screen = QGuiApplication::primaryScreen();
    return QGuiApplication::screens().indexOf(screen);
#else
    return QApplication::desktop()->screenNumber(pos);
#endif
}

QRect screenGeometry(int i)
{
#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
    auto screen = screenFromNumber(i);
    return screen ? screen->geometry() : QRect();
#else
    return QApplication::desktop()->screenGeometry(i);
#endif
}

QRect screenAvailableGeometry(const QPoint &pos)
{
#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
    auto screen = QGuiApplication::screenAt(pos);
    if (screen == nullptr) {
        screen = screenFromNumber(0);
        if (screen == nullptr)
            return QRect();
    }

    const QRect g = screen->availableGeometry();
    const qreal ratio = screen->devicePixelRatio();
    return QRect(g.topLeft() * ratio, g.bottomRight() * ratio);
#else
    return QApplication::desktop()->availableGeometry(pos);
#endif
}
