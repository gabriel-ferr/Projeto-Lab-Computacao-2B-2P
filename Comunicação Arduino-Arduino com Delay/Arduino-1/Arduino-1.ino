  /* -------------------------------------------------------------------------------------------- *
   *  Código do Arduino 1 ~ Arduino de Entrada.                                                   *
   * -------------------------------------------------------------------------------------------- *
   *    Código do arduino de 'ID' 1 da cadeia de ligação Arduino-Arduino I2C.                     *
   *    Responsável pela entrada de informações via portas ou monitor serial e envio para a       *
   *    cadeia.                                                                                   *
   * -------------------------------------------------------------------------------------------- *
   * Versão 1.0:                                                                                  *
   *    ~ O sistema comporta uma quantidade de até 9 arduinos ligados em cadeia, permitindo o     *
   * envio de mensagens em uma única direção, partindo do Arduino de 'ID' 1 até o de 'ID' 9.      *
   *    ~ Para redução do código, foi removida a função de recebimento de dados do Arduino'1.     *
   *                                                                                              *
   * Versão 1.1:                                                                                  *
   *    ~ Inclusão do sistema de delay. Como resultado o uso da memória dinâmica do Arduino 1     *
   * avançou para 58% para 100 espaços de mensagem no vetor de registro de delay.                 *
   * -------------------------------------------------------------------------------------------- *
   * Versão 1.1                                                                                   *
   *    por Gabriel Vinicius Ferreira.                                                            *
   * -------------------------------------------------------------------------------------------- *
   * - Definições                                                                                 */
  // Representa o ID do arduino na rede de conexões. Pode variar entre 1 a 9, não podendo ser repetido.
  //    OBS*: Organize os IDs na ordem dos arduinos, pois, o sistema não enviará a mensagem para um arduino com ID inferior ao dele.
  #define ID 1
  // Representa o limite do vetor de dados a serem enviados.
  #define VECTOR_LIMIT 100
  // Representa o valor de Delay adicional em 'ms'.
  #define DELAY 5000
  /* -------------------------------------------------------------------------------------------- */
  /* - Estruturas                                                                                 */
  // Cria uma estrutura para setar as mensagens que devem ser enviadas para o próximo arduino e o instante em 'ms' em que o
  // envio deve ser efetuado.
  //    ~ int message: define a mensagem que deve ser enviada.
  //    ~ int code: código de identificação da mensagem a ser enviada.
  //    ~ int to: destino da mensagem.
  //    ~ unsigned long timeToSend: define o instante em 'ms' de execução do arduino em que o envio da mensagem deve ser efetuado.
  typedef struct
  {
    int message;    // Define a mensagem propriamente dita que deve ser enviada.
    int code;       // Define o código da mensagem.
    int to;         // Define o destino da mensagem.

    unsigned long timeToSend; // Define o instante de envio da mensagem.
  } Message;
  /* -------------------------------------------------------------------------------------------- */
  /* - Variáveis do sistema de delay.                                                             */
  // Registra o tempo de funcionamento do Arduino.
  unsigned long Time;
  // Vetor de registro das mensagens a serem enviadas pelo arduino.
  Message MenssagesToSend[VECTOR_LIMIT];
  // Seta o ponteiro de fim do vetor de mensagens.
  int VectorPoint;
  /* -------------------------------------------------------------------------------------------- */
  /* - Inicialização das funções.                                                                 */
  void SendTo(int to, int code, int message);         // Função de envio de informações.
  void RemoveMessage();                               // Faz a remoção da mensagem no topo da cadeia e a movimentação do vetor.
  void AddMessage(int to, int code, int message);     // Função responsável por adicionar informações ao vetor de envio.
  void TimeVerify();                                  // Função responsável por fazer a validação da mensagem no topo do vetor.
  /* -------------------------------------------------------------------------------------------- */
  /* - Funções específicas de tratamento de dados do monitor serial.                              */
  void Print(String command, String message);         // Exemplo de função de envio.
  
  void SerialManager();                               // Faz o gerenciamento dos dados retidos do monitor serial.
  /* -------------------------------------------------------------------------------------------- */
  /* Inicialização do Arduino.                                                                    */
  void setup()
  {
    // Inicializa o sistema Serial em uma atualização de 9600.
    Serial.begin(9600);
    while (!Serial){
      ; // Força a espera da porta serial ser conectada.
    }
    // Inicializa o tempo de funcionamento do Arduino;
    Time = millis();
    // Coloca o ponteiro do vetor na posição [0].
    VectorPoint = 0;
    // Inicializa a estrutura de dados.
    for(int i = 0; i < VECTOR_LIMIT; i++)
    {
      MenssagesToSend[i].message = -1;
      MenssagesToSend[i].code = -1;
      MenssagesToSend[i].to = -1;
      MenssagesToSend[i].timeToSend = 2592000;  // Equivalente ao funcionamento do sistema por 30 dias.
    }
  }
  
  /* -------------------------------------------------------------------------------------------- */
  /* Laço de repetição do loop.                                                                   */
  void loop()
  {
    // Atualiza o valor de tempo.
    Time = millis();
    // Verifica a existência de dados do monitor serial, se existirem, manda para o tratamento.
    if(Serial.available() > 0) SerialManager();
    // Faz a validação de envios do programa.
    TimeVerify();
    // Efetua um delay de 100ms.
    delay(100);
  }
  /* -------------------------------------------------------------------------------------------- */
  /* Faz o gerenciamento das mensagens adquidas do monitor serial.                                */
  void SerialManager()
  {
    //  Captura a string vinda do Monitor Serial.
    String message = Serial.readString();
    //   Deixa todo o comando em letras minúsculas.
    message.toLowerCase();
    //   Remove as letras anteriores e posteriores do comando.
    message.trim();
    //   Verifica o início da mensagem e repassa para a função responsável por organizar o envio.
    if(message.startsWith("teste")) Print("teste", message);
  }

  /* -------------------------------------------------------------------------------------------- */
  /* Adiciona um novo elemento ao vetor de mensagens a serem enviadas.                            */
  void AddMessage(int to, int code, int message)
  {
    // Verifica a posição do ponteiro. Isso é necessário para evitar o estouro do vetor.
    if (VectorPoint >= 99) RemoveMessage();
    // Adiciona a mensagem no ponteiro.
    MenssagesToSend[VectorPoint].message = message;
    MenssagesToSend[VectorPoint].code = code;
    MenssagesToSend[VectorPoint].to = to;
    MenssagesToSend[VectorPoint].timeToSend = Time + DELAY;
    // Move o ponteiro para a próxima posição.
    VectorPoint++;
  }

  /* -------------------------------------------------------------------------------------------- */
  /* Faz a remoção do elemento no inicio do vetor.                                                */
  void RemoveMessage()
  {
    // Ponto do próximo elemento do vetor.
    int n;
    // Faz a listagem do vetor e repassa.
    for (int i = 0; i < VECTOR_LIMIT - 1; i++)
    {
      // Define o valro de n como (i+1).
      n = i + 1;
      // Repassa o valor.
      MenssagesToSend[i] = MenssagesToSend[n];
    }
    // Altera o último valor para o Default.
    MenssagesToSend[VECTOR_LIMIT - 1].message = -1;
    MenssagesToSend[VECTOR_LIMIT - 1].code = -1;
    MenssagesToSend[VECTOR_LIMIT - 1].to = -1;
    MenssagesToSend[VECTOR_LIMIT - 1].timeToSend = 2592000;  // Equivalente ao funcionamento do sistema por 30 dias.
    // Move o ponteiro do vetor.
    VectorPoint--;
    
  }

  /* -------------------------------------------------------------------------------------------- */
  /* Laço de repetição do loop.                                                                   */
  void TimeVerify()
  {
    if (Time >= MenssagesToSend[0].timeToSend)
    {
      SendTo(MenssagesToSend[0].to, MenssagesToSend[0].code, MenssagesToSend[0].message);
      RemoveMessage();
    }
  }
  
  /* -------------------------------------------------------------------------------------------- */
  /* Faz o envio de uma mensagem para outro arduino.                                              */
  // O "to" representa o ID do arduino de destino, podendo variar de 1 a 9. O '0' representa todos.
  // "code" representa o código de identificação do sentido da mensagem, para o processamento no arduino de destino. Pode assumir valores de 0 a 99.
  // "message", por fim, representa o valor da mensagem que pode variar de 0 a 1023.
  void SendTo(int to, int code, int message)
  {
    // Verifica a validade das entradas.
    if ((to < 0) or (to > 9)) return;
    if ((code < 0) or (code > 99)) return;
    if ((message < 0) or (message > 1023)) return;
  
    // Verifica se a mensagem não tem como destino um ID inferior ao atual.
    if ((to <= ID) && (to != 0)) return;
  
    // Define o buffer de construção da mensagem.
    unsigned long _buffer;

    // Inicializa o buffer com o valor da mensagem.
    _buffer = (unsigned long) message;
            // A mensagem em si ocupará os 4 primeiros digitos do envio. _buffer = (####)
    // Adiciona o código de identificação ao buffer.
    _buffer += (code * 10000UL);
            // O código de identificação ocupará os 2 digitos seguintes. _buffer = (CC####)
    // Adiciona o destino ao buffer.
    _buffer += (to * 1000000UL);
            // O destino da mensagem ocupará 1 digito na sequência. _buffer = (TCC####)
    // Adiciona a origem ao buffer.
    _buffer += (ID * 10000000UL);
            // O arduino de origem, por fim, ocupará o último digito. _buffer = (FTCC####)
    // Faz o envio da mensagem.
    Serial.print(_buffer);
  }

  /* Exemplo de função de envio. */
  void Print(String command, String message)
  {
    message.replace(command, "");
    message.trim();
    AddMessage(2, 0, message.toInt());
  }
