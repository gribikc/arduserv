#include <QCoreApplication>

#include <typeinfo>
#include <iostream>
#include <variant>

#include "gr_binary_ser_deser.h"

using namespace std;

////////////////////////////////////

////////////////////////////////////

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //////////////////////////////////


    Array arr({1,2,3});

    GR_binary_ser_deser inf({
                             {
                              {"a",false}, //bool
                              {"b",3},     //int
                              {"c",4.0},   //double
                              {"d",4.0f}, //float
                              {"e",'c'},   //char
                              {"f","eee"s},//string
                              {"g",'q'},   //char
                              {"h",'c'},    //char
                              {"i",arr}
                             }
                            });


    Buffer buff;
    inf.to_bin(buff);
    Buffer buff_test=buff;

    inf.from_bin(buff);
    buff.erase(buff.begin(),buff.end());
    inf.to_bin(buff);

    if(buff_test==buff){
        cout<<"OK";
    }else{
        cout<<"NE OK";
    }



    //////////////////////////////////

    return a.exec();
}
