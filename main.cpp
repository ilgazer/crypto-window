#include "mytable.h"

#include <QApplication>
#include<QFile>

// returns names or symbols of coins in the input file as a QSet<QString>
QSet<QString> getInputCoinNames()
{
    // reading value of environment variable: MYCRYPTOCONVERT
    char envVar[16] = "MYCRYPTOCONVERT";
    QString inputFileName(qgetenv(envVar));

    // opening the input file
    QFile inputFile(inputFileName);
    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);

    // adding coin names/symbols to QSet coinList
    QSet<QString> coinList;
    while(true)
    {
        // read coin name
         QString coinName(inputFile.readLine());
         // if name of coin is nothing then we are at the end of file
         if(coinName.size() == 0)break;
         //erase unnecessary \n s at the end
         int n = coinName.size() - 1;
         while(coinName.data()[n] == '\n')
             coinName.remove(n,coinName.size());
        //insert this coin into coin_list
         coinList.insert(coinName);
    }
    //closing the input file
    inputFile.close();
    return coinList;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto names = getInputCoinNames();
    MyTable table(names);
    return a.exec();
}
