#include <iostream>
#include <vector>
#include <stdint.h>
using namespace std;

using Buffer = std::vector<uint8_t>;

template<typename T>
typename std::enable_if<std::is_pod_v<T>>::type
serialize(Buffer& buff, T value)
{
    buff.resize(buff.size() + sizeof(T));
    memcpy(&buff[0], &value, sizeof(value));
}

template<typename String>
typename std::enable_if<std::is_same_v<std::string, typename remove_reference<String>::type>>::type
serialize(Buffer& buff, String&& value)
{
    auto offset = buff.size();
    buff.resize(buff.size() + sizeof(size_t) + value.size() * sizeof(char));
    const auto size = value.size();
    memcpy(&buff[offset], &size, sizeof(size_t));
    offset += sizeof(size_t);
    memcpy(&buff[offset], value.data(), size);
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

template<>
std::string deserialize(const Buffer& buf, size_t& offset)
{
    std::string value;
    size_t size{0};
    memcpy( &size, &buf[offset],  sizeof(size_t));
    offset += sizeof(size_t);
    value.resize(size);
    memcpy(value.data(),&buf[offset] , size);
    offset += size;
    return value;
}


int main2()
{
    size_t offset = 0;
    Buffer buff;

    int testVal = 42;
    serialize(buff, testVal);

    std::string s{"Super test string"};
    serialize(buff, s);

    char *cha="Super test char";
    serialize(buff, cha);

    int testVal2 = deserialize<int>(buff, offset);
    std::string str = deserialize<std::string>(buff, offset);

    cout << testVal<<"\t"<<testVal2<<"\t"<<str << endl;
    return 0;
}
