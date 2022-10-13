#include <QCoreApplication>

#include <typeinfo>
#include <iostream>
#include <variant>

#include "gr_binary_ser_deser.h"

using namespace std;

////////////////////////////////////
void print_rec(Node &node,string pre="") {
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
            //serialize(buff,std::get<Array>(data.second));
            //auto vect=std::get<Array>(data.second);
            //auto a=3;
            //a++;
            //for(auto &a:vect){
            //    cout<<"    "<<a<<endl;
            //}
            for(auto &a:std::get<Array>(node)){
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


    //Array arr({1,2,3});


    /*GR_binary_ser_deser inf({{
                             {
                              {"a"s,false}, //bool
                              {"b"s,3},     //int
                              {"c"s,4.35},   //double
                              {"d"s,7.2f}, //float
                              {"e"s,'a'},   //char
                              {"f"s,"eee"s},//string
                              {"g"s,'b'},   //char
                              {"h"s,'c'}    //char
                              //{"i",arr},
                              //{"j",'h'},
                              //{"k","f"},
                              //{"l",3},
                              //{"m",45.0},
                              //{"n",arr}
                             }
                            }});*/
    //Node test{3};
    //test=4;

    Array fff={Array({ {1},{2},{3} })};
    GR_binary_ser_deser inf({{
                                 {
                                  {"a"s,{false}}, //bool
                                  {"b"s,{3}},     //int
                                  {"c"s,{4.35}},   //double
                                  {"d"s,{7.2f}}, //float
                                  {"e"s,{'a'}},   //char
                                  {"f"s,{"eee"s}},//string
                                  {"g"s,{'b'}},   //char
                                  {"h"s,{'c'}},    //char
                                  {"i",{Array({ {"asvas"s},{2.2},{3.3},{'v'} })}},
                                  {"j"s,{'h'}},
                                  {"k",{"f"}},
                                  {"l",{3}},
                                  {"m",{45.736}}
                                  //{"n",arr}
                                 }
                                }});
    GR_binary_ser_deser inf2({{
                                 {
                                  {"a"s,{true}}, //bool
                                  {"b"s,{0}},     //int
                                  {"c"s,{0.0}},   //double
                                  {"d"s,{0.0f}}, //float
                                  {"e"s,{'0'}},   //char
                                  {"f"s,{""s}},//string
                                  {"g"s,{'0'}},   //char
                                  {"h"s,{'0'}},    //char
                                  {"i",{Array({ {""s},{0.0},{0.0},{'0'} })}},
                                  {"j"s,{'0'}},
                                  {"k",{"0"}},
                                  {"l",{0}},
                                  {"m",{0.0}}
                                  //{"n",arr}
                                 }
                                }});

    Buffer buff;
    inf.to_bin(buff);
    Buffer buff_test=buff;

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
