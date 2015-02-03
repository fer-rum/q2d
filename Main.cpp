
#include "Application.h"

int
main(int argc, char* argv[]) {

    q2d::Application* application = new q2d::Application(argc, &argv);

    int returnValue = application->exec();

    delete application;

    return returnValue;
}
