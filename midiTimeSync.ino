/**************************************************************************
--                      Arduino Midi Master Clock 
-- 
--           Copyright (C) 2021 By Ulrik Hørlyk Hjort
--
--  This Program is Free Software; You Can Redistribute It and/or
--  Modify It Under The Terms of The GNU General Public License
--  As Published By The Free Software Foundation; Either Version 2
--  of The License, or (at Your Option) Any Later Version.
--
--  This Program is Distributed in The Hope That It Will Be Useful,
--  But WITHOUT ANY WARRANTY; Without Even The Implied Warranty of
--  MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See The
--  GNU General Public License for More Details.
--
-- You Should Have Received A Copy of The GNU General Public License
-- Along with This Program; if not, See <Http://Www.Gnu.Org/Licenses/>.
***************************************************************************/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 
#define OLED_ADDR 0x3C

#define PIN_TEMPO_POT 1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/********************************************
 * 
 *  Print the BPM on the OLED
 *  
 ********************************************/
void print_tempo(uint32_t bpm) {
  display.clearDisplay();
  display.setTextSize(7);             
  display.setTextColor(WHITE);        
  display.setCursor(0,0);             
  display.println(bpm, DEC);
  display.display();
}

/********************************************
 * 
 *  Setup
 *  
 ********************************************/
void setup() {
  
 Serial.begin(31250);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) { 
    for(;;); 
  }
}

/********************************************
 * 
 *  Send the sync command to the slave chain 
 *  (24 pulses per quarter note). 
 *  Read for pot changes every second and 
 *  adjust BPM if necessary
 *  
 ********************************************/
void send_sync() {
  double factor = 1023/240.0; // Max bpm setting from pot = 240 with 10 bit ADC resolution
  uint32_t bpm = 120;
  uint32_t tempo = 1000.0/(bpm/60.0);
  
  uint32_t interval_tempo = tempo/24.0; // 24 ppqn 
  uint32_t interval_read = 1000;        
  
  uint32_t prev_millis_tempo = 0;
  uint32_t prev_millis_read = 0;
  
  int16_t pot_val = analogRead(PIN_TEMPO_POT);
  
  while (1) {  
    uint32_t current_millis = millis();

    // Read analog port for pot value
    if (current_millis - prev_millis_read > interval_read) {
        pot_val = analogRead(PIN_TEMPO_POT);
        bpm = pot_val / factor;
        tempo = 1000/(bpm/60.0);
        interval_tempo = tempo/24.0; // 24 ppqn    
        print_tempo(bpm);
        prev_millis_read = current_millis;
    }

    // Send sync command
    if (current_millis - prev_millis_tempo > interval_tempo) {
        prev_millis_tempo = current_millis;
        Serial.write(0xF8);  // Midi time sync command
    }
  }  
}

/********************************************
 * 
 *  Main loop
 *  
 ********************************************/
void loop() {
  send_sync();
}
