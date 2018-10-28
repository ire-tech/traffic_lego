/***   Included libraries  ***/
//Aquí lo que hacemos es cargar las librerías necesarias para poder utilizar el ledRGB
#include <BitbloqRGB.h>
#include <BitbloqSoftwareSerial.h>

/***   Global variables and function definition  ***/
const int led_MID_NARANJA = 6;
ZumRGB led_TOP_ROJO(5, 4, 3);
const int led_BOT_VERDE = 7;
//Iniciar variable que llama a BT main de la placa, siempre con 19200 como valor de baudios
bqSoftwareSerial bluetooth_de_la_placa(0, 1, 19200);
//Inicializamos y asignamos qué tipo de variables vamos a usar.
int tiempo_int = 0;
char green_control = "";

// readSring genera un IRQ para que entre el dat de BT.
String DATOS_BT = bluetooth_de_la_placa.readString();
/**
 * FUNCION SEMAFORO
 * 
 * Esta función es la principal que vamos a usar, se utiliza para llamarla desde el loop principal.
 * Característica principal, variable DATOS_BT es la que se espera de la lectura de entrada del BT.
 * Funcionamiento:
 * Apagar led NARANJA y VERDE / Encender led ROJO y abrir secuencia con 2s para para pasar a verde. Luego de verde ROJO
 * loop de 4 vueltas con un delay de 1s de parpadeo del led verde. Pasaremos al final el for > until 4t a verde pasando por naranja
 **/
void SEMAFORO(String DATOS_BT) {
        Serial.println("Entrado en la función");
        // IMPORTANTE! la entrada de datos por BT hacia la variable nos la hace en char por lo que hemos de convertir en INT con la funcion .toINT()
        tiempo_int = DATOS_BT.toInt();
        digitalWrite(led_MID_NARANJA, LOW);
        digitalWrite(led_BOT_VERDE, LOW);
        led_TOP_ROJO.setRGBcolor(255, 0, 0);
        delay(2000);
        led_TOP_ROJO.setRGBcolor(0, 0, 0);
        digitalWrite(led_BOT_VERDE, HIGH);
        delay(tiempo_int + 2000);
        for (int bitbloqForCounter = 0; bitbloqForCounter < 4; bitbloqForCounter += 1) {
            digitalWrite(led_BOT_VERDE, HIGH);
            delay(1000);
            digitalWrite(led_BOT_VERDE, LOW);
            delay(1000);
        }
        digitalWrite(led_MID_NARANJA, HIGH);
        delay(1000);
        digitalWrite(led_MID_NARANJA, LOW);
        delay(1000);
        led_TOP_ROJO.setRGBcolor(255, 0, 0);
        delay(3000);
    }
    /**
     * Función APAGAR
     * Función que sirve para apagar todos los leds del SEMAFORO
     **/

void APAGAR(String interruptor) {
    if (interruptor = "off") {
        digitalWrite(led_MID_NARANJA, LOW);
        digitalWrite(led_BOT_VERDE, LOW);
        led_TOP_ROJO.setRGBcolor(0, 0, 0);
    }

}

// Funcion en construccion
/**
void ONOFF(char estado, char led_color) {

    Str4[0] == estado+"_"+led_color;
    Serial.println(Str4[0]);
    switch (Str4[0]) {
        case '1_verde':
        if (estado=='encendido'){
          digitalWrite(led_BOT_VERDE, LOW);
          return 1;
        }else{
          digitalWrite(led_BOT_VERDE, HIGH);
          return 0;
        }
            break;
        case '1_naranja':
            break;
        case '1_rojo':
        break;
        default:
        break;
    }
}
**/


/***   Setup  ***/
void setup() {
    pinMode(led_MID_NARANJA, OUTPUT);
    pinMode(led_BOT_VERDE, OUTPUT);
    bluetooth_de_la_placa.begin(19200);
    // Con Serial.begin 9600 lo usamos para que el usb lea datos de la main a modo debug
    Serial.begin(9600);
    Serial.println("--- Lecturas entrada BT ---");
}


/***   Loop  ***/
void loop() {
    // Cambiamos ahora el sistema para encender y apagar el LED verde de tal manera que cuando le das se apaga al momento debido al loop, pendiente de solucionarlo.
    DATOS_BT = bluetooth_de_la_placa.readString();
    if (DATOS_BT == "traffic_green" && gren_control!="encendido") {
        digitalWrite(led_BOT_VERDE, HIGH);
        green_control="encendido";
    }
    else {
        digitalWrite(led_BOT_VERDE, LOW);
        green_control("apagado");
    }

    if (DATOS_BT == "traffic_red") {
        led_TOP_ROJO.setRGBcolor(255, 0, 0);
    }

    if (DATOS_BT == "traffic_orange"){
      digitalWrite(led_MID_NARANJA, HIGH);
    }
    if (DATOS_BT == "traffic_stop"){
      APAGAR("off");
    }

    if (DATOS_BT == "traffic_start") {
        SEMAFORO("10");
        //APAGAR("off");
    }
}
