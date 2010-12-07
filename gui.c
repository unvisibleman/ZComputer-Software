//A simple Graphical interface
//for MT12864 128x64

#define GUI_CHR_W 21
#define GUI_CHR_H 6 
#define GUI_CHR_XO 7
#define GUI_CHR_YO 12

void guiText(flash unsigned char str[],byte x,byte y);
void guiTitle(flash unsigned char str[]);
int guiInputVar(flash unsigned char msg[]);
byte guiGetSize(flash unsigned char str[]);
void guiVar(byte i,byte x,byte y);
void guiShowChars(void);
void guiSine(void);
byte guiMenu(void);
void guiCls(void);
void guiScan(void);

void guiTitle(flash unsigned char str[]){    
    byte x=0;
    x=((GUI_CHR_W-guiGetSize(str))/2-1);
    guiText(str,x,0);    
} 

byte guiGetSize(flash unsigned char str[]){
    byte i=0;                   
    while(str[i]){
        i++; 
    }
    return i;  
}

void guiText(flash unsigned char str[],byte x,byte y){
    x=x * GUI_CHR_XO;
    y=y * GUI_CHR_YO;
    LCD_PUTSF(x,y,str);
}

void guiVar(byte i,byte x,byte y){
    x=x * GUI_CHR_XO;
    y=y * GUI_CHR_YO;
    LCD_PUTC(x,y,i);
}

void guiVar3(byte ch,byte x, byte y){
    byte a=0,b=0,c=0;
    a=ch/100;
    ch=ch%100;
    b=ch/10;
    ch=ch%10;
    c=ch;
    guiVar(a+48,x,y);
    guiVar(b+48,x+1,y);
    guiVar(c+48,x+2,y);    
}

int guiInputVar(flash unsigned char msg[]){
    byte i=0,x=0,ch=0;
    int as[3],ret=0;
    as[0]=0;as[1]=0;as[2]=0;
    x=guiGetSize(msg);
    guiText(msg,0,1);
    guiText("[",x-1,1);
    guiText("]",x+3,1);
    ch=kbdReadASCII();
    i=0;
    while(ch!=13 && ch!=27){
        if(ch!=0){
          if(i<3){
            as[i]=ch-48;
            guiVar(ch,i+x,1);
            i++;  
          }
        }
        ch=kbdReadASCII();    
    }
    
    if(ch==27){
        return 0;
    }else{
        if(as[2]!=0){
            ret= as[0]*100+as[1]*10+as[2];            
        }else{
            if(as[1]!=0){
                ret= as[0]*10+as[1];
            }else{
                if(as[0]!=0){
                    ret= as[0];
                }
            }
        }
    
        return ret;
    }
    
    
}

void guiShowChars(void){
    
    guiText("123456789012345678901",0,0);
    guiText("ABCDEFGHIJKLMNOPQRSTU",0,1); 
    guiText("VWXYZ +-*/()<>,.;:?!@",0,2);
    guiText("јЅ¬√ƒ≈∆«» ЋћЌќѕ–—“”‘’",0,3);
    guiText("÷„ЎўЏџьЁёя           ",0,4);
    
}

void guiSine(void){
    int x,y,z=0;
    for(x=1;x<128;x++){
        y=sin(x*100)*5+40;
        LCD_PUT_PIXEL(x,y);
    }
    
}

byte guiMenu(void){
    byte i=1,j=0;
    byte ch=0;        
    
    guiText("скан. клавиатуры",2,2);
    guiText("ввод данных",2,3);
    guiText("график функции",2,4);
    guiText("таблица символов",2,1);
                            
    guiText(">",0,i);
    ch=kbdReadASCII();
     while(ch!=13 && ch!=27){
        
        if(ch!=0){
          if(ch==39){
            i--;            
          }
          if(ch==141){
            i++;
          }
          if(i<1){
            i=4;
          }
          if(i>4){
            i=1;
          }
          
                         
          for(j=1;j<5;j++){
            guiText(" ",0,j); 
          } 
          guiText(">",0,i); 
        }
        ch=kbdReadASCII();    
    }
    
    if(ch==27){
        return 0;
    }else{
        return i;
    }
    
}

void guiScan(void){
    byte i=1,j=0;
    byte ch=0;        
    
    guiText("код клавиши",1,1);    
    guiText("[ESC] выход",1,4);
    guiText("ASCII:",1,2);  
                            
    
    ch=kbdReadASCII();
     while(ch!=27){
        
        if(ch!=0){           
            guiVar3(ch,7,2); 
        }
        ch=kbdReadASCII();    
    }
  
  
}

void guiCls(void){
    guiText("                     ",0,0);
    guiText("                     ",0,1); 
    guiText("                     ",0,2);
    guiText("                     ",0,3);
    guiText("                     ",0,4);
    
    /*byte x=0,y=0;
    for(x=0;x<21;x++){
        for(y=0;y<6;y++){
            guiText(" ",x,y); 
        }
    } */
}