void LCD_PUT_BYTE(byte x, byte y, byte data){
    
    byte tmp_data;
    byte page;
    byte bite;
    byte inv_data;
    //���� ����� �� ��������� ������ �������
    if((x>MAX_X)|(y>MAX_Y)) return;
    //���� � ������ 63 �������� ������ �������
    if(x>=64){
        ClrBit(LCD_CONTROL_PORT, E1);
        SetBit(LCD_CONTROL_PORT, E2);
        x=x-64;
        }
        else{
        ClrBit(LCD_CONTROL_PORT, E2);
        SetBit(LCD_CONTROL_PORT, E1);
        }     
    //���������� �� ����� �������� ����� �������� ����
    page=y/8;
    bite=y%8;
    //�������� ������ ����� ���������(�� ��� ��� ���� �� ������)
    LCD_SET_PAGE(page);
    LCD_SET_ADDRESS(x);
    //��������� ����, 2 �����, �.�. � ������ ��� ������ �����
    tmp_data=ReadData(); 
    tmp_data=ReadData();  
    //������ �������� ������
    LCD_SET_PAGE(page);
    LCD_SET_ADDRESS(x);
    //� ����������� �� ������ ������ ������ ���� � �������                     
    switch(met){
        case MET_OR : {WriteData(tmp_data|(data<<bite)); break;}
        case MET_XOR : {WriteData(tmp_data^(data<<bite)); break;} 
        case MET_NOT_OR : {WriteData(tmp_data| ((data^0xFF)<<bite)); break;}
        case MET_NOT_XOR : {WriteData(tmp_data^((data^0xFF)<<bite)); break;}  
        }
    //���� � ��� �� ������ ������ ������� ���������� ����� ������ �����
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
    //� ������� ���� ������� ���� ��������� �����, ������� ����������� 
    //����� ������� ��� �����������
    if(ch<0x90) textL=0x20;
    else textL=0x60;

    for(i=0; i<5; i++){
        LCD_PUT_BYTE(x+i, y, sym[ch-textL][i]);
        } 
    //��� ���������� ��������
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