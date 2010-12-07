
#define KBD_PORT    PORTA 
#define KBD_DDR     DDRA 
#define KBD_PIN     PINA

void kbdInit( void ){
     KBD_DDR=0b11110000;  
     KBD_PORT=0b11110000; 
} 

byte kbdReadRAW(void){
     
     byte bScanMask=0b00001111;     
     byte bKeyMask=0b00010000;
     byte bKeyMask2;
     byte ret,reti;
     int iColCnt=0;
     
     KBD_PORT=0b11110000;
     
     
     while(iColCnt<4){
        bKeyMask2=~bKeyMask ;
        KBD_PORT = bKeyMask2;
        delay_us(10);
        ret=KBD_PIN;
        ret=ret & bScanMask;                     
        
        if(ret<15 ){
            /*
            reti=ret;
            while(reti==ret){
                ret=KBD_PIN;
            }
            */
            delay_ms(300);
            ret=ret | bKeyMask;
            //LCD_PUTC3(20,50,ret);
            return ret;
        }
        
                
        bKeyMask=bKeyMask*2;
        iColCnt++;        
     }      
    
     
     KBD_PORT=0b11110000;
     return 0;
} 
    
byte kbdReadASCII(void){
    byte b,r;
    b=kbdReadRAW();
    r=b;
    
    if(b!=0){
        switch(b){
            case 71: r=48; break; //0
            case 30: r=49; break;
            case 46: r=50; break;
            case 78: r=51; break;
            case 29: r=52; break;
            case 45: r=53; break;
            case 77: r=54; break;
            case 27: r=55; break;
            case 43: r=56; break;
            case 75: r=57; break; //9
            
            case 142: r=13; break; //ENTER
            case 135: r=27; break; //ESC
            //up 39
            //dn 141
            //lt 23
            //rt 139
        }
    }
    return r;
}

