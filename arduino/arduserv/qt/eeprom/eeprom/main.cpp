#include <QCoreApplication>

#include <typeinfo>
#include <iostream>
#include <variant>

#include "gr_binary_ser_deser.h"

using namespace std;

////////////////////////////////////
void print_rec(bsd::Node &node,string pre="") {
    cout<<pre;
    switch ( node.index() ) {
        case 0://bool
            cout<<node.get_t<bool>()<<endl;
            break;
        case 1://char
            //char a=data.second.get_t<char>();
            cout<<node.get_t<char>()<<endl;  //std::get<char>(data.second)
            break;
        case 2://int
            cout<<node.get_t<int>()<<endl;
            break;
        case 3://float
            cout<<node.get_t<float>()<<endl;
            break;
        case 4://double
            cout<<node.get_t<double>()<<endl;
            break;
        case 5://string
            cout<<node.get_t<string>()<<endl;
            break;
        case 6://Array
            for(auto &a:std::get<bsd::Array>(node)){
                print_rec(a,pre+"|-");
            }
            break;
    }

};
////////////////////////////////////

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //////////////////////////////////
    char valid=0;
    //EEPROM.get(0,valid);
    if(valid==1){
      //EEPROM.get(1,work_model.mem);
    }

    ///
    struct eedat_upr_def{
      char valid=0;
      float k_p=-0.05;
      float k_d=0.99;
      float pre_error=0;
      float target_diametr=1.75f;
      int iad=20;
    };

    struct work_model_def:eedat_upr_def{
      int w_mode=0;//!!!=0//0-none;1-auto;2-uderjanie;
    }work_model;

    //EEPROM.get(0);
    work_model=work_model_def({});

    ///
    struct Data {
      double bright = 0;
      int counter = 0;
      float fvalue = 0;
      //16
      char text='c';
      //24
      string str="svsbvdbsdb";
      string str2="svsbvdbsdb";

      array<double,3> ard;

    };
    // глобальный экземпляр для личного использования
    Data data{1,2,3};
    Data data2{0,0,0};
    cout<<sizeof (data)<<endl;
    memcpy(&data2,&data,sizeof (data));
    data.str="";

    //////////////////////////////////
    bsd::GR_binary_ser_deser inf({{
                                 {
                                  {"a"s,{false}}, //bool
                                  {"b"s,{3}},     //int
                                  {"c"s,{4.35}},   //double
                                  {"d"s,{7.2f}}, //float
                                  {"e"s,{'a'}},   //char
                                  {"f"s,{"eee"s}},//string
                                  {"g"s,{'b'}},   //char
                                  {"h"s,{'c'}},    //char
                                  {"i",{bsd::Array({ {"asvas"s},{2.2},{3.3},{'v'} })}},
                                  {"j"s,{'h'}},
                                  {"k",{"f"}},
                                  {"l",{3}},
                                  {"m",{45.736}}
                                  //{"n",arr}
                                 }
                                }});
    bsd::GR_binary_ser_deser inf2({{
                                 {
                                  {"a"s,{true}}, //bool
                                  {"b"s,{0}},     //int
                                  {"c"s,{0.0}},   //double
                                  {"d"s,{0.0f}}, //float
                                  {"e"s,{'0'}},   //char
                                  {"f"s,{""s}},//string
                                  {"g"s,{'0'}},   //char
                                  {"h"s,{'0'}},    //char
                                  {"i",{bsd::Array({ {""s},{0.0},{0.0},{'0'} })}},
                                  {"j"s,{'0'}},
                                  {"k",{"0"}},
                                  {"l",{0}},
                                  {"m",{0.0}}
                                  //{"n",arr}
                                 }
                                }});

    bsd::Buffer buff;
    inf.to_bin(buff);
    bsd::Buffer buff_test=buff;

    inf2.from_bin(buff);
    buff.erase(buff.begin(),buff.end());
    inf2.to_bin(buff);

    if(buff_test==buff){
        cout<<"OK"<<endl;;
    }else{
        cout<<"NE OK"<<endl;;
    }


    for(auto& data:inf2.structure){
        print_rec(data.second);
    }

    cout<<endl<<"-----"<<endl;
    cout<<inf2.structure["m"].get_t<double>()<<endl;
    inf2.structure["m"].set<double>(3.56);
    cout<<inf2.structure["m"].get_t<double>()<<endl;
    //////////////////////////////////

    return a.exec();
}
