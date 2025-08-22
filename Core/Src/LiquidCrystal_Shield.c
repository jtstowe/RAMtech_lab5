/*
 * LiquidCrystal.c - LiquidCrystal Library for STM32 ARM microcontrollers
 *
 *  Created on: April 12, 2018
 *      Author: S. Saeed Hosseini (sayidhosseini@hotmail.com)
 *      Ported from: Arduino, Adafruit (https://github.com/arduino-libraries/LiquidCrystal)
 *      Published to: Github (https://github.com/SayidHosseini/STM32LiquidCrystal)
 */

#include <LiquidCrystal_Shield.h>
#include "stm32l1xx_hal.h" // change this line accordingly
#include <stdio.h>
#include <stdint.h>
#include <string.h>


// change this to LCD_5x10DOTS for some 1 line displays that can select a 10 pixel high font
uint8_t dotsize = LCD_5x8DOTS;

// pin definitions and other LCD variables
GpioPin lcd_rs;
GpioPin lcd_e;
GpioPin lcd_data[4];

uint8_t _displayfunction;
uint8_t _displaycontrol;
uint8_t _displaymode;

uint8_t _initialized;

uint8_t _numlines;
uint8_t _row_offsets[4];



void LiquidCrystal_Init(GPIO_TypeDef *rs_port, uint16_t rs, GPIO_TypeDef *e_port, uint16_t e,
		GPIO_TypeDef *d4_port, uint16_t d4, GPIO_TypeDef *d5_port, uint16_t d5,
		GPIO_TypeDef *d6_port, uint16_t d6, GPIO_TypeDef *d7_port, uint16_t d7)
{
	lcd_rs.port = rs_port;
	lcd_rs.pin  = rs;

	lcd_e.port = e_port;
	lcd_e.pin  = e;

	lcd_data[0].port = d4_port;
	lcd_data[0].pin  = d4;

	lcd_data[1].port = d5_port;
	lcd_data[1].pin  = d5;

	lcd_data[2].port = d6_port;
	lcd_data[2].pin  = d6;

	lcd_data[3].port = d7_port;
	lcd_data[3].pin  = d7;

	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  
	begin(16, 2);
}


void begin(uint8_t cols, uint8_t lines) {
  if (lines > 1) {
    _displayfunction |= LCD_2LINE;
  }
  _numlines = lines;

  setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);  

  // for some 1 line displays you can select a 10 pixel high font
  if ((dotsize != LCD_5x8DOTS) && (lines == 1)) {
    _displayfunction |= LCD_5x10DOTS;
  }

  //Initializing GPIO Pins
  gpio_pin_init_output(&lcd_rs);
  gpio_pin_init_output(&lcd_e);
  gpio_pin_init_output(&lcd_data[0]);
  gpio_pin_init_output(&lcd_data[1]);
  gpio_pin_init_output(&lcd_data[2]);
  gpio_pin_init_output(&lcd_data[3]);

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // so we'll wait 50 just to make sure
  HAL_Delay(250);

  // Now we pull both RS and R/W low to begin commands
  gpio_write(&lcd_rs, GPIO_PIN_RESET);
  gpio_write(&lcd_e, GPIO_PIN_RESET);

  // this is according to the hitachi HD44780 datasheet
  // page 45 figure 23

  // Send function set command sequence
  command(LCD_FUNCTIONSET | _displayfunction);
  HAL_Delay(10);  // wait more than 4.1ms

  // second try
  command(LCD_FUNCTIONSET | _displayfunction);
  HAL_Delay(5);

  // third go
  command(LCD_FUNCTIONSET | _displayfunction);

  // finally, set # lines, font size, etc.
  command(LCD_FUNCTIONSET | _displayfunction);  

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
  display();

  // clear it off
  clear();

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  command(LCD_ENTRYMODESET | _displaymode);

}


void setRowOffsets(int row0, int row1, int row2, int row3)
{
  _row_offsets[0] = row0;
  _row_offsets[1] = row1;
  _row_offsets[2] = row2;
  _row_offsets[3] = row3;
}

/********** high level commands, for the user! */
void clear(void)
{
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  HAL_Delay(2);  // this command takes a long time!
}

void home(void)
{
  command(LCD_RETURNHOME);  // set cursor position to zero
  HAL_Delay(2);  // this command takes a long time!
}

void setCursor(uint8_t col, uint8_t row)
{
  const size_t max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
  if ( row >= max_lines ) {
    row = max_lines - 1;    // we count rows starting w/0
  }
  if ( row >= _numlines ) {
    row = _numlines - 1;    // we count rows starting w/0
  }
  
  command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

// Turn the display on/off (quickly)
void noDisplay(void) {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void display(void) {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void noCursor(void) {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void cursor(void) {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void noBlink(void) {
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void blink(void) {
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void scrollDisplayLeft(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void scrollDisplayRight(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void autoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void noAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will print character string to the LCD
size_t print(const char str[]) {
  if (str == NULL) return 0;

  const uint8_t *buffer = (const uint8_t *)str;
  size_t size = strlen(str);
  size_t n = 0;

  while (size--) {
    if (write(*buffer++)) n++;
    else break;
  }
  return n;
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void createChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++) {
    write(charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */

inline void command(uint8_t value) {
  send(value, GPIO_PIN_RESET);
}

inline size_t write(uint8_t value) {
  send(value, GPIO_PIN_SET);
  return 1; // assume sucess
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
void send(uint8_t value, GPIO_PinState mode) {
	gpio_write(&lcd_rs, mode);
  
    write4bits(value>>4);
    write4bits(value);

}

void pulseEnable(void) {
	gpio_write(&lcd_e, GPIO_PIN_RESET);
	HAL_Delay(5);
	gpio_write(&lcd_e, GPIO_PIN_SET);
  	HAL_Delay(5);    // enable pulse must be >450ns
  	gpio_write(&lcd_e, GPIO_PIN_RESET);
  	HAL_Delay(5);   // commands need > 37us to settle
}

void write4bits(uint8_t value) {
  for (int i = 0; i < 4; i++) {
	  gpio_write(&lcd_data[i], ((value >> i) & 0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
  }

  pulseEnable();
}


void gpio_write(GpioPin *pin, GPIO_PinState state) {
    HAL_GPIO_WritePin(pin->port, pin->pin, state);
}

void gpio_pin_init_output(GpioPin *p) {
	enableClock(p->port);
	GPIO_InitTypeDef gpio_init = {0};
    gpio_init.Pin = p->pin;
    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(p->port, &gpio_init);
}

// enables GPIO RCC Clock
void enableClock(GPIO_TypeDef *port) {
  if(port == GPIOA)
		__HAL_RCC_GPIOA_CLK_ENABLE();
  else if(port == GPIOB)
		__HAL_RCC_GPIOB_CLK_ENABLE();
  else if(port == GPIOB)
		__HAL_RCC_GPIOB_CLK_ENABLE();
	else if(port == GPIOC)
		__HAL_RCC_GPIOC_CLK_ENABLE();
	else if(port == GPIOD)
		__HAL_RCC_GPIOD_CLK_ENABLE();
	else if(port == GPIOE)
		__HAL_RCC_GPIOE_CLK_ENABLE();
	else if(port == GPIOF)
		__HAL_RCC_GPIOF_CLK_ENABLE();
}
