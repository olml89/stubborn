#include "stubborn.h"
#include <exception>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    try {
        Stubborn stubborn(app.applicationDirPath() + "/config.json");

        if (!stubborn.start(app)) {
            exit(0);
        }

        return app.exec();
    }
    catch (std::exception const &e) {
        return Stubborn::displayException(e);
    }

}
