/*
 * LCD_interface.h
 *
 * Created: 2/9/2024 9:35:53 PM
 *  Author: Saed Abozied
 */ 




#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define LCD_SHIFT_DIS_RIGHT		1
#define LCD_SHIFT_DIS_LEFT		2

#define LCD_LINE_ONE			1
#define LCD_LINE_TWO			2


void LCD_voidInit(void);
void LCD_voidSendCommand(u8 copy_u8Command);
void LCD_voidDisplayChar(u8 copy_u8Data);

void LCD_voidDisplayString(u8* copy_pu8String);//loop
void LCD_voidDisplayNumber(u8 copy_u8Number);//int to string
void LCD_voidClear(void);//cmnd datasheet
void LCD_voidShift(u8 copy_u8ShifttingDirection);//cmnd datasheet
void LCD_voidGoTOSpecificPosition(u8 copy_u8LineNumber,u8 copy_u8Position);//cmnd datasheet

#endif /* LCD_INTERFACE_H_ */