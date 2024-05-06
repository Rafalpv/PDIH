# Práctica 3. Experimentación con Arduino

### Parpadeo de 3 LEDs

#### Diseño del Circuito

La primera configuración implica la conexión de tres LEDs a las salidas 11, 12 y 13 respectivamente, los cuales se encienden alternativamente con un intervalo de 1.5 segundos. El diseño específico del circuito se puede visualizar en la siguiente imagen :

![Parpadeo 3 LEDS](https://github.com/Rafalpv/PDIH/assets/116666555/8363a85f-fe79-4e69-84b7-f749debdca94)

#### Código

```Arduino
int pins[] = {11, 12, 13};
int numPins = 3;

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop()
{
  for (int i = 0; i < numPins; i++) {
    for (int j = 0; j < numPins; j++) {
      digitalWrite(pins[j], (i == j) ? HIGH : LOW);
    }
    delay(1500);
  }  
}
```
#### Simulación
[SimulacionParpadeo3LEDS.webm](https://github.com/Rafalpv/PDIH/assets/116666555/5e0ff615-a353-49c9-a639-a293a334a014)

---

### Parpadeo de 3 LEDs + Pulsador

#### Diseño del Circuito

En la segunda configuración, se presenta una estructura similar a la anterior, con la adición de un pulsador. Cuando este pulsador se activa, el parpadeo de los tres LEDs se detiene y se enciende el LED rojo mientras el pulsador esté activado. La disposición del circuito se muestra en la siguiente imagen:

![3 LEDS + Pulsador](https://github.com/Rafalpv/PDIH/assets/116666555/acef580d-2a96-4293-a093-b082d8925c88)

#### Código

```arduino
int pins[] = {11, 12, 13};
int numPins = 3;
const int LED=13;
const int BOTON=7;

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(LED, OUTPUT); // LED ROJO (13)
  pinMode(BOTON, OUTPUT);

}

void loop(){  
  for (int i = 0; i < numPins; i++) {
    for (int j = 0; j < numPins; j++){
       while(digitalRead(BOTON)==HIGH){
        	digitalWrite(LED,HIGH);
            digitalWrite(12,LOW);
            digitalWrite(11,LOW);
    	};
          digitalWrite(pins[j], (i == j) ? HIGH : LOW);
  	}
    	delay(1500);	
  }
}
```

#### Simulación

[SimulacionParpaedo3LedsPulsador.webm](https://github.com/Rafalpv/PDIH/assets/116666555/11e5f19b-49ed-4ae8-acea-88c75b8a8882)

---

### Cronómetro

#### Diseño del Circuito

La útlima configuración trata de un cronómetro 

![Cronometro](https://github.com/Rafalpv/PDIH/assets/116666555/72a0f32d-7bd7-4d3f-8669-56b6f1c03c03)

#### Código

1. **Inclusión de bibliotecas y definición del objeto LiquidCrystal:**
   - Se incluye la biblioteca `LiquidCrystal.h`, que permite controlar pantallas LCD.
   - Se crea un objeto `lcd` de la clase `LiquidCrystal`, con los pines 7, 6, 5, 4, 3 y 2 conectados al display LCD.

2. **Declaración de variables:**
   - `k` se utiliza para controlar el estado del cronómetro.
   - `horas`, `minutos`, `segundos` y `centesimos` almacenan el tiempo transcurrido en cada unidad de tiempo.
   - `milisegundos` guarda el valor actual de millis(), que se utiliza para calcular el tiempo transcurrido.

3. **Definición de pines:**
   - Se asignan los pines A0, A1 y A2 para los botones de pausa, inicio y reset respectivamente.

4. **Configuración inicial en el método `setup()`:**
   - Se establecen los pines como entradas.
   - Se inicializa el display LCD con una configuración de 16 columnas por 2 filas.
   - Se imprime "CRONOMETRO" en la primera fila del LCD.

5. **Bucle principal en el método `loop()`:**
   - Se lee el estado de los botones y se actualiza la variable `k` en función de su estado.
   - Según el valor de `k`, se ejecuta una de las siguientes acciones:
     - Si `k` es 0, se resetea el cronómetro (Bóton izquierdo).
     - Si `k` es 1, se pausa el cronómetro. (Botón derecho)
     - Si `k` es 2, se inicia o reanuda el cronómetro (Botón central).

6. **Función `cronometro()`:**
   - Se calcula el tiempo transcurrido desde el último ciclo de loop utilizando la función `millis()`.
   - Si han pasado 10 milisegundos (correspondientes a 1 centésima de segundo), se actualizan las variables de tiempo y se actualiza la pantalla LCD con el tiempo transcurrido.


```arduino
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int k;
unsigned int horas = 0;
unsigned int minutos = 0;
unsigned int segundos = 0;
unsigned int centesimos = 0;
unsigned int milisegundos;
int reset = A2;
int inicio = A1;
int pausa = A0;

void setup()
{
    pinMode(pausa, INPUT);
    pinMode(reset, INPUT);
    pinMode(inicio, INPUT);
    lcd.begin(16, 2);
    lcd.setCursor(3, 0);
    lcd.print("CRONOMETRO");
}

void loop()
{
    if (digitalRead(reset) == LOW)
        k = 0;

    if (digitalRead(pausa) == LOW)
        k = 1;
    
    if (digitalRead(inicio) == LOW)
        k = 2;
    
    switch (k)
    {
    case 0:
        horas = 0;
        minutos = 0;
        segundos = 0;
        break;
    case 1:
        delay(10);
        break;
    case 2:
        cronometro();
        break;
    }
}

void cronometro()
{
    milisegundos = millis();
    if (milisegundos % 10 == 0)
    {
        centesimos++;
        if (centesimos == 100)
        {
            centesimos = 0;
            segundos++;
        }
        if (segundos == 60)
        {
            segundos = 0;
            minutos++;
        }
        if (minutos == 60)
        {
            minutos = 0;
            horas++;
        }
        lcd.setCursor(3, 1);
        if (horas < 10)
        {
            lcd.print("0");
        }

        lcd.print(horas);
        lcd.print(":");
        lcd.setCursor(6, 1);

        if (minutos < 10)
        {
            lcd.print("0");
        }

        lcd.print(minutos);
        lcd.print(":");
        lcd.setCursor(9, 1);

        if (segundos < 10)
        {
            lcd.print("0");
        }

        lcd.print(segundos);
        lcd.print(":");
        lcd.setCursor(12, 1);

        if (centesimos < 10)
        {
            lcd.print("0");
        }
        lcd.print(centesimos);
    }
}
```
#### Simulación

[Cronometro.webm](https://github.com/Rafalpv/PDIH/assets/116666555/cf95ce39-9926-455f-bc21-453e05a208cb)

