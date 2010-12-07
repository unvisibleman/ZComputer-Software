/*
LCD           ATmega16    ������� 1 ���
DI  ��������� � PA0 
RW  ��������� � PA1
E   ��������� � PA2
CS1 ��������� � PA3 
CS2 ��������� � PA4
RST ��������� � PA5
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
                a=guiInputVar("������� A");
                guiText("                     ",0,2);
                b=guiInputVar("������� B");
                guiText("                     ",0,2);
                c=guiInputVar("������� C");
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




