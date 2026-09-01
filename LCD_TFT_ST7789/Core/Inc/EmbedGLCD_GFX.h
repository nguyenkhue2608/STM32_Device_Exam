/*
 * EmbedGLCD_GFX.h
 *
 *  Created on: Oct 28, 2024
 *      Author: KhueND8
 */

#ifndef INC_EMBEDGLCD_GFX_H_
#define INC_EMBEDGLCD_GFX_H_
#include <stdint.h>
#include <stdlib.h>
typedef struct {
    void (*Reset)(void *config);
    void (*WriteCommand)(void *config, uint8_t cmd);
    void (*WriteData)(void *config, uint8_t *buff, size_t buff_size);
    void (*WriteData8)(void *config, uint8_t data);
    void (*WriteData16)(void *config, uint16_t data);
    void (*SetAddressWindow)(void *config, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    void (*SetCursor)(void *config, uint16_t Xpos, uint16_t Ypos);
    void (*WriteRAMPrepare)(void *config);
} LCD_Driver;
void ST7789_InitDriver(LCD_Driver *driver);
void GFX_DrawPixel(LCD_Driver *driver, void *config, uint16_t x, uint16_t y, uint16_t color);
void GFX_DrawLine(LCD_Driver *driver, void *config, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_Clear(LCD_Driver *driver, uint16_t color);


#endif /* INC_EMBEDGLCD_GFX_H_ */
