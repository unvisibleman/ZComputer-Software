//Наш метод вывода
byte met;
//Дефайни методов. Текст запомнить легче
#define MET_OR 0
#define MET_XOR 1 
#define MET_NOT_OR 2
#define MET_NOT_XOR 3
//Список команд для ЛСД                         
#define LCD_ON WriteCode(0x3F)
#define LCD_OFF WriteCode(0x3E) 
#define LCD_START_LINE(x) WriteCode(0xC0 | x)
#define LCD_SET_PAGE(x) WriteCode(0xB8 | x)
#define LCD_SET_ADDRESS(x) WriteCode(0x40 | x) 