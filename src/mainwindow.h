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
    void loadAccount(Account[]);            //??????????????????????????????
    void putAccount(Account a[]);           //????????????????????????
    void sortAccount(Account[],int);        //?????????????????????
    int findAccount(Account[],int ,int ,QString);       //????????????????????????
    void swap(Account[],int,int);                       //??????????????????
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
    Airline* getAirline();                 //??????????????????
    void putAirline(Airline*);             //??????????????????
    client* getClient(Airline);            //??????????????????
    void addClient(client *c,client *q);   //????????????
    void putClient(Airline,client*);       //??????????????????
    void reprice();                        //??????????????????
};

extern QString Name;              //?????????????????????
extern Airline *L;                //????????????
extern Account ac;                //??????
extern Account acall[];           //????????????

#endif // MAINWINDOW_H
