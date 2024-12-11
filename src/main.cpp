/***********************************************************************
 * Project      :     tiny32_801S
 * Description  :     801S vibration sensor
 * Hardware     :     tiny32_v3
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     11/12/2024
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     +66 89-140-7205
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>
#include <esp_task_wdt.h>

/**************************************/
/*          Firmware Version          */
/**************************************/
String version = "0.1";

/**************************************/
/*          Header project            */
/**************************************/
void header_print(void)
{
    Serial.printf("\r\n***********************************************************************\r\n");
    Serial.printf("* Project      :     tiny32_801S\r\n");
    Serial.printf("* Description  :     801S vibration sensor\r\n");
    Serial.printf("* Hardware     :     tiny32_v3\r\n");
    Serial.printf("* Author       :     Tenergy Innovation Co., Ltd.\r\n");
    Serial.printf("* Date         :     11/12/2024\r\n");
    Serial.printf("* Revision     :     %s\r\n", version);
    Serial.printf("* Rev1.0       :     Origital\r\n");
    Serial.printf("* website      :     http://www.tenergyinnovation.co.th\r\n");
    Serial.printf("* Email        :     uten.boonliam@tenergyinnovation.co.th\r\n");
    Serial.printf("* TEL          :     +66 89-140-7205\r\n");
    Serial.printf("***********************************************************************/\r\n");
}

/**************************************/
/*        define object variable      */
/**************************************/
tiny32_v3 mcu;

/**************************************/
/*            GPIO define             */
/**************************************/
#define VIBRATION_SENSOR_PIN 27 // GPIO27

/**************************************/
/*       Constand define value        */
/**************************************/
// 10 seconds WDT
#define WDT_TIMEOUT 10

/**************************************/
/*       eeprom address define        */
/**************************************/

/**************************************/
/*        define global variable      */
/**************************************/

/**************************************/
/*           define function          */
/**************************************/

/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    Serial.begin(115200);
    header_print();

    //--- Initial GPIO ---//
    Serial.printf("Info: GPIO Initial ....");
    pinMode(VIBRATION_SENSOR_PIN, INPUT);
    analogSetAttenuation(ADC_11db);
    Serial.println("done");

    Serial.println("Configuring WDT...");
    esp_task_wdt_init(WDT_TIMEOUT, true); // enable panic so ESP32 restarts
    esp_task_wdt_add(NULL);               // add current thread to WDT watch
    mcu.buzzer_beep(2);
}

/***********************************************************************
 * FUNCTION:    loop
 * DESCRIPTION: loop process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void loop()
{
    int _vibrationValue = analogRead(VIBRATION_SENSOR_PIN);
    static long _intervalTime = 0;

    if ((millis() - _intervalTime) > 1000)
    {
        Serial.printf("Vibration value reading : %d\r\n", _vibrationValue);
        _intervalTime = millis();
    }

    esp_task_wdt_reset();
    vTaskDelay(100);
}
