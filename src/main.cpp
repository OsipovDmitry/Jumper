#include <QApplication>

#include "core.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Core::run();
	int returnCode = app.exec();
	Core::deinit();

	return returnCode;
}
