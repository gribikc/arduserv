class GR_step_driver
{

public:
    GR_step_driver(int step_pin,int dir_pin,int en_pin=0,int fb_pin=0,float degres=1.8f,int reduction=0):
        step_pin_(step_pin),
        dir_pin_(dir_pin),
        en_pin_(en_pin),
        fb_pin_(fb_pin),
        degres_(degres),
        reduction_(reduction)
    {
        pinMode (step_pin_, OUTPUT);
        pinMode (dir_pin_, OUTPUT);
        if(en_pin!=0){
            pinMode (en_pin_, OUTPUT);
        }
        if(fb_pin_!=0){
            pinMode (fb_pin_, INPUT_PULLUP);
        }

        digitalWrite(en_pin,0);
        digitalWrite(en_pin,0);
    }

    void doit(){
        acc_+=inc_;
        if(acc_>0 && step_state_==0){
            step_state_=1;
            digitalWrite(step_pin_,step_state_);
            ++cur_odometr;
        }else if(acc_<0 && step_state_==1){
            step_state_=0;
            digitalWrite(step_pin_,step_state_);
        }
    }

    void set_ob_sec(float freq){
        inc_=(freq*(micro_step_*360/degres_)*exp32_)/fs_;
    }

    void inc_ob_sec(float freq){
        inc_+=(freq*(micro_step_*360/degres_)*exp32_)/fs_;
    }

    float get_ob_sec(){
        return (get_freq()/(micro_step_*360/degres_));
    }

    void set_freq(float freq){
        inc_=(freq*exp32_)/fs_;
    }

    void inc_freq(float freq){
        inc_=(freq*exp32_)/fs_;
    }
        
    float get_freq(){
        return (fs_/exp32_)*inc_;
    }

    signed int get_inc(){
        return inc_;
    }


private:
    int step_pin_=0;
    int dir_pin_=0;
    int en_pin_=0;
    int fb_pin_=0;
    float degres_=1.8f;
    int micro_step_=8;
    int reduction_=1;

    signed int acc_=0;
    signed int inc_=21474836;
    bool    step_state_=0;
    float fs_=100000;//KHz
    float exp32_=4294967296;

    volatile signed long int cur_odometr=0;
    volatile signed long int target_odometr=0;
    //
    //f0=(fs*inc_)/2^32
    //1об/сек==200pps;          200*2^32/100000= 8589934,592
    //2об/сек==400pps;          400*2^32/100000=17179869,184
    //         400,00001899     17179870
    //8об/сек==1600pps;1600*2^32/100000=68719476,736
    //inc_=(f0*2^32)/fs

};




