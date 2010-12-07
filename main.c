/*
LCD           ATmega16    частота 1 МГЦ
DI  соединить с PA0 
RW  соединить с PA1
E   соединить с PA2
CS1 соединить с PA3 
CS2 соединить с PA4
RST соединить с PA5
*/

#include <mega32.h>  
#include <stdio.h>
#include <delay.h>
#include <math.h> 


#define UDRE 5 
#define RXC 7   

//========================================================================================================
#include <macros.h>
#include <sym.h>
#include <config.h> 
#include <driver.h>
#include <driver.c>  
#include <gl.c>  
#include <text.c>
#include <kbd.c>
#include <gui.c>
//========================================================================================================
  


                    

void main(void){
    
    LCD_INIT();
    met=MET_XOR;
        
    kbdInit();
    //met=MET_NOT_XOR; 
    //met=MET_XOR;   
      

    while (1){ 
        int i=0,j=0,a=0,b=0,c=0;
        byte ch;
        
        
        guiCls();
        guiTitle("HELLO",);
                
        j=guiMenu();
        
        guiCls();
        guiTitle("HELLO",);
        
        switch(j){
            case 1:
                guiShowChars();
                delay_ms(3000);
                break;
                
            case 2:
                guiScan();
                break;
                
            case 3:
                a=guiInputVar("введите A");
                guiText("                     ",0,2);
                b=guiInputVar("введите B");
                guiText("                     ",0,2);
                c=guiInputVar("введите C");
                guiText("                     ",0,2);
                guiCls();
                guiText("A=",1,1);guiVar3(a,4,1);                
                guiText("B=",1,2);guiVar3(b,4,2);                
                guiText("C=",1,3);guiVar3(c,4,3);
                
                delay_ms(3000);
                break;
                
            case 4:
                guiText("Y=SIN(X)",0,2);
                guiSine();
                delay_ms(3000);
                break;            
        }     
        
    };          
}




