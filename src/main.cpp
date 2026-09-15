#include <Arduino.h>

const int LED_1 = 40;
const int LED_2 = 41;

void toggleLed(int led, int delayTime)
{
  digitalWrite(led, !digitalRead(led));
  delay(delayTime);

  digitalWrite(led, !digitalRead(led));
  delay(delayTime);
}

void vTaskLed1(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  //int led = *(int *)pvParameters;
  while (1)
  {
    digitalWrite(LED_1, !digitalRead(LED_1));
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500));

    digitalWrite(LED_1, !digitalRead(LED_1));
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500));
  }
}

void vTaskLed2(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  //int led = *(int *)pvParameters;
  while (1)
  {
    digitalWrite(LED_2, !digitalRead(LED_2));
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));

    digitalWrite(LED_2, !digitalRead(LED_2));
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
  }
}

void vTaskChargeCPU(void *pvParameters){
  while (1)
    {
        for (volatile int i = 0; i < 200000; i++);
    }
}

void setup()
{
  // Configurer les broches des LED comme sorties
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
/*
  xTaskCreate(vTaskLed1, "LED1", 1000, NULL, 2, NULL);
  xTaskCreate(vTaskLed2, "LED2", 1000, NULL, 1, NULL);
  xTaskCreate(vTaskChargeCPU, "CPU", 1000, NULL, 0, NULL);
  */
}

void loop()
{
/*
  // Boucle pour charger le CPU
  // for (volatile int i = 0; i < 200000; i++);

  // Clignoter LED_1
  toggleLed(LED_1, 500); // Attendre 0.5 seconde

  // Boucle pour charger le CPU
  // for (volatile int i = 0; i < 200000; i++);

  // Clignoter LED_2
  toggleLed(LED_2, 1000); // Attendre 1 seconde
  
  */

}
