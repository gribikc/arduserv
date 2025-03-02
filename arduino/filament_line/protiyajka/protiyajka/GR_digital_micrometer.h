class GR_digital_micrometer{
    public:
        GR_digital_micrometer(int data_pin,int clk_pin):data_pin_(data_pin),clk_pin_(clk_pin){
            pinMode (data_pin_, INPUT);
            pinMode (clk_pin_, INPUT);
            pinMode (data_pin_, INPUT_PULLUP);//INPUT_PULLDOWN 
            pinMode (clk_pin_, INPUT_PULLUP );
            //digitalWrite (data_pin_, 0);
            //digitalWrite (clk_pin_, 0);
            //attachInterrupt(clk_pin_,get_bit,RISING);
        }
    
        void get_bit(){
            //bit_valid_=1;
            //bit_=digitalRead(data_pin_);
            //time_arrave_=millis();
            ///!!! переделать на кольцевой буфер !!!
            auto t=millis();
            int a=digitalRead(data_pin_);
            a+=digitalRead(data_pin_);
            a+=digitalRead(data_pin_);
            a+=digitalRead(data_pin_);
            a+=digitalRead(data_pin_);
            data_in_buf_[wr_p]=std::make_pair( ((a>2)?true:false),t);
            //if(a==4 || a==3 || a==2 || a==1){
            //    Serial.print("major:");
            //    Serial.println(a);
            //}
            ++wr_p&=mask;
        }

        bool doit(){
            if(fake_mode_==1){
              auto t=millis();
              if(t-previousGetMillis_>100/14){//70*24
                previousGetMillis_=t;
                izm_=1.75f+(float)((float)(random(-1000, 1000))/(float)100000.0f)+(float)((float)fake_cnt_/(float)10000.0f);
                ++fake_cnt_;
                if(fake_cnt_>1000) fake_cnt_=-1000;
                //Serial.println(izm_);
                return true;
              }
              return false;
            }
            //for(auto &data:data_in_buf_){
            while(wr_p!=rd_p){
                //auto& data=data_in_buf_[0];
                auto& time_arrave=data_in_buf_[rd_p].second;
                auto& bit=data_in_buf_[rd_p].first;
                ++rd_p&=mask;

                auto delta_time=time_arrave - previousGetMillis_;
                if ((bit_cnt_ !=0) && (delta_time > 8/*8*/) ) { //обнуление по превышению таймаута
                    Serial.print("lost sync:");
                    Serial.print(time_arrave - previousGetMillis_);
                    Serial.print(":");
                    Serial.print(bit_cnt_);
                    Serial.print(":");
                    Serial.println(lost_cnt);

                    bit_cnt_ = 0; 
                    xData_ = 0; 
                    lost_cnt++;
                }; 
                previousGetMillis_=time_arrave; 

                if(bit_cnt_ < 20){ 
                    if(bit==1){ 
                        xData_|= 1<<bit_cnt_;
                    } 
                } else { 
                    if (bit_cnt_==20) //минус
                        isfs_=bit; 
                    
                    if (bit_cnt_==23) //дюймы
                        isin_=bit; 
                }; 
                bit_cnt_++; 

                if (bit_cnt_ >23) { //если слово считано полностью
                    if (isin_==1){ //дюймы 
                        return 0; 
                    }else{ //мм
                        izm_ =xData_;//1000.00;
                        izm_/=1000.00;
                        if (isfs_==1){ //минус
                            izm_=(float)(izm_*(-1.0f));
                        }
                        if(obr_!=nullptr){
                            obr_(izm_);
                        }
                    }; 
                    /*if(izm_<-10.051 || izm_>-10.046){
                        Serial.println(izm_);
                        //Serial.print(":");
                        //Serial.print(delta_time);
                        //Serial.print(":");
                        //Serial.println(xData_);
                    }*/
                    bit_cnt_=0; 
                    xData_=0; 
                    return 1;
                } 
            }
            return 0;
        }

        float get_izm() const{
            return izm_;///!!! надо с этим разобратся почемуто иногда инверсия измерений идет!!!
        }

        void set_obr(void (*obr)(float)) {
            obr_=obr;
        }

        void fake_mode_set(bool set){
          fake_mode_=set;
        }

        //void (*obr)(float)=nullptr;
        int lost_cnt=0;
    private:
        bool fake_mode_=0;
        int fake_cnt_=0;
    
        int data_pin_=13;
        int clk_pin_=14;
        
        long unsigned int previousGetMillis_=0;

        //bool bit_valid_=0;
        //bool bit_=0;
        //long unsigned int time_arrave_=0;
        std::array<std::pair<bool,long unsigned int>,128> data_in_buf_;
        const char mask=0x7F;
        volatile int rd_p=0,wr_p=0;
        
        int bit_cnt_=0;
        int isin_ = 0; //д=1 мм=0 
        int isfs_ = 0; //минус 
        unsigned long xData_;
        float izm_;
        void (*obr_)(float)=nullptr;
};
