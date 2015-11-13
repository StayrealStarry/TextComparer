#include "mainwindow.h"
#include <QApplication>
#include <sys/stat.h>
#include <cmath>
#include <cstring>
#include <string>
#include<iostream>
#include<string>
#include<list>
#include<fstream>
#include<map>
#include<vector>
#include<iomanip>
#include <QTextCodec>
using namespace std;

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForTr( QTextCodec::codecForName("GBK") );
    QApplication a(argc, argv);
    MainWindow w;
    QApplication::setStyle("macintosh");
    w.show();
    w.setWindowTitle(QStringLiteral("Data Finder"));
    return a.exec();
}
