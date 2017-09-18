#include "menudialog.h"
#include "ui_menudialog.h"

#include <qpainter.h>

MenuDialog::MenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    int offsetX = (QApplication::desktop()->width()-width())/2;
    int offsetY = (QApplication::desktop()->height()-height())/2;
    move(offsetX,offsetY);
    ui->pb_copy->installEventFilter(this);
    ui->pb_cut->installEventFilter(this);
    ui->pb_paste->installEventFilter(this);
    ui->pb_del->installEventFilter(this);
    ui->pb_refactor->installEventFilter(this);
    installEventFilter(this);
}

MenuDialog::~MenuDialog()
{
    delete ui;
}

void MenuDialog::disableAll(){
    ui->pb_copy->setEnabled(false);
    ui->pb_cut->setEnabled(false);
    ui->pb_paste->setEnabled(false);
    ui->pb_del->setEnabled(false);
    ui->pb_refactor->setEnabled(false);
}

void MenuDialog::setPasteEnable(bool b){
    ui->pb_paste->setEnabled(b);
}

bool MenuDialog::eventFilter(QObject *watcher, QEvent *event){
    if(QEvent::FocusIn == event->type()&&watcher->inherits("QPushButton")){
        QWidget* widget = static_cast<QWidget*>(watcher);
        widget->setStyleSheet("color:red");
    }

    if(QEvent::FocusOut == event->type()&&watcher->inherits("QPushButton")){
        QWidget* widget = static_cast<QWidget*>(watcher);
        widget->setStyleSheet("color:black");
    }

    if(QEvent::KeyPress == event->type()){
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if(Qt::Key_Return == keyEvent->key()){
            QPushButton* btn = static_cast<QPushButton*>(watcher);
            close();
            emit onOperator(btn->text());//发送点击信号到外面去
            return true;

        }else if(Qt::Key_Home == keyEvent->key()){
            qDebug()<<"menudialog close";
            close();
            return true;
        }
    }
    return QDialog::eventFilter(watcher,event);
}
