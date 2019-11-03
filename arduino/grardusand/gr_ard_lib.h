//////////////////
/////////////////
////////////////
  int check_time(unsigned int id,unsigned long m_sec){
    static unsigned long mils[dtd_count];
    unsigned long cur_mils=micros();
    unsigned long delta=cur_mils-mils[id];
    if(id==0 && m_sec==0){
      for(int i=0;i<dtd_count;i++){
          mils[i]=0;
      }
    }else{
      if(delta>m_sec){
        mils[id]=cur_mils-(delta-m_sec);
        return 1;
      }
    }
    return 0;
  }
//////////////////
/////////////////
////////////////
