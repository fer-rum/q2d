#ifndef QUANTORRESULTDIALOG_H
#define QUANTORRESULTDIALOG_H

#include <QDialog>

namespace Ui {
class QuantorResultDialog;
}

class QuantorResultDialog : public QDialog {
    Q_OBJECT
private:
    Ui::QuantorResultDialog* m_ui;
public:
    explicit QuantorResultDialog(QWidget* parent, QString resultText,
                                 const QMap<QString, bool>* resultMapping);
    ~QuantorResultDialog();
};

#endif // QUANTORRESULTDIALOG_H
