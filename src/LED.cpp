#ifndef LED_h
#define LED_h

#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT 8


class LED
{
    
Adafruit_NeoPixel strip;

public:
    LED() : strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800){}

    void begin()
    {
        strip.begin();
        strip.setBrightness(100);
        rainbow(2);
        strip.clear();
        strip.show();
    }

    void show()
    {
        strip.show();
    }

    void set_playing(uint8_t *notes, uint8_t notes_len)
    {
        for (uint8_t i = 0; i < notes_len; i++)
        {
            if(notes[i] >= 60 && notes[i] < 60 + LED_COUNT)
            {
                strip.setPixelColor(notes[i]-59, strip.Color(200,200,0));
            }
        }
        
    }

private:
    void rainbow(int wait) {
        for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
            strip.rainbow(firstPixelHue);
            strip.show();
            delay(wait);
        }
    }
};

#endif