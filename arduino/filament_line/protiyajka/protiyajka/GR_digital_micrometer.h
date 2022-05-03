class GR_digital_micrometer{
    public:
        GR_digital_micrometer(int data_pin,int clk_pin):data_pin_(data_pin),clk_pin_(clk_pin){
            digitalWrite (data_pin_, 0);
            digitalWrite (clk_pin_, 0);
            pinMode (data_pin_, INPUT);
            pinMode (clk_pin_, INPUT);
            //attachInterrupt(clk_pin_,get_bit,RISING);
        }
    
        void get_bit(){
            bit_valid_=1;
            bit_=digitalRead(data_pin_);
            time_arrave_=millis();
        }

        bool doit(){
            if(!bit_valid_)
                return 0;
            bit_valid_=0;

            if ((bit_cnt_ !=0) && (time_arrave_ - previousGetMillis_ > 8) ) { //обнуление по превышению таймаута
                bit_cnt_ = 0; 
                xData_ = 0; 
            }; 
            previousGetMillis_=time_arrave_; 

            if(bit_cnt_ < 20){ 
                if(bit_==1){ 
                    xData_|= 1<<bit_cnt_;
                } 
            } else { 
                if (bit_cnt_==20) //минус
                    isfs_=bit_; 
                
                if (bit_cnt_==23) //дюймы
                    isin_=bit_; 
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

                bit_cnt_=0; 
                xData_=0; 
                return 1;
            } 
            return 0;
        }

        float get_izm() const{
            return izm_;
        }

        void set_obr(void (*obr)(float)) {
            obr_=obr;
        }

        //void (*obr)(float)=nullptr;
    private:
        int data_pin_=13;
        int clk_pin_=14;
        
        long previousGetMillis_=0;

        bool bit_valid_=0;
        bool bit_=0;
        long time_arrave_=0;
        
        int bit_cnt_=0;
        int isin_ = 0; //д=1 мм=0 
        int isfs_ = 0; //минус 
        unsigned long xData_;
        float izm_;
        void (*obr_)(float)=nullptr;
};