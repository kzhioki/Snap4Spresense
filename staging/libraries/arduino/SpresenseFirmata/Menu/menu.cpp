#include "MenuSystem.h"
#include "../Games/joystick.h"

#include "MenuSystem.cpp"

#ifdef USE_TETRIS
#include "../Games/Tetris/ArduinoTetris.cpp"
#endif
#ifdef USE_BREAKOUT
#include "../Games/Breakout/ArduinoBreakout.cpp"
#endif

#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

MenuSystem menu = MenuSystem();

typedef void (* MenuFuncPtr) (); // Function pointer for Main Menu

char* mainMenu[] =
{
  "    Main Menu",
  "Game          ",
  "Settings      ",
};

char* gameMenu[] =
{
  "   Game Menu",
  "Tetris        ",
  "Breakout      ",
  "Back          ",
};

char* settingtMenu[] =
{
  "   Settings",
  "Volume        ",
  "Back          ",
};

// Predefine functions
void buildGameMenu(void);
void buildSettingMenu(void);
void returnMainMenu(void);
void tetris_start();
void breakout_start();
void volume_setting();

// Main menu func pointer
MenuFuncPtr menu_func[] =
{
  0,
  buildGameMenu,
  buildSettingMenu,
};

// Menu Func Pointer
MenuFuncPtr game_func[] =
{
  0,
  tetris_start,
  breakout_start,
  returnMainMenu,
};

MenuFuncPtr setting_func[] =
{
  0,
  returnMainMenu,
  returnMainMenu,
};

void returnMainMenu(void) {
  menu.setMenu(mainMenu, COUNTOF(mainMenu));
  menu.setFunc(menu_func, COUNTOF(menu_func));
  menu.displayMenu();
}

void buildGameMenu(void) {
  menu.setMenu(gameMenu, COUNTOF(gameMenu));
  menu.setFunc(game_func, COUNTOF(game_func));
  menu.displayMenu();
}

void buildSettingMenu(void) {
  menu.setMenu(settingtMenu, COUNTOF(settingtMenu));
  menu.setFunc(setting_func, COUNTOF(setting_func));
  menu.displayMenu();
}

void tetris_start()
{
  struct msg_s smsg;

  smsg.cmd = PLAY;
  smsg.arg = 99;
  mq_send(mqd1, (const char*)&smsg, sizeof(msg_s), 0);

  //printf("Let's Tetris\n");
  tetris_main();

  smsg.cmd = STOP;
  smsg.arg = 0;
  mq_send(mqd1, (const char*)&smsg, sizeof(msg_s), 0);

  returnMainMenu();
}

void breakout_start()
{
  struct msg_s smsg;

  smsg.cmd = PLAY;
  smsg.arg = 41;
  mq_send(mqd1, (const char*)&smsg, sizeof(msg_s), 0);

  //printf("Let's Breakout\n");
  breakout_main();

  smsg.cmd = STOP;
  smsg.arg = 0;
  mq_send(mqd1, (const char*)&smsg, sizeof(msg_s), 0);

  returnMainMenu();
}

void menu_setup() {
  struct msg_s smsg;

  smsg.cmd = VOL;
  smsg.arg = -100;
  mq_send(mqd1, (const char*)&smsg, sizeof(msg_s), 0);

  smsg.cmd = REPEAT;
  smsg.arg = 1;
  mq_send(mqd1, (const char*)&smsg, sizeof(msg_s), 0);

  Joystick::init();
  Joystick::waitForRelease(BUTTON_SELECT);

  menu.start();
  returnMainMenu();
}

void menuInput(void) {

  if (Joystick::getY() > 0) {
    while (Joystick::getY() != 0);
    menu.action(DOWN);
  }

  if (Joystick::getY() < 0) {
    while (Joystick::getY() != 0);
    menu.action(UP);
  }

  if (Joystick::getX() > 0) {
    while (Joystick::getX() != 0);
    menu.action(SELECT);
  }

  if (Joystick::getX() < 0) {
    while (Joystick::getX() != 0);
    returnMainMenu();
  }

  if (Joystick::pressed(BUTTON_SELECT)) {
    Joystick::waitForRelease(BUTTON_SELECT);
    menu.action(DOWN);
  }
  if (Joystick::pressed(BUTTON_START)) {
    Joystick::waitForRelease(BUTTON_START);
    menu.action(SELECT);
  }
}

void menu_loop() {
  menuInput();
  usleep(1000 * 10);
}

void menu_main() {
  menu_setup();
  while (1) {
    menu_loop();
  }
}
