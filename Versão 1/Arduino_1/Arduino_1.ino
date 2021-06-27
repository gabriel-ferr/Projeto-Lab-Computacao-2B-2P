/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições globais de Configuração da Placa.                                                                                                */
//  Representa o ID da placa no contexto. O valor pode adotar qualqer número entre 1 e 9.                                                         //
#define ID 1                                                                                                                                      //
//  Configura o ID do último arduino utilizado na cadeia. Isso evita repassar mensagens para o arduino na sequência.                              //
//    Essa configuração não está presente no Arduino de ID 1, pois, ele não possuí a função de recebimento de dados.                              //
#define CHAIN_LIMIT 4                                                                                                                             //
//  Determina que os arduinos estão ligados em loop. Marque isso se você quiser enviar do Arduino de ID 'CHAIN_LIMIT' para um de ID inferior.     //
//    Caso 'true' ativa a fução; caso 'false' desativa.                                                                                           //
//  !~~! O SISTEMA DE CHAIN_LOOP NÃO ESTÁ FUNCIONANDO DEVIDAMENTE, RECOMENDA-SE NÃO UTILIZÁ-LO.                                                   //
#define CHAIN_LOOP false                                                                                                                          //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Definições locais de Configuração da Placa.                                                                                                 */
//  Porta de leitura do potenciometro responsável pelo controle da câmera.                                                                        //
#define CAM_CONTROL A5                                                                                                                            //
//  Porta do botão para frente.                                                                                                                   //
#define BUTTON_UP 2                                                                                                                               //
//  Porta do botão para trás.                                                                                                                     //
#define BUTTON_DOWN 3                                                                                                                             //
//  Porta do botão para a esquerda.                                                                                                               //
#define BUTTON_LEFT 4                                                                                                                             //
//  Porta do botão para a direita.                                                                                                                //
#define BUTTON_RIGHT 5                                                                                                                            //
//  Porta de troca entre modo de movimentação automática ou manual.                                                                               //
#define INT_MOVE 6                                                                                                                                //
//  Porta do botão de reinicialização (desligar e ligar).                                                                                         //
#define BUTTON_RESET 7                                                                                                                            //
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
/*  ~ Variáveis de estado utilizadas no loop.                                                                                                     */
//  Indica o estado de envio do modo de operação do robo, entre automático e manual.                                                              //
//  O modo default é automático.                                                                                                                  //
bool bot_auto_mov;                                                                                                                                //
//  Lê a direção indicada no modo de controle manual.                                                                                             //
int bot_direction = 0;                                                                                                                            //
//  Lê o valor induzido pelo potenciomêtro para indicar a posição da câmera.                                                                      //
int pot_camera = 0;                                                                                                                               //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função do loop principal do sistema.                                                                                                        */
void loop()                                                                                                                                       //
{                                                                                                                                                 //
  //  ~ Verifica se a última mensagem foi enviada a um tempo considerável para reiniciar a dormência.                                             //
  if (LastMessage <= (millis() + (SleepMultiplyer * DELAY_SLEEP) + RESET_SLEEP)) { LastMessage = 2592000000; SleepMultiplyer = 0; }               //
                                                                                                                                                  //
  //  ~ Declara as variáveis de estado locais.                                                                                                    //
  bool _bot_auto_mov = bot_auto_mov;                                                                                                              //
  int _bot_direction = bot_direction;                                                                                                             //
  int _pot_camera = pot_camera;                                                                                                                   //
                                                                                                                                                  //
  //  ~ Verifica atualizações de entrada de dados.                                                                                                //
  if (Serial.available() > 0) Receive();                                                                                                          //
                                                                                                                                                  //
  //  ~ Verifica atualizações de entrada.                                                                                                         //
  //  ~ Verifica se o botão de reset foi ou não apertado.                                                                                         //
  if (digitalRead(BUTTON_RESET) == HIGH) { AddMessage(2, 0, 1); while(digitalRead(BUTTON_RESET) == HIGH); }                                       //
  //  ~ Verifica altera troca de posição do botão de modo de movimentação do robo.                                                                //
  if (digitalRead(INT_MOVE) == HIGH) { bot_auto_mov = true; } else { bot_auto_mov = false; }                                                      //
  //  ~ Se o modo automático estiver desligado (modo manual ativado), verifica alteração dos botões de controle.                                  //
  if (!bot_auto_mov)                                                                                                                              //
  {                                                                                                                                               //
    //  ~ Verifica alteração do botão para frente.                                                                                                //
    if (digitalRead(BUTTON_UP) == HIGH) { bot_direction = 1; while(digitalRead(BUTTON_UP) == HIGH); }                                             //
    //  ~ Verifica alteração do botão para trás.                                                                                                  //
    else if (digitalRead(BUTTON_DOWN) == HIGH) { bot_direction = 2; while(digitalRead(BUTTON_DOWN) == HIGH); }                                    //
    //  ~ Verifica alteração do botão para a esquerda.                                                                                            //
    else if (digitalRead(BUTTON_LEFT) == HIGH) { bot_direction = 3; while(digitalRead(BUTTON_LEFT) == HIGH); }                                    //
    //  ~ Verifica alteração do botão para a direita.                                                                                             //
    else if (digitalRead(BUTTON_RIGHT) == HIGH) { bot_direction = 4; while(digitalRead(BUTTON_RIGHT) == HIGH); }                                  //
  }                                                                                                                                               //
  //  ~ Verifica a posição do potenciometro para enviar uma atualização sobre o controle da câmera.                                               //
  pot_camera = analogRead(CAM_CONTROL);                                                                                                           //
                                                                                                                                                  //
  //  ~ Verifica a atualização de estado das variáveis de estado.                                                                                 //
  if (bot_auto_mov != _bot_auto_mov) { AddMessage(3, 1, (int) bot_auto_mov); }                                                                    //
  if (bot_direction != _bot_direction) { AddMessage(3, 2, bot_direction); }                                                                       //
  if (pot_camera != _pot_camera) { AddMessage(2, 3, pot_camera); }                                                                                //
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
  //  ~ Botão que comando o robo em ir para a frente.                                                                                             //
  pinMode(BUTTON_UP, INPUT);                                                                                                                      //
  //  ~ Botão que comando o robo em ir para a trás.                                                                                               //
  pinMode(BUTTON_DOWN, INPUT);                                                                                                                    //
  //  ~ Botão que comando o robo em ir para a esquerda.                                                                                           //
  pinMode(BUTTON_LEFT, INPUT);                                                                                                                    //
  //  ~ Botão que comando o robo em ir para a direita.                                                                                            //
  pinMode(BUTTON_RIGHT, INPUT);                                                                                                                   //
  //  ~ Botão que comando o robo em realizar a alteração de controle entre automático e manual.                                                   //
  pinMode(INT_MOVE, INPUT);                                                                                                                       //
  //  ~ Botão que comando o robo em ir para a frente.                                                                                             //
  pinMode(BUTTON_RESET, INPUT);                                                                                                                   //
                                                                                                                                                  //
  //  ~ Carrega as definições iniciais do robo.                                                                                                   //
  bot_auto_mov = (bool) digitalRead(INT_MOVE);                                                                                                    //
  pot_camera = analogRead(CAM_CONTROL);                                                                                                           //
                                                                                                                                                  //
  //  ~ Manda mensagens de atualização para reiniciar o robo em seu estado inicial.                                                               //
  //  ~ Coloca o robo no padrão.                                                                                                                  //
  SendTo(3, 1, (int) bot_auto_mov);                                                                                                               //
  //  ~ Espera alguns milissegundos.                                                                                                              //
  //  ~ Atualiza a posição da câmera.                                                                                                             //
  SendTo(2, 3, pot_camera);                                                                                                                       //
  //  ~ Espera alguns milissegundos.                                                                                                              //
  //  ~ Informa o robo que é para ele ligar (o default é registrado no sistema como desligado por padrão).                                        //
  AddMessage(0, 0, 1);                                                                                                                            //
  //  ~ Espera alguns milissegundos.                                                                                                              //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  ~ Função responsável pelo tratamento dos dados recebido de outro arduino.                                                                     */
void HandleData(int code, int message)                                                                                                            //
{                                                                                                                                                 //
  //  ~ Verifica o que deve fazer com a mensagem recebida baseando-se no código de função que foi recebido junto dela.                            //
  switch(code)                                                                                                                                    //
  {                                                                                                                                               //
    case 0:                                                                                                                                       //
      break;                                                                                                                                      //
  }                                                                                                                                               //
}                                                                                                                                                 //
/* ---------------------------------------------------------------------------------------------------------------------------------------------- */
