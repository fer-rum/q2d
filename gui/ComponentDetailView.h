#ifndef COMPONENTDETAILVIEW_H
#define COMPONENTDETAILVIEW_H

#include <QDialog>

namespace Ui {
class ComponentDetailView;
}

namespace q2d {

namespace model {
class Component;
}

namespace gui {
class MainWindow;

class ComponentDetailView : public QDialog {
    Q_OBJECT

private:
    Ui::ComponentDetailView* m_ui;

public:
    explicit ComponentDetailView(model::Component* component, MainWindow* parent);
    ~ComponentDetailView();

};

} // namespace gui
} // namespace q2d

#endif // COMPONENTDETAILVIEW_H
