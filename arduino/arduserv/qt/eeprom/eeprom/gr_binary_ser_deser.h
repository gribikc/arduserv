#ifndef GR_BINARY_SER_DESER_H
#define GR_BINARY_SER_DESER_H

#include <vector>
#include <variant>
#include <string>
#include <unordered_map>
#include <iostream>

using Buffer = std::vector<uint8_t>;
//using Node = std::unordered_map<std::string,std::variant<bool,char,int,float,double,std::string,std::vector<Node>>>;
class Node;
using Array = std::vector<std::variant<bool,char,int,float,double>>;
class Node
    : public std::unordered_map<std::string,std::variant<bool,char,int,float,double,std::string,Array>> {
public:

};


class GR_binary_ser_deser
{
public:
    GR_binary_ser_deser(Node node):node_(std::move(node)){

    }

public:
    void to_bin(Buffer &buff){
        for(auto &data:node_){
            switch ( data.second.index() ) {
            case 0://bool
                serialize(buff,std::get<bool>(data.second));
                break;
            case 1://char
                serialize(buff,std::get<char>(data.second));
                break;
            case 2://int
                serialize(buff,std::get<int>(data.second));
                break;
            case 3://float
                serialize(buff,std::get<float>(data.second));
                break;
            case 4://double
                serialize(buff,std::get<double>(data.second));
                break;
            case 5://string
                serialize(buff,std::get<std::string>(data.second));
                break;
            case 6://Array
                //serialize(buff,std::get<Array>(data.second));
                break;
            }
        }
    }
    void from_bin(Buffer &buff){
        size_t offset = 0;
        for(auto &data:node_){
            switch ( data.second.index() ) {
            case 0://bool
                data.second=deserialize<bool>(buff, offset);
                break;
            case 1://char
                data.second=deserialize<char>(buff, offset);
                break;
            case 2://int
                data.second=deserialize<int>(buff, offset);
                break;
            case 3://float
                data.second=deserialize<float>(buff, offset);
                break;
            case 4://double
                data.second=deserialize<double>(buff, offset);
                break;
            case 5://string
                //data.second=deserialize<std::string>(buff, offset);
                data.second=deserialize_string(buff, offset);
                break;
            }
        }
    }
private:
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
    //////
    //////
    template<typename String>
    typename std::enable_if<std::is_same_v<std::string, typename std::remove_reference<String>::type>>::type
    serialize(Buffer& buff, String&& value)
    {
        auto offset = buff.size();
        buff.resize(buff.size() + /*sizeof(size_t)*/ 1 + value.size() * sizeof(char));
        const auto size = value.size()&0xFF;
        memcpy(&buff[offset], &size, sizeof(size_t));
        offset += /*sizeof(size_t)*/ 1;
        memcpy(&buff[offset], value.data(), size);
    }

    //template<>//нет у меня 20 стандарта)))
    std::string deserialize_string(const Buffer& buf, size_t& offset)
    {
        std::string value;
        size_t size{0};
        memcpy( &size, &buf[offset],  /*sizeof(size_t)*/1);
        offset += /*sizeof(size_t)*/1;
        value.resize(size);
        memcpy(value.data(),&buf[offset] , size);
        offset += size;
        return value;
    }
private:
    Node node_;
};

#endif // GR_BINARY_SER_DESER_H
