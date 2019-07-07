#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <QTextCodec>
//打开文件
#include <QFileDialog>
#include <QString>
#include <QDebug>
#define cout qDebug()

QString fileName = NULL;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveFile(const char * file, const char * buf)
{
    FILE * fp = fopen(file,"w");
    if(!fp)
        return;

    //保存文件
    fputs(buf,fp);
}

void MainWindow::on_actiondakai_triggered()
{
    //打开文件
    /* 1、fopen(文件名，打开方式)
     * 2、判断可用性
     * 3、读取内容
     * 4、关闭文件
     */

    //通过对话框打开文件 获取文件路径 QString
    fileName = QFileDialog::getOpenFileName();
    //将Qstring转换为char*使得fopen可以接收
    QTextCodec * codec = QTextCodec::codecForName("GBK");//注意需要打开的文件为GBK
    char * file = codec->fromUnicode(fileName).data();

    FILE * fp = fopen(file,"r");
    if(!fp)
        return ;

    QString txt;
    char buf[1024];
    while(!feof(fp)) {
        memset(buf,0,1024);
        fgets(buf,1024,fp);
        //cout<<buf;
        txt += codec->toUnicode(buf);
    }
    //为文本标签 设置内容
    ui->textEdit->setText(txt);

    fclose(fp);

}

void MainWindow::on_actionbaocun_triggered()
{
    //打开文件
    if(fileName == NULL)//避免保存弹出另存为对话框
    fileName = QFileDialog::getSaveFileName();

    // 转码
    QTextCodec * codec = QTextCodec::codecForName("GBK");
    char * file = codec->fromUnicode(fileName).data();

    //读取textedit
    QString txt = ui->textEdit->toPlainText();
    //转成char*类型
    const char * buf = txt.toStdString().data();

    saveFile(file,buf);
}

void MainWindow::on_actionxinjian_triggered()
{
    //暂时无保存当前正在编辑文件的功能，仅清空

    //ui->textEdit->setText("");
    ui->textEdit->clear();
    fileName.clear();//使fileName置为空，则下次保存新文件弹出另存为
}

void MainWindow::on_actiontuichu_triggered()
{
    //缺少提示用户保存
    exit(0);
}

void MainWindow::on_actionchexiao_triggered()
{
    //撤销
    ui->textEdit->undo();
}

void MainWindow::on_actionfuzhi_triggered()
{
    //复制
    ui->textEdit->copy();
}

void MainWindow::on_actionzhantie_triggered()
{
     //粘贴
    ui->textEdit->paste();
}

void MainWindow::on_actionjianqie_triggered()
{
    //剪贴
    ui->textEdit->cut();
}

void MainWindow::on_actionbianji_triggered()
{
     /* 编译步骤
      * 1、判断是否保存(保存则编译否则进行保存操作)
      * 2、组装cmd 中 执行的 gcc格式
      * 3、编译 如果出错提示错误信息 执行程序
      */
    if(fileName == NULL) {
        //打开文件
        fileName = QFileDialog::getSaveFileName();

        // 将QString类型的文件名转码
        QTextCodec * codec = QTextCodec::codecForName("GBK");
        char * file = codec->fromUnicode(fileName).data();

        //读取textedit的内容
        QString txt = ui->textEdit->toPlainText();
        //转成char*类型
        const char * buf = txt.toStdString().data();

        saveFile(file,buf);
    }
    else {
        //格式为  gcc -o D:\a.exe D:\a.c
        QString des = fileName;
        //此时des为将 .c替换为 .exe的filename
        des.replace(".c",".exe");

        char comm[1024] = "gcc -o ";
        //字符串拼接,并且进行转码
        strcat(comm,des.toStdString().data());
        strcat(comm," ");
        strcat(comm,fileName.toStdString().data());
        //执行并判断是否成功
        if(!system(comm)) {//若执行成功 system返回值为0
            cout<<"cg!";
            char cmd[256]  = "cmd /k ";
            strcat(cmd,des.toStdString().data());
            system(cmd);
        }
    }
}

void MainWindow::on_actionlingcunwei_triggered()
{
    //打开文件
    fileName = QFileDialog::getSaveFileName();

    // 转码
    QTextCodec * codec = QTextCodec::codecForName("GBK");
    char * file = codec->fromUnicode(fileName).data();

    //读取textedit
    QString txt = ui->textEdit->toPlainText();
    //转成char*类型
    const char * buf = txt.toStdString().data();

    saveFile(file,buf);
}

void MainWindow::on_actionguanyu_triggered()
{

}
