/*
    Arduino Breakout
    Copyright (C) 2015 João André Esteves Vilaça

    https://github.com/vilaca/Handheld-Color-Console

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9341.h> // Hardware-specific library
#include "../TFTv2_extended.h"
#include "breakout.cpp"
#include "../TFTv2_extended.cpp"

void drawWallTiles()
{
  for ( int c = 0; c <  320; c+=40)
  {
    
    tft.fillRect(c+0, 0, 39, 240, RED);

    for ( int i = 20; i < 240; i+= 20)
    {
      tft.drawFastHLine(c+0, i, 40, GRAY2);
      tft.drawFastHLine(c+0, i+1, 40, GRAY2);
    }

    for ( int i = 0; i < 240; i+= 40)
    {
      tft.drawFastVLine(c+20, i, 20, GRAY2 );
      tft.drawFastVLine(c+21, i, 20, GRAY2 );
      tft.drawFastVLine(c+39, i+20, 20, GRAY2 );
      tft.drawFastVLine(c+38, i+20, 20, GRAY2 );
    }
  }
}

void animateScreen()
{
  int addr = 320;
  while(addr >= 0 && !Joystick::pressed(BUTTON_A))
  {
    tft.scrollTo(addr);
    addr-=2;
    
    delay(10);
  }
  tft.scrollTo(0);
}

void breakout_setup() {
  
  Joystick::init();
}

void breakout_loop() {
  
  drawWallTiles();

  const char* bo ="BREAKOUT";
  const int len = strlen (bo) * FONT_SPACE * 6;
  const int left = (MAX_X - len ) / 2;

  drawStringWithShadow(bo, left, 78, 6, WHITE, BLACK);

  boolean go = false;
  do
  {
    animateScreen();

    drawCenteredString("Press A to play!", 136, 2, CYAN);

    unsigned long last = millis();
    do
    {
      go = Joystick::pressed(BUTTON_A);
      
      if ( millis() - last > 8000 ) break;
      
    } while (!go);

  } while (!go);

  Breakout game;
  game.run();
}

void breakout_main()
{
  breakout_setup();
  //while (1)
  {
    breakout_loop();
  }
}
