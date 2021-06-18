  /* -------------------------------------------------------------------------------------------- *
   *  Código do Arduino 2 ~ Arduino de Cadeia ou Final.                                           *
   * -------------------------------------------------------------------------------------------- *
   *    Código do arduino de 'ID' 2 a 9 da cadeia de ligação Arduino-Arduino I2C.                 *
   * -------------------------------------------------------------------------------------------- *
   *    ~ O sistema comporta uma quantidade de até 9 arduinos ligados em cadeia, permitindo o     *
   * envio de mensagens em uma única direção, partindo do Arduino de 'ID' 1 até o de 'ID' 9.      *
   *    ~ Nesse caso, o código está completo. Contudo, a função 'SendTo()' pode ser removida do   *
   * código para economizar espaço, já que ela torna-se desnecessária no final da cadeia.         *
   * -------------------------------------------------------------------------------------------- *
   * Versão 1.0                                                                                   *
   *    por Gabriel Vinicius Ferreira.                                                            *
   * -------------------------------------------------------------------------------------------- *
   * - Definições                                                                                 */
  // Representa o ID do arduino na rede de conexões. Pode variar entre 1 a 9, não podendo ser repetido.
  //    OBS*: Organize os IDs na ordem dos arduinos, pois, o sistema não enviará a mensagem para um arduino com ID inferior ao dele.
  #define ID 2
  // Define o limite da cadeia de recebimento de dados.
  //    ~ O valor definido aqui deve ser igual ao último ID usado na cadeia de arduinos.
  #define ID_LIMIT 3
  /* -------------------------------------------------------------------------------------------- */
  /* - Portas do Arduino.                                                                         */
  #define LED_ON 8
  /* -------------------------------------------------------------------------------------------- */
  /* - Variáveis de estado atualizado.                                                            */
  // Determina se o robo está ligado ou não.
  bool RobotOn = false;
  /* -------------------------------------------------------------------------------------------- */
  /* - Variáveis de estado desatualizado.                                                            */
  // Determina se o robo está ligado ou não.
  bool _RobotOn = false;
  /* -------------------------------------------------------------------------------------------- */
  /* Inicialização do Arduino.                                                                    */
  void setup()
  {
    // Inicializa o sistema Serial em uma atualização de 9600.
    Serial.begin(9600);
    while (!Serial){
      ; // Força a espera da porta serial ser conectada.
    }
    // Seta as portas digitais de saída de dados.
    pinMode(LED_ON, OUTPUT);
    // Equaliza as variáveis de estado.
    _RobotOn = RobotOn;
  }

  /* -------------------------------------------------------------------------------------------- */
  /* Laço de repetição do loop.                                                                   */
  void loop()
  {
    // Verifica se existem atualizações a serem efetuadas.
    if (Serial.available() > 0) ReceiveFrom();

    // Atualiza o estado do robo.
    if (_RobotOn != RobotOn) {
      if (RobotOn) digitalWrite(LED_ON, HIGH);
      else digitalWrite(LED_ON, LOW);
      _RobotOn = RobotOn; 
    }
  }

  /* -------------------------------------------------------------------------------------------- */
  /* Faz o tratamento e o manuseio dos dados.                                                     */
  //    Em 'code' deverá estar o código de identificação da mensagem. Ele será utilizado para que o sistema saiba
  // a finalidade da mensagem no decorrer do tratamento das informações.
  //    Em 'message' temos a mensagem propriamente dita.
  void HandleData(int code, int message)
  {
    Serial.println("");
    // Verifica com base no código.
    switch (code)
    {
      case 0:
          Serial.println("Mensagem recebida!");
          break;
      case 1:
          Serial.print("Estado de sistema: ");
          Serial.println(message);

          RobotOn = (bool) message;
          break;
      case 99:
          Serial.print("Mensagem recebida! Reenviando: ");
          Serial.println(message);
    }
  }
  
  /* -------------------------------------------------------------------------------------------- */
  /* Faz o recebimento das mensagens.                                                             */
  void ReceiveFrom()
  {
    // Converte o valor do buffer para Inteiro.
    unsigned long _buffer = (unsigned long) (Serial.readString().toInt());

    // Se o valor do '_buffer' for '0' our inferior a 10000000 significa que pode ser ignorado.
    if ((_buffer == 0) or (_buffer < 10000)) return;

    // Informa o recebimento da informação.
    Serial.print("RECEIVED: ");
    Serial.print(_buffer);

    // Remove do buffer o ID do arduino de origem.
    int _from = (int) (_buffer / 10000000UL);
    // Remove do buffer o ID do arduino de destino.
    int _to = (int) ((_buffer / 1000000UL) % 10);
    // Remove do buffer o código da mensagem.
    int _code = (int) ((_buffer / 10000UL) % 100);
    // Remove do buffer a mensagem em sí.
    int _message = (int) (_buffer % 10000UL);
    
    // Verifica se o arduino de origem é o arduino anterior a este. Caso não for, ele ignora a mensagem.
    if (_from != (ID - 1)) return;
    // Verifica se o arduino de origem é esse. Caso não for, envia para o arduino de origem.
    if (_to != ID)
    {
      // Ignora destinos anteriores na cadeia.
      if ((_to < ID) and (_to != 0)) return;
      // Repassa a mensagem, caso o arduino não seja o limite da cadeia.
      if (ID < ID_LIMIT)
      {
        Serial.print("[");
        SendTo(_to, _code, _message);
        Serial.println("]");
      }
      // Se não for para interpretar a mensagem, ignora.
      if (_to != 0) return;
    }
    Serial.print(" | from: ");
    Serial.print(_from);
    Serial.print(" | to: ");
    Serial.print(_to);
    Serial.print(" | code: ");
    Serial.print(_code);
    Serial.print(" | message: ");
    Serial.println(_message);    

    // Envia o código de indentificação e a mensagem para o tratamento.
    HandleData(_code, _message);
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
