#include <vector>

template<typename Type>
class GR_data_collector{
    public:
        GR_data_collector(int size=100){
            vector_.resize(size);
            size_=size;
        }

        std::vector<Type>& get(){
            cleaninc(1);

            return vector_;
        }

        void add(const Type& data){
            cleaninc(0);
            if(vector_.size()>=size_){
                vector_.erase(vector_.begin());
            }
            vector_.push_back(data);
        }

    private:
        void cleaninc(bool clean=0){
            if(need_clear_){
                vector_.clear();
                need_clear_=0;
            }
            need_clear_=clean;
        }
        std::vector<Type> vector_;
        bool need_clear_=0;
        int size_=100;
};