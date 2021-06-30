/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Inclusões de bibliotecas externas.                                                                                                          */
#include <Servo.h>                                                                                                                                //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Defiições das configurações do robo.                                                                                                        */
//  Define o percentual de erro do sensor de gás.                                                                                                 //
#define GAS_PERCENT_ERR 5                                                                                                                         //
//  Intervalo de tempo para abertura (ou fechamento) do painel solar.                                                                             //
#define PAINEL_SOLAR_FUNC_DELAY 2000                                                                                                              //
//  Definição do valor que indica que o robo deve parar.                                                                                          //
#define PARAR 0                                                                                                                                   // 
//  Definição do valor que indica que o robo deve ir para frente.                                                                                 //
#define FRENTE 1                                                                                                                                  //
//  Definição do valor que indica que o robo deve ir para trás.                                                                                   //
#define ATRAS 2                                                                                                                                   //
//  Definição do valor que indica que o robo deve ir para a esquerda.                                                                             //
#define ESQUERDA 3                                                                                                                                //
//  Definição do valor que indica que o robo deve ir para  direita.                                                                               //
#define DIREITA 4                                                                                                                                 //
//  Porta do sensor ultrassônico, responsável por determinar a existência de objetos a frente. Porta de emissão de eco.                           //
#define ULTRASOUND_SENSOR_TRIGGER 4                                                                                                               //
//  Porta do sensor ultrassônico, responsável por determinar a existência de objetos a frente. Porta de recepção de eco.                          //
#define ULTRASOUND_SENSOR_ECHO 5                                                                                                                  //
//  Velocidade do som no ar em m/s.                                                                                                               //
//    No caso, utilizamos a velocidade do som no ar na CATP (Condições Ambientes de Temperatura e Pressão), sendo assim, uma temperatura de 25°C. //
#define SOUND_SPEED_IN_AIR 346.3                                                                                                                  //
//  Distância mínima em que o objeto deve estar para o robo executar a frenagem e trocar de sentido.                                              //
//    Deve ser inserido o valor em 'cm'.                                                                                                          //
#define MIN_DISTANCE 12                                                                                                                           //
//  Intervalo de tempo entre os quais as medidas devem ser efetuadas.                                                                             //
//    O valor informado deve estar em 'ms'.                                                                                                       //
#define MEASURING_RANGE_TIME 1000                                                                                                                 //
//  Intervalo de tempo para o robo realizar sua rotação.                                                                                          //
//    O valor informado deve estar em 'ms'.                                                                                                       //
#define ROTATE_RANGE_TIME 2000                                                                                                                    //
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
//  Porta responsável pela câmera.                                                                                                                //
#define CAMERA 3                                                                                                                                  //
//  Motor Direito, entrada reversa.                                                                                                               //
#define ENGINE_RIGHT_REVERSE 4                                                                                                                    //
//  Motor Direito, entrada padrão.                                                                                                                //
#define ENGINE_RIGHT 5                                                                                                                            //
//  Motor Esquerdo, entrada padrão.                                                                                                               //
#define ENGINE_LEFT 6                                                                                                                             //
//  Motor Esquerdo, entrada reversa.                                                                                                              //
#define ENGINE_LEFT_REVERSE 7                                                                                                                     //
//  Porta do motor de abertura (e fechamento) do painel solar.                                                                                    //
#define ENGINE_PAINEL_SOLAR 10                                                                                                                    //
//  Porta de reversão do motor de abertura (e fechamento) do painel solar.                                                                        //
#define ENGINE_PAINEL_SOLAR_REVERSE 11                                                                                                            //
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
//  Variável que indica se o painel solar está aberto ou não.                                                                                     //
bool open_solar_painel = false;                                                                                                                   //
//  Variável que indica se o painel solar está abrindo ou não.                                                                                    //
bool opening_painel_solar = false;                                                                                                                //
//  Variável que indica se o painel solar está fechando ou não.                                                                                   //
bool closing_painel_solar = false;                                                                                                                //
//  Variável que indica o instante de início de operação da abertura do painel solar.                                                             //
unsigned long start_func_painel_solar = 2592000000;                                                                                               //
//  Multiplicador de casos específicos.(1 - ((start_func_painel_solar + PAINEL_SOLAR_FUNC_DELAY) - millis()) / PAINEL_SOLAR_FUNC_DELAY))          //
float specifit_painel_case_multiplier = 1;                                                                                                        //
//  Estrutura da câmera.                                                                                                                          //
Servo camera;                                                                                                                                     //
//  Sinal de posicionamento da câmera.                                                                                                            //
int camera_signal = 0;                                                                                                                            //
//  Modo de movimentação do robo, alterna entre altomático ('true') ou manual ('false').                                                          //
//    Por padrão o robo inicializa no automático, contudo, é possível alterar essa inicialização no código do Arduino 1.                          //
bool robot_auto_move = true;                                                                                                                      //
//  Direção de movimentação do robo. 1 = frente; 2 = trás; 3 = esquerda; 4 = direita; 0 = parar.                                                  //
int robot_direction = 1;                                                                                                                          //
//  Instante em 'ms' de inicialização de alguma atividade de movimentação.                                                                        //
unsigned long start_move_time = 0;                                                                                                                //
//  Instante em 'ms' da atividade anterior executada pelo robo.                                                                                   //
unsigned long last_move_time = 0;                                                                                                                 //
//  Informa se o robo deve retroceder ou não.                                                                                                     //
bool robot_return = false;                                                                                                                        //
//  Registro da última verificação de distância.                                                                                                  //
unsigned long last_time_distance_calc = 0;                                                                                                        //
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
/*  ~ Inicializa as funções de movimentação do robo.                                                                                              */
//  Responsável por informar se há ou não um objeto na distância mínima prevista nas configurações.                                               //
bool CheckObstacles();                                                                                                                            //
//  Responsável pela movimentação própriamente dita.                                                                                              //
//      ~ 'robot_direction': direção para a qual o robo deve se dirigir.                                                                          //
void Translate(int robot_direction);                                                                                                              //
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
/*  ~ Inicializa as funções do sensor ultrassônico.                                                                                               */
bool CheckObstacles()                                                                                                                             //
{                                                                                                                                                 //
  //  ~ Envia um sinal pelo emissor Trigger do sensor ultrassônico.                                                                               //
  digitalWrite(ULTRASOUND_SENSOR_TRIGGER, HIGH);                                                                                                  //
  //  ~ O sinal deve ser enviado por pelo menos 10 microssegundos para poder ser reconhecido pelo sensor.                                         //
  delayMicroseconds(10);                                                                                                                          //
  //  ~ Interrompe o envio do sinal.                                                                                                              //
  digitalWrite(ULTRASOUND_SENSOR_TRIGGER, LOW);                                                                                                   //
                                                                                                                                                  //
  //  ~ Captura em uma variável long o tempo de retorno.                                                                                          //
  unsigned long timer = pulseIn(ULTRASOUND_SENSOR_ECHO, HIGH);                                                                                    //
                                                                                                                                                  //
  //  ~ Calcula a distância baseando-se na velocidade do som no ar.                                                                               //
  float distance = (timer * (SOUND_SPEED_IN_AIR / 100.0)) / 2.0;                                                                                  //
                                                                                                                                                  //
  //  ~ Atualiza o tempo da checagem.                                                                                                             //
  last_time_distance_calc = millis();                                                                                                             //
                                                                                                                                                  //
  //  ~ Por fim, retorna conforme a distância calculada está relacionada com o valor mínimo aceitável.                                            //
  if (distance <= MIN_DISTANCE) return true; else return false;                                                                                   //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Responsável pela movimentação própriamente dita.                                                                                            */
void Translate(int robot_direction)                                                                                                               //
{                                                                                                                                                 //
  //  ~ Verifica o tipo de movimentação de entrada.                                                                                               //
  switch(robot_direction)                                                                                                                         //
  {                                                                                                                                               //
    //  ~ Caso o robo deva parar.                                                                                                                 //
    case PARAR:                                                                                                                                   //
        //  ~ Para os motores.                                                                                                                    //
        digitalWrite(ENGINE_RIGHT, LOW);                                                                                                          //
        digitalWrite(ENGINE_RIGHT_REVERSE, LOW);                                                                                                  //
        digitalWrite(ENGINE_LEFT, LOW);                                                                                                           //
        digitalWrite(ENGINE_LEFT_REVERSE, LOW);                                                                                                   //
      break;                                                                                                                                      //
    //  ~ Caso o robo deva ir para frente.                                                                                                        //
    case FRENTE:                                                                                                                                  //
        //  ~ Para os motores.                                                                                                                    //
        digitalWrite(ENGINE_RIGHT, HIGH);                                                                                                         //
        digitalWrite(ENGINE_RIGHT_REVERSE, LOW);                                                                                                  //
        digitalWrite(ENGINE_LEFT, HIGH);                                                                                                          //
        digitalWrite(ENGINE_LEFT_REVERSE, LOW);                                                                                                   //
      break;                                                                                                                                      //
    //  ~ Caso o robo deva ir para trás.                                                                                                          //
    case ATRAS:                                                                                                                                   //
        //  ~ Para os motores.                                                                                                                    //
        digitalWrite(ENGINE_RIGHT, LOW);                                                                                                          //
        digitalWrite(ENGINE_RIGHT_REVERSE, HIGH);                                                                                                 //
        digitalWrite(ENGINE_LEFT, LOW);                                                                                                           //
        digitalWrite(ENGINE_LEFT_REVERSE, HIGH);                                                                                                  //
      break;                                                                                                                                      //
    //  ~ Caso o robo deva virar para a esquerda.                                                                                                 //
    case ESQUERDA:                                                                                                                                //
        //  ~ Para os motores.                                                                                                                    //
        digitalWrite(ENGINE_RIGHT, HIGH);                                                                                                         //
        digitalWrite(ENGINE_RIGHT_REVERSE, LOW);                                                                                                  //
        digitalWrite(ENGINE_LEFT, LOW);                                                                                                           //
        digitalWrite(ENGINE_LEFT_REVERSE, HIGH);                                                                                                  //
      break;                                                                                                                                      //
    //  ~ Caso o robo deva virar para a direita.                                                                                                  //
    case DIREITA:                                                                                                                                 //
        //  ~ Para os motores.                                                                                                                    //
        digitalWrite(ENGINE_RIGHT, LOW);                                                                                                          //
        digitalWrite(ENGINE_RIGHT_REVERSE, HIGH);                                                                                                 //
        digitalWrite(ENGINE_LEFT, HIGH);                                                                                                          //
        digitalWrite(ENGINE_LEFT_REVERSE, LOW);                                                                                                   //
      break;                                                                                                                                      //
    //  ~ Caso nenhuma delas, retorna.                                                                                                            //
    default:                                                                                                                                      //
      return;                                                                                                                                     //
  }                                                                                                                                               //
  //  ~ Define o novo tempo de inicio do movimento.                                                                                               //
  start_move_time = millis();                                                                                                                     //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função do loop principal do sistema.                                                                                                        */
void loop()                                                                                                                                       //
{                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Declaração das variáveis de estado locais, para realizar comparações pré-atualização.                                                       */
  bool _robot_power = robot_power;                                                                                                                //
  int _temp_signal = temp_signal;                                                                                                                 //
  int _gas_signal = gas_signal;                                                                                                                   //
  int _light_signal = light_signal;                                                                                                               //
  int _camera_signal = camera_signal;                                                                                                             //
  int _robot_direction = robot_direction;                                                                                                         //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Faz o recebimento e dados via Serial.                                                                                                       */
  if (Serial.available() > 0) Receive();                                                                                                          //
                                                                                                                                                  //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Atualiza os sensores locais.                                                                                                                */
  //  ~ Realiza a leitura do sensor de temperatura.                                                                                               //
  _temp_signal = analogRead(TMP_SENSOR);                                                                                                          //
  //  ~ Realiza a leitura do sensor de gás.                                                                                                       //
  _gas_signal = analogRead(GAS_SENSOR);                                                                                                           //
  //  ~ Realiza a leitura do sensor de luz ambiente.                                                                                              //
  _light_signal = analogRead(LIGHT_SENSOR);                                                                                                       //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Verifica atualizações de luz ambiente.                                                                                                      */
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
      if (opening_painel_solar)                                                                                                                   //
      {                                                                                                                                           //
        //  ~ Cancela a abertura do painel solar.                                                                                                 //
        opening_painel_solar = false;                                                                                                             //
        //  ~ Começa a fechar.                                                                                                                    //
        closing_painel_solar = true;                                                                                                              //
        //  ~ Calcula o multiplicador especial.                                                                                                   //
        specifit_painel_case_multiplier = 1 - (((start_func_painel_solar + PAINEL_SOLAR_FUNC_DELAY) - millis()) / PAINEL_SOLAR_FUNC_DELAY);       //
        //  ~ Seta um novo valor de início.                                                                                                       //
        start_func_painel_solar = millis();                                                                                                       //
      }                                                                                                                                           //
      //  ~ Se o painel solar estiver aberto, fecha ele.                                                                                          //
      if ((open_solar_painel) and (!closing_painel_solar))                                                                                        //
      {                                                                                                                                           //
        //  ~ Começa a fechar.                                                                                                                    //
        closing_painel_solar = true;                                                                                                              //
        //  ~ Define o multiplicador especial como 1.                                                                                             //
        specifit_painel_case_multiplier = 1;                                                                                                      //
        //  ~ Seta um novo valor de início.                                                                                                       //
        start_func_painel_solar = millis();                                                                                                       //
      }                                                                                                                                           //
    }                                                                                                                                             //
    else                                                                                                                                          //
    {                                                                                                                                             //
      //  ~ Faz a função de apagar as luzes.                                                                                                      //
      digitalWrite(LIGHT_LEDS, LOW);                                                                                                              //
      light_led_status = false;                                                                                                                   //
      //  ~ Abre o painel solar.                                                                                                                  //
      if (closing_painel_solar)                                                                                                                   //
      {                                                                                                                                           //
        //  ~ Cancela a abertura do painel solar.                                                                                                 //
        closing_painel_solar = false;                                                                                                             //
        //  ~ Começa a fechar.                                                                                                                    //
        opening_painel_solar = true;                                                                                                              //
        //  ~ Calcula o multiplicador especial.                                                                                                   //
        specifit_painel_case_multiplier = 1 - (((start_func_painel_solar + PAINEL_SOLAR_FUNC_DELAY) - millis()) / PAINEL_SOLAR_FUNC_DELAY);       //
        //  ~ Seta um novo valor de início.                                                                                                       //
        start_func_painel_solar = millis();                                                                                                       //
      }                                                                                                                                           //
      //  ~ Se o painel solar estiver fechado, abre ele.                                                                                          //
      if ((!open_solar_painel) and (!opening_painel_solar))                                                                                       //
      {                                                                                                                                           //
        //  ~ Começa a fechar.                                                                                                                    //
        opening_painel_solar = true;                                                                                                              //
        //  ~ Define o multiplicador especial como 1.                                                                                             //
        specifit_painel_case_multiplier = 1;                                                                                                      //
        //  ~ Seta um novo valor de início.                                                                                                       //
        start_func_painel_solar = millis();                                                                                                       //
      }                                                                                                                                           //
    }                                                                                                                                             //
  }                                                                                                                                               //
  //  ~ Corrige o fator de multiplicidade do cálculo.                                                                                             //
  if ((specifit_painel_case_multiplier > 1) or (specifit_painel_case_multiplier < 0)) specifit_painel_case_multiplier = 1;                        //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Faz verificação de temperatura ambiente.                                                                                                    */
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
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Verifica os sensores de gás ambiente.                                                                                                       */
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
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Execuções quando o robo está ligado ou em ligação forçada devido a baixa temperatura.                                                       */
  if(((robot_power) or (robot_power_on_tmp)) and (!robot_power_off_tmp))                                                                          //                                                //
  {                                                                                                                                               //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ [SUB] Faz o acionamento das LEDs do robo.                                                                                                   */
    digitalWrite(POWER_LED, HIGH);                                                                                                                //
    //  ~ Liga os leds que foram desligados.                                                                                                      //
    digitalWrite(HEATER_LED, (bool) heater_led_status);                                                                                           //
    digitalWrite(LIGHT_LEDS, (bool) light_led_status);                                                                                            //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ [SUB] Rotacionamento do servo onde a camera do robo estaria acoplada.                                                                       */
    if (_camera_signal != camera_signal)                                                                                                          //
    {                                                                                                                                             //
      //  ~ Calcula o ângulo.                                                                                                                     //
      int angle = map(camera_signal, 0, 1023, 0, 180);                                                                                            //
      Serial.println(angle);
      //  ~ Efetua a rotação.                                                                                                                     //
      camera.write(angle);                                                                                                                        //        
    }                                                                                                                                             //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ [SUB] Executa comandos de translação antes da fixação de ações locais.                                                                      */
    if (_robot_direction != robot_direction)                                                                                                      //
    {                                                                                                                                             //
      //  ~ Calcula o tempo de movimentação anterior com base no tipo da movimentação anterior.                                                   //
      if (_robot_direction == FRENTE) last_move_time = millis() - start_move_time;                                                                //
      else last_move_time = 0;                                                                                                                    //
      //  ~ Altera a direção do robo.                                                                                                             //
      Translate(robot_direction);                                                                                                                 //
      //  ~ Informa que a alteração JÁ FOI EXECUTADA.                                                                                             //
      _robot_direction = robot_direction;                                                                                                         //
      //  ~ Informa a alteração de movimento.                                                                                                     //
      //  [SEND TO - ADD HERE]
    }                                                                                                                                             //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ [SUB] Realiza as configurações e calculos locais de movimentação e permissão de translação do robo, tanto em modo automático quanto em modo //
//  manual.                                                                                                                                       */
    switch (robot_direction)                                                                                                                      //
    {                                                                                                                                             //
      //  ~ Verificações caso o robo esteja indo para a frente.                                                                                   //
      case FRENTE:                                                                                                                                //
        //  ~ Verifica se o robo deve ou não analizar a existência de um objeto a frente.                                                         //
        //  O robo apenas irá realizar a medição de distância 1 vez a cada o tempo inserido nas configurações.                                    //
        if (millis() >= (last_time_distance_calc + MEASURING_RANGE_TIME))                                                                         //
        {                                                                                                                                         //
          //  ~ Faz a verificação, caso haja um objeto a frente, realiza os procedimentos conforme a lógica proposta.                             //
          if (CheckObstacles())                                                                                                                   //
          {                                                                                                                                       //
            //  ~ Se o robo estiver no modo automático e encontrar um obstáculo, ele deverá virar a esquerda.                                     //
            //  Caso ele esteja no modo manual, ele deverá parar.                                                                                 //
            if (robot_auto_move) robot_direction = ESQUERDA;                                                                                      //
            else robot_direction = PARAR;                                                                                                         //
          }                                                                                                                                       //
        }                                                                                                                                         //
        break;                                                                                                                                    //
      //  ~ Verificações caso o robo esteja indo para trás.                                                                                       //
      case ATRAS:                                                                                                                                 //
          //  ~ Se o modo automático estiver ligado, altera para o robo seguir para a frente.                                                     //
          if (robot_auto_move) { robot_direction = FRENTE; last_time_distance_calc = millis() - MEASURING_RANGE_TIME; break; }                    //
          //  ~ Verifica se o robo pode continuar indo para trás.                                                                                 //
          if (millis() >= (start_move_time + last_move_time))                                                                                     //
          {                                                                                                                                       //
            //  ~ Como o robo não pode ir para trás no modo automático, apenas trata para o modo manual parando o robo.                           //
            robot_direction = PARAR;                                                                                                              //
          }                                                                                                                                       //
        break;                                                                                                                                    //
      //  ~ Verificação caso o robo esteja virando para a esquerda.                                                                               //
      case ESQUERDA:                                                                                                                              //
        //  ~ Verifica a conclusão da rotação.                                                                                                    //
        if (millis() >= (start_move_time + ROTATE_RANGE_TIME))                                                                                    //
        {                                                                                                                                         //
          //  ~ Se estiver no modo automático, ele verifica se tem algum obstáculo a frente. Caso haja, ele rotaciona o robo para a direita.      //
          if ((robot_auto_move) and (CheckObstacles())) robot_direction = DIREITA;                                                                //
          //  ~ Caso não haja, ele segue em frente.                                                                                               //
          else if ((robot_auto_move) and (!CheckObstacles()))                                                                                     //
          {                                                                                                                                       //
            robot_direction = FRENTE;                                                                                                             //
            last_time_distance_calc = millis() - MEASURING_RANGE_TIME;                                                                            //
          }                                                                                                                                       //
          //  ~ Se ele estiver no modo manual, ele para.                                                                                          //
          else robot_direction = PARAR;                                                                                                           //
        }                                                                                                                                         //
        break;                                                                                                                                    //
      //  ~ Verificação caso o robo esteja virando para a direita.                                                                                //
      case DIREITA:                                                                                                                               //
          //  ~ Caso esteja no modo automático, a rotação para a direita é dobrada, então, separa-se os dois casos.                               //
          //  No caso, por ser mais simples, tratamos do modo manual. Caso o tempo de execução seja atingido, o robo para.                        //
          if(!robot_auto_move) { if (millis() >= (start_move_time + ROTATE_RANGE_TIME)) robot_direction = PARAR; }                                //
          else                                                                                                                                    //
          {                                                                                                                                       //
            //  ~ Multiplicador para as rotações.                                                                                                 //
            int turns = robot_return ? 1 : 2;                                                                                                     //
            //  ~ Verifica se a(s) volta(s) já foram concluidas.                                                                                  //
            if (millis() >= (start_move_time + (turns * ROTATE_RANGE_TIME)))                                                                      //
            {                                                                                                                                     //
              //  ~ Se o retorno estiver desligado ele verifica para seguir em frente. Caso haja obstáculos, ele vira para a direita e liga o     //
              //  retorno.                                                                                                                        //
              if ((!robot_return) and (CheckObstacles())) { robot_direction = DIREITA; robot_return = true; }                                     //
              //  ~ Se não houver obstáculos, ele segue em frente.                                                                                //
              else if ((!robot_return) and (!CheckObstacles()))                                                                                   //
              {                                                                                                                                   //
                robot_direction = FRENTE;                                                                                                         //
                last_time_distance_calc = millis() - MEASURING_RANGE_TIME;                                                                        //
              }                                                                                                                                   //
              //  ~ Se o retorno estiver ligado e não houverem obstáculos, ele segue em frente e desliga o retorno.                               //
              else if ((robot_return) and (CheckObstacles())) { robot_direction = FRENTE; robot_return = false; }                                 //
              //  ~ Se o retorno estiver ligado e houverem obstáculos, ele desliga o robo e informa o erro.                                       //
              else                                                                                                                                //
              {                                                                                                                                   //
                //  ~ Desliga o robo.                                                                                                             //
                robot_power = false;                                                                                                              //
                //  ~ Para o robo.                                                                                                                //
                robot_return = PARAR;                                                                                                             //
                //  ~ Informa o erro (código de erro: 2 | destino: <4>).                                                                          //
                //  [SEND TO - ADD HERE]
              }                                                                                                                                   //
            }                                                                                                                                     //
          }                                                                                                                                       //
        break;                                                                                                                                    //
      //  ~ Se o robo estiver parado.                                                                                                             //
      case PARAR:                                                                                                                                 //
        //  ~ Se o robo estiver no modo automático e estiver parado ele automaticamente troca para "seguir em frente".                            //
        if (robot_auto_move) { robot_direction = FRENTE; last_time_distance_calc = millis() - MEASURING_RANGE_TIME; }                             //
        break;                                                                                                                                    //
      //  ~ Se nenhuma das opções, para o robo e informa um erro.                                                                                 //
      default:                                                                                                                                    //
        //  ~ Para o robo.                                                                                                                        //
        robot_direction = PARAR;                                                                                                                  //
        //  ~ Informa o erro (código de erro: 1 | destino: <4>).                                                                                  //
        //  [SEND TO - ADD HERE]
        break;                                                                                                                                    //
    }                                                                                                                                             //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ [SUB] Abertura do painel solar (caso ordenado).                                                                                             */
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ [SUB] Abertura do painel solar (caso ordenado).                                                                                             */
    if(opening_painel_solar)                                                                                                                      //
    {                                                                                                                                             //
      //  ~ Mantem o motor para abertura do painel funcionando.                                                                                   //
      digitalWrite(ENGINE_PAINEL_SOLAR, HIGH);                                                                                                    //
      digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);                                                                                             //
      //  ~ Verifica se o tempo foi ou não atingido.                                                                                              //
      if(millis() >= (start_func_painel_solar + (specifit_painel_case_multiplier * PAINEL_SOLAR_FUNC_DELAY)))                                     //
      {                                                                                                                                           //
        //  ~ Informa que o painel solar já foi aberto.                                                                                           //
        opening_painel_solar = false;                                                                                                             //
        open_solar_painel = true;                                                                                                                 //
        //  ~ Para os motores.                                                                                                                    //
        digitalWrite(ENGINE_PAINEL_SOLAR, LOW);                                                                                                   //
        digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);                                                                                           //
      }                                                                                                                                           //
    }                                                                                                                                             //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ [SUB] ] Fechamento do painel solar (caso ordenado).                                                                                         */
    else if(closing_painel_solar)                                                                                                                 //
    {                                                                                                                                             //
      //  ~ Mantem o motor para abertura do painel funcionando.                                                                                   //
      digitalWrite(ENGINE_PAINEL_SOLAR, LOW);                                                                                                     //
      digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, HIGH);                                                                                            //
      //  ~ Verifica se o tempo foi ou não atingido.                                                                                              //
      if(millis() >= (start_func_painel_solar + (specifit_painel_case_multiplier * PAINEL_SOLAR_FUNC_DELAY)))                                     //
      {                                                                                                                                           //
        //  ~ Informa que o painel solar já foi aberto.                                                                                           //
        closing_painel_solar = false;                                                                                                             //
        open_solar_painel = false;                                                                                                                //
        //  ~ Para os motores.                                                                                                                    //
        digitalWrite(ENGINE_PAINEL_SOLAR, LOW);                                                                                                   //
        digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);                                                                                           //
      }                                                                                                                                           //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ [SUB] Desligamento dos motores do painel solar (automático).                                                                                */
      else                                                                                                                                        //
      {                                                                                                                                           //
        //  ~ Para os motores.                                                                                                                    //
        digitalWrite(ENGINE_PAINEL_SOLAR, LOW);                                                                                                   //
        digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);                                                                                           //
      }                                                                                                                                           //
    }                                                                                                                                             //
  }                                                                                                                                               //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Execuções quando o robo está desligado ou em alta temperatura.                                                                              */
  else                                                                                                                                            //
  {                                                                                                                                               //
    //  ~ Apaga a LED que indica que o robo está ligado.                                                                                          //
    digitalWrite(POWER_LED, LOW);                                                                                                                 //
    //  ~ Salva o status dos leds antes de desligar.                                                                                              //
    heater_led_status = (bool) digitalRead(HEATER_LED);                                                                                           //
    light_led_status = (bool) digitalRead(LIGHT_LEDS);                                                                                            //
                                                                                                                                                  //
                                                                                                                                                  //
    //  ~ Verifica se já iniciou o fechamento.                                                                                                    //
    if ((open_solar_painel) and (!closing_painel_solar))                                                                                          //
    {                                                                                                                                             //
      //  ~ Informa o fechamento.                                                                                                                 //
      closing_painel_solar = true;                                                                                                                //
      //  ~ Altera o multiplicador.                                                                                                               //
      specifit_painel_case_multiplier = 1.0;                                                                                                      //
      //  ~ Altera o inicio da função.                                                                                                            //
      start_func_painel_solar = millis();                                                                                                         //
    }                                                                                                                                             //
                                                                                                                                                  //
    //  ~ Verifica se é para fechar.                                                                                                              //
    if (closing_painel_solar)                                                                                                                     //
    {                                                                                                                                             //
      //  ~ Aciona os motores de fechamento.                                                                                                      //
      digitalWrite(ENGINE_PAINEL_SOLAR, LOW);                                                                                                     //
      digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);                                                                                             //
      //  ~ Verifica se atingiu o tempo.                                                                                                          //
      if(millis() >= (start_func_painel_solar + (specifit_painel_case_multiplier * PAINEL_SOLAR_FUNC_DELAY)))                                     //
      {                                                                                                                                           //
        //  ~ Informa que o painel solar já foi aberto.                                                                                           //
        closing_painel_solar = false;                                                                                                             //
        open_solar_painel = false;                                                                                                                //
        //  ~ Para os motores.                                                                                                                    //
        digitalWrite(ENGINE_PAINEL_SOLAR, LOW);                                                                                                   //
        digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);                                                                                           //
      }                                                                                                                                           //
                                                                                                                                                  //
    }                                                                                                                                             //
    else                                                                                                                                          //
    {                                                                                                                                             //
      //  ~ Para os motores.                                                                                                                      //
      digitalWrite(ENGINE_PAINEL_SOLAR, LOW);                                                                                                     //
      digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);                                                                                             //
    }                                                                                                                                             //
                                                                                                                                                  //
    //  ~ Apaga o LED que indica o funcionamento do aquecedor.                                                                                    //
    digitalWrite(HEATER_LED, LOW);                                                                                                                //
    //  ~ Apaga o LED de luz.                                                                                                                     //
    digitalWrite(LIGHT_LEDS, LOW);                                                                                                                //

    //  ~ Atualiza as variáveis de início para o mais próximo da alteração.                                                                       //
    start_func_painel_solar = millis();                                                                                                           //
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
  pinMode(ENGINE_PAINEL_SOLAR, OUTPUT);                                                                                                           //
  pinMode(ENGINE_PAINEL_SOLAR_REVERSE, OUTPUT);                                                                                                   //
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
                                                                                                                                                  //
  //  ~ Verifica alterações de luz ambiente.                                                                                                      //                                                                                                                                             //
  //  ~ Se o sinal for maior do que 100, está escuro.                                                                                             //
  if(light_signal > 100)                                                                                                                          //
  {                                                                                                                                               //
    //  ~ Faz a função de acender as luzes.                                                                                                       //
    digitalWrite(LIGHT_LEDS, HIGH);                                                                                                               //
    //  ~ Fecha o painel solar.                                                                                                                   //
    opening_painel_solar = false;                                                                                                                 //
    closing_painel_solar = true;                                                                                                                  //
    start_func_painel_solar = millis();                                                                                                           //
  }                                                                                                                                               //
  else                                                                                                                                            //
  {                                                                                                                                               //
    //  ~ Faz a função de apagar as luzes.                                                                                                        //
    digitalWrite(LIGHT_LEDS, LOW);                                                                                                                //
    //  ~ Abre o painel solar.                                                                                                                    //
    opening_painel_solar = true;                                                                                                                  //
    closing_painel_solar = false;                                                                                                                 //
    start_func_painel_solar = millis();                                                                                                           //
  }                                                                                                                                               //
                                                                                                                                                  //
  //  ~ Agrega a camera ao controle do servo.                                                                                                     //
  camera.attach(CAMERA);                                                                                                                          //
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
    //  ~ Recebe a posição da câmera.                                                                                                             //
    case 1:                                                                                                                                       //
      camera_signal = message;                                                                                                                    //
      break;                                                                                                                                      //
  }                                                                                                                                               //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
