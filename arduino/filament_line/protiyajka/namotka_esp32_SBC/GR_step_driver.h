class GR_step_driver
{

public:
    GR_step_driver(int step_pin,int dir_pin,int en_pin=0,int fb_pin=0,float degres=1.8f,float reduction=5.18f,bool dir=true):
        step_pin_(step_pin),
        dir_pin_(dir_pin),
        en_pin_(en_pin),
        fb_pin_(fb_pin),
        degres_(degres),
        reduction_(reduction),
        dir_(dir)
    {
        //pinModeFast(pinNum, OUTPUT);
        pinMode (step_pin_, OUTPUT);
        pinMode (dir_pin_, OUTPUT);
        digitalWrite(dir_pin_,dir);//dir
        if(en_pin!=0){
            pinMode (en_pin_, OUTPUT);
        }
        if(fb_pin_!=0){
            pinMode (fb_pin_, INPUT_PULLUP);
        }

        digitalWrite(en_pin,0);
    }

    void doit(){
        //accelerate
            //int max_accelerate=2000;
            //int min_accelerate=2000;
            //if(inc_target!=inc_){
            //    if(inc_target>inc_){
            //        inc_=(inc_target-inc_)<max_accelerate?inc_target:inc_+max_accelerate;
            //    }else{
            //        inc_=(inc_-inc_target)<max_accelerate?inc_target:inc_-max_accelerate;
            //    }
            //    if(inc_target==0)inc_=0;
            //}
            inc_=inc_target;//>inc_

        //ACC
            acc_+=inc_;
            if(acc_>0 && step_state_==0){
                step_state_=1;
                //digitalWriteFast(pinNum, HIGH);
                digitalWrite(step_pin_,step_state_);
                dir_cur_==dir_?++cur_odometr:--cur_odometr;
            }else if(acc_<0 && step_state_==1){
                step_state_=0;
                digitalWrite(step_pin_,step_state_);
            }

        //odometr
            if(odometr_en){
                if((dir_cur_==dir_ && target_odometr<cur_odometr) || (dir_cur_!=dir_ && target_odometr>cur_odometr)){
                    Serial.println("ОДОМЕТР АЛЯРМ!!!!");
                }
                if(target_odometr==cur_odometr){
                    //Serial.println("Одометр стоп!!!");
                    set_ob_sec(0.0);
                    odometr_en=false;
                    digitalWrite(dir_pin_,dir_);//!!!спорно убрать
                }
            }
    }
    /////////////
    void set_ob_sec(float freq){
        inc_target=(freq*(reduction_*micro_step_*360/degres_)*exp32_)/fs_;
    }

    void inc_ob_sec(float freq){
        inc_target+=(freq*(reduction_*micro_step_*360/degres_)*exp32_)/fs_;
    }

    float get_ob_sec(){
        return (get_freq()/(reduction_*micro_step_*360/degres_));
    } 
    /////////////
    void inc_freq(float freq){
        inc_target+=(freq*exp32_)/fs_;
    }

    void set_freq(float freq){
        inc_target=((freq/fs_)*exp32_);
    }

    float get_freq(){
        return (fs_*static_cast<float>(inc_target)/exp32_);
    }
    /////////////
    signed long get_inc(){
        return inc_target;
    }
    /////////////
    void dir(bool dir){
        dir_cur_=dir;
        digitalWrite(dir_pin_,dir_cur_);
    }
    void dir_ivert(){
        dir_cur_=!dir_;
        digitalWrite(dir_pin_,dir_cur_);
    }
    /////////////
    void odometr_reset(){
        cur_odometr=0;
        target_odometr=0;
        odometr_en=false;
    }
    
    signed long int get_odometr(){
        return cur_odometr;
    }

    void go_inc(signed long int dist){
        if(dist==0){
            return;
        }
        odometr_en=true;
        target_odometr=cur_odometr+dist;
        if(target_odometr>cur_odometr){
            dir_cur_=dir_;
        }else{
            dir_cur_=!dir_;
        }
        digitalWrite(dir_pin_,dir_cur_);
    }
    void go_to(signed long int dist){
        //Serial.print("dist:");Serial.println(dist);
        //Serial.print("cur_odometr:"); Serial.println(cur_odometr);
        //Serial.print("target_odometr:"); Serial.println(target_odometr);
        //Serial.print("odometr_en:"); Serial.println(odometr_en);
        //if(dist==target_odometr && !odometr_en)return;
        if(dist==cur_odometr){
            target_odometr=dist;
            odometr_en=false;
            set_ob_sec(0.0);
            return;
        }
        
        odometr_en=true;
        target_odometr=dist;
        if(target_odometr>cur_odometr){
            dir_cur_=dir_;
        }else{
            dir_cur_=!dir_;
        }
        digitalWrite(dir_pin_,dir_cur_);
    }
    /////////////

private:
    int step_pin_=0;
    int dir_pin_=0;
    int en_pin_=0;
    int fb_pin_=0;
    float degres_=1.8f;
    int micro_step_=8;
    float reduction_=5.18;
    volatile bool dir_=true;//!!! constant
    volatile bool dir_cur_=true;

    signed long acc_=0;
    signed long inc_=0;
    volatile signed long inc_target=21474836;
    bool    step_state_=0;
    float fs_=100000;//KHz
    float exp32_=4294967296ULL;

    volatile signed long int cur_odometr=0;
    volatile signed long int target_odometr=0;
    volatile bool odometr_en=false;
    //
    //f0=(fs*inc_)/2^32
    //1об/сек==200pps;          200*2^32/100000= 8589934,592
    //2об/сек==400pps;          400*2^32/100000=17179869,184
    //         400,00001899     17179870
    //8об/сек==1600pps;1600*2^32/100000=68719476,736
    //inc_=(f0*2^32)/fs

};
