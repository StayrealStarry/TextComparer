#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

QString all1;
QString all2;
QString abspath1;
QString abspath2;
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openSFile_clicked()
{
    //file_full_short = QFileDialog::getOpenFileName(this,tr("open"),
    //                                               ".",tr("Text Files(*.txt)"));
    file_full_short = QFileDialog::getOpenFileName(this,tr("open"),"
		。",tr("Text Files(*.txt)"));
    fi_short = QFileInfo(file_full_short);//转移到windows时修改上面的路径
    file_name_short = fi_short.fileName();
    file_path_short = fi_short.absolutePath();
    ui->textEdit_2->setText(file_path_short+"/"+file_name_short);//?
    abspath2 = ui -> textEdit_2 ->toPlainText();
    //qDebug()<<abspath2<<endl;
}

void MainWindow::on_openLFile_clicked()
{
    //file_full_long = QFileDialog::getOpenFileName(this,tr("open"),
    //                                              .,tr("Text Files(*.txt)"));
    file_full_long = QFileDialog::getOpenFileName(this,tr("open"),".",tr("Text Files(*.txt)"));
    fi_long = QFileInfo(file_full_long);//转移到windows时修改上面的路径
    file_name_long = fi_long.fileName();
    file_path_long = fi_long.absolutePath();
    ui->textEdit->setText(file_path_long+"/"+file_name_long);//?
    abspath1 = ui -> textEdit ->toPlainText();
}



void MainWindow::on_startBtn_clicked()
{
    QFile longFile(file_full_long);
    QFile shortFile(file_full_short);
    QFileInfo longInfo(longFile);
    QFileInfo shortInfo(shortFile);
        //////////////////////
    if(!longFile.open(QIODevice::ReadOnly | QIODevice::Text) ||
             !shortFile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    QTextStream streamShort(&shortFile);
    QTextStream streamLong(&longFile);
    ///////////////////////////////////////////////////////
    QTextDocument *document = ui -> FileData -> document();
    QTextCursor cursor(document);
    QDateTime dt;
    QTime time;
    QDate date;
    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());
    QString currentDate = dt.toString("yyyy:MM:dd  hh:mm:ss");
    ui->FileData->clear();
    cursor.insertText(QStringLiteral("当前系统时间为："));
    cursor.insertText(currentDate);
    cursor.insertBlock();
    cursor.insertBlock();
    //////////////////////////////////////////////////////
    while( !streamLong.atEnd())
    {
        all2 = streamLong.readAll();
        ui->textEdit_Long->setPlainText(all2);
        cursor.insertText(QStringLiteral("文件1："));
        cursor.insertBlock();
        cursor.insertText(file_full_long);
        cursor.insertBlock();
        cursor.insertText(QStringLiteral("大小为："));
        cursor.insertText(QString::number(longFile.size(), 16).toUpper());
        cursor.insertText(QStringLiteral("字节"));
        cursor.insertBlock();
        cursor.insertText(QStringLiteral("创建时间"));
        cursor.insertBlock();
        cursor.insertText(longInfo.created().toString());
    }
    while( !streamShort.atEnd())
    {
        all1 = streamShort.readAll();
        ui->textEdit_Short->setPlainText(all1);
        //qDebug()<<all1<<endl;
        cursor.insertBlock();cursor.insertBlock();
        cursor.insertText(QStringLiteral("文件2:"));
        cursor.insertBlock();
        cursor.insertText(file_full_short);
        cursor.insertBlock();
        cursor.insertText(QStringLiteral("大小为："));
        cursor.insertText(QString::number(shortFile.size(), 10).toUpper());
        cursor.insertText(QStringLiteral("字节"));
        cursor.insertBlock();
        cursor.insertText(QStringLiteral("创建时间"));
        cursor.insertBlock();
        cursor.insertText(shortInfo.created().toString());
    }
    streamShort.seek(streamShort.pos());
    longFile.close();
    shortFile.close();
}


void MainWindow::on_startCompare_clicked()
{
    QString search_text1 = ui ->textEdit_Short->toPlainText();
    search_text1.replace(QString("!"),QString("."));//替换特殊符号
    search_text1.replace(QString("\n"),QString("."));
    search_text1.replace(QString("?"),QString("."));
    search_text1.replace(QString("\\"),QString("."));
    //search_text1.replace(QString(" "),QString(""));
    //qDebug()<<search_text1<<endl;
    QStringList search_text_split = search_text1.split(".");//使用QStringList存储，可以使用foreach，用.分割
    int j=1;
    foreach (QString search_text,search_text_split)
    {
        if(search_text!=" ")
        {
            qDebug()<<search_text<<endl;
            QTextDocument *document = ui -> textEdit_Long -> document();
            QTextDocument *document2 = ui -> textEdit_Short -> document();
            bool found = false;
            QTextCursor highlight_cursor(document);
            QTextCursor cursor(document);
            QTextCursor highlight_cursor2(document2);
            QTextCursor cursor2(document2);
            //开始
            cursor.beginEditBlock();
            cursor2.beginEditBlock();
            QTextCharFormat color_format(highlight_cursor.charFormat());
            if(j==1)
            {
            color_format.setForeground(Qt::red);
            color_format.setBackground(Qt::yellow);
            }
            else if (j==2)
            {
                color_format.setForeground(Qt::blue);
                color_format.setBackground(Qt::yellow);
            }
            else if (j==3)
            {
                color_format.setForeground(Qt::black);
                color_format.setBackground(Qt::yellow);
            }
            while (!highlight_cursor.isNull() && !highlight_cursor.atEnd())
            {

            //查找指定的文本，匹配整个单词
                highlight_cursor = document->find(search_text, highlight_cursor, QTextDocument::FindWholeWords);
                highlight_cursor2 = document2->find(search_text, highlight_cursor2, QTextDocument::FindWholeWords);
                if (!highlight_cursor.isNull())
                {
                //if(!found)
                    //found = true;
                    highlight_cursor.mergeCharFormat(color_format);
                    highlight_cursor2.mergeCharFormat(color_format);
                }

            }
            cursor.endEditBlock();
        //结束

            j++;
            if(j==4) j=1;
        }
    }
}


//////////////////////////////////////////////////////////////////////
/// 下面是实现计算重复率的一些函数
/// Insert_Sum() Count() Compare()
///
///////////////////////////////////////////////////////////////////////


void Insert_Sum(std::string sentence, std::set<std::string>&s){//分词、建立词库
    //该函数可以向set数组中存入两句话中所有词，形成词库
    int pos1;
    int pos2;
    std::string word;
    pos1 = 0;
    while (true){
        pos2 = sentence.find(" ", pos1);
        word = sentence.substr(pos1, pos2 - pos1);
        s.insert(word);
        pos1 = pos2 + 1;
        if ((int)pos2 == -1)
            break;
    }
}

void Count(std::map<std::string, int>&s, std::string sentence){//查找相同因子
    int pos1;
    int pos2;
    std::string word;
    pos1 = 0;
    while (true){
        pos2 = sentence.find(" ", pos1);
        word = sentence.substr(pos1, pos2 - pos1);
        s[word]++;
        pos1 = pos2 + 1;
        if ((int)pos2 == -1)
            break;
    }
}


QString Compare(){//比较
    std::string sen1;
    std::string sen2;
    std::set<std::string> word_sum;//两个句子所有词语的总集合
    std::set<std::string>::iterator word_sumIter;
    //qDebug()<<all2<<endl;
    all1.replace(QString("!"),QString(" "));//替换特殊符号1
    all1.replace(QString("\n"),QString(" "));
    all1.replace(QString("?"),QString(" "));
    all1.replace(QString("\\"),QString(" "));
    all1.replace(QString("."),QString(" "));
    all1.replace(QString(","),QString(" "));
    all2.replace(QString("!"),QString(" "));//替换特殊符号2
    all2.replace(QString("\n"),QString(" "));
    all2.replace(QString("?"),QString(" "));
    all2.replace(QString("\\"),QString(" "));
    all2.replace(QString("."),QString(" "));
    all2.replace(QString(","),QString(" "));
    //qDebug()<<all2<<endl;
    //qDebug()<<all1<<endl;
    sen1 = all1.toStdString();
    sen2 = all2.toStdString();

    Insert_Sum(sen1, word_sum);
    Insert_Sum(sen2, word_sum);

    std::map<std::string, int> word1;//统计两个句子的词频
    std::map<std::string, int>::iterator wordIter1;
    std::map<std::string, int> word2;
    std::map<std::string, int>::iterator wordIter2;

    for (word_sumIter = word_sum.begin(); word_sumIter != word_sum.end(); word_sumIter++){//容器归零
        word1[*word_sumIter] = 0;
        word2[*word_sumIter] = 0;
    }
    Count(word1, sen1);
    Count(word2, sen2);
/*
    for (wordIter1 = word1.begin(); wordIter1 != word1.end(); wordIter1++)
        cout << (*wordIter1).first << (*wordIter1).second << endl;

    for (wordIter2 = word2.begin(); wordIter2 != word2.end(); wordIter2++)
        cout << (*wordIter2).first << (*wordIter2).second << endl;
*/
    //下面计算word1，word2向量之间的夹角
    double a;
    double b;
    double c;
    a = 0, b = 0, c = 0;
    double result=0;
    for (wordIter1 = word1.begin(), wordIter2 = word2.begin();
         wordIter1 != word1.end(), wordIter2 != word2.end();
         wordIter1++, wordIter2++)
    {
        a = (*wordIter1).second*(*wordIter2).second + a;
        b = pow((double)(*wordIter1).second, 2) + b;
        c = pow((double)(*wordIter2).second, 2) + c;
    }
    //cout << pow(b, 1.0 / 2.0)*pow(c, 1.0 / 2.0);
	b = sqrt(b);
	c = sqrt(c);
    result = (double)a / (b*c);
    qDebug()<<a<<endl;
    qDebug()<<b<<endl;
    qDebug()<<c<<endl;
    qDebug()<<b*c<<endl;
    char buffer[10];
    sprintf_s(buffer,"%f",result*100);
    //qDebug()<<s<<endl;
    //qDebug()<<result<<endl;
    std::string results = buffer;
    QString resultsq = QString::fromStdString(results);
    qDebug()<<resultsq<<endl;
    //cout << "余弦相似度为：  " << result;
    return resultsq;
}
void MainWindow::on_simiStart_clicked()
{
    QString resultq = Compare()+"%";
    ui->simiView->setPlainText(resultq);
}

