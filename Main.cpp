
#include "Application.h"

int
main(int argc, char *argv[]){

    q2d::Application* application = new q2d::Application(argc, &argv);
    application->initialize();
    application->run();

    int returnValue = application->exec();

    delete application;

    return returnValue;
}
