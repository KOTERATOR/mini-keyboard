#include <Keyboard.h>
#include "Adafruit_SSD1306.h"

#define ROWS_COUNT 2
#define COLUMNS_COUNT 4
const int KEYS_COUNT = ROWS_COUNT * COLUMNS_COUNT; 

const byte columns [] = { A0, A1, A2, A3 }, rows [] = { A9, A8 };

bool states [KEYS_COUNT] = {};

Adafruit_SSD1306 display(128, 32);

int start_x = (128 - 16 * COLUMNS_COUNT) / 2;

void setup()
{
	Keyboard.begin();
    delay(2000);
    for (int i = 0; i < COLUMNS_COUNT; i++)
    {
        pinMode(columns[i], INPUT_PULLUP);
    }
    for (int i = 0; i < COLUMNS_COUNT; i++)
    {
        pinMode(rows[i], INPUT_PULLUP);
    }
    for (int i = 0; i < KEYS_COUNT; i++)
    {
        states[i] = false;
    }
    display.begin();
    display.setRotation(2);
    display.clearDisplay();
    display.display();
    
}

void update_display()
{
    display.clearDisplay();
    for (int i = 0; i < COLUMNS_COUNT; i++)
    {
        for (int j = 0; j < ROWS_COUNT; j++)
        {
            int x = start_x + i * 16, y = j * 16;
            
            if (states[j * COLUMNS_COUNT + i])
            {
                display.fillRect(x, y, 16, 16, WHITE);
            }
            else
            {
                display.drawRect(x, y, 16, 16, WHITE);
            }
        }
    }
    display.display();
}

void loop()
{   
    for (int i = 0; i < COLUMNS_COUNT; i++)
    {
        pinMode(columns[i], OUTPUT);
        digitalWrite(columns[i], 0);
        for (int j = 0; j < ROWS_COUNT; j++)
        {
            if (!digitalRead(rows[j]))
            {
                bool prev_state = states[j * COLUMNS_COUNT + i];
                states[j * COLUMNS_COUNT + i] = true;
                if (!prev_state)
                {
                    Keyboard.println(String(j * COLUMNS_COUNT + i));
                }
            }
            else
            {
                states[j * COLUMNS_COUNT + i] = false;
            }
        }
        pinMode(columns[i], INPUT);
        digitalWrite(columns[i], 1);
        
    }

    update_display();

    delay(50);
}
