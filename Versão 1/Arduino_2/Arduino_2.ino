/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições globais de Configuração da Placa.                                                                                                */
//  Representa o ID da placa no contexto. O valor pode adotar qualqer número entre 1 e 9.                                                         //
#define ID 2                                                                                                                                      //
//  Configura o ID do último arduino utilizado na cadeia. Isso evita repassar mensagens para o arduino na sequência.                              //
//    Essa configuração não está presente no Arduino de ID 1, pois, ele não possuí a função de recebimento de dados.                              //
#define CHAIN_LIMIT 4                                                                                                                             //
//  Determina que os arduinos estão ligados em loop. Marque isso se você quiser enviar do Arduino de ID 'CHAIN_LIMIT' para um de ID inferior.     //
//    Caso 'true' ativa a fução; caso 'false' desativa.                                                                                           //
//  !~~! O SISTEMA DE CHAIN_LOOP NÃO ESTÁ FUNCIONANDO DEVIDAMENTE, RECOMENDA-SE NÃO UTILIZÁ-LO.                                                   //
#define CHAIN_LOOP false                                                                                                                          //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições locais de Configuração da Placa.                                                                                                 */
//  Porta responsável pela comunicação com o servo de rotação da câmera.                                                                          //
//    Uso de saída de informações via PWM.                                                                                                        //
#define CAMERA 5                                                                                                                                  //
//  Porta responsável pela iluminação frontal do robo.                                                                                            //
#define LIGHT_LEDS 3                                                                                                                              //
//  Porta responsável pelo led que indica o funcionamento do aquecedor interno do robo.                                                           //
#define HEATER_LED 6                                                                                                                              //
//  Porta de entrada de informação via sensor de luminosidade ambiente.                                                                           //
#define ENVIRONMENT_LIGHT_SENSOR 13                                                                                                               //
//  Porta de entrada de informação via sensor de temperatura.                                                                                     //
#define TMP_SENSOR A0                                                                                                                             //
//  Porta de entrada de informação via sensor de gás.                                                                                             //
#define GAS_SENSOR A1                                                                                                                             //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições de Configuração do código.                                                                                                       */
//  Configuração do modo de Debug. Caso 'true' ativa; caso 'false' desativa.                                                                      //
//    O Debug exibe no Monitor Serial as execuções. Como resultado, ele envia essas mensagens para o próximo arduino que as ignora, contudo,      //
//    isso pode gerar interferência, então, evite mantê-lo ativado.                                                                               //
//  !~~! O DEBUG PROVOCA UM ATRAZO NO FUNCIONAMENTO DO CÓDIGO, ALÉM DE POSSIVEIS PERDAS DE INFORMAÇÃO. PORTANTO, EVITE UTILIZA-LO FUNCIONALMENTE. //
#define DEBUG true                                                                                                                                //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Inicializa as variáveis de estado do sistema.                                                                                               */
//  Informa se o robo está ligado ou desligado. Por padrão, é essa variável que define o estado dos dois arduinos. Porém, por conta de possiveis  //
//  erros operacionais é possível que o sistema do arduino 3 desligue, enquanto o do arduino 2 continue funcionando. Nesse caso, é necessário re- //
//  -iniciar o Arduino-2 a partir do Arduino-1. Essa situação específica será alertada no LCD do Arduino-4 como um erro.                          //
//      Por padrão, o arduino inicializa desligado, sendo necessária interferência do Arduino-1 para ligá-lo.                                     //
bool power_on = false;                                                                                                                            //
//  Informa o ângulo de rotação da câmera.                                                                                                        //
int cam_rotation_angle = 90;                                                                                                                      //
//  Informa o novo ângulo de rotação da câmera.                                                                                                   //
int new_cam_rotation_angle = cam_rotation_angle;                                                                                                  //
//  Informa se esta claro ou escuro.                                                                                                              //
bool environment_daytime = false;                                                                                                                 //
//  Informa a temperatura atual.                                                                                                                  //
float temperature = 0;                                                                                                                            //
//  Informa a presença e quantidade percentual de gás.                                                                                            //
int gas_sensor = 0;                                                                                                                               //
//  Salva o estado dos leds quando o robo for desligado.                                                                                          //
bool backup_light_led = false;                                                                                                                    //
bool backup_heater_led = false;                                                                                                                   //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Inicializa as funções de comunicação I2C.                                                                                                   */
//  Função responsável por enviar mensagens ao próximo arduino.                                                                                   //
//        ~ 'to': ID do arduino de destino da mensagem. Caso o valor de 'to' seja '0' ele faz o envio a todos os arduinos.                        //
//        ~ 'code': Código da função da mensagem enviada. Pode assumir valores de 0 a 99.                                                         //
//        ~ 'message': Mensagem propriamente dita.                                                                                                //
void SendTo(int to, int code, int message);                                                                                                       //
//  Função responsável por receber as mensagens enviadas pelos demais arduinos.                                                                   //
void Receive();                                                                                                                                   //
//  Função responsável pelo tratamento dos dados recebido de outro arduino.                                                                       //
//        ~ 'code': Código da função da mensagem recebida. Simboliza o que a função HandleData deve fazer com a mensagem.                         //
//        ~ 'message': Mensagem recebida para ser interpretada.                                                                                   //
void HandleData(int code, int message);                                                                                                           //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Inicializa as funções de leitura dos sensores.                                                                                              */
//  Faz a leitura da temperatura registrada no sensor TMP36.                                                                                      //
//        ~ return: retorna a temperatura na escala Celsius.                                                                                      //
float Temperature();                                                                                                                              //
//  Faz a leitura de presensa de gás registrada no sensor responsável.                                                                            //
//        ~ return: retorna o percentual de gás encontrado.                                                                                       //
int Gas();                                                                                                                                        //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Faz a leitura da temperatura registrada no sensor TMP36.                                                                                    */
float Temperature()                                                                                                                               //
{                                                                                                                                                 //
  return ((analogRead(TMP_SENSOR) * (5000.0/1024.0)) - 500) / 10.0;                                                                               //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Faz a leitura de presensa de gás registrada no sensor responsável.                                                                          */
int Gas()                                                                                                                                         //
{                                                                                                                                                 //
  return map(analogRead(GAS_SENSOR), 300, 750, 0, 100);                                                                                           //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função responsável por enviar mensagens ao próximo arduino.                                                                                 */
void SendTo(int to, int code, int message)                                                                                                        //
{                                                                                                                                                 //
  //  ~ Ignora valores negativos para 'to'.                                                                                                       //
  if (to < 0) return;                                                                                                                             //
  //  ~ Caso o destino possua uma ID superior ao limite, ele intercepta a mensagem e a ignora, pois não existe um destino válido para ela.        //
  if (to > CHAIN_LIMIT) return;                                                                                                                   //
  //  ~ Caso o sistema de loop esteja desligado ele intercepta e ignora o retorno das mensagens.                                                  //
  if ((!CHAIN_LOOP) and ((to < ID) and (to != 0))) return;                                                                                        //
  //  ~ Evita o envio de uma mensagem para ele mesmo.                                                                                             //
  if (to == ID) return;                                                                                                                           //
  //  ~ O valor do 'code' é limitado entre 0 e 99, portanto, ele ignora valores diferentes para 'code'.                                           //
  if ((code < 0) or (code >99)) return;                                                                                                           //
  //  ~ O valor da mensagem pode variar entre 0 e 1023, então, ele ignora valores negativos ou superiores a 1023.                                 //
  if ((message < 0) or (message >1023)) return;                                                                                                   //
                                                                                                                                                  //
  //  ~ Inicializa a variável de buffer para o envio.                                                                                             //
  unsigned long _buffer;                                                                                                                          //
  //  ~ Define o valor inicial do buffer como o valor da mensagem.                                                                                //
  // A mensagem ocupará os 4 primeiros digitos a direita do buffer. Então, o formato atual é: _buffer = mmmm.                                     //
  _buffer = (unsigned long) message;                                                                                                              //
  //  ~ Incrementa ao buffer o código da função da mensagem ('code').                                                                             //
  // O código ocupara os 2 digitos a esquerda da mensagem. Então, o formato atual é: _buffer = ccmmmm.                                            //
  _buffer += (code * 10000UL);                                                                                                                    //                                                               
  //  ~ Incrementa ao buffer o destino da mensagem.                                                                                               //
  // O destino da mensagem ocupara o digito seguinte a esquerda do código. Então, o formato atual é: _buffer = tccmmmm.                           //
  _buffer += (to * 1000000UL);                                                                                                                    //
  //  ~ Incrementa ao buffer a origem da mensagem.                                                                                                //
  // A origem, por fim, ocupará o digito a esquerda do destino, então, o formato final será: _buffer = ftccmmmm.                                  //
  _buffer += (ID * 10000000UL);                                                                                                                   //
  //  Assim, a mensagem ocupará uma quantidade de 8 digitos do long, podendo variar de 12.000.000 a 89.991.023 com o CHAIN_LOOP desativado ou     //
  // 98.991.023 com o CHAIN_LOOP ativado.                                                                                                         //
                                                                                                                                                  //
  //  ~ Por fim, faz o envio da mensagem.                                                                                                         //
  Serial.print(_buffer);                                                                                                                          //
  if(DEBUG) Serial.println("");                                                                                                                   //
                                                                                                                                                  //
  //  ~ Se o modo de debug estiver habilitado, ele realiza o debug da mensagem.                                                                   //
  if(DEBUG)                                                                                                                                       //
  {                                                                                                                                               //
    Serial.print("[SEND]: ");                                                                                                                     //
    Serial.print(message);                                                                                                                        //
    Serial.print(" to [");                                                                                                                        //
    Serial.print(to);                                                                                                                             //
    Serial.print("] with code <");                                                                                                                //
    Serial.print(code);                                                                                                                           //
    Serial.print("> in ");                                                                                                                        //
    Serial.print(millis());                                                                                                                       //
    Serial.println("ms.");                                                                                                                        //
  }                                                                                                                                               //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função responsável por receber as mensagens enviadas pelos demais arduinos.                                                                 */
void Receive()                                                                                                                                    //
{                                                                                                                                                 //
  //  ~ Faz a leitura da mensagem recebida.                                                                                                       //
  unsigned long _buffer = (unsigned long) (Serial.readString().toInt());                                                                          //
                                                                                                                                                  //
  //  ~ Verifica a validade da mensagem recebida (se ela possui ou não um valor dentro dos limites do buffer).                                    //
  if ((_buffer < 12000000) or (((CHAIN_LOOP) and (_buffer > 98991023)) or ((!CHAIN_LOOP) and (_buffer > 89991023)))) return;                      //
                                                                                                                                                  //
  //  ~ Recupera do buffer os valores de 'from', 'to', 'code' e 'message'.                                                                        //
  // A ordem de remoção pouco importa, porém, o código fará isso na ordem inversa a utilizada na construção do buffer de envio.                   //
  //  ~ Recupera do buffer o ID do Arduino de origem ('from').                                                                                    //
  int _from = (int) (_buffer / 10000000UL);                                                                                                       //
  //  ~ Recupera do buffer o ID do Arduino de destino ('to').                                                                                     //
  int _to = (int) ((_buffer / 1000000UL) % 10);                                                                                                   //
  //  ~ Recupera do buffer o código da função da mensagem ('code').                                                                               //
  int _code = (int) ((_buffer / 10000UL) % 100);                                                                                                  //
  //  ~ Recupera do buffer a mensagem recebida ('message').                                                                                       //
  int _message = (int) (_buffer % 10000UL);                                                                                                       //
                                                                                                                                                  //
  //  ~ Verifica se o arduino de origem é o anterior a este. Isso evita o desemparelhamento das mensagens, pois, ignora possiveis erros. Caso a   //
  // CHAIN_LOOP esteja ativa ele permite o envio do Arduino de ID CHAIN_LIMIT para um Arduino de ID inferior.                                     //
  if(((!CHAIN_LOOP) and (_from != ID - 1)) or ((CHAIN_LOOP) and ((_from != ID - 1) or (_from == CHAIN_LIMIT)))) return;                           //
  //  ~ Verifica se o destino da mensagem é diferente do ID do Arduino atual. Caso for, faz a análise para o reenvio da mensagem na cadeia.       //
  if (_to != ID)                                                                                                                                  //
  {                                                                                                                                               //
    //  ~ Caso o CHAIN_LOOP esteja desligado, ele ignora destinos anteriores na cadeia.                                                           //
    if ((!CHAIN_LOOP) and ((_to < ID) and (_to != 0))) return;                                                                                    //
    //  ~ Repassa a mensagem para o próximo arduino. Ele sempre irá ignorar mensagens que ultrapassem o limite da cadeia.                         //
    if (_to <= CHAIN_LIMIT) SendTo(_to, _code, _message);                                                                                         //
    //  ~ Se não for para interpretar a mensagem, ignora.                                                                                         //
    if (_to != 0) return;                                                                                                                         //
  }                                                                                                                                               //
  //  ~ Se a função de debug estiver ativa, faz o debug da mensagem.                                                                              //
  if(DEBUG)                                                                                                                                       //
  {                                                                                                                                               //
    Serial.print("[RECEIVED]: ");                                                                                                                 //
    Serial.print(_message);                                                                                                                       //
    Serial.print(" from [");                                                                                                                      //
    Serial.print(_from);                                                                                                                          //
    Serial.print("] with code <");                                                                                                                //
    Serial.print(_code);                                                                                                                          //
    Serial.print("> in ");                                                                                                                        //
    Serial.print(millis());                                                                                                                       //
    Serial.println("ms.");                                                                                                                        //
  }                                                                                                                                               //
  //  ~ Envia o código para o tratamento dos dados recebidos.                                                                                     //
  HandleData(_code, _message);                                                                                                                    //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função do loop principal do sistema.                                                                                                        */
void loop()                                                                                                                                       //
{                                                                                                                                                 //
  //  ~ Define as variaveis de estado locais para fazer a validação de alteração.                                                                 //
  bool _power_on = power_on;                                                                                                                      //
  bool _environment_daytime = environment_daytime;                                                                                                //
  float _temperature = temperature;                                                                                                               //
  int _gas_sensor = gas_sensor;                                                                                                                   //
                                                                                                                                                  //
  //  ~ Verifica atualizações de entrada de dados.                                                                                                //
  if (Serial.available() > 0) Receive();                                                                                                          //
                                                                                                                                                  //
  //  ~ Realiza alterações na medição da temperatura.                                                                                             //
  temperature = Temperature();                                                                                                                    //
  //  ~ Realiza alterações na medição de gás.                                                                                                     //
  gas_sensor = Gas();                                                                                                                             //
                                                                                                                                                  //
  //  ~ Verifica mudança de medição da temperatura.                                                                                               //
  if (_temperature != temperature)                                                                                                                //
  {                                                                                                                                               //
    //  ~ Se a temperatura medida for maior do que 100°C, ele desliga o robo.                                                                     //
    if (temperature > 100) { power_on = false; digitalWrite(HEATER_LED, LOW); }                                                                   //
    else if (temperature < 0) { power_on = true; digitalWrite(HEATER_LED, HIGH); }                                                                //
    else digitalWrite(HEATER_LED, LOW);                                                                                                           //
    //  ~ Envia para a central de controle a alteração de temperatura.                                                                            //
    SendTo(3, 5, map((int) temperature, -50, 150, 300, 500));                                                                                     //
  }                                                                                                                                               //
  //  ~ Verifica mudanças no sensor de gás.                                                                                                       //
  if (_gas_sensor != gas_sensor)                                                                                                                  //
  {                                                                                                                                               //
    //  ~ Verifica a existência de gás. Caso exista, informa a central de comando.                                                                //
    if (gas_sensor > 0)                                                                                                                           //
      SendTo(3, 6, map(gas_sensor, 0, 100, 400, 500));                                                                                            //
    else                                                                                                                                          //
      SendTo(3, 6, 0);                                                                                                                            //
  }                                                                                                                                               //

  //  ~ Verifica alterações de estado do robo.                                                                                                    //
  if (_power_on != power_on)                                                                                                                      //
  {                                                                                                                                               //
    //  ~ Trava o sistema por alguns milissegundos.                                                                                               //
    delay(300);                                                                                                                                   //
    //  ~ Se o robo tiver que ligar.                                                                                                              //
    if (power_on)                                                                                                                                 //
    {                                                                                                                                             //
      //  ~ Liga o sistema de motores.                                                                                                            //
      SendTo(3, 4, (int) power_on);                                                                                                               //
      //  ~ Recupera o estado dos leds do robo.                                                                                                   //
      digitalWrite(LIGHT_LEDS, (int) backup_light_led);                                                                                           //
      digitalWrite(HEATER_LED, (int) backup_heater_led);                                                                                          //
    }                                                                                                                                             //
    //  ~ Se o robo tiver que desligar.                                                                                                           //
    else                                                                                                                                          //
    {                                                                                                                                             //
      //  ~ Desliga o sistema de motores.                                                                                                         //
      SendTo(3, 4, (int) power_on);                                                                                                               //
      //  ~ Salva o estado dos leds.                                                                                                              //
      backup_light_led = digitalRead(LIGHT_LEDS);                                                                                                 //
      backup_heater_led = digitalRead(HEATER_LED);                                                                                                //
      //  ~ Desliga as luzes.                                                                                                                     //
      digitalWrite(LIGHT_LEDS, LOW);                                                                                                              //
      digitalWrite(HEATER_LED, LOW);                                                                                                              //
    }                                                                                                                                             //
  }                                                                                                                                               //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função inicial do código.                                                                                                                   */
void setup()                                                                                                                                      //
{                                                                                                                                                 //
  //  ~ Inicializa o sistema Serial com uma taxa de atualização de 9600 bits por segundo (equivalente a 1200 Bytes por segundo).                  //
  Serial.begin(9600);                                                                                                                             //
  //  ~ Faz o arduino aguardar a inicialização da comunicação Serial antes de prosseguir.                                                         //
  while(!Serial);                                                                                                                                 //
                                                                                                                                                  //
  //  ~ Define os pinos de entrada digital como modo 'INPUT'.                                                                                     //
  //  ~ Porta de entrada do sensor de luz ambiente.                                                                                               //
  pinMode(ENVIRONMENT_LIGHT_SENSOR, INPUT);                                                                                                       //
                                                                                                                                                  //
  //  ~ Define os pinos de saída digital como modo 'OUTPUT'.                                                                                      //
  //  ~ Porta de saída para os leds de iluminação frontal.                                                                                        //
  pinMode(LIGHT_LEDS, OUTPUT);                                                                                                                    //
  //  ~ Porta de saída para o led que indica o funcionamento do aquecedor.                                                                        //
  pinMode(HEATER_LED, OUTPUT);                                                                                                                    //
                                                                                                                                                  //
  //  ~ Altera a temperatura registrada na variável para aquela registrada no sensor.                                                             //
  temperature = Temperature();                                                                                                                    //
  //  ~ Altera o percentual de gás ambiente encontrado para aquele registrado no sensor.                                                          //
  gas_sensor = Gas();                                                                                                                             //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função responsável pelo tratamento dos dados recebido de outro arduino.                                                                     */
void HandleData(int code, int message)                                                                                                            //
{                                                                                                                                                 //
  //  ~ Verifica o que deve fazer com a mensagem recebida baseando-se no código de função que foi recebido junto dela.                            //
  switch(code)                                                                                                                                    //
  {                                                                                                                                               //
    //  ~ Informa o arduino que deve "reiniciar" (desliga se estiver ligado e liga se estiver desligado.                                          //
    case 0:                                                                                                                                       //
      //  ~ Alterna o status de ligado e desligado do sistema.                                                                                    //
      power_on = !power_on;                                                                                                                       //
      break;                                                                                                                                      //
    //  ~ Realiza alterações relacionadas a câmera.                                                                                               //
    case 3:                                                                                                                                       //
      break;                                                                                                                                      //
  }                                                                                                                                               //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
