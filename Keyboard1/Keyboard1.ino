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

int pressedRows[5];
int pressedColumns[5];
int rowPin[5] = { 4, 3, 2, 5, 20};
int columnPin[12] = { 16, 12, 13, 14, 8, 6, 15, 7, 11, 25, 27, 26};
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
{ { '\e', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\b' } ,
  { 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '-' } ,
  { 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\r' } ,
  { 0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '\'' } ,
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
char activationCodes[5][12] =
{ { HID_KEY_ESCAPE, HID_KEY_1, HID_KEY_2, HID_KEY_3, HID_KEY_4, HID_KEY_5, HID_KEY_6, HID_KEY_7, HID_KEY_8, HID_KEY_9, HID_KEY_0, HID_KEY_BACKSPACE } ,
  { HID_KEY_TAB, HID_KEY_Q, HID_KEY_W, HID_KEY_E, HID_KEY_R, HID_KEY_T, HID_KEY_Y, HID_KEY_U, HID_KEY_I, HID_KEY_O, HID_KEY_P, HID_KEY_MINUS } ,
  { HID_KEY_CAPS_LOCK, HID_KEY_A, HID_KEY_S, HID_KEY_D, HID_KEY_F, HID_KEY_G, HID_KEY_H, HID_KEY_J, HID_KEY_K, HID_KEY_L, HID_KEY_SEMICOLON, HID_KEY_RETURN } ,
  { HID_KEY_SHIFT_LEFT, HID_KEY_Z, HID_KEY_X, HID_KEY_C, HID_KEY_V, HID_KEY_B, HID_KEY_N, HID_KEY_M, HID_KEY_COMMA, HID_KEY_PERIOD, HID_KEY_BACKSLASH, HID_KEY_SHIFT_RIGHT } ,
  { HID_KEY_CONTROL_LEFT, HID_KEY_GUI_LEFT, HID_KEY_SPACE, HID_KEY_SPACE, HID_KEY_SPACE, HID_KEY_SPACE, HID_KEY_SPACE, HID_KEY_SPACE, HID_KEY_NONE, HID_KEY_ALT_RIGHT, HID_KEY_POWER }
};
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
     Note: Apple requires BLE device must have min connection interval >= 20m
     ( The smaller the connection interval the faster we could send data).
     However for HID and MIDI device, Apple could accept min connection interval
     up to 11.25 ms. Therefore BLEHidAdafruit::begin() will try to set the min and max
     connection interval to 11.25  ms and 15 ms respectively for best performance.
  */
  blehid.begin();

  // Set callback for set LED from central
  //  blehid.setKeyboardLedCallback(set_keyboard_led);

  /* Set connection interval (min, max) to your perferred value.
     Note: It is already set by BLEHidAdafruit::begin() to 11.25ms - 15ms
     min = 9*1.25=11.25 ms, max = 12*1.25= 15 ms
  */
  /* Bluefruit.setConnInterval(9, 12); */
Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  // Set up and start advertising
  startAdv();

  pinMode(20, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
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
     - Enable auto advertising if disconnected
     - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
     - Timeout for fast mode is 30 seconds
     - Start(timeout) with timeout = 0 will advertise forever (until connected)
     For recommended advertising interval
     https://developer.apple.com/library/content/qa/qa1931/_index.html
  */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}
void modkeyreport(bool shift, bool alt, bool control, char key, char standardKey)
{
  if ( standardKey == 0 )
 {
   uint8_t keyCodes[6] = { key, 0, 0, 0, 0, 0 };
   if ( shift == true)
   {
     blehid.keyboardReport( KEYBOARD_MODIFIER_LEFTSHIFT , keyCodes );
     return;
   }
   if ( alt == true)
   {
     blehid.keyboardReport( KEYBOARD_MODIFIER_RIGHTALT , keyCodes );
     return;
   }
   if ( control == true)
   {
     blehid.keyboardReport( KEYBOARD_MODIFIER_LEFTCTRL , keyCodes );
     return;
   }
   blehid.keyboardReport( HID_KEY_NONE , keyCodes );
 } else
 {
  blehid.keyPress(standardKey);
  blehid.keyRelease();
 }
}
void blinky(int number_of_blinks)
{
  while (number_of_blinks > 0)
  {
    digitalWrite(LED_BUILTIN, 1);
  delay(200);
  digitalWrite(LED_BUILTIN, 0);
  delay(200);
  number_of_blinks--;
  }
  delay(500);
}
void loop()
{
  bool shift;
  bool control;
  bool alt;
  digitalWrite(rowPin[3], LOW);
  if (digitalRead(columnPin[0]) == LOW)
  {
     shift = true;
  } else
  {
     shift = false;
  }
  digitalWrite(rowPin[3], HIGH);

  digitalWrite(rowPin[4], LOW);
  if (digitalRead(columnPin[0]) == LOW)
  {
     control = true;
  } else
  {
     control = false;
  }
  digitalWrite(rowPin[4], HIGH);
  
  digitalWrite(rowPin[4], LOW);
  if (digitalRead(columnPin[10]) == LOW)
  {
     alt = true;
  } else
  {
     alt = false;
  }
  digitalWrite(rowPin[4], HIGH);
  // Modifiers are here..
  // https://github.com/adafruit/Adafruit_nRF52_Arduino/blob/200b3aaefb3256ac26df82ebc9b5b58923d9c37c/cores/nRF5/Adafruit_TinyUSB_Core/tinyusb/src/class/hid/hid.h#L188
  // Keycodes are here..
  // https://github.com/adafruit/Adafruit_nRF52_Arduino/blob/200b3aaefb3256ac26df82ebc9b5b58923d9c37c/cores/nRF5/Adafruit_TinyUSB_Core/tinyusb/src/class/hid/hid.h#L212

  // Only send KeyRelease if previously pressed to avoid sending
  // multiple keyRelease reports (that consume memory and bandwidth)
  //  if ( hasKeyPressed )
  //  {
  for (int columnCount = 0; columnCount < 12; columnCount++)
  {
    digitalWrite(columnPin[columnCount], LOW);
    for (int rowCount = 0; rowCount < 5; rowCount++)
    {
      if (digitalRead(rowPin[rowCount]) == LOW)
      {
        int a = Activation[rowCount][columnCount];
            modkeyreport( shift, alt, control, activationCodes[rowCount][columnCount], a);
      }
    }
    digitalWrite(columnPin[columnCount], HIGH);
  }
}
