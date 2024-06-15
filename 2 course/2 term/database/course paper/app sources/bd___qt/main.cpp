#include <QApplication>
#include "registrationwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Создаем объект окна регистрации
    registrationwindow registrationWindow;

    // Отображаем окно регистрации
    registrationWindow.show();

    // Запускаем цикл обработки событий приложения
    return a.exec();
}
