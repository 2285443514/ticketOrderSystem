#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QtGlobal>
#include <QTime>

int Airline::number = 0;
int Account::number = 0;
Account ac;                  //账户
Account acall[100];          //所有账户
QString Client;              //用户登录的姓名
Airline *L;                  //航线指针

void Account::loadAccount(Account a[])
{
    QFile f("账户信息.txt");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QString s;
    QStringList sl;
    int i=0;
    while((s=f.readLine()).isNull() == false)
    {
        sl=s.split(" ");
        a[i].account=sl[0];
        a[i].password=sl[1];
        a[i].name=sl[2];
        i++;
    }
    a->number=i;
    f.close();
}

void Account::putAccount(Account a[])
{
    QFile f("账户信息.txt");
    f.open(QIODevice::WriteOnly);
    QString s;
    int i=0;
    for(i=0;i<a->number;i++)
    {
        s = a[i].account + " " + a[i].password + " " + a[i].name +  " \n" ;
        f.write(s.toUtf8());
    }
    f.close();
}

void Account::swap(Account a[], int j,int k)
{
    Account t=a[j];
    a[j]=a[k];
    a[k]=t;
}
void Account::sortAccount(Account a[],int len)
{
    for (int i = 0; i < len - 1; ++i)
        for (int j = 0; j < len - i - 1; j++)
            if (a[j].account > a[j + 1].account)
                swap(a,j, j + 1);
}

int Account::findAccount(Account a[],int begin,int end, QString Key)
{
    if (begin > end)
    {
        return -1;
    }
    int Mid = (begin + end) / 2;
    if (a[Mid].account == Key)
    {
        return Mid;
    }
    else if (a[Mid].account > Key)
    {
        return findAccount(a, begin, Mid - 1, Key);
    }
    else
    {
        return findAccount(a, Mid + 1, end, Key);
    }
}

Airline* Airline::getAirline()  //读取文件中的航班信息
{
    QFile f("航班信息.txt");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QString s;
    QStringList sl;
    int i=0;
    Airline *line=new Airline [100];
    while((s=f.readLine()).isNull() == false)
    {
        sl=s.split(" ");
        line[i].start_station=sl[0];
        line[i].end_station=sl[1];
        line[i].air_num=sl[2];
        line[i].plane_num=sl[3];
        line[i].day=sl[4];
        line[i].more_ticket_1 = sl[5].toInt();
        line[i].more_ticket_2 = sl[6].toInt();
        line[i].more_ticket_3 = sl[7].toInt();
        line[i].price = sl[8].toDouble();
        line[i].people_quota= sl[9].toInt();
        i++;
    }
    line->number=i;
    f.close();
    return line;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    L=L->getAirline();
    acall->loadAccount(acall);
    acall->sortAccount(acall,acall->number);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void Airline::addClient(client *c,client *q) //增加乘客
{
    client *p = c;
    while(p->next) p=p->next;
    p->next=q;
    q->next=NULL;
}

client* Airline::getClient(Airline l)   //读取某航班乘客信息
{
    QFile f(l.air_num+".txt");
    f.open(QIODevice::ReadWrite);
    QString s;
    QStringList sl;
    client *c = new client,*p,*q=c;
    while((s=f.readLine()).isNull() == false)
    {
        sl=s.split(" ");
        p=new client;
        p->account=sl[0];
        p->ordering_number=sl[1].toInt();
        p->grade=sl[2];
        q->next=p;
        q=q->next;
    }
    q->next=NULL;
    f.close();
    return c;
}
void Airline::putClient(Airline l,client *c)    //输出乘客信息到文件
{
    QFile f(l.air_num+".txt");
    QString s;
    f.open(QIODevice::WriteOnly);
    client *p=c->next;
    while(p)
    {
        s = p->account + " " + QString::number(p->ordering_number) + " " + p->grade + " \n";
        f.write(s.toUtf8());
        p=p->next;
    }
    f.close();
}
void Airline::putAirline(Airline *L)    //输出修改后的航班信息
{
    QFile f("航班信息.txt");
    f.open(QIODevice::WriteOnly);
    QString s;
    int i=0;
    for(i=0;i<L->number;i++)
    {
        s = L[i].start_station + " " + L[i].end_station + " " + L[i].air_num + " " + L[i].plane_num + " " +
                L[i].day + " " + QString::number(L[i].more_ticket_1) + " " + QString::number(L[i].more_ticket_2) + " "
                + QString::number(L[i].more_ticket_3) + " " + QString::number(L[i].price) + " " +
                QString::number(L[i].people_quota)+ " \n";
        f.write(s.toUtf8());
    }
    f.close();
}

void MainWindow::on_lineEdit_2_returnPressed()
{
    if(ui->lineEdit_2->text()=="666666")
    {
        ui->stackedWidget->setCurrentIndex(4);
        ui->tableWidgetAdmin->horizontalHeader()->setVisible(true);
        ui->tableWidgetAdmin->setRowCount(L->number);
        for(int r=0;r<L->number;r++)
        {
            for(int c=0;c<10;c++)
            {
                switch (c) {
                case 0:ui->tableWidgetAdmin->setItem(r,c,new QTableWidgetItem(L[r].air_num));break;
                case 1:ui->tableWidgetAdmin->setItem(r,c,new QTableWidgetItem(L[r].plane_num));break;
                case 2:ui->tableWidgetAdmin->setItem(r,c,new QTableWidgetItem(L[r].start_station));break;
                case 3:ui->tableWidgetAdmin->setItem(r,c,new QTableWidgetItem(L[r].end_station));break;
                case 4:ui->tableWidgetAdmin->setItem(r,c,new QTableWidgetItem(L[r].day));break;
                case 5:ui->tableWidgetAdmin->setItem(r,c,new QTableWidgetItem(QString::number(L[r].more_ticket_1)));break;
                case 6:ui->tableWidgetAdmin->setItem(r,c,new QTableWidgetItem(QString::number(L[r].more_ticket_2)));break;
                case 7:ui->tableWidgetAdmin->setItem(r,c,new QTableWidgetItem(QString::number(L[r].more_ticket_3)));break;
                case 8:ui->tableWidgetAdmin->setItem(r,c,new QTableWidgetItem(QString::number(L[r].price)));break;
                case 9:ui->tableWidgetAdmin->setItem(r,c,new QTableWidgetItem("点击查看"));break;
                }
            }
        }
        ui->label_3->setVisible(false);
    }
    else
    {
        ui->label_3->setVisible(true);
    }
}

void MainWindow::on_ButtonBook_clicked()
{
    QStringList slStart;
    ui->StartStation->clear();
    for(int i=0;i<L->number;i++)
    {
        if(!slStart.contains(L[i].start_station))
            slStart<<L[i].start_station;
    }
    ui->StartStation->addItems(slStart);
    ui->stackedWidget->setCurrentIndex(2);
    ui->tableWidgetBook->clearContents();
    ui->tableWidgetBook->horizontalHeader()->setVisible(true);

}

void MainWindow::on_ButtonReturn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_ButtonReturn_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tableWidgetBook->setRowCount(0);
}




void MainWindow::on_pushButton_2_clicked()
{
    MainWindow::on_lineEdit_2_returnPressed();
}

void MainWindow::on_ButtonRefund_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->label_4->setText("顾客："+ac.name+"，选择要退的票：");
    ui->tableWidgetRefund->clearContents();
    ui->tableWidgetRefund->horizontalHeader()->setVisible(true);
    int row = 0;
    ui->tableWidgetRefund->setRowCount(0);
    for(int i=0; i<L->number ;i++)
    {
        if(L[i].more_ticket_1+L[i].more_ticket_2+L[i].more_ticket_3<L[i].people_quota)
        {
            client *c = L->getClient(L[i]),*p=c;
            for(;;p=p->next)
            {
                if(p->account==ac.account)
                {
                    ui->tableWidgetRefund->setRowCount(row+1);
                    for(int col = 0; col<5; col++)
                    {
                        switch (col) {
                        case 0:ui->tableWidgetRefund->setItem(row,col,new QTableWidgetItem(L[i].air_num));break;
                        case 1:ui->tableWidgetRefund->setItem(row,col,new QTableWidgetItem(L[i].day));break;
                        case 2:ui->tableWidgetRefund->setItem(row,col,new QTableWidgetItem(p->grade));break;
                        case 3:ui->tableWidgetRefund->setItem(row,col,new QTableWidgetItem(QString::number(p->ordering_number)));break;
                        case 4:ui->tableWidgetRefund->setItem(row,col,new QTableWidgetItem("点击退票"));break;
                        }
                    }
                    row++;
                }
                if(p->next==NULL) break;
            }
        }
    }
}

void MainWindow::on_radioButton_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->label_3->setVisible(false);
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_StartStation_currentIndexChanged(const QString &arg1)
{
    QStringList slEnd;
    for(int i=0;i<L->number;i++)
    {
        if(!slEnd.contains(L[i].end_station)&&L[i].end_station!=arg1&&L[i].start_station==arg1)
            slEnd<<L[i].end_station;
    }
    ui->EndStation->clear();
    ui->EndStation->addItems(slEnd);
}
void MainWindow::on_EndStation_currentIndexChanged(const QString &arg1)
{
    QStringList slDate;
    for(int i=0;i<L->number;i++)
    {
        if(!slDate.contains(L[i].day)&&L[i].end_station==arg1&&L[i].start_station==ui->StartStation->currentText())
            slDate<<L[i].day;
    }
    ui->EndStation_2->clear();
    ui->EndStation_2->addItems(slDate);
}

void MainWindow::on_ButtonSearch_clicked()
{
    int row = 0;
    QList<int> lines;
    for(int i=0;i<L->number;i++)
    {
        if(L[i].start_station==ui->StartStation->currentText()&&L[i].end_station==ui->EndStation->currentText()
                &&L[i].day==ui->EndStation_2->currentText())
        {
            row++;
            lines<<i;
        }
    }
    ui->tableWidgetBook->setRowCount(row);
    for(int r=0;r<row;r++)
    {
        for(int c=0;c<8;c++)
        {
            switch (c) {
            case 0:ui->tableWidgetBook->setItem(r,c,new QTableWidgetItem(L[lines[r]].air_num));break;
            case 1:ui->tableWidgetBook->setItem(r,c,new QTableWidgetItem(L[lines[r]].plane_num));break;
            case 2:ui->tableWidgetBook->setItem(r,c,new QTableWidgetItem(L[lines[r]].day));break;
            case 3:ui->tableWidgetBook->setItem(r,c,new QTableWidgetItem(QString::number(L[lines[r]].more_ticket_1)));break;
            case 4:ui->tableWidgetBook->setItem(r,c,new QTableWidgetItem(QString::number(L[lines[r]].more_ticket_2)));break;
            case 5:ui->tableWidgetBook->setItem(r,c,new QTableWidgetItem(QString::number(L[lines[r]].more_ticket_3)));break;
            case 6:ui->tableWidgetBook->setItem(r,c,new QTableWidgetItem("点击购买"));break;
            }
        }
    }
}


void MainWindow::on_ButtonReturn_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tableWidgetBook->setRowCount(0);
}

void MainWindow::on_ButtonReturn_4_clicked()
{
    exit(0);
}

void MainWindow::on_tableWidgetRefund_cellClicked(int row, int column)
{
    if  (column == 4)
    {
        int i = ui->tableWidgetRefund->item(row,0)->text().toInt()-1;
        bool ticketOK;
        client *c = L->getClient(L[i]),*p=c->next,*pre=c;
        for(;;p=p->next,pre=pre->next)
        {
            if(p->account==ac.account&&p->grade==ui->tableWidgetRefund->item(row,2)->text())
            {
                break;
            }
        }
        int ticket = QInputDialog::getInt(this, "退票","输入退票数量", 1,1, p->ordering_number,1, &ticketOK);
        if (ticketOK)
        {
            QMessageBox::information(this,"提示","退票成功");
            int* more_ticket;
            if(p->grade=="头等舱") more_ticket=&L[i].more_ticket_1;
            else if(p->grade=="商务舱") more_ticket=&L[i].more_ticket_2;
            else more_ticket=&L[i].more_ticket_3;
            *more_ticket += ticket;
            L->putAirline(L);
            if(ticket<p->ordering_number)
            {
                p->ordering_number-=ticket;
                L->putClient(L[i],c);
                on_ButtonRefund_clicked();
            }
            else
            {
                pre->next = p->next;
                delete p;
                L->putClient(L[i],c);
                on_ButtonRefund_clicked();
            }
        }
    }
}


void MainWindow::on_tableWidgetAdmin_cellClicked(int row, int column)
{
    if  (column == 8)
    {
        bool priceOK;
        int price = QInputDialog::getInt(this, "票价","输入修改的票价", 1,1,99999,1, &priceOK);
        if (priceOK)
        {
            L[row].price=price;
            ui->tableWidgetAdmin->setItem(row,8,new QTableWidgetItem(QString::number(L[row].price)));
            L->putAirline(L);
            QMessageBox::information(this,"提示","修改成功");
        }
    }
    if  (column == 9)
    {
        int i=ui->tableWidgetAdmin->item(row,0)->text().toInt()-1;
        if(L[i].more_ticket_1+L[i].more_ticket_2+L[i].more_ticket_3<150)
        {
            ui->stackedWidget->setCurrentIndex(6);
            ui->label_14->setText("航班号："+ui->tableWidgetAdmin->item(row,0)->text());
            ui->label_15->setText("飞机号："+ui->tableWidgetAdmin->item(row,1)->text());
            ui->label_16->setText("日期："+ui->tableWidgetAdmin->item(row,4)->text());
            ui->tableWidgetList->clearContents();
            ui->tableWidgetList->horizontalHeader()->setVisible(true);
            int row = 0;
            ui->tableWidgetList->setRowCount(0);
            if(L[i].more_ticket_1+L[i].more_ticket_2+L[i].more_ticket_3<150)
            {
                client *c = L->getClient(L[i]),*p=c->next;
                for(;;p=p->next)
                {
                    ui->tableWidgetList->setRowCount(row+1);
                    for(int col = 0; col<5; col++)
                    {
                        Account t=acall[ac.findAccount(acall,0,ac.number,p->account)];
                        switch (col) {
                        case 0:ui->tableWidgetList->setItem(row,col,new QTableWidgetItem(t.account));break;
                        case 1:ui->tableWidgetList->setItem(row,col,new QTableWidgetItem(t.name));break;
                        case 2:ui->tableWidgetList->setItem(row,col,new QTableWidgetItem(p->grade));break;
                        case 3:ui->tableWidgetList->setItem(row,col,new QTableWidgetItem(QString::number(p->ordering_number)));break;
                        case 4:ui->tableWidgetList->setItem(row,col,new QTableWidgetItem("点击协商"));break;
                        }
                    }
                    row++;
                    if(p->next==NULL) break;
                }
            }
        }
        else
        {
            QMessageBox::information(this,"提示","无乘客");
            ui->stackedWidget->setCurrentIndex(4);
        }

    }
}

void MainWindow::on_tableWidgetList_cellClicked(int row, int column)
{
    if(column==4)
    {
        int i = ui->label_14->text().remove(0,4).toInt()-1;
        bool ticketOK;
        client *c = L->getClient(L[i]),*p=c->next,*pre=c;
        for(;;p=p->next,pre=pre->next)
        {
            if(p->account==ui->tableWidgetList->item(row,0)->text()&&p->grade==ui->tableWidgetList->item(row,2)->text())
            {
                break;
            }
        }
        int ticket = QInputDialog::getInt(this, "退票","输入退票数量", 1,1, p->ordering_number,1, &ticketOK);
        if (ticketOK)
        {
            QMessageBox::information(this,"提示","协商成功");
            int* more_ticket;
            if(p->grade=="头等舱") more_ticket=&L[i].more_ticket_1;
            else if(p->grade=="商务舱") more_ticket=&L[i].more_ticket_2;
            else more_ticket=&L[i].more_ticket_3;
            *more_ticket += ticket;
            L->putAirline(L);
            if(ticket<p->ordering_number)
            {
                p->ordering_number-=ticket;
                L->putClient(L[i],c);
                on_tableWidgetAdmin_cellClicked(i,9);
                on_lineEdit_2_returnPressed();
            }
            else
            {
                pre->next = p->next;
                delete p;
                L->putClient(L[i],c);
                on_tableWidgetAdmin_cellClicked(i,9);
                on_lineEdit_2_returnPressed();
            }
        }
    }
}

void MainWindow::on_ButtonReturn_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_ButtonReturn_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_account_returnPressed()
{
    ac.account=ui->account->text();
    ui->password->setFocus();
}

void MainWindow::on_password_returnPressed()
{
    ac.password=ui->password->text();
    int i;
    i=ac.findAccount(acall,0,acall->number-1,ac.account);
    if(i!=-1)
    {
        if(ac.password==acall[i].password)
        {
            ac.name=acall[i].name;
            ui->stackedWidget->setCurrentIndex(1);
        }
        else QMessageBox::information(this,"提示","密码错误");
    }
    else QMessageBox::information(this,"提示","账号不存在");
}

void MainWindow::on_ButtonLogin_clicked()
{
    on_account_returnPressed();
    on_password_returnPressed();
}

void MainWindow::on_account_2_returnPressed()
{
    ac.account=ui->account_2->text();
    ui->account_3->setFocus();
}

void MainWindow::on_password_2_returnPressed()
{
    ui->password_3->setFocus();
}

void MainWindow::on_password_3_returnPressed()
{
    on_ButtonLogin_3_clicked();
}

void MainWindow::on_account_3_returnPressed()
{
    ui->password_2->setFocus();
}

void MainWindow::on_ButtonLogin_3_clicked()
{
    ac.account=ui->account_2->text();
    ac.password=ui->password_2->text();
    ac.name=ui->account_3->text();
    if(ac.account.isEmpty()==false&&ac.password.isEmpty()==false&&ac.name.isEmpty()==false)
    {
        if(ac.findAccount(acall,0,ac.number-1,ac.account)==-1)
        {
            if(ui->password_3->text()==ac.password)
            {
                acall[ac.number]=ac;
                ac.number++;
                ac.sortAccount(acall,ac.number);
                ac.putAccount(acall);
                QMessageBox::information(this,"提示","注册成功");
                ui->stackedWidget_2->setCurrentIndex(0);
            }
            else QMessageBox::information(this,"提示","请重新输入密码");
        }
        else QMessageBox::information(this,"提示","账户已经存在");
    }
    else QMessageBox::information(this,"提示","不能为空");
}

void MainWindow::on_ButtonLogin_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_ButtonLogin_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

double discount;

void MainWindow::on_tableWidgetBook_cellClicked(int row, int column)
{
    if  (column == 6)
    {
        ui->air_num->setText(ui->tableWidgetBook->item(row,0)->text());
        ui->day->setText(ui->tableWidgetBook->item(row,2)->text());
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        discount = qrand()%3+6;
        on_comboBox_currentIndexChanged("头等舱");
        ui->stackedWidget->setCurrentIndex(5);
    }
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    int i = ui->air_num->text().toInt()-1;
    double totalPrice=L[i].price;
    ui->spinBox->setMinimum(1);
    if(arg1=="头等舱")
    {
        ui->spinBox->setMaximum(L[i].more_ticket_1);
        ui->spinBox->setValue(1);
        totalPrice*=1.5;
    }
    if(arg1=="商务舱")
    {
        ui->spinBox->setMaximum(L[i].more_ticket_2);
        ui->spinBox->setValue(1);
        totalPrice*=1.2;
    }
    if(arg1=="经济舱")
    {
        ui->spinBox->setMaximum(L[i].more_ticket_3);
        ui->spinBox->setValue(1);
    }
    totalPrice*=ui->spinBox->text().toInt();
    ui->totalPrice->setText(QString::number(totalPrice)+"x"+QString::number(discount)+"折 ="
                            +QString::number(totalPrice*discount*0.1)+"￥");
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    int i = ui->air_num->text().toInt()-1;
    double totalPrice=L[i].price;
    if(ui->comboBox->currentText()=="头等舱")
    {
        totalPrice*=1.5;
    }
    if(ui->comboBox->currentText()=="商务舱")
    {
        totalPrice*=1.2;
    }
    totalPrice*=arg1;
    ui->totalPrice->setText(QString::number(totalPrice)+"x"+QString::number(discount)+"折 ="
                            +QString::number(totalPrice*discount*0.1)+"￥");
}

void MainWindow::on_pushButton_clicked()
{
    int i = ui->air_num->text().toInt()-1;
    QString grade = ui->comboBox->currentText();
    int* more_ticket;
    if(grade=="头等舱") more_ticket=&L[i].more_ticket_1;
    else if(grade=="商务舱") more_ticket=&L[i].more_ticket_2;
    else more_ticket=&L[i].more_ticket_3;
    int ticket = ui->spinBox->text().toInt();
    *more_ticket-=ticket;
    L->putAirline(L);
    client *c = L->getClient(L[i]);
    client *p=c;
    bool repeated=false;
    for(;;p=p->next)
    {
        if(p->account==ac.account&&p->grade==grade)
        {
            p->ordering_number+=ticket;
            L->putClient(L[i],c);
            repeated=true;
            break;
        }
        if(p->next==NULL)
            break;
    }
    if(!repeated)
    {
        p=new client;
        p->account = ac.account;
        p->ordering_number=ticket;
        p->grade=grade;
        L->addClient(c,p);
        L->putClient(L[i],c);
    }
    QMessageBox::information(this,"提示","付款成功");
    ui->stackedWidget->setCurrentIndex(2);
    on_ButtonSearch_clicked();
}


void MainWindow::on_radioButton_4_toggled(bool checked)
{
    if(checked)
        on_comboBox_currentIndexChanged(ui->comboBox->currentText());
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    int i = ui->air_num->text().toInt()-1;
    double totalPrice=L[i].price;
    if(ui->comboBox->currentText()=="头等舱")
    {
        totalPrice*=1.5;
    }
    if(ui->comboBox->currentText()=="商务舱")
    {
        totalPrice*=1.2;
    }
    totalPrice*=ui->spinBox->text().toDouble();
    if(checked)
        ui->totalPrice->setText(QString::number(totalPrice)+"x5折 ="+QString::number(totalPrice*0.5)+"￥");
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
