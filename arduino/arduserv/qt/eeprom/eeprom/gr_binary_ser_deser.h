#ifndef GR_BINARY_SER_DESER_H
#define GR_BINARY_SER_DESER_H

#include <vector>
#include <variant>
#include <string>
#include <unordered_map>
#include <iostream>

namespace bsd {

using Buffer = std::vector<uint8_t>;
class Node;
using Array = std::vector<Node>;

class Node
    : public std::variant<bool,char,int,float,double,std::string,Array> {
public:
    /*Node operator= (Node other){
        *this=other;
        return *this;
    }*/
    /*template<typename T>
    Node(T t){
         *this=t;
    }*/

    template<typename T>
    void set(T i){
        *this={i};
    }
    template<typename T>
    T get_t(){
        T t;
        if(std::holds_alternative<T>(*this)){
            t=std::get<T>(*this);
        }
        return t;
    }

};

class GR_binary_ser_deser
{
public:
    GR_binary_ser_deser(std::unordered_map<std::string,Node> structure_ext):structure(std::move(structure_ext)){

    }

private:
    void to_bin_parser(Buffer &buff,Node &node){
        switch ( node.index() ) {
            case 0://bool
                serialize(buff,std::get<bool>(node));
                break;
            case 1://char
                serialize(buff,std::get<char>(node));
                break;
            case 2://int
                serialize(buff,std::get<int>(node));
                break;
            case 3://float
                serialize(buff,std::get<float>(node));
                break;
            case 4://double
                serialize(buff,std::get<double>(node));
                break;
            case 5://string
                serialize(buff,std::get<std::string>(node));
                break;
            case 6://Array
                for(auto &a:std::get<Array>(node)){
                    to_bin_parser(buff,a);
                }
                break;
        }
    }

    void from_bin_parser(Buffer &buff,Node &node,size_t &offset){
        switch ( node.index() ) {
            case 0://bool
                node={deserialize<bool>(buff, offset)};
                break;
            case 1://char
                //data.second={deserialize<char>(buff, offset)};//!!!
                node.set(deserialize<char>(buff, offset));
                break;
            case 2://int
                node={deserialize<int>(buff, offset)};
                break;
            case 3://float
                node={deserialize<float>(buff, offset)};
                break;
            case 4://double
                node={deserialize<double>(buff, offset)};
                break;
            case 5://string
                //data.second=deserialize<std::string>(buff, offset);
                node={deserialize_string(buff, offset)};
                break;
            case 6://Array
                for(auto &a:std::get<Array>(node)){
                    from_bin_parser(buff,a,offset);
                }
                break;
        }
    }
public:
    void to_bin(Buffer &buff){
        for(auto &data:structure){
            to_bin_parser(buff,data.second);
        }
    }
    void from_bin(Buffer &buff){
        size_t offset = 0;
       for(auto &data:structure){
           from_bin_parser(buff,data.second,offset);
        }
    }
private:
    ///bool,char,int,float,double
    template<typename T>
    typename std::enable_if<std::is_pod_v<T>>::type
    serialize(Buffer& buff, T value)
    {
        auto offset = buff.size();
        buff.resize(buff.size() + sizeof(T));
        memcpy(&buff[offset], &value, sizeof(value));
    }

    template<typename T>
    T deserialize(const Buffer& buf, size_t& offset)
    {
        static_assert(std::is_default_constructible_v<T>, "Value is not default constructible");
        T value;
        if constexpr (std::is_pod_v<T>)
        {
            memcpy(&value, &buf[offset], sizeof(T));
            offset += sizeof(T);
        }
        else
        {
            static_assert("Serializer for type not defined");
        }
        return value;
    }
    /// string
    template<typename String>
    typename std::enable_if<std::is_same_v<std::string, typename std::remove_reference<String>::type>>::type
    serialize(Buffer& buff, String&& value)
    {
        auto offset = buff.size();
        buff.resize(buff.size() + 1 + value.size() * sizeof(char));
        const auto size = value.size();
        memcpy(&buff[offset], &size, 1);
        offset += 1;
        memcpy(&buff[offset], value.data(), size * sizeof(char));
    }

    //template<>//нет у меня 20 стандарта)))
    std::string deserialize_string(const Buffer& buf, size_t& offset)
    {
        std::string value;
        size_t size{0};
        memcpy( &size, &buf[offset], 1);
        offset += 1;
        value.resize(size);
        memcpy(value.data(),&buf[offset] , size);
        offset += size;
        return value;
    }
    /// vector
    template<typename T>
    void serialize_vector(Buffer& buff, T& value)
    {
        typename T::value_type s;
        auto offset = buff.size();
        buff.resize(buff.size() + 1 + value.size() * sizeof(s));//рассчет размера буфера
        const auto size = value.size();
        memcpy(&buff[offset], &size, 1);
        offset += 1;
        memcpy(&buff[offset], value.data(), size*sizeof(s));
    }

    //template<>//нет у меня 20 стандарта)))
    template<typename T>
    std::vector<T> deserialize_vector(const Buffer& buf, size_t& offset)
    {
        typename T::value_type s;
        T value;//возвращаемый вектор
        size_t size{0};
        memcpy( &size, &buf[offset], 1);//определяем размер вектора
        offset += 1;//переход по адресу к началу массива
        value.resize(size);
        size*=sizeof(s);
        memcpy(value.data(),&buf[offset] , size);
        offset += size;
        return value;
    }
    //
    public:
    std::unordered_map<std::string,Node> structure;
};

}
#endif // GR_BINARY_SER_DESER_H
 /* //////////////////////////////////
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
 */
