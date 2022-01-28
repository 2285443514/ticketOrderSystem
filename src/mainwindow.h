#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QtGlobal>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_account_returnPressed();

    void on_lineEdit_2_returnPressed();

    void on_ButtonBook_clicked();

    void on_ButtonReturn_clicked();

    void on_ButtonReturn_2_clicked();

    void on_ButtonSearch_clicked();

    void on_pushButton_2_clicked();

    void on_ButtonRefund_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_StartStation_currentIndexChanged(const QString &arg1);

    void on_tableWidgetBook_cellClicked(int row, int column);

    void on_ButtonReturn_3_clicked();

    void on_ButtonReturn_4_clicked();

    void on_tableWidgetRefund_cellClicked(int row, int column);

    void on_tableWidgetAdmin_cellClicked(int row, int column);

    void on_ButtonReturn_5_clicked();

    void on_password_returnPressed();

    void on_ButtonLogin_clicked();

    void on_account_2_returnPressed();

    void on_password_2_returnPressed();

    void on_password_3_returnPressed();

    void on_account_3_returnPressed();

    void on_ButtonLogin_3_clicked();

    void on_ButtonLogin_4_clicked();

    void on_ButtonLogin_2_clicked();

    void on_EndStation_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_radioButton_4_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_pushButton_3_clicked();

    void on_tableWidgetList_cellClicked(int row, int column);

    void on_ButtonReturn_6_clicked();

private:
    Ui::MainWindow *ui;
};

class Account
{
private:
    QString account;
    QString password;
    QString name;
    static int number;
public:
    friend MainWindow;
    void loadAccount(Account[]);            //从文件中读取所有账户
    void putAccount(Account a[]);           //保存账户到文件中
    void sortAccount(Account[],int);        //对账户信息排序
    int findAccount(Account[],int ,int ,QString);       //二分查找账户信息
    void swap(Account[],int,int);                       //交换两个位置
};

struct client
{
    QString account;
    int ordering_number;
    QString grade;
    client *next;
};

class Airline
{
private:
    QString start_station;
    QString end_station;
    QString air_num;
    QString plane_num;
    QString day;
    int people_quota;
    int more_ticket_1;
    int more_ticket_2;
    int more_ticket_3;
    double price;
    static int number;
public:
    friend MainWindow;
    Airline* getAirline();                 //读取航线信息
    void putAirline(Airline*);             //保存航线信息
    client* getClient(Airline);            //读取乘客信息
    void addClient(client *c,client *q);   //添加客户
    void putClient(Airline,client*);       //保存乘客信息
    void reprice();                        //修改航线价格
};

extern QString Name;              //用户登录的姓名
extern Airline *L;                //航线指针
extern Account ac;                //账户
extern Account acall[];           //所有账户

#endif // MAINWINDOW_H
