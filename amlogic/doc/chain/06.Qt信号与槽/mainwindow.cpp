#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	//使用connect函数进行信号与槽连接
    connect(ui->le_num1,SIGNAL(textChanged(QString)),this,SLOT(checkInputIllegal(QString)));
    connect(ui->le_num2,SIGNAL(textChanged(QString)),this,SLOT(checkInputIllegal(QString)));
    initOperate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkInputIllegal(const QString &text)
{
    showResult("receive textChanged signal",1);
    QRegExp reg("^[0-9]*$");
    QString num1 = ui->le_num1->text();
    QString num2 = ui->le_num2->text();
    if(reg.indexIn(num1)>=0&&reg.indexIn(num2)>=0){
        isIllegal = true;
    }else{
        isIllegal = false;
        showResult(ERROR_LOG,0);
    }

}

void MainWindow::showResult(const QString &result,int type)
{
    QListWidgetItem* item = new QListWidgetItem;
    if(type == 0){
        item->setTextColor(QColor(255,0,0));
        ui->lb_result->setText("");
    }else if(type == 1){
        item->setTextColor(QColor(0,0,255));
    }
    QDateTime time = QDateTime::currentDateTime();
    QString t = time.toString("hh:mm:ss");
    item->setText(t+"    "+result);
    ui->lw_result->insertItem(0,item);
}

void MainWindow::initOperate()
{
    ui->cb_operate->addItem("+");
    ui->cb_operate->addItem("-");
    ui->cb_operate->addItem("*");
    ui->cb_operate->addItem("/");
    isIllegal = 0;
}

//通过命名约束进行连接
void MainWindow::on_pb_calculate_clicked()
{
    showResult("receive clicked signal",1);
    if(isIllegal){
        QString num1 = ui->le_num1->text();
        QString num2 = ui->le_num2->text();
        int operateNum1 = num1.toInt();
        int operateNum2 = num2.toInt();
        QString operate = ui->cb_operate->currentText();
        QString result = 0;
        switch (ui->cb_operate->currentIndex()) {
        case 0:
        {
            result = QString::number(operateNum1+operateNum2);
            break;
        }
        case 1:
            result = QString::number(operateNum1-operateNum2);
            break;
        case 2:
            result = QString::number(operateNum1*operateNum2);
            break;
        case 3:
            if(operateNum2 == 0){
                showResult(ERROR_LOG,0);
                return ;
            }
            result = QString::number(operateNum1/operateNum2);
            break;
        }
        QString log = num1+operate+num2+"="+result;
        showResult(log);
        ui->lb_result->setText(result);
    }else{
        showResult(ERROR_LOG,0);
    }
}
