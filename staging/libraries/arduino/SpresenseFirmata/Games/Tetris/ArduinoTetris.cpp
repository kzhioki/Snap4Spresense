/*
    Arduino Tetris
    Copyright (C) 2015 Joao Andre Esteves Vilaca

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
#include "../joystick.h"
#include "../TFTv2_extended.h"
#include "Tetris.cpp"

void drawPreGameScreen()
{
  tft.fillScreen(BLACK);
  drawCenteredString("Tetris", 40, 4, BLUE);
  drawCenteredString("Click A to play", 110, 2, WHITE);
}

void gameOver()
{
  tft.fillRect(32, 84, 256, 52, BLACK);
  drawString("Game Over", 48, 94, 4, WHITE);

  tft.drawRect(32, 84, 256, 52, RED);

  Joystick::shock(200);
  Beeping::beep(600, 200);
  usleep(300*1000);
  Beeping::beep(600, 200);
  usleep(300*1000);
  Beeping::beep(200, 600);
  usleep(1500*1000);
  Joystick::waitForClick(BUTTON_A);
}

void tetris_setup() {

  Beeping::turnOn();
  Joystick::init();
}

void tetris_loop() {

  // title screen
  drawPreGameScreen();

  // wait a bit before playing sounds
  delay(700);

  // wait for click
  while (!Joystick::pressed(BUTTON_A));

  // load game
  Tetris t;
  t.run();

  // game ended
  gameOver();

}

void tetris_main()
{
  tetris_setup();
  //while (1)
  {
    tetris_loop();
  }
}
