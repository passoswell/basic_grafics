#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include "basic_graphics.h"
/* #include "your_display.h" */


/* Prototype to a possible function to write the pixels to the display */
void DISP_WritePixels(uint8_t *Buffer, uint16_t Size)
{
  /* Your display code here */
}

/* Clears the display */
void DISP_ClearScreen(uint16_t color)
{
  /* Your display code here */
}

/* Blocking delay */
void Delay(void)
{
  /* Change for your system's delay */
  for(int i = 0; i < 5000000; i++);
}


void main(void)
{
  /* Writing in an area with size 128 x 64, equivalent to SSD1306 */
  static BGFX_Parameters_t BGFX_1;
  uint16_t main_color = BLACK;
  uint16_t background_color = WHITE;
  uint32_t counter = 0;

  BGFX_1.HEIGHT      = 64;
  BGFX_1.WIDTH       = 128;
  BGFX_1.WidthPixelsOnWrite  = 1;
  BGFX_1.HeightPixelsOnWrite = 1; /* Number of pixels in a page */
  BGFX_1.Rotation = 0; /* No software rotation intended */
  BGFX_1.ColorScheme = BGFX_16BITS;
  BGFX_1.Buffer      = NULL;//(void*)buffer;
  BGFX_1.DrawPixel   = ILI9341_DrawPixel;
  BGFX_1.GfxFont     = NULL;

  /* Setting rotation to zero */
  BGFX_SetRotation(0, &BGFX_1);


  /* Cleaning the display */
  DISP_ClearScreen(background_color);

  /* Drawing a few lines to the buffer */
  BGFX_DrawLine(1, 1, 1, 62, main_color, BGFX_1);     /* Top    */
  BGFX_DrawLine(1, 62, 126, 62, main_color, BGFX_1);  /* Right  */
  BGFX_DrawLine(126, 62, 126, 1, main_color, BGFX_1); /* Bottom */
  BGFX_DrawLine(126, 1, 1, 1, main_color, BGFX_1);    /* Left   */

  BGFX_DrawLine(0, 0, 127, 63, main_color, BGFX_1);   /* 1st diagonal */
  BGFX_DrawLine(0, 63, 127, 0, main_color, BGFX_1);   /* 2nd diagonal */

  /* No need to update display */

  Delay();


  /* Cleaning the display, a different background color */
  DISP_ClearScreen(main_color);

  /* Drawing a few lines to the buffer with different color */
  BGFX_DrawLine(1, 1, 1, 62, background_color, BGFX_1);     /* Top    */
  BGFX_DrawLine(1, 62, 126, 62, background_color, BGFX_1);  /* Right  */
  BGFX_DrawLine(126, 62, 126, 1, background_color, BGFX_1); /* Bottom */
  BGFX_DrawLine(126, 1, 1, 1, background_color, BGFX_1);    /* Left   */

  BGFX_DrawLine(0, 0, 127, 63, background_color, BGFX_1);   /* 1st diagonal */
  BGFX_DrawLine(0, 63, 127, 0, background_color, BGFX_1);   /* 2nd diagonal */

  /* No need to update display */

  Delay();


  /* Cleaning the display */
  DISP_ClearScreen(background_color);

  /* Drawing rectangles */
  BGFX_DrawRect(25, 0, 10, 64, main_color, BGFX_1);
  BGFX_DrawRectFill(51, 0, 10, 64, main_color, BGFX_1);

  /* No need to update display */


  Delay();


  /* Cleaning the buffer */
  DISP_ClearScreen(background_color);

  /* Drawing round rectangles */
  BGFX_DrawRoundRect(0, 0, 50, 64, 10, main_color, BGFX_1);
  BGFX_DrawRoundRectFill(128-50, 0, 50, 64, 10, main_color, BGFX_1);

  /* No need to update display */


  Delay();


  /* Cleaning the buffer */
  DISP_ClearScreen(background_color);

  /* Drawing triangles */
  BGFX_DrawTriangle(25, 0, 50, 63, 0, 63, main_color, BGFX_1);
  BGFX_DrawTriangleFill(127-25, 0, 127, 63, 127-50, 63, main_color, BGFX_1);

  /* No need to update display */


  Delay();


  /* Cleaning the buffer */
  DISP_ClearScreen(background_color);

  /* Drawing circles */
  BGFX_DrawCircleFill(60, 32, 30, main_color, BGFX_1);
  BGFX_DrawCircle(30, 32, 10, main_color, BGFX_1);
  BGFX_DrawCircle(90, 32, 10, main_color, BGFX_1);
  BGFX_DrawCircle(10, 10, 10, main_color, BGFX_1);
  BGFX_DrawCircle(60, 10, 10, main_color, BGFX_1);

  /* No need to update display */


  Delay();


  /* Plotting a sine wave */
  /* Cleaning the space where the plot will be positioned */
  BGFX_DrawRectFill(0, 25, 128, 25, main_color, BGFX_1);


  /* Pre-computing sine table */
  uint16_t sine_table[128];
  for(uint32_t i = 0; i < 128; i++)
  {
    float auxf = sinf((float)(i + counter)*0.2);
    auxf *= 12;
    auxf += 37;
    sine_table[i] = auxf;
  }

  uint8_t head = 0;
  uint8_t tail = 127;
  while(1)
  {
    for(uint32_t i = 0; i < 128; i++)
    {
      if(head+i < 128)
      {
        BGFX_DrawPixel(i, sine_table[head+i], background_color, BGFX_1);
      }else
      {
        BGFX_DrawPixel(i, sine_table[(head+i)-128], background_color, BGFX_1);
      }
      if(tail+i < 128)
      {
        BGFX_DrawPixel(i, sine_table[tail+i], main_color, BGFX_1);
      }else
      {
        BGFX_DrawPixel(i, sine_table[(tail+i)-128], main_color, BGFX_1);
      }
    }
    head++;  if(head >= 128){head = 0;}
    tail++;  if(tail >= 128){tail = 0;}
  }
}
