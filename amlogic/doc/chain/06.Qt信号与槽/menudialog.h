#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QDesktopWidget>

namespace Ui {
class MenuDialog;
}

class MenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MenuDialog(QWidget *parent = 0);
    ~MenuDialog();
    void disableAll();
    void setPasteEnable(bool b);

private:
    Ui::MenuDialog *ui;
signals:
    void onOperator(QString type);
protected:
    bool eventFilter(QObject *watcher, QEvent *event);
};

#endif // MENUDIALOG_H
