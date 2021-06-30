#include <Servo.h>
#define GAS_PERCENT_ERR 5
#define PAINEL_SOLAR_FUNC_DELAY 2000
#define PARAR 0
#define FRENTE 1
#define ATRAS 2
#define ESQUERDA 3
#define DIREITA 4
#define SOUND_SPEED_IN_AIR 346.3
#define MIN_DISTANCE 12
#define MEASURING_RANGE_TIME 1000
#define ROTATE_RANGE_TIME 2000
#define ID 2
#define CHAIN_LIMIT 2
#define CHAIN_LOOP false
#define LIGHT_LEDS 2
#define CAMERA 3
#define ENGINE_RIGHT_REVERSE 4
#define ENGINE_RIGHT 5
#define ULTRASOUND_SENSOR_ECHO 6
#define ULTRASOUND_SENSOR_TRIGGER 7
#define ENGINE_LEFT_REVERSE 8
#define ENGINE_LEFT 9
#define ENGINE_PAINEL_SOLAR 10
#define ENGINE_PAINEL_SOLAR_REVERSE 11
#define HEATER_LED 12
#define POWER_LED 13
#define LIGHT_SENSOR A0
#define TMP_SENSOR A1
#define GAS_SENSOR A2
#define DEBUG true
bool robot_power = false;
bool robot_power_off_tmp = false;
bool robot_power_on_tmp = false;
bool heater_led_status = false;
bool light_led_status = false;
int temp_signal;
int gas_signal;
int light_signal;
bool open_solar_painel = false;
bool opening_painel_solar = false;
bool closing_painel_solar = false;
unsigned long start_func_painel_solar = 2592000000;
float specifit_painel_case_multiplier = 1;
Servo camera;
int camera_signal = 0;
bool robot_auto_move = true;
int robot_direction = 1;
unsigned long start_move_time = 0;
unsigned long last_move_time = 0;
bool robot_return = false;
unsigned long last_time_distance_calc = 0;
int speed_signal = 0;
void SendTo(int to, int code, int message);
void Receive();
void HandleData(int code, int message);
bool CheckObstacles();
void Translate(int robot_direction);
void SendTo(int to, int code, int message){if (to < 0) return;if (to > CHAIN_LIMIT) return;if ((!CHAIN_LOOP) and ((to < ID) and (to != 0))) return;if (to == ID) return;if ((code < 0) or (code >99)) return;if ((message < 0) or (message >1023)) return;
  unsigned long _buffer;_buffer = (unsigned long) message;_buffer += (code * 10000UL);_buffer += (to * 1000000UL);_buffer += (ID * 10000000UL);Serial.print(_buffer);if(DEBUG) Serial.println("");
  if(DEBUG){Serial.print("[SEND]: ");Serial.print(message);Serial.print(" to [");Serial.print(to);Serial.print("] with code <");Serial.print(code);Serial.print("> in ");Serial.print(millis());Serial.println("ms.");}}
void Receive(){unsigned long _buffer = (unsigned long) (Serial.readString().toInt());
  if ((_buffer < 12000000) or (((CHAIN_LOOP) and (_buffer > 98991023)) or ((!CHAIN_LOOP) and (_buffer > 89991023)))) return;
  int _from = (int) (_buffer / 10000000UL);int _to = (int) ((_buffer / 1000000UL) % 10);int _code = (int) ((_buffer / 10000UL) % 100);int _message = (int) (_buffer % 10000UL);
  if(((!CHAIN_LOOP) and (_from != ID - 1)) or ((CHAIN_LOOP) and ((_from != ID - 1) or (_from == CHAIN_LIMIT)))) return;if (_to != ID)
  {if ((!CHAIN_LOOP) and ((_to < ID) and (_to != 0))) return;if (_to <= CHAIN_LIMIT) SendTo(_to, _code, _message);if (_to != 0) return;}
  if(DEBUG){Serial.print("[RECEIVED]: ");Serial.print(_message);Serial.print(" from [");Serial.print(_from);Serial.print("] with code <");Serial.print(_code);Serial.print("> in ");Serial.print(millis());Serial.println("ms.");}
  HandleData(_code, _message);}
bool CheckObstacles(){digitalWrite(ULTRASOUND_SENSOR_TRIGGER, HIGH);delayMicroseconds(10);digitalWrite(ULTRASOUND_SENSOR_TRIGGER, LOW);
  unsigned long timer = pulseIn(ULTRASOUND_SENSOR_ECHO, HIGH);float distance = (timer * (SOUND_SPEED_IN_AIR / 100.0)) / 2.0;last_time_distance_calc = millis();if (distance <= MIN_DISTANCE) return true; else return false;}
void Translate(int robot_direction){
  switch(robot_direction){
    case PARAR:digitalWrite(ENGINE_RIGHT, LOW);digitalWrite(ENGINE_RIGHT_REVERSE, LOW);digitalWrite(ENGINE_LEFT, LOW);digitalWrite(ENGINE_LEFT_REVERSE, LOW);break;
    case FRENTE:digitalWrite(ENGINE_RIGHT, HIGH);digitalWrite(ENGINE_RIGHT_REVERSE, LOW);digitalWrite(ENGINE_LEFT, HIGH);digitalWrite(ENGINE_LEFT_REVERSE, LOW);break;
    case ATRAS:digitalWrite(ENGINE_RIGHT, LOW);digitalWrite(ENGINE_RIGHT_REVERSE, HIGH);digitalWrite(ENGINE_LEFT, LOW);digitalWrite(ENGINE_LEFT_REVERSE, HIGH);break;
    case ESQUERDA:digitalWrite(ENGINE_RIGHT, HIGH);digitalWrite(ENGINE_RIGHT_REVERSE, LOW);digitalWrite(ENGINE_LEFT, LOW);digitalWrite(ENGINE_LEFT_REVERSE, HIGH);break;
    case DIREITA:digitalWrite(ENGINE_RIGHT, LOW);digitalWrite(ENGINE_RIGHT_REVERSE, HIGH);digitalWrite(ENGINE_LEFT, HIGH);digitalWrite(ENGINE_LEFT_REVERSE, LOW);break;                                                                                                                                      //
    default:return;}start_move_time = millis();}
void loop(){
  bool _robot_power = robot_power;int _temp_signal = temp_signal;int _gas_signal = gas_signal;int _light_signal = light_signal;int _camera_signal = camera_signal;int _robot_direction = robot_direction;                                                                                                         //
  if (Serial.available() > 0) Receive();_temp_signal = analogRead(TMP_SENSOR);_gas_signal = analogRead(GAS_SENSOR);_light_signal = analogRead(LIGHT_SENSOR);
  if (_light_signal != light_signal){light_signal = _light_signal;if(light_signal > 100){digitalWrite(LIGHT_LEDS, HIGH);light_led_status = true;
      if (opening_painel_solar){opening_painel_solar = false;closing_painel_solar = true;
        specifit_painel_case_multiplier = 1 - (((start_func_painel_solar + PAINEL_SOLAR_FUNC_DELAY) - millis()) / PAINEL_SOLAR_FUNC_DELAY);start_func_painel_solar = millis();}
      if ((open_solar_painel) and (!closing_painel_solar)){closing_painel_solar = true;specifit_painel_case_multiplier = 1;start_func_painel_solar = millis();}}else {digitalWrite(LIGHT_LEDS, LOW);light_led_status = false;
      if (closing_painel_solar){closing_painel_solar = false;opening_painel_solar = true;
        specifit_painel_case_multiplier = 1 - (((start_func_painel_solar + PAINEL_SOLAR_FUNC_DELAY) - millis()) / PAINEL_SOLAR_FUNC_DELAY); start_func_painel_solar = millis();}
      if ((!open_solar_painel) and (!opening_painel_solar)){opening_painel_solar = true;specifit_painel_case_multiplier = 1;start_func_painel_solar = millis();                                                                                                       //
      }}}if ((specifit_painel_case_multiplier > 1) or (specifit_painel_case_multiplier < 0)) specifit_painel_case_multiplier = 1;
  if (temp_signal != _temp_signal){temp_signal = _temp_signal;float temperature = ((temp_signal * (5000.0 / 1024.0)) - 500) / 10.0;
    if (temperature > 100) {digitalWrite(HEATER_LED, LOW);robot_power_off_tmp = true;}else if (temperature < 0){digitalWrite(HEATER_LED, HIGH);heater_led_status = true;robot_power_on_tmp = true;}else { digitalWrite(HEATER_LED, LOW); robot_power_off_tmp = false; robot_power_on_tmp = false; }}
  if (_gas_signal != gas_signal){gas_signal = _gas_signal;int gas_percent = map(gas_signal, 300, 800, 0, 100);if(gas_percent > GAS_PERCENT_ERR) ;}
  if(((robot_power) or (robot_power_on_tmp)) and (!robot_power_off_tmp)){digitalWrite(POWER_LED, HIGH);digitalWrite(HEATER_LED, (bool) heater_led_status);digitalWrite(LIGHT_LEDS, (bool) light_led_status);
    if (_camera_signal != camera_signal){int angle = map(camera_signal, 0, 1023, 0, 180);Serial.println(angle);camera.write(angle);}
    if (_robot_direction != robot_direction){if (_robot_direction == FRENTE) last_move_time = millis() - start_move_time;else last_move_time = 0;Translate(robot_direction);_robot_direction = robot_direction;}
    switch (robot_direction){
      case FRENTE:if (millis() >= (last_time_distance_calc + MEASURING_RANGE_TIME)){if (CheckObstacles()){if (robot_auto_move) robot_direction = ESQUERDA;else robot_direction = PARAR;}}break;
      case ATRAS:if (robot_auto_move) { robot_direction = FRENTE; last_time_distance_calc = millis() - MEASURING_RANGE_TIME; break; }if (millis() >= (start_move_time + last_move_time)){robot_direction = PARAR;}break;
      case ESQUERDA:if (millis() >= (start_move_time + ROTATE_RANGE_TIME)){if ((robot_auto_move) and (CheckObstacles())) robot_direction = DIREITA;
          else if ((robot_auto_move) and (!CheckObstacles())){robot_direction = FRENTE;last_time_distance_calc = millis() - MEASURING_RANGE_TIME;}else robot_direction = PARAR;}
        break;
      case DIREITA:if(!robot_auto_move) { if (millis() >= (start_move_time + ROTATE_RANGE_TIME)) robot_direction = PARAR; }else {int turns = robot_return ? 1 : 2;                                                                                                     //
            if (millis() >= (start_move_time + (turns * ROTATE_RANGE_TIME))){if ((!robot_return) and (CheckObstacles())) { robot_direction = DIREITA; robot_return = true; }else if ((!robot_return) and (!CheckObstacles())){robot_direction = FRENTE;last_time_distance_calc = millis() - MEASURING_RANGE_TIME;}else if ((robot_return) and (CheckObstacles())) { robot_direction = FRENTE; robot_return = false; }else{robot_power = false;robot_return = PARAR;}}}
        break;
      case PARAR: if (robot_auto_move) { robot_direction = FRENTE; last_time_distance_calc = millis() - MEASURING_RANGE_TIME; } break;                                                                                                                                    //
      default: robot_direction = PARAR; break;
    }
    if (_robot_direction != robot_direction){if (_robot_direction == FRENTE) last_move_time = millis() - start_move_time; else last_move_time = 0; Translate(robot_direction); } 
    if(opening_painel_solar) {
      digitalWrite(ENGINE_PAINEL_SOLAR, HIGH);digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);
      if(millis() >= (start_func_painel_solar + (specifit_painel_case_multiplier * PAINEL_SOLAR_FUNC_DELAY))) {
        opening_painel_solar = false; open_solar_painel = true;
        digitalWrite(ENGINE_PAINEL_SOLAR, LOW); digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);
      } } else if(closing_painel_solar){
       digitalWrite(ENGINE_PAINEL_SOLAR, LOW); digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, HIGH);
      if(millis() >= (start_func_painel_solar + (specifit_painel_case_multiplier * PAINEL_SOLAR_FUNC_DELAY))) { 
        closing_painel_solar = false;open_solar_painel = false;
        digitalWrite(ENGINE_PAINEL_SOLAR, LOW); digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);
      } else { digitalWrite(ENGINE_PAINEL_SOLAR, LOW); digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);
      } } } else { 
    digitalWrite(POWER_LED, LOW); heater_led_status = (bool) digitalRead(HEATER_LED); light_led_status = (bool) digitalRead(LIGHT_LEDS);
    Translate(PARAR);
    if ((open_solar_painel) and (!closing_painel_solar)) { closing_painel_solar = true;specifit_painel_case_multiplier = 1.0;start_func_painel_solar = millis(); }
    if (closing_painel_solar){
      digitalWrite(ENGINE_PAINEL_SOLAR, LOW);digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);
      if(millis() >= (start_func_painel_solar + (specifit_painel_case_multiplier * PAINEL_SOLAR_FUNC_DELAY))){
        closing_painel_solar = false;
        open_solar_painel = false;
        digitalWrite(ENGINE_PAINEL_SOLAR, LOW);digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);
      } }else{ digitalWrite(ENGINE_PAINEL_SOLAR, LOW);digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW); }
    digitalWrite(HEATER_LED, LOW);digitalWrite(LIGHT_LEDS, LOW);
    start_func_painel_solar = millis();
} }
void setup() {
  Serial.begin(9600);
  while(!Serial);
  pinMode(ULTRASOUND_SENSOR_ECHO, INPUT);
  pinMode(HEATER_LED, OUTPUT);
  pinMode(POWER_LED, OUTPUT);
  pinMode(LIGHT_LEDS, OUTPUT);
  pinMode(ENGINE_PAINEL_SOLAR, OUTPUT);
  pinMode(ENGINE_PAINEL_SOLAR_REVERSE, OUTPUT);
  pinMode(ULTRASOUND_SENSOR_TRIGGER, OUTPUT);
  pinMode(ENGINE_RIGHT_REVERSE, OUTPUT);
  pinMode(ENGINE_LEFT_REVERSE, OUTPUT);
  temp_signal = analogRead(TMP_SENSOR);
  gas_signal = analogRead(GAS_SENSOR);
  light_signal = analogRead(LIGHT_SENSOR);
  float temperature = ((temp_signal * (5000.0 / 1024.0)) - 500) / 10.0;
  if(temperature > 100){ robot_power = false; digitalWrite(HEATER_LED, LOW); robot_power_off_tmp = true; }
  else if(temperature < 0){ robot_power = true; digitalWrite(HEATER_LED, HIGH); heater_led_status = true; robot_power_on_tmp = true; }
  else{ digitalWrite(HEATER_LED, LOW); robot_power_off_tmp = false; robot_power_on_tmp = false; }
  if(light_signal > 100) {
    digitalWrite(LIGHT_LEDS, HIGH);
    opening_painel_solar = false;
    closing_painel_solar = true;
    start_func_painel_solar = millis();
  } else {
    digitalWrite(LIGHT_LEDS, LOW);
    opening_painel_solar = true;
    closing_painel_solar = false;
    start_func_painel_solar = millis(); }
  camera.attach(CAMERA);
  heater_led_status = (bool) digitalRead(HEATER_LED);
  light_led_status = (bool) digitalRead(LIGHT_LEDS);
  digitalWrite(ULTRASOUND_SENSOR_TRIGGER, LOW);
  analogWrite(ENGINE_RIGHT, 0);
  digitalWrite(ENGINE_RIGHT_REVERSE, LOW);
  analogWrite(ENGINE_LEFT, 0);
  digitalWrite(ENGINE_LEFT_REVERSE, LOW);
  digitalWrite(ENGINE_PAINEL_SOLAR, LOW);
  digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);
}
void HandleData(int code, int message) {
  switch(code) {
    case 0: robot_power = (bool) message; break;
    case 1: camera_signal = message; break; 
} }
