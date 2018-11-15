#include <Driving.h> //LIBRERIA DE CONTROL DEL SISTEMA (INCLUYE SERVO_T3.H, LED.H, LDR.H, CNY.H, STEPPER_MOTOR.H)
Driver driver; //INSTANCIACION DE UN CONTROLADOR
short counting = 0; //CONTADOR DE CARAS NEGRAS

void setup() {
  driver.init_stepper(); //INICIALIZA MOTOR PASO A PASO, 200 PASOS POR REVOLUCIÓN, PINES 10,11,12,13
  driver.init_cnys(); //INICIALIZA CNYS, PINES A0,A1
  driver.init_ldrs(); //INICIALIZA LDRS, PINES A2,A3,A4,A5
  driver.init_leds(); //INICIALIZA LED, PIN D0
  driver.init_servos(); //INICIALIZA SERVOS, PINES D1, D9
  /*INICIALIZACION BRAZO ROBOT*/
  driver.check_initialized(); //COMPRUEBA QUE TODOS LOS COMPONENTES ESTAN CONECTADOS (RECIBIENDO SEÑAL DEL ARDUINO)

  driver.modulateSpeed(100); //VELOCIDAD DEL MOTOR PASO A PASO A 100RPM
  driver.servos_initial_state(); //SERVOS A POSICIONES INICIALES 10º Y 180º RESPECTIVAMENTE

  driver.turnOn(); //ILUMINA EL LED DE LA ZONA DE ALMACENAJE DURANTE 5 SEGUNDOS INDICANDO EL INICIO DEL SISTEMA
}

void loop() {
  if(driver.check_cube(0)) {
    driver.goOn(-80); //COMPRUEBA QUE EL VALOR DE LA LDR CONECTADA AL TAMBOR DE LA ZONA DE ESPERA ES SUPERIOR A 450, 
                      //INDICANDO QUE HAY UN CUBO Y HA DE GIRAR 144º
  
    counting += driver.watch_initial();  //MUEVE EL SERVO1 A LA POSICIÓN INICIAL E INICIA LA LECTURA CON EL CNY
                                        //PARA ELIMINAR DATOS ANOMALOS, SE QUEDARA CON LA MEDIANA DE 20 LECTURAS
                                        //GARANTIZANDO UN VALOR "REAL". SI LA LECTURA ES SUPERIOR A 600, CONTARÁ
                                        //1 CARA BLANCA, DEVOLVIENDO 0(EL CUAL SE SUMARÁ AL CONTADOR DE CARAS NEGRAS.
                                        //EN CASO CONTRARIO, CONTARÁ 1 CARA NEGRA DEVOLVIENDO 1, QUE SUMARÁ A COUNTING.
    counting += driver.watch_base();    //ANALOGA A LA ANTERIOR, POSICION CENTRAL
    counting += driver.watch_final();   //ANALOGA A LA ANTERIOR, POSICIÓN FINAL
  
    counting += driver.watch_initial_phase();//MUEVE EL SERVO2 A LA POSICIÓN INICIAL E INICIA LA LECTURA CON EL CNY
                                          //PARA ELIMINAR DATOS ANOMALOS, SE QUEDARA CON LA MEDIANA DE 20 LECTURAS
                                          //GARANTIZANDO UN VALOR "REAL". SI LA LECTURA ES SUPERIOR A 600, CONTARÁ
                                          //1 CARA BLANCA, DEVOLVIENDO 0(EL CUAL SE SUMARÁ AL CONTADOR DE CARAS NEGRAS.
                                          //EN CASO CONTRARIO, CONTARÁ 1 CARA NEGRA DEVOLVIENDO 1, QUE SUMARÁ A COUNTING.
    counting += driver.watch_base_phase();//ANALOGA A LA ANTERIOR, POSICION CENTRAL
    counting += driver.watch_final_phase();//ANALOGA A LA ANTERIOR, POSICIÓN FINAL
  
    /* CODIGO DE MANIPULACION DEL BRAZO ROBOTICO */
    
    if(driver.check_cube(counting + 1)) driver.blink_leds(counting + 1); //COMPRUEBA QUEEL VALOR DE LA LDR CONECTADA AL CONTENEDOR DE LA ZONA DE ALMACENAJE ES SUPERIOR A 450,
                                                                         //INDICANDO QUE HAY UN CUBO EN ESA ZONA, IMPRIMIENDO UN MENSAJE Y HACIENDO PARPADEAR EL LED CON EL ÍNDICE
                                                                          //DE CONTENEDOR ASOCIADO (1 = 0 CARAS BLANCAS, 2 = 1 CARA BLANCA, 3 = 2 CARAS BLANCAS)
    driver.re_init(); //REINICIA LAS POSICIONES DEL MOTOR PASO A PASO Y DE LOS SERVOS
    counting = 0; //REINICIA EL CONTADOR PARA LA SIGUIENTE FASE
  }
  else  driver.forceStop(); //EN CASO CONTRARIO FORZARA LA PARADA DEL MOTOR Y NO INICIARA LA SECUENCIA
}
