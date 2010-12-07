void LCD_PUT_BYTE(byte x, byte y, byte data){
    
    byte tmp_data;
    byte page;
    byte bite;
    byte inv_data;
    //Если точка за приделами экрана выходим
    if((x>MAX_X)|(y>MAX_Y)) return;
    //Если х больше 63 выбираем второй кристал
    if(x>=64){
        ClrBit(LCD_CONTROL_PORT, E1);
        SetBit(LCD_CONTROL_PORT, E2);
        x=x-64;
        }
        else{
        ClrBit(LCD_CONTROL_PORT, E2);
        SetBit(LCD_CONTROL_PORT, E1);
        }     
    //Определяем на какой странице будем выводить байт
    page=y/8;
    bite=y%8;
    //Выбираем откуда будем считывать(то что уже есть на экране)
    LCD_SET_PAGE(page);
    LCD_SET_ADDRESS(x);
    //Считываем байт, 2 цикла, т.к. в первый раз выдаст мусор
    tmp_data=ReadData(); 
    tmp_data=ReadData();  
    //Заново выбираем адресс
    LCD_SET_PAGE(page);
    LCD_SET_ADDRESS(x);
    //В зависимосте от метода вывода меняем байт и выводим                     
    switch(met){
        case MET_OR : {WriteData(tmp_data|(data<<bite)); break;}
        case MET_XOR : {WriteData(tmp_data^(data<<bite)); break;} 
        case MET_NOT_OR : {WriteData(tmp_data| ((data^0xFF)<<bite)); break;}
        case MET_NOT_XOR : {WriteData(tmp_data^((data^0xFF)<<bite)); break;}  
        }
    //Если у был не кратен восьми выводим оставшиюся часть нашего байта
    if(bite>0){ 
        LCD_SET_PAGE(page+1);
        LCD_SET_ADDRESS(x);
       
        tmp_data=ReadData(); 
        tmp_data=ReadData();
        
        LCD_SET_PAGE(page+1);
        LCD_SET_ADDRESS(x);
    
        switch(met){
            case MET_OR : {WriteData(tmp_data|(data>>(8-bite))); break;}
            case MET_XOR : {WriteData(tmp_data^(data>>(8-bite))); break;} 
            case MET_NOT_OR : {WriteData(tmp_data|((data^0xFF)>>(8-bite))); break;}
            case MET_NOT_XOR : {WriteData(tmp_data^((data^0xFF)>>(8-bite))); break;} 
        }
    } 
}

void LCD_PUTC(byte x, byte y, byte ch){
    byte textL;
    byte i;   
    //В таблице аски символы идут несколько иначе, поэтому преобразуем 
    //номер символа под нашутаблицу
    if(ch<0x90) textL=0x20;
    else textL=0x60;

    for(i=0; i<5; i++){
        LCD_PUT_BYTE(x+i, y, sym[ch-textL][i]);
        } 
    //Для раздиления символов
    LCD_PUT_BYTE(x+i, y, 0x00);      
}   
         
void LCD_PUTSF(byte x, byte y, flash unsigned char str[]){
    byte i=0;
    
    while(str[i]){
        LCD_PUTC(x+i*5+i, y, str[i]);
        i++; 
    }  
}



void LCD_PUTI(byte x, byte y, byte ch){

    LCD_PUTC(x,y,ch+48);
 
}