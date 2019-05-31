/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/
#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

bool haskeyPressed[5][12];
int rowPin[5] = { 4, 3, 2, 5, 20};
int columnPin[12] = { 16, 12, 13, 14, 8, 6, 15, 7, 11, 27, 26, 25};
/*char Activation[2][5][12] = {
  
{{ HID_KEY_ESCAPE,HID_KEY_1,HID_KEY_2,HID_KEY_3,HID_KEY_4,HID_KEY_5,HID_KEY_6,HID_KEY_7,HID_KEY_8,HID_KEY_9,HID_KEY_0, HID_KEY_BACKSPACE } ,
{ HID_KEY_TAB,HID_KEY_Q,HID_KEY_W,HID_KEY_E,HID_KEY_R,HID_KEY_T,HID_KEY_Y,HID_KEY_U,HID_KEY_I,HID_KEY_O,HID_KEY_P,HID_KEY_MINUS } ,
{ HID_KEY_CAPS_LOCK, HID_KEY_A,HID_KEY_S, HID_KEY_D,HID_KEY_F,HID_KEY_G,HID_KEY_H,HID_KEY_J,HID_KEY_K,HID_KEY_L,HID_KEY_SEMICOLON, HID_KEY_RETURN } ,
{ HID_KEY_SHIFT_LEFT,HID_KEY_Z,HID_KEY_X, HID_KEY_C,HID_KEY_V, HID_KEY_B,HID_KEY_N,HID_KEY_M,HID_KEY_COMMA,HID_KEY_PERIOD,HID_KEY_BACKSLASH, HID_KEY_SHIFT_RIGHT } ,
{ HID_KEY_CONTROL_LEFT, HID_KEY_GUI_LEFT,HID_KEY_SPACE,HID_KEY_SPACE,HID_KEY_SPACE,HID_KEY_SPACE,HID_KEY_SPACE, HID_KEY_SPACE, HID_KEY_NONE, HID_KEY_ALT_RIGHT, HID_KEY_POWER }} ,

{{ HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE,HID_KEY_EQUAL, HID_KEY_NONE } ,
{ HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE,HID_KEY_BACKSLASH } ,
{ HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE,HID_KEY_NONE, HID_KEY_NONE } ,
{ HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE,HID_KEY_NONE, HID_KEY_NONE,HID_KEY_BRACKET_LEFT, HID_KEY_BRACKET_RIGHT } ,
{ HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE }}

}; */
char Activation[5][12] = 
{{ 0,'1','2','3','4','5','6','7','8','9','0',0 } ,
{ 0,'Q','W','E','R','T','Y','U','I','O','P','-' } ,
{ 0,'A','S','D','F','G','H','J','K','L',';',0 } ,
{ 0,'Z','X','C','V','B','N','M',',','.','\'', } ,
{ 0,0,0,0,0,0,0,0,0,0,0 }};
char modsnnonprntbles[5][12] = 
{{ HID_KEY_ESCAPE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE,HID_KEY_NONE, HID_KEY_BACKSPACE } ,
{ HID_KEY_TAB, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE,HID_KEY_NONE } ,
{ HID_KEY_CAPS_LOCK, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE,HID_KEY_NONE, HID_KEY_RETURN } ,
{ HID_KEY_SHIFT_LEFT, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE,HID_KEY_NONE, HID_KEY_NONE,HID_KEY_NONE, HID_KEY_NONE } ,
{ HID_KEY_CONTROL_LEFT, HID_KEY_GUI_LEFT,HID_KEY_SPACE,HID_KEY_SPACE,HID_KEY_SPACE,HID_KEY_SPACE,HID_KEY_SPACE, HID_KEY_SPACE, HID_KEY_NONE, HID_KEY_ALT_RIGHT, HID_KEY_POWER }};
void setup() 
{
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb

  Serial.println("Bluefruit52 HID Keyboard Example");
  Serial.println("--------------------------------\n");

  Serial.println();
  Serial.println("Go to your phone's Bluetooth settings to pair your device");
  Serial.println("then open an application that accepts keyboard INPUT_PULLUP");

  Serial.println();
  Serial.println("Enter the character(s) to send:");
  Serial.println();  

  Bluefruit.begin();
  // Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName("Bluefruit52");

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather 52");
  bledis.begin();

  /* Start BLE HID
   * Note: Apple requires BLE device must have min connection interval >= 20m
   * ( The smaller the connection interval the faster we could send data).
   * However for HID and MIDI device, Apple could accept min connection interval 
   * up to 11.25 ms. Therefore BLEHidAdafruit::begin() will try to set the min and max
   * connection interval to 11.25  ms and 15 ms respectively for best performance.
   */
  blehid.begin();

  // Set callback for set LED from central
//  blehid.setKeyboardLedCallback(set_keyboard_led);

  /* Set connection interval (min, max) to your perferred value.
   * Note: It is already set by BLEHidAdafruit::begin() to 11.25ms - 15ms
   * min = 9*1.25=11.25 ms, max = 12*1.25= 15 ms 
   */
  /* Bluefruit.setConnInterval(9, 12); */

  // Set up and start advertising
  startAdv();
  
pinMode(20, OUTPUT);
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(12, INPUT_PULLUP);
pinMode(13, INPUT_PULLUP);
pinMode(14, INPUT_PULLUP);
pinMode(8, INPUT_PULLUP);
pinMode(6, INPUT_PULLUP);
pinMode(25, INPUT_PULLUP);
pinMode(26, INPUT_PULLUP);
pinMode(27, INPUT_PULLUP);
pinMode(11, INPUT_PULLUP);
pinMode(7, INPUT_PULLUP);
pinMode(15, INPUT_PULLUP);
pinMode(16, INPUT_PULLUP);

}

void startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);

  // There is enough room for the dev name in the advertising packet
  Bluefruit.Advertising.addName();
  
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html   
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}
void keyreport(char HIDcode)
{
  uint8_t keyCodes[6] = {  HIDcode , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( HID_KEY_NONE , keyCodes );
}
void loop() 
{
  // Modifiers are here..
  // https://github.com/adafruit/Adafruit_nRF52_Arduino/blob/200b3aaefb3256ac26df82ebc9b5b58923d9c37c/cores/nRF5/Adafruit_TinyUSB_Core/tinyusb/src/class/hid/hid.h#L188
  // Keycodes are here..
  // https://github.com/adafruit/Adafruit_nRF52_Arduino/blob/200b3aaefb3256ac26df82ebc9b5b58923d9c37c/cores/nRF5/Adafruit_TinyUSB_Core/tinyusb/src/class/hid/hid.h#L212

  // Only send KeyRelease if previously pressed to avoid sending
  // multiple keyRelease reports (that consume memory and bandwidth)
//  if ( hasKeyPressed )
//  {
for (int rowCount = 0; rowCount < 5; rowCount++)
{
digitalWrite(rowPin[rowCount], LOW);
for (int columnCount = 0; columnCount < 12; columnCount++)
  {
if(digitalRead(columnPin[columnCount]) == LOW)
{
  int a = Activation[rowCount][columnCount];
  if(a == 0)//zero means non letter
  {
    
    keyreport(modsnnonprntbles[rowCount][columnCount]);
    haskeyPressed[rowCount][columnCount] = true;
  } else
  {
      blehid.keyPress(a);
      blehid.keyRelease();
      haskeyPressed[rowCount][columnCount] = true;
  }
} else
{
  haskeyPressed[rowCount][columnCount] = false;
}
  }
digitalWrite(rowPin[rowCount], HIGH);
}
/*for (int rowCount; rowCount < 5; rowCount++)
{
  digitalWrite(rowPin[rowCount], LOW);
  for (int columnCount; columnCount < 12; columnCount++)
  {
    blehid.keyPress(Activation[1][1]);
    blehid.keyRelease();
//    blehid.keyPress(Activation[rowCount][columnCount]);
//      blehid.keyRelease();
  }
  digitalWrite(rowPin[rowCount], HIGH);
}*/
/*for (int rowCount; rowCount < 5; rowCount++)
{
  digitalWrite(rowPin[rowCount], LOW);
  for (int columnCount; columnCount < 12; columnCount++)
  {
    if ( digitalRead(columnPin[columnCount]) == LOW)
   {
    /*  if ( columnCount == 0 || columnCount == 11)
    {
      if ( rowCount == 0 )
      {
        
        if ( columnCount == 0 )
        {
         
        }
        
        if ( columnCount == 11 )
        {
         uint8_t keycodesforbcs[6] = {  HID_KEY_BACKSPACE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( HID_KEY_NONE , keycodesforbcs );
        }
      }
      if ( rowCount == 1 )
      {
         
         if ( columnCount == 0 )
        {
         uint8_t keycodesfortab[6] = {  HID_KEY_TAB , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( HID_KEY_NONE , keycodesfortab );
        }
      }
      if ( rowCount == 2 )
      {
         
          if ( columnCount == 0 )
        {
          bool capsLock = true;
        }
        
          if ( columnCount == 11 )
        {
         uint8_t keycodesforrtn[6] = {  HID_KEY_RETURN , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( HID_KEY_NONE , keycodesforrtn );
        }
      }
      if ( rowCount == 3 )
      {
        
        if ( columnCount == 0 )
        {
          bool Shift = true;
        }
      }
    }
      if( rowCount == 4 )
    {
      if ( columnCount > 1 || columnCount < 9)
      {
        uint8_t keycodesforspc[6] = {  HID_KEY_SPACE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( HID_KEY_NONE , keycodesforspc );
      }
      if ( columnCount == 0)
      {
        uint8_t keycodesforlctrl[6] = {  HID_KEY_CONTROL_LEFT , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( HID_KEY_NONE , keycodesforlctrl );
      }
      if ( columnCount == 1)
      {
        uint8_t keycodesforlgui[6] = {  HID_KEY_GUI_LEFT , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( HID_KEY_NONE , keycodesforlgui );
      }
      if ( columnCount == 9)
      {
        bool right = true;
      }
      if ( columnCount == 10)
      {
        uint8_t keycodesforralt[6] = {  HID_KEY_ALT_RIGHT , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( HID_KEY_NONE , keycodesforralt );
      }
      if ( columnCount == 11)
      {
        uint8_t keycodesforrgui[6] = {  HID_KEY_GUI_RIGHT , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( HID_KEY_NONE , keycodesforrgui );
      }
      
    } 
    if ( rowCount != 4 || columnCount != 0 || columnCount != 11)
    {
     blehid.keyPress(Activation[rowCount][columnCount]);
      blehid.keyRelease();
    } 
   } 
  }
} */
}
/*
    hasKeyPressed = false;
    blehid.keyPress('M');
    blehid.keyRelease();
    blehid.keyPress('i');
    blehid.keyRelease();
    blehid.keyPress('l');
    blehid.keyRelease();
    blehid.keyPress('e');
    blehid.keyRelease();
    blehid.keyPress('s');
    blehid.keyRelease();
    uint8_t keycodes[6] = {  HID_KEY_1 , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( HID_KEY_NONE , keycodes );
    blehid.keyPress(13);
    blehid.keyRelease();
    
    // Delay a bit after a report
    delay(1000); 
} */

    
/*  if (Serial.available())
  {
    char ch = (char) Serial.read();

    // echo
    Serial.write(ch); 

    blehid.keyPress(ch);
    hasKeyPressed = true;
    
    // Delay a bit after a report
    delay(5);
  }

  // Request CPU to enter low-power mode until an event/interrupt occurs
  waitForEvent();  
}
*/
/**
 * Callback invoked when received Set LED from central.
 * Must be set previously with setKeyboardLedCallback()
 *
 * The LED bit map is as follows: (also defined by KEYBOARD_LED_* )
 *    Kana (4) | Compose (3) | ScrollLock (2) | CapsLock (1) | Numlock (0)
 */
/*void set_keyboard_led(uint8_t led_bitmap)
{
  // light up Red Led if any bits is set
  if ( led_bitmap )
  {
    ledOn( LED_RED );
  }
  else
  {
    ledOff( LED_RED );
  }
} */
