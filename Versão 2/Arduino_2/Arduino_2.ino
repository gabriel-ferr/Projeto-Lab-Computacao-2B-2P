/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Defiições das configurações do robo.                                                                                                        */
//  Define o percentual de erro do sensor de gás.                                                                                                 //
#define GAS_PERCENT_ERR 5                                                                                                                         //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições globais de Configuração da Placa.                                                                                                */
//  Representa o ID da placa no contexto. O valor pode adotar qualqer número entre 1 e 9.                                                         //
#define ID 2                                                                                                                                      //
//  Configura o ID do último arduino utilizado na cadeia. Isso evita repassar mensagens para o arduino na sequência.                              //
//    Essa configuração não está presente no Arduino de ID 1, pois, ele não possuí a função de recebimento de dados.                              //
#define CHAIN_LIMIT 2                                                                                                                             //
//  Determina que os arduinos estão ligados em loop. Marque isso se você quiser enviar do Arduino de ID 'CHAIN_LIMIT' para um de ID inferior.     //
//    Caso 'true' ativa a fução; caso 'false' desativa.                                                                                           //
//  !~~! O SISTEMA DE CHAIN_LOOP NÃO ESTÁ FUNCIONANDO DEVIDAMENTE, RECOMENDA-SE NÃO UTILIZÁ-LO.                                                   //
#define CHAIN_LOOP false                                                                                                                          //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições locais de Configuração da Placa (PORTAS).                                                                                        */
//  Porta responsável pelo LED das luzes frontais do robo.                                                                                        //
#define LIGHT_LEDS 2                                                                                                                              //
//  Porta responsável pelo LED que indica o funcionamento do aquecedor.                                                                           //
#define HEATER_LED 12                                                                                                                             //
//  Porta responsável pelo LED que indica o funcionamento do robo.                                                                                //
#define POWER_LED 13                                                                                                                              //
//  Porta responsável pelo sensor de luz ambiente.                                                                                                //
#define LIGHT_SENSOR A0                                                                                                                           //
//  Porta responsável pelo sensor TMP36.                                                                                                          //
#define TMP_SENSOR A1                                                                                                                             //
//  Porta responsável pelo sensor de Gás.                                                                                                         //
#define GAS_SENSOR A2                                                                                                                             //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições de Configuração do código.                                                                                                       */
//  Configuração do modo de Debug. Caso 'true' ativa; caso 'false' desativa.                                                                      //
//    O Debug exibe no Monitor Serial as execuções. Como resultado, ele envia essas mensagens para o próximo arduino que as ignora, contudo,      //
//    isso pode gerar interferência, então, evite mantê-lo ativado.                                                                               //
//  !~~! O DEBUG PROVOCA UM ATRAZO NO FUNCIONAMENTO DO CÓDIGO, ALÉM DE POSSIVEIS PERDAS DE INFORMAÇÃO. PORTANTO, EVITE UTILIZA-LO FUNCIONALMENTE. //
#define DEBUG true                                                                                                                                //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Variáveis de estado utilizadas no funcionamento do código.                                                                                  */
//  Variável responsável por determinar se o robo está ligado ou desligado.                                                                       //
bool robot_power = false;                                                                                                                         //
//  Variável responsável por determinar se o robo foi desligado ou não devido a excesso de temperatura.                                           //
bool robot_power_off_tmp = false;                                                                                                                 //
//  Variável responsável por determinar se o robo foi ligado ou não devido a falta de temperatura.                                                //
bool robot_power_on_tmp = false;                                                                                                                  //
//  Estado anterior do LED de aquecimento, antes do desligamento do robo.                                                                         //
bool heater_led_status = false;                                                                                                                   //
// Estado anterior do LED que representa as luzes frontais do robo.                                                                               //
bool light_led_status = false;                                                                                                                    //
//  Variável responsável por registrar o sinal da temperatura.                                                                                    //
int temp_signal;                                                                                                                                  //
//  Variável responsável por registrar o sinal de gás.                                                                                            //
int gas_signal;                                                                                                                                   //
//  Variável responsável por registrar o sinal de luz ambiente.                                                                                   //
int light_signal;                                                                                                                                 //
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
                                                                                                                                                  //
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
  //  ~ Variaveis locais de estado para determinar alterações.                                                                                    //
  bool _robot_power = robot_power;                                                                                                                //
  int _temp_signal = temp_signal;                                                                                                                 //
  int _gas_signal = gas_signal;                                                                                                                   //
  int _light_signal = light_signal;                                                                                                               //
                                                                                                                                                  //
  //  ~ Verifica atualizações de entrada de dados.                                                                                                //
  if (Serial.available() > 0) Receive();                                                                                                          //
                                                                                                                                                  //
  //  ~ Realiza a leitura do sensor de temperatura.                                                                                               //
  _temp_signal = analogRead(TMP_SENSOR);                                                                                                          //
  //  ~ Realiza a leitura do sensor de gás.                                                                                                       //
  _gas_signal = analogRead(GAS_SENSOR);                                                                                                           //
  //  ~ Realiza a leitura do sensor de luz ambiente.                                                                                              //
  _light_signal = analogRead(LIGHT_SENSOR);                                                                                                       //
                                                                                                                                                  //
  //  ~ Verifica alterações de luz ambiente.                                                                                                      //
  if (_light_signal != light_signal)                                                                                                              //
  {                                                                                                                                               //
    //  ~ Seta a alteração de sinal.                                                                                                              //
    light_signal = _light_signal;                                                                                                                 //
    //  ~ Se o sinal for maior do que 100, está escuro.                                                                                           //
    if(light_signal > 100)                                                                                                                        //
    {                                                                                                                                             //
      //  ~ Faz a função de acender as luzes.                                                                                                     //
      digitalWrite(LIGHT_LEDS, HIGH);                                                                                                             //
      light_led_status = true;                                                                                                                    //
      //  ~ Fecha o painel solar.                                                                                                                 //
      //  [FUNC HERE]
    }                                                                                                                                             //
    else                                                                                                                                          //
    {                                                                                                                                             //
      //  ~ Faz a função de apagar as luzes.                                                                                                      //
      digitalWrite(LIGHT_LEDS, LOW);                                                                                                              //
      light_led_status = false;                                                                                                                   //
      //  ~ Abre o painel solar.                                                                                                                  //
      //  [FUNC HERE]
    }                                                                                                                                             //
  }                                                                                                                                               //
                                                                                                                                                  //
  //  ~ Verifica alterações no sinal de temperatura.                                                                                              //
  if (temp_signal != _temp_signal)                                                                                                                //
  {                                                                                                                                               //
    //  ~ Seta a alteração de sinal.                                                                                                              //
    temp_signal = _temp_signal;                                                                                                                   //
    //  ~ Calcula a nova temperatura.                                                                                                             //
    float temperature = ((temp_signal * (5000.0 / 1024.0)) - 500) / 10.0;                                                                         //
    //  ~ Verifica se o sistema deve ser desligado ou ativar o aquecimento.                                                                       //
    if (temperature > 100) {                                                                                                                      //
      digitalWrite(HEATER_LED, LOW);                                                                                                              //
      robot_power_off_tmp = true;                                                                                                                 //
    }                                                                                                                                             //
    else if (temperature < 0)                                                                                                                     //
    {                                                                                                                                             //
      digitalWrite(HEATER_LED, HIGH);                                                                                                             //
      heater_led_status = true;                                                                                                                   //
      robot_power_on_tmp = true;                                                                                                                  //
    }                                                                                                                                             //
    else { digitalWrite(HEATER_LED, LOW); robot_power_off_tmp = false; robot_power_on_tmp = false; }                                              //
    //  ~ Envia a atualização para a central de controle.                                                                                         //
    //  [SEND TO - ADD HERE]
  }                                                                                                                                               //
                                                                                                                                                  //
  //  ~ Verifica alterações no sinal de gás.                                                                                                      //
  if (_gas_signal != gas_signal)                                                                                                                  //
  {                                                                                                                                               //
    //  ~ Seta a alteração de sinal.                                                                                                              //
    gas_signal = _gas_signal;                                                                                                                     //
                                                                                                                                                  //
    //  ~ Calcula o percentual de gás.                                                                                                            //
    int gas_percent = map(gas_signal, 300, 800, 0, 100);                                                                                          //
                                                                                                                                                  //
    //  ~ Se o percentual de gás estiver acima de uma margem de erro pré-definida, ele alerta a existência.                                       //
    if(gas_percent > GAS_PERCENT_ERR) ;     //  [SEND TO - ADD HERE]
  }                                                                                                                                               //
                                                                                                                                                  //                                                                                                                                             //
  //  ~ Verifica se ocorreu alteração de estado no funcionamento do robo.                                                                         //                                                                                                                                            //
  //  ~ Verifica se o robo deve ser ligado ou desligado.                                                                                          //
  if(((robot_power) or (robot_power_on_tmp)) and (!robot_power_off_tmp))                                                                          //                                                //
  {                                                                                                                                               //
    //  ~ Acende a LED que indica que o robo está ligado.                                                                                         //
    digitalWrite(POWER_LED, HIGH);                                                                                                                //
    //  ~ Liga os leds que foram desligados.                                                                                                      //
    digitalWrite(HEATER_LED, (bool) heater_led_status);                                                                                           //
    digitalWrite(LIGHT_LEDS, (bool) light_led_status);                                                                                            //
  }                                                                                                                                               //
  else                                                                                                                                            //
  {                                                                                                                                               //
    //  ~ Apaga a LED que indica que o robo está ligado.                                                                                          //
    digitalWrite(POWER_LED, LOW);                                                                                                                 //
    //  ~ Salva o status dos leds antes de desligar.                                                                                              //
    heater_led_status = (bool) digitalRead(HEATER_LED);                                                                                           //
    light_led_status = (bool) digitalRead(LIGHT_LEDS);                                                                                            //
                                                                                                                                                  //
    //  ~ Apaga o LED que indica o funcionamento do aquecedor.                                                                                    //
    digitalWrite(HEATER_LED, LOW);                                                                                                                //
    //  ~ Apaga o LED de luz.                                                                                                                     //
    digitalWrite(LIGHT_LEDS, LOW);                                                                                                                //
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
  //  ~ Coloca as portas de modo de saída como 'OUTPUT'.                                                                                          //
  pinMode(HEATER_LED, OUTPUT);                                                                                                                    //
  pinMode(POWER_LED, OUTPUT);                                                                                                                     //
  pinMode(LIGHT_LEDS, OUTPUT);                                                                                                                    //
                                                                                                                                                  //
  //  ~ Faz a leitura padrão dos valores, para garatir sincronização.                                                                             //
  temp_signal = analogRead(TMP_SENSOR);                                                                                                           //
  gas_signal = analogRead(GAS_SENSOR);                                                                                                            //
  light_signal = analogRead(LIGHT_SENSOR);                                                                                                        //
                                                                                                                                                  //
  //  ~ Faz a validação da temperatura para alterações.                                                                                           //
  float temperature = ((temp_signal * (5000.0 / 1024.0)) - 500) / 10.0;                                                                           //
  //  ~ Verifica se o sistema deve ser desligado ou ativar o aquecimento.                                                                         //
  if (temperature > 100) { robot_power = false; digitalWrite(HEATER_LED, LOW); robot_power_off_tmp = true; }                                      //
  else if (temperature < 0) { robot_power = true; digitalWrite(HEATER_LED, HIGH); heater_led_status = true; robot_power_on_tmp = true; }          //
  else { digitalWrite(HEATER_LED, LOW); robot_power_off_tmp = false; robot_power_on_tmp = false; }                                                //
                                                                                                                                                  
  //  ~ Verifica alterações de luz ambiente.                                                                                                      //                                                                                                                                             //
  //  ~ Se o sinal for maior do que 100, está escuro.                                                                                             //
  if(light_signal > 100)                                                                                                                          //
  {                                                                                                                                               //
    //  ~ Faz a função de acender as luzes.                                                                                                       //
    digitalWrite(LIGHT_LEDS, HIGH);                                                                                                               //
    //  ~ Fecha o painel solar.                                                                                                                   //
    //  [FUNC HERE]
  }                                                                                                                                               //
  else                                                                                                                                            //
  {                                                                                                                                               //
    //  ~ Faz a função de apagar as luzes.                                                                                                        //
    digitalWrite(LIGHT_LEDS, LOW);                                                                                                                //
    //  ~ Abre o painel solar.                                                                                                                    //
    //  [FUNC HERE]
  }                                                                                                                                               //
                                                                                                                                                  //
  //  ~ Salva o status do led de aquecimento.                                                                                                     //
  heater_led_status = (bool) digitalRead(HEATER_LED);                                                                                             //
  //  ~ Salva o status das luzes frontais.                                                                                                        //  
  light_led_status = (bool) digitalRead(LIGHT_LEDS);                                                                                              //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função responsável pelo tratamento dos dados recebido de outro arduino.                                                                     */
void HandleData(int code, int message)                                                                                                            //
{                                                                                                                                                 //
  //  ~ Verifica o que deve fazer com a mensagem recebida baseando-se no código de função que foi recebido junto dela.                            //
  switch(code)                                                                                                                                    //
  {                                                                                                                                               //
    //  ~ Altera o estado do LED entre ligado e desligado conforme recebido.                                                                      //
    case 0:                                                                                                                                       //
      robot_power = (bool) message;                                                                                                               //
      break;                                                                                                                                      //
  }                                                                                                                                               //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
