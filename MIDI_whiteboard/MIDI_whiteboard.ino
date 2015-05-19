/* Copyright (c) SB Hackerspace 2015

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */


// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MIDIUSB.write(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MIDIUSB.write(noteOff);
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  MIDIEvent event = {0x0B, 0xB0 | channel, control, value};
  MIDIUSB.write(event);
}

int thresh = 2;
int val, attack;

void loop() {
    val = analogRead(A0);
    if(val > thresh){
      noteOn(0, map(val, 2, 1023, 20, 127), 127);   // Channel 0, middle C, normal velocity
      MIDIUSB.flush();
      delay(50);
      while((val >> 2) == (analogRead(A0) >> 2));
      
      noteOff(0,map(val, 2, 1023, 20, 127),127);  // Channel 0, middle C, normal velocity
      MIDIUSB.flush();
      delay(10);
    }
  delay(10);

  // controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65
}

void setup() {

}
