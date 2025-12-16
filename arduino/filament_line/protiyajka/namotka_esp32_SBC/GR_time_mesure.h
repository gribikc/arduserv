class GR_time_mesure
{

public:
    GR_time_mesure(){
    }
    void doit(){
        long cur=millis();
        if(!pre_mills_==0){
            measure_=cur-pre_mills_;
            if(st){
                min_measure_=measure_;
                max_measure_=measure_;
                avg_measure_=measure_;
                st=0;
            }else{
                if(min_measure_>measure_){
                    min_measure_=measure_;
                }
                if(max_measure_<measure_){
                    max_measure_=measure_;
                }
                avg_measure_=avg_measure_*0.999+measure_*0.001;
            }
        }
        pre_mills_=cur;
    }

    void reset(){
        st=1;
        pre_mills_=0;
    }

    float get_min(){return min_measure_;}
    float get_max(){return max_measure_;}
    float get_avr(){return avg_measure_;}
    float get_cur(){return measure_;}

private:
    long pre_mills_=0;
    float measure_=0;
    float min_measure_=0;
    float max_measure_=0;
    float avg_measure_=0;
    bool st=1;
};




