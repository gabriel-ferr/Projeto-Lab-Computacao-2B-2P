/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições globais de Configuração da Placa.                                                                                                */
//  Representa o ID da placa no contexto. O valor pode adotar qualqer número entre 1 e 9.                                                         //
#define ID 1                                                                                                                                      //
//  Configura o ID do último arduino utilizado na cadeia. Isso evita repassar mensagens para o arduino na sequência.                              //
//    Essa configuração não está presente no Arduino de ID 1, pois, ele não possuí a função de recebimento de dados.                              //
#define CHAIN_LIMIT 2                                                                                                                             //
//  Determina que os arduinos estão ligados em loop. Marque isso se você quiser enviar do Arduino de ID 'CHAIN_LIMIT' para um de ID inferior.     //
//    Caso 'true' ativa a fução; caso 'false' desativa.                                                                                           //
//  !~~! O SISTEMA DE CHAIN_LOOP NÃO ESTÁ FUNCIONANDO DEVIDAMENTE, RECOMENDA-SE NÃO UTILIZÁ-LO.                                                   //
#define CHAIN_LOOP false                                                                                                                          //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições locais de Configuração da Placa (PORTAS).                                                                                        */
//  Porta responsável pelo interruptor de ligado e desligado.                                                                                     //
#define POWER_INT 2                                                                                                                               //
//  Porta responsável pela mudança entre automático e manual do robo.                                                                             //
#define ROBOT_MODE 3                                                                                                                              //
//  Porta reponsável pelo potenciometro de controle da câmera.                                                                                    //
#define CAMERA A5                                                                                                                                 //
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
#define DELAY 1000                                                                                                                                //
//  Tempo extra em situações de sobrecarga de mensagens.                                                                                          //
#define DELAY_SLEEP 150                                                                                                                           //
//  Tempo de intervalo para resetar o acumulador de sobrecarga.                                                                                   //
#define RESET_SLEEP 3000                                                                                                                          //
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
/*  ~ Variáveis de estado utilizadas no funcionamento do código.                                                                                  */
//  Variável responsável por determinar se o robo está ligado ou desligado.                                                                       //
bool robot_power;                                                                                                                                 //
//  Indica se o robo está no modo automático ou não.                                                                                              //
bool robot_automatic;                                                                                                                             //
//  Variável responsável por armazenar o sinal do potenciometro de controle da câmera.                                                            //
int camera_signal;                                                                                                                                //
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
/*  ~ Função do loop principal do sistema.                                                                                                        */
void loop()                                                                                                                                       //
{                                                                                                                                                 //
  //  ~ Variáveis de estado.                                                                                                                      //
  int _camera_signal = camera_signal;                                                                                                             //
                                                                                                                                                  //
  //  ~ Verifica se a última mensagem foi enviada a um tempo considerável para reiniciar a dormência.                                             //
  if (LastMessage <= (millis() + (SleepMultiplyer * DELAY_SLEEP) + RESET_SLEEP)) { LastMessage = 2592000000; SleepMultiplyer = 0; }               //
                                                                                                                                                  //
  //  ~ Atualiza o valor referenciado no potenciometro.                                                                                           //
  camera_signal = analogRead(CAMERA);                                                                                                             //
                                                                                                                                                  //
  //  ~ Verifica alteração de estado no interruptor de ligar e desligar.                                                                          //
  if (digitalRead(POWER_INT) != (int) robot_power) { robot_power = digitalRead(POWER_INT); AddMessage(2, 0, (int) robot_power); }                 //
  //  ~ Verifica alteração do potenciometro.                                                                                                      //
  if (camera_signal != _camera_signal) AddMessage(2, 1, camera_signal);                                                                           //

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
  //  ~ Definição das portas de entrada (INPUT).                                                                                                  //
  pinMode(POWER_INT, INPUT);                                                                                                                      //
                                                                                                                                                  //
  //  ~ Carrega as definições padrão a partir dos componentes da placa.                                                                           //
  robot_power = digitalRead(POWER_INT);                                                                                                           //
  camera_signal = analogRead(CAMERA);                                                                                                             //
  robot_automatic = digitalRead(ROBOT_MODE);                                                                                                      //
                                                                                                                                                  //
  //  ~ Configura o robo a partir das pré-definições, sem passar por delay.                                                                       //
  SendTo(2, 0, (int) robot_power);                                                                                                                //
  SendTo(2, 1, camera_signal);                                                                                                                    //
}                                                                                                                                                 //
