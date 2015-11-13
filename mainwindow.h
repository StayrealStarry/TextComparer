#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QString>
#include <QMessageBox>
#include <set>
#include <map>
#include <list>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <QByteArray>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QDateTime>
#include <cmath>
#include <cstdio>

extern QString line_long_in;
extern QString line_short_in;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT
    QString file_full_long, file_name_long, file_path_long;
    QFileInfo fi_long;
    QString file_full_short, file_name_short, file_path_short;
    QFileInfo fi_short;
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	///////////////////////////////////////
	
	///////////////////////////////
private slots:
    void on_openSFile_clicked();

    void on_openLFile_clicked();

    void on_startBtn_clicked();

    void on_startCompare_clicked();

    void on_simiStart_clicked();
private:
        Ui::MainWindow *ui;
		friend class Compare;
        friend void create();

};

#endif // MAINWINDOW_H
