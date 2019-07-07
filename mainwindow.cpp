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
    QString fileName = QFileDialog::getOpenFileName();
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
    QString fileName = QFileDialog::getSaveFileName();

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
