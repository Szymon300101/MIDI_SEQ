#ifndef MIDI_h
#define MIDI_h

#include <Arduino.h>
#include <usbh_midi.h>
#include <usbhub.h>

enum MIDI_command
{
    note = 144,
    pedal = 177,
    bend = 224
};


class MIDI
{
USBH_MIDI usb_midi;
USB Usb;

public:
    uint8_t notes[10];
    uint8_t notes_len=0;
    uint8_t special[5];
    uint8_t special_len=0;

    MIDI() : usb_midi(&Usb){}

    void begin()
    {
        if (Usb.Init() == -1) {
            Serial.println("USB error. Halted.");
            while (1);
        }
    }

    void read()
    {
        Usb.Task();

        if ( usb_midi ) {
            MIDI_poll();
        }
    }

private:
    void add_note(uint8_t note)
    {
        if(notes_len < 10)
        {
            notes[notes_len++] = note;
        }
    }

    void remove_note(uint8_t note)
    {
        bool found = false;
        for (uint8_t i = 0; i < notes_len; i++)
        {
            if(found == false && notes[i] == note)
            {
                found = true;
                notes_len--;
            }
            if(found == true)
            {
                notes[i] = notes[i+1];
            }
        }
        
    }

    void MIDI_poll()
    {
        Serial.println("poll");
        uint8_t buffer[ 3 ];
        if(usb_midi.RecvData(buffer) > 0)
        {
            Serial.println(buffer[0]);
            //digitalWrite(5, led_on);
            //led_on=!led_on;
            switch (buffer[0])
            {
                case MIDI_command::note:
                    if(buffer[2] > 0)
                    {
                        add_note(buffer[1]);
                    }else
                    {
                        remove_note(buffer[1]);
                    }
                    break;
                
                default:
                    break;
            }
        }
        
    }
};

#endif