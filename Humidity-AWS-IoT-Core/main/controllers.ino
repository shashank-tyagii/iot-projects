
void RGBLed(int red_val, int green_val, int blue_val){
int  red1 = map(red_val, 0, 100, 0, 1023);
int  green1 = map(green_val, 0, 100, 0, 1023);
int  blue1 = map(blue_val, 0, 100, 0, 1023);

  analogWrite(red, red1);//change the brightness of red
  analogWrite(green, green1);//change the brightness of red
  analogWrite(blue, blue1);//change the brightness of red
}
