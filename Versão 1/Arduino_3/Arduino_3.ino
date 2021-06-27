/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Configurações do modo de inicialização do robo.                                                                                             */
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
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições globais de Configuração da Placa.                                                                                                */
//  Representa o ID da placa no contexto. O valor pode adotar qualqer número entre 1 e 9.                                                         //
#define ID 3                                                                                                                                      //
//  Configura o ID do último arduino utilizado na cadeia. Isso evita repassar mensagens para o arduino na sequência.                              //
//    Essa configuração não está presente no Arduino de ID 1, pois, ele não possuí a função de recebimento de dados.                              //
#define CHAIN_LIMIT 4                                                                                                                             //
//  Determina que os arduinos estão ligados em loop. Marque isso se você quiser enviar do Arduino de ID 'CHAIN_LIMIT' para um de ID inferior.     //
//    Caso 'true' ativa a fução; caso 'false' desativa.                                                                                           //
//  !~~! O SISTEMA DE CHAIN_LOOP NÃO ESTÁ FUNCIONANDO DEVIDAMENTE, RECOMENDA-SE NÃO UTILIZÁ-LO.                                                   //
#define CHAIN_LOOP false                                                                                                                          //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições locais de Configuração da Placa.                                                                                                 */
//  Porta do sensor ultrassônico, responsável por determinar a existência de objetos a frente. Porta de emissão de eco.                           //
#define ULTRASOUND_SENSOR_TRIGGER 4                                                                                                               //
//  Porta do sensor ultrassônico, responsável por determinar a existência de objetos a frente. Porta de recepção de eco.                          //
#define ULTRASOUND_SENSOR_ECHO 5                                                                                                                  //
//  Motor Direito, entrada padrão.                                                                                                                //
#define ENGINE_RIGHT 9                                                                                                                            //
//  Motor Direito, entrada reversa.                                                                                                               //
#define ENGINE_RIGHT_REVERSE 8                                                                                                                    //
//  Motor Esquerdo, entrada padrão.                                                                                                               //
#define ENGINE_LEFT 10                                                                                                                            //
//  Motor Esquerdo, entrada reversa.                                                                                                              //
#define ENGINE_LEFT_REVERSE 11                                                                                                                    //
//  Motor do painel solar, entrada padrão.                                                                                                        //
#define ENGINE_PAINEL_SOLAR 13                                                                                                                    //
//  Motor do painel solar, entrada reversa.                                                                                                       //
#define ENGINE_PAINEL_SOLAR_REVERSE 12                                                                                                            //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições de Configuração do código.                                                                                                       */
//  Configuração do modo de Debug. Caso 'true' ativa; caso 'false' desativa.                                                                      //
//    O Debug exibe no Monitor Serial as execuções. Como resultado, ele envia essas mensagens para o próximo arduino que as ignora, contudo,      //
//    isso pode gerar interferência, então, evite mantê-lo ativado.                                                                               //
#define DEBUG true                                                                                                                                //
//  Define o tamanho do vetor responsável por armazenar as mensagens a serem enviadas no sistema de delay.                                        //
//    Cada elemento no vetor ocupara 20 Bytes, portanto, é importante tomar cuidado ao dimensionar o vetor.                                       //
#define DELAY_VECTOR_LENGTH 50                                                                                                                    //
//  Define o delay para envio das mensagens em 'ms'.                                                                                              //
#define DELAY 5000                                                                                                                                //
//  Tempo extra em situações de sobrecarga de mensagens.                                                                                          //
#define DELAY_SLEEP 50                                                                                                                            //
//  Tempo de intervalo para resetar o acumulador de sobrecarga.                                                                                   //
#define RESET_SLEEP 500                                                                                                                           //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Configurações de movimentação do robo.                                                                                                      */
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
//  Intervalo para a abertura ou fechamento dos paineis solares.                                                                                  //
//    O valor informado deve estar em 'ms'.                                                                                                       //
#define PAINEL_SOLAR_FUNCTIONS_RANGE_TIME 3000                                                                                                    //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Estruturas utilizadas no código.                                                                                                            */
//  Define a estrutura responsável por representar uma mensagem no sistema de Delay..                                                             //
typedef struct                                                                                                                                    //
{                                                                                                                                                 //
  //  ~ Inteiro que representa o destino da mensagem.                                                                                             //
  int to;                                                                                                                                         //
  //  ~ Inteiro que representa o código de função da mensagem.                                                                                    //
  int code;                                                                                                                                       //
  //  ~ Inteiro que representa a mensagem.                                                                                                        //
  int message;                                                                                                                                    //
  //  ~ Unsigned Long que representa o instante em 'ms' em que a mensagem deve ou deveria ser enviada.                                            //
  unsigned long timeToSend;                                                                                                                       //
} Message;                                                                                                                                        //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Variáveis de estado do robo.                                                                                                                */
//  Indica se o robo está ligado ou desligado.                                                                                                    //
//    Por padrão o robo inicializa desligado.                                                                                                     //
bool power_on = false;                                                                                                                            //
//  Modo de movimentação do robo, alterna entre altomático ('true') ou manual ('false').                                                          //
//    Por padrão o robo inicializa no automático, contudo, é possível alterar essa inicialização no código do Arduino 1.                          //
bool robot_auto_move = true;                                                                                                                      //
//  Direção de movimentação do robo. 1 = frente; 2 = trás; 3 = esquerda; 4 = direita; 0 = parar.                                                  //
int robot_direction = 1;                                                                                                                          //
//  Instante em 'ms' de inicialização de alguma atividade de movimentação.                                                                        //
unsigned long start_move_time = 0;                                                                                                                //
//  Instante em 'ms' da atividade anterior executada pelo robo.                                                                                   //
unsigned long last_move_time = 0;                                                                                                                 //
//  Registro da última verificação de distância.                                                                                                  //
unsigned long last_time_distance_calc = 0;                                                                                                        //
//  Instante da última atividade do painel solar.                                                                                                 //
unsigned long start_painel_solar_function = 0;                                                                                                    //
//  Informa se o painel solar deve ser aberto.                                                                                                    //
bool opening_painel_solar = false;                                                                                                                //
//  Informa se o painel solar deve ser fechado.                                                                                                   //
bool closing_painel_solar = false;                                                                                                                //
//  Informa se o painel solar está totalmente aberto.                                                                                             //
bool painel_solar_open = false;                                                                                                                   //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Inicialização das variáveis do sistema de Delay.                                                                                            */
//  Vetor responsável por armazenar os elementos do sistema de delay.                                                                             //
Message MessageToSend[DELAY_VECTOR_LENGTH];                                                                                                       //
//  Ponteiro do vetor 'MessageToSend' em que um novo elemento pode e deve ser adicionado.                                                         //
int AddCursor;                                                                                                                                    //
//  Ponteiro do vetor 'MessageToSend' em que um elemento deve ser lido, enviado e excluído.                                                       //
int SendCursor;                                                                                                                                   //
//  Multiplicador de sobrecarga do delay.                                                                                                         //
int SleepMultiplyer;                                                                                                                              //
//  Momento de envio da última mensagem enviada em 'ms'.                                                                                          //
unsigned long LastMessage;                                                                                                                        //
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
/*  ~ Inicializa as funções do sistema de delay.                                                                                                  */
//  Define uma nova mensagem a ser inclusa no sistema de delay.                                                                                   //
//      ~ 'to': ID do arduino de destino da mensagem.                                                                                             //
//      ~ 'code': Código da função da mensagem enviada.                                                                                           //
//      ~ 'message': Mensagem a ser enviada.                                                                                                      //
void AddMessage(int to, int code, int message);                                                                                                   //
//  Função responsável por preparar o sistema de delay para o envio da mensagem, limpar a posição da pilha e avançar para a próxima posição.      //
void PrepareToSend();                                                                                                                             //
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
/*  ~ Define uma nova mensagem a ser inclusa no sistema de delay.                                                                                 */
void AddMessage(int to, int code, int message)                                                                                                    //
{                                                                                                                                                 //
  // ~ Altera a mensagem no ponteiro de adição.                                                                                                   //
  MessageToSend[AddCursor].to = to;                                                                                                               //
  MessageToSend[AddCursor].code = code;                                                                                                           //
  MessageToSend[AddCursor].message = message;                                                                                                     //
  MessageToSend[AddCursor].timeToSend = (millis() + DELAY + (SleepMultiplyer * DELAY_SLEEP));                                                     //
  //  ~ Atualiza o tempo de envio da última mensagem.                                                                                             //
  LastMessage = millis();                                                                                                                         //
  //  ~ Move o cursor de adição para a próxima posição.                                                                                           //
  AddCursor++;                                                                                                                                    //
  //  ~ Se o ponteiro de adição estourar o limite do vetor, volta para a primeira posição.                                                        //
  if (AddCursor >= DELAY_VECTOR_LENGTH) AddCursor = 0;                                                                                            //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função responsável por preparar o sistema de delay para o envio da mensagem, limpar a posição da pilha e avançar para a próxima posição.    */
void PrepareToSend()                                                                                                                              //
{                                                                                                                                                 //
  //  ~ Faz o envio da mensagem.                                                                                                                  //
  SendTo(MessageToSend[SendCursor].to, MessageToSend[SendCursor].code, MessageToSend[SendCursor].message);                                        //
  //  ~ Reseta o valor no ponteiro.                                                                                                               //
  MessageToSend[SendCursor].to = -1;                                                                                                              //
  MessageToSend[SendCursor].code = -1;                                                                                                            //
  MessageToSend[SendCursor].message = -1;                                                                                                         //
  MessageToSend[SendCursor].timeToSend = 2592000000;                                                                                              //
  //  ~ Move o cursor de envio para a próxima posição.                                                                                            //
  SendCursor++;                                                                                                                                   //
  //  ~ Se o cursor de envio tiver estourado o limite do vetor, volta para a primeira posição.                                                    //
  if (SendCursor >= DELAY_VECTOR_LENGTH) SendCursor = 0;                                                                                          //
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
  
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função do loop principal do sistema.                                                                                                        */
void loop()                                                                                                                                       //
{                                                                                                                                                 //
  //  ~ Verifica se a última mensagem foi enviada a um tempo considerável para reiniciar a dormência.                                             //
  if (LastMessage <= (millis() + (SleepMultiplyer * DELAY_SLEEP) + RESET_SLEEP)) { LastMessage = 2592000000; SleepMultiplyer = 0; }               //
                                                                                                                                                  //
  //  ~ Declara as variáveis de estado locais.                                                                                                    //
  bool _robot_auto_move = robot_auto_move;                                                                                                        //
  int _robot_direction = robot_direction;                                                                                                         //
                                                                                                                                                  //
  //  ~ Verifica atualizações de entrada de dados.                                                                                                //
  if (Serial.available() > 0) Receive();                                                                                                          //
                                                                                                                                                  //
  //  ~ Ignora qualquer função local, exceto relacionada a comunicação, caso o robo esteja desligado.                                             //
  if (power_on)                                                                                                                                   //
  {                                                                                                                                               //
    //  ~ Primeiro o robo irá trabalhar com sua movimentação, então, ele trata do caso para as 4 direções em que pode se mover.                   //
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
    }                                                                                                                                             //
  }                                                                                                                                               //
  //  ~ Caso o robo esteja desligado, mantém a propriedade de paralização, as únicas coisas funcionando são a comunicação no caso do arduino 3.   //
  else                                                                                                                                            //
  {                                                                                                                                               //
    //  ~ Faz com que o robo pare por completo.                                                                                                   //
    Translate(PARAR);                                                                                                                             //
    //  ~ Caso o painel solar esteja aberto, ele fecha.                                                                                           //
    if (painel_solar_open)                                                                                                                        //
    {                                                                                                                                             //
      //  ~ Realiza a atualização de contexto entre abertura e fechamento do painel solar.                                                        //
      if (!closing_painel_solar) {                                                                                                                //
        closing_painel_solar = true;                                                                                                              //
        if (opening_painel_solar) opening_painel_solar = false;                                                                                   //
        start_painel_solar_function = millis();                                                                                                   //
      }                                                                                                                                           //
      //  ~ Se o fechamento do painel solar estiver ativo, liga os motores.                                                                       //
      else                                                                                                                                        //
      {                                                                                                                                           //
        //  ~ Verifica se o tempo para o fechamento do painel solar foi ou não excedido.                                                          //
        if (millis() >= (start_painel_solar_function + PAINEL_SOLAR_FUNCTIONS_RANGE_TIME))                                                        //
        {                                                                                                                                         //
          //  ~ Para o motor responsável.                                                                                                         //
          digitalWrite(ENGINE_PAINEL_SOLAR, LOW);                                                                                                 //
          digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);                                                                                         //
          //  ~ Informa que o fechamento está completo.                                                                                           //
          closing_painel_solar = false;                                                                                                           //
          //  ~ Informa que o painel está fechado.                                                                                                //
          painel_solar_open = false;                                                                                                              //
        }                                                                                                                                         //
        //  ~ Caso não tenha excedido o tempo, faz com que os motores responsáveis realizem o fechamento.                                         //
        else                                                                                                                                      //
        {                                                                                                                                         //
          //  ~ Coloca a função de reversão do motor para funcionar.                                                                              //
          digitalWrite(ENGINE_PAINEL_SOLAR, LOW);                                                                                                 //
          digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, HIGH);                                                                                        //
        }                                                                                                                                         //
      }                                                                                                                                           //
    }                                                                                                                                             //
  }                                                                                                                                               //
                                                                                                                                                  //
  //  ~ Verifica se a mensagem selecionada no ponteiro de envio do vetor de Delay deve ou não ser enviada. Caso deva, chama a função responsável  //
  // por preparar o envio.                                                                                                                        //
  if (MessageToSend[SendCursor].timeToSend <= millis()) PrepareToSend();                                                                          //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função inicial do código.                                                                                                                   */
void setup()                                                                                                                                      //
{                                                                                                                                                 //
  //  ~ Inicializa o sistema Serial com uma taxa de atualização de 9600 bits por segundo (equivalente a 1200 Bytes por segundo).                  //
  Serial.begin(9600);                                                                                                                             //
  //  ~ Faz o arduino aguardar a inicialização da comunicação Serial antes de prosseguir.                                                         //
  while(!Serial);                                                                                                                                 //
  //  ~ Inicializa o vetor do sistema de delay.                                                                                                   //
  for (int i = 0; i < DELAY_VECTOR_LENGTH; i++)                                                                                                   //
  {                                                                                                                                               //
    MessageToSend[i].to = -1;                                                                                                                     //
    MessageToSend[i].code = -1;                                                                                                                   //
    MessageToSend[i].message = -1;                                                                                                                //
    MessageToSend[i].timeToSend = 2592000000;                                                                                                     //
  }                                                                                                                                               //
  //  ~ Seta a posição inicial do cursor responsável por indicar o ponto de adição do vetor de delay.                                             //
  AddCursor = 0;                                                                                                                                  //
  //  ~ Seta a posição inicial do cursor responsável por selecionar a mensagem a ser enviada.                                                     //
  SendCursor = 0;                                                                                                                                 //
  //   ~ Inicializa o multiplicador por 0.                                                                                                        //
  SleepMultiplyer = 0;                                                                                                                            //
  //  ~ Define o valor inicial do tempo de envio da última mensagem no limite da variável.                                                        //
  LastMessage = 2592000000;                                                                                                                       //
                                                                                                                                                  //
  //  ~ Define o modo de entrada (INPUT) para as respectivas portas.                                                                              //
  //  ~ Porta de entrada do sinal enviado pelo receptor do sensor ultrassônico (ECHO).                                                            //
  pinMode(ULTRASOUND_SENSOR_ECHO, INPUT);                                                                                                         //
                                                                                                                                                  //
  //  ~ Define o modo de entrada (OUTPUT) para as respectivas portas.                                                                             //
  //  ~ Porta de saída do sinal que será emitido pelo sensor ultrassônico (TRIGGER).                                                              //
  pinMode(ULTRASOUND_SENSOR_TRIGGER, OUTPUT);                                                                                                     //
  //  ~ Portas de sinal do motor direito.                                                                                                         //
  pinMode(ENGINE_RIGHT, OUTPUT);                                                                                                                  //
  pinMode(ENGINE_RIGHT_REVERSE, OUTPUT);                                                                                                          //
  //  ~ Portas de sinal do motor esquerdo.                                                                                                        //
  pinMode(ENGINE_LEFT, OUTPUT);                                                                                                                   //
  pinMode(ENGINE_LEFT_REVERSE, OUTPUT);                                                                                                           //
  //  ~ Portas de sinal do motor do painel solar.                                                                                                 //
  pinMode(ENGINE_PAINEL_SOLAR, OUTPUT);                                                                                                           //
  pinMode(ENGINE_PAINEL_SOLAR_REVERSE, OUTPUT);                                                                                                   //
                                                                                                                                                  //
  //  ~ Pré-define os envios das portas como LOW.                                                                                                 //
  digitalWrite(ULTRASOUND_SENSOR_TRIGGER, LOW);                                                                                                   //
  digitalWrite(ENGINE_RIGHT, LOW);                                                                                                                //
  digitalWrite(ENGINE_RIGHT_REVERSE, LOW);                                                                                                        //
  digitalWrite(ENGINE_LEFT, LOW);                                                                                                                 //
  digitalWrite(ENGINE_LEFT_REVERSE, LOW);                                                                                                         //
  digitalWrite(ENGINE_PAINEL_SOLAR, LOW);                                                                                                         //
  digitalWrite(ENGINE_PAINEL_SOLAR_REVERSE, LOW);                                                                                                 //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função responsável pelo tratamento dos dados recebido de outro arduino.                                                                     */
void HandleData(int code, int message)                                                                                                            //
{                                                                                                                                                 //
  //  ~ Verifica o que deve fazer com a mensagem recebida baseando-se no código de função que foi recebido junto dela.                            //
  switch(code)                                                                                                                                    //
  {                                                                                                                                               //
    //  ~ Informa se a movimentação do robo está em modo automático ou manual.                                                                    //
    case 1:                                                                                                                                       //
      robot_auto_move = (bool) message;                                                                                                           //
      break;                                                                                                                                      //
    //  ~ Alterações de movimentação do robo.                                                                                                     //
    case 2:                                                                                                                                       //
      if (robot_direction == message) break;                                                                                                      //
      robot_direction = message;                                                                                                                  //
      break;                                                                                                                                      //
    //  ~ Informa se o robo deve estar funcionando ou não. Quem irá coordenar isso será o Arduino 2.                                              //
    case 4:                                                                                                                                       //
      power_on = (bool) message;                                                                                                                  //
      break;                                                                                                                                      //
  }                                                                                                                                               //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
