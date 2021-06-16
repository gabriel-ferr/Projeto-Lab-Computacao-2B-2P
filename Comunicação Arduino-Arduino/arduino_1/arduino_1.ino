  /* -------------------------------------------------------------------------------------------- *
   *  Código do Arduino 1 ~ Arduino de Entrada.                                                   *
   * -------------------------------------------------------------------------------------------- *
   *    Código do arduino de 'ID' 1 da cadeia de ligação Arduino-Arduino I2C.                     *
   * -------------------------------------------------------------------------------------------- *
   *    ~ O sistema comporta uma quantidade de até 9 arduinos ligados em cadeia, permitindo o     *
   * envio de mensagens em uma única direção, partindo do Arduino de 'ID' 1 até o de 'ID' 9.      *
   *    ~ Para redução do código, foi removida a função de recebimento de dados do Arduino'1.     *
   * -------------------------------------------------------------------------------------------- *
   * Versão 1.0                                                                                   *
   *    por Gabriel Vinicius Ferreira.                                                            *
   * -------------------------------------------------------------------------------------------- *
   * - Definições                                                                                 */
  // Representa o ID do arduino na rede de conexões. Pode variar entre 1 a 9, não podendo ser repetido.
  //    OBS*: Organize os IDs na ordem dos arduinos, pois, o sistema não enviará a mensagem para um arduino com ID inferior ao dele.
  #define ID 1
  /* -------------------------------------------------------------------------------------------- */
  /* Inicialização do Arduino.                                                                    */
  void setup()
  {
    // Inicializa o sistema Serial em uma atualização de 9600.
    Serial.begin(9600);
    while (!Serial){
      ; // Força a espera da porta serial ser conectada.
    }
  }
  
  /* -------------------------------------------------------------------------------------------- */
  /* Laço de repetição do loop.                                                                   */
  void loop()
  {
    SendTo(2, 0, 1);
    delay(2000);
    SendTo(0, 99, 1023);
    delay(2000);
    SendTo(3, 0, 55);
    delay(2000);
    SendTo(2, 0, 893);
    delay(2000);
    SendTo(1, 0, 1);
    delay(2000);
    SendTo(0, 99, 1023);
    delay(2000);
    SendTo(2, 0, 55);
    delay(2000);
    SendTo(3, 0, 893);
    delay(2000);
  }

  /* -------------------------------------------------------------------------------------------- */
  /* Faz o envio de uma mensagem para outro arduino.                                              */
  // O "to" representa o ID do arduino de destino, podendo variar de 1 a 9. O '0' representa todos.
  // "code" representa o código de indentificação do sentido da mensagem, para o processamento no arduino de destino. Pode assumir valores de 0 a 99.
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
    // Adiciona o código de indentificação ao buffer.
    _buffer += (code * 10000UL);
            // O código de indentificação ocupará os 2 digitos seguintes. _buffer = (CC####)
    // Adiciona o destino ao buffer.
    _buffer += (to * 1000000UL);
            // O destino da mensagem ocupará 1 digito na sequência. _buffer = (TCC####)
    // Adiciona a origem ao buffer.
    _buffer += (ID * 10000000UL);
            // O arduino de origem, por fim, ocupará o último digito. _buffer = (FTCC####)
    // Faz o envio da mensagem.
    Serial.print(_buffer);
  }
