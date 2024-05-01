/*
 * LCD_INTERFACE.h
 *
 * Created: 3/12/2024 5:46:28 AM
 *  Author: Karim
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void	LCD_voidInit			    (void);
void	LCD_voidSendCommand		    (u8 copy_u8cmd);
void	LCD_voidDisplayChar		    (u8 copy_u8Data);
void	LCD_voidDisplayString       (u8* copy_pu8String);
void	LCD_voidDisplayStringDelay  (u8* copy_pu8StringDelay);
void	LCD_voidDisplayNumber	    (u32 copy_u32Number);	// Int to String
void	LCD_voidClear			    (void);
void	LCD_voidShiftCursor			(u8 copy_u8ShifttingDirection);
void	LCD_voidShiftDisplay			    (u8 copy_u8ShifttingDirection);
void	LCD_voidMoveCursor		    (u8 copy_u8LineNumber, u8 copy_u8Postion);

void LCD_voidGoTOSpecificPosition(u8 copy_u8LineNumber,u8 copy_u8Position);
void LCD_voidPwdEffect();

#endif /* LCD_INTERFACE_H_ */