class GR_time_mesure
{

public:
    GR_time_mesure(){
    }
    void doit(){
        long cur=millis();
        if(!pre_mills_==0){
            measure_=cur-pre_mills_;
        }else{
            measure_=0;
        }
        pre_mills_=cur;
    }

    float get() const{
        return measure_;
    }

private:
    long pre_mills_=0;
    float measure_=0;

};




