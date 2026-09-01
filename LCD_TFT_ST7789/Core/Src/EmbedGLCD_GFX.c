/*
 * EmbedGLCD_GFX.c
 *
 *  Created on: Oct 28, 2024
 *      Author: KhueND8
 */


#include "EmbedGLCD_GFX.h"



void GFX_DrawPixel(LCD_Driver *driver, void *config, uint16_t x, uint16_t y, uint16_t color) {
    driver->SetAddressWindow(config, x, y, x, y);
    driver->WriteRAMPrepare(config);
    driver->WriteData16(config, color);
}

void GFX_DrawLine(LCD_Driver *driver, void *config, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int16_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int16_t err = dx + dy, e2;

    while (1) {
        GFX_DrawPixel(driver, config, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void LCD_Clear(LCD_Driver *driver, uint16_t color) {
    // Thiết lập cửa sổ địa chỉ cho toàn bộ màn hình
    driver->SetAddressWindow(driver, 0, 0, 240 - 1, 320 - 1);

    // Chuẩn bị ghi vào RAM
    driver->WriteRAMPrepare(driver);

    // Tính toán số lượng pixel
    uint32_t totalPixels = 240 * 320;

    // Tạo một mảng chứa dữ liệu màu để gửi
    uint16_t *colorBuffer = malloc(totalPixels * sizeof(uint16_t));
    if (colorBuffer == NULL) {
        // Xử lý lỗi phân bổ bộ nhớ nếu cần
        return;
    }

    // Điền mảng với màu đã chỉ định
    for (uint32_t i = 0; i < totalPixels; i++) {
        colorBuffer[i] = color;
    }

    // Ghi dữ liệu màu vào màn hình
    driver->WriteData(driver, (uint8_t *)colorBuffer, totalPixels * sizeof(uint16_t));

    // Giải phóng bộ nhớ
    free(colorBuffer);
}



