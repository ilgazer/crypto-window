#include "mytable.h"

#include <QApplication>
#include<QFile>

// returns names or symbols of coins in the input file as a QSet<QString>
QSet<QString> get_input_coin_names()
{
    // reading value of environment variable: MYCRYPTOCONVERT
    char envVar[16] = "MYCRYPTOCONVERT";
    QString input_file_name(qgetenv(envVar));

    // opening the input file
    QFile input_file(input_file_name);
    input_file.open(QIODevice::ReadOnly | QIODevice::Text);

    // adding coin names/symbols to QSet coinList
    QSet<QString> coinList;
    while(true)
    {
        // read coin name
         QString coin_name(input_file.readLine());
         // if name of coin is nothing then we are at the end of file
         if(coin_name.size() == 0)break;
         //erase unnecessary \n s at the end
         int n = coin_name.size() - 1;
         while(coin_name.data()[n] == '\n')
             coin_name.remove(n,coin_name.size());
        //insert this coin into coin_list
         coinList.insert(coin_name);
    }
    //closing the input file
    input_file.close();
    //"https://api.coingecko.com/api/v3/simple/price?ids=bitcoin,litecoin&vs_currencies=usd,eur,gbp"
   // for(QString s : coinList)
     //   qDebug() << s;
    return coinList;

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTable table;
    return a.exec();
}
