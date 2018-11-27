#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>             // Library for SPI mode
#include <Adafruit_ILI9341.h> // Controller chip library
#include "TouchScreen.h"    //Library for TouchScreen

// Draws outcome (0 is lose, 1 is win, 2 is tie)
void draw_outcome(Adafruit_ILI9341 display, int win_status){
  // Need to do this to rotate text
  display.setRotation(1);

  // Set text size and color
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(10);

  // Have to make cursor x different for each one because of the size of the characters
  if ( win_status == 0 ){
    display.setCursor(45, 85);
    display.fillScreen(ILI9341_RED);
    display.print("Lose");
  }
  else if ( win_status == 1){
    display.setCursor(50, 85);
    display.fillScreen(ILI9341_GREEN);
    display.print("Win!");
  }
  else if (win_status == 2){
    display.setCursor(50, 85);
    display.fillScreen(ILI9341_YELLOW);
    display.print("Tie!");
  }
}

// Draw menu for # of players selection
void draw_menu(Adafruit_ILI9341 display){
  int char_size = 10;
  // Need to do this to rotate text
  display.setRotation(1);

  display.fillRect((display.width() / 2), 0, (display.width() / 2), display.height(), ILI9341_BLUE);
  display.fillRect(0, 0, (display.width() / 2), display.height(), ILI9341_PINK);

  // Characters are (5,7) * char_size
  // Using this expression, we can center characters
  display.drawChar(((display.width() / 4) - (char_size * (5 / 2))), ((display.height() / 2) - (char_size * (7 / 2))), '1', ILI9341_WHITE, ILI9341_PINK, char_size);
  display.drawChar((((3 * display.width()) / 4) - (char_size * (5 / 2))), ((display.height() / 2)- (char_size * (7 / 2))), '2', ILI9341_WHITE, ILI9341_BLUE, char_size);
}

// Draws a waiting screen when waiting for a response from the other arduino
void draw_waiting(Adafruit_ILI9341 display){
  // Need to do this to rotate text
  display.setRotation(1);

  // Fill screen with black
  display.fillScreen(ILI9341_BLACK);

  // Set text size and color
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(5);

  display.setCursor(40, 103);
  display.print("Waiting.");

}

// Draws an empty grid
void draw_empty_grid(Adafruit_ILI9341 display, int BOXSIZE){
  // Need to do this to rotate to standard game rotations as specified in readme (after main menu).
  display.setRotation(0);

  display.fillScreen(ILI9341_BLACK);

  // Draws a 6 x 7 grid of 40x40 pixel boxes
  // Starts at index 0 because 40*0=0
  for (int i = 1; i < 8; i++){
    for (int j = 1; j < 7; j++){
      display.drawRect((display.width() - BOXSIZE * j), (display.height() - BOXSIZE * i), BOXSIZE, BOXSIZE, ILI9341_WHITE);
    }
  }
}

// Draws a grey confirm button
void draw_grey_confirm(Adafruit_ILI9341 display, int BOXSIZE){
  display.fillRect(120, 0, 120, BOXSIZE, 0x8410);
}

// Draws a green confirm button
void draw_green_confirm(Adafruit_ILI9341 display, int BOXSIZE){
  display.fillRect(120, 0, 120, BOXSIZE, ILI9341_GREEN);
}

// Draws a red cancel button
void draw_cancel(Adafruit_ILI9341 display, int BOXSIZE){
  display.fillRect(0, 0, 120, BOXSIZE, ILI9341_RED);
}

// Draws an empty battleship map
void draw_empty_map(Adafruit_ILI9341 display, int BOXSIZE){
  draw_empty_grid(display, BOXSIZE);
  draw_grey_confirm(display, BOXSIZE);
  draw_cancel(display, BOXSIZE);
}

// Fill in grid box at a given location
void draw_at_grid_pos(Adafruit_ILI9341 display, int BOXSIZE, String grid_pos, int color){
  char let[7] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  char num[6] = {'0', '1', '2', '3', '4', '5'};
  // Indice shifted because of the menu on the left side of the screen.
  for (int i = 7; i > 0; i--){
    for (int j = 5; j > -1; j--){
      if (let[i - 1] == grid_pos[0] and num[j] == grid_pos[1]){
        // Fill the rectangle
        display.fillRect((BOXSIZE * j), (BOXSIZE * i), BOXSIZE, BOXSIZE, color);
        // Redraw the white border
        display.drawRect((BOXSIZE * j), (BOXSIZE * i), BOXSIZE, BOXSIZE, ILI9341_WHITE);
      }
    }
  }
}

// Clears selected tile(s)
void clear_all_selections(Adafruit_ILI9341 display, int BOXSIZE, String block_array[], int length){
  for(int i = 0; i < length; i++){
    draw_at_grid_pos(display, BOXSIZE, block_array[i], ILI9341_BLACK);   // Draw black at every previously selected square
  }
  draw_grey_confirm(display, BOXSIZE);  // Draws a grey confirm button
}
