#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "Application.h"

#include "ui_MainWindow.h"

#include <QWindow>

namespace q2d {
    // forward declaration
    class Application;

namespace gui {

class MainWindow : public QWindow {
    Q_OBJECT
private:
    q2d::Application* application;
public:
    explicit MainWindow();
    ~MainWindow();
};

} // namespace gui
} // namespace q2d

#endif // MAINWINDOW_H
