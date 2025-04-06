#include "WS_Matrix.h"
// English: Please note that the brightness of the lamp bead should not be too high, which can easily cause the temperature of the board to rise rapidly, thus damaging the board !!!
uint8_t RGB_Data[3] = {30,30,30}; 
uint8_t Matrix_Data[8][8];  
Adafruit_NeoPixel pixels(RGB_COUNT, RGB_Control_PIN, NEO_RGB + NEO_KHZ800); 
int randomValue = random(1, 250);
int i(randomValue); // Declare globally if needed

// I updated this section to make the color change based on the location of the lit pixel on the matrix, white was cool but boring. (Jon Ericson 3-13-25)
void RGB_Matrix() {
  for (int row = 0; row < 8; row++) { // Loop through 8 rows
    for (int col = 0; col < 8; col++) { // Loop through 8 columns
      if (Matrix_Data[row][col] == 1) {
        // Adjust color transitions
        int red = map(row, 0, 7, 255, 0); // Red fades from top-left to bottom
        int green = map(col, 0, 7, 0, 255); // Green strictly transitions from left to right
        int blue = map(row, 0, 7, 0, 255); // Blue strictly transitions from top to bottom

        // Isolate green where red isn't needed
        if (col > 4) red = 60; // Reduce red in areas where green is dominant
        if (col > 5) red = 40; // Reduce red in areas where green is dominant
        if (col > 6) red = 20; // Reduce red in areas where green is dominant

        // Ensure the bottom-right corner is white
        if (row == 7 && col == 7) {
          red = 255;
          green = 255;
          blue = 255;
        }

        // Constrain RGB values to valid ranges
        red = constrain(red, 0, 255);
        green = constrain(green, 0, 255);
        blue = constrain(blue, 0, 255);

        // Set the pixel color
        pixels.setPixelColor(row * 8 + col, pixels.Color(red, green, blue));
      } else {
        // Turn off pixels where Matrix_Data is not 1
        pixels.setPixelColor(row * 8 + col, pixels.Color(0, 0, 0));
      }
    }
  }
  pixels.show();
}


uint8_t x=4,y=4;
void Game(uint8_t X_EN,uint8_t Y_EN) 
{
  Matrix_Data[x][y] = 0;
  if(X_EN && Y_EN){
    if(X_EN == 1)
      x=x+1;
    else
      x=x-1;
    if(Y_EN == 1)
      y=y+1;
    else
      y=y-1;
  }
  else if(X_EN){
    if(X_EN == 1)
      x=x+1;
    else
      x=x-1;
  }
  else if(Y_EN){
    if(Y_EN == 1)
      y=y+1;
    else
      y=y-1;
  }
  if(x < 0) x = 0;
  if(x == 8) x = 7;
  if(x > 8) x = 0;
  if(y < 0) y = 0;
  if(y == 8) y = 7;
  if(y > 8) y = 0;
  printf("%d\r\n",y);
  Matrix_Data[x][y]=1;
  RGB_Matrix();
}
void Matrix_Init() {
  pixels.begin();
  // English: Please note that the brightness of the lamp bead should not be too high, which can easily cause the temperature of the board to rise rapidly, thus damaging the board !!!
  pixels.setBrightness(30);                       // set brightness  
  memset(Matrix_Data, 0, sizeof(Matrix_Data)); 
}