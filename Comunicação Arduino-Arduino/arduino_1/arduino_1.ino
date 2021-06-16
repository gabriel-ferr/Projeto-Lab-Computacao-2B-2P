  /* -------------------------------------------------------------------------------------------- *
   *  Arduino de entrada de dados a partir do monitor serial.                                     *
   *  É o primeiro arduino da conexão estabelecida no protótipo simulado.                         *
   * -------------------------------------------------------------------------------------------- *
   *                                                                                              *
   * Nele está presente um sistema de processamento em paralelo para interpretar entradas de      *
   * dados a partir do monitor serial e adicioná-las ao vetor de execuções, assim como o proces-  *
   * samento do vetor e envio dos dados no devido delay do processo.                              *
   * -------------------------------------------------------------------------------------------- *
   * Versão 1.0                                                                                   *
   *    por Gabriel Vinicius Ferreira.                                                            *
   * -------------------------------------------------------------------------------------------- */
  /* - Definições                                                                                 */
  // Representa o ID do arduino na rede de conexões. Pode variar entre 1 a 9, não podendo ser repetido.
  //    OBS*: Organize os IDs na ordem dos arduinos, pois, o sistema não enviará a mensagem para um arduino com ID inferior ao dele.
  #define ID 1
  
  /* Inicialização do Arduino. */
  void setup()
  {
    // Inicializa o sistema Serial em uma atualização de 9600.
    Serial.begin(9600);
    while (!Serial){
      ; // Força a espera da porta serial ser conectada.
    }
  }

  /* Laço de repetição do loop. */
  void loop()
  {
    // Verifica se existem atualizações a serem efetuadas.
    if ((Serial.available() > 0) && (ID != 1)) ReceiveFrom();       // Para economizar espaço, está linha pode ser removida no Arduino de 'ID' 1, assim como a função 'ReceiveFrom()'.
                                                                    // Também é possível eliminar a função 'SendTo()' do Arduino de 'ID' 9, ou no Arduino que estiver ao final da cadeia.
  }

  /* Faz o tratamento dos dados recebidos. */
  void HandleData(int code, int message)
  {
    // Faz a determinação da função baseado no código.
    switch (code)
    {
      case 0:
              Serial.print("Funcionou: ");
              Serial.println(message);
              break;
      
    }
  }

  /* Faz o recebimento das mensagens. */
  void ReceiveFrom()
  {
    // Buffer para leitura do valor presente na porta serial.
    unsigned long _sbuffer = (unsigned long) Serial.readString();
    // Separa-se do buffer a origem da mensagem.
    int _from = (int) _sbuffer / 10000000UL;
    // Separa-se do buffer o destino da mensagem.
    int _to = (int) ((_sbuffer / 1000000UL) % 10);
    // Separa-se do buffer o código indentificação.
    int _code = (int) ((_sbuffer / 10000UL) % 100);
    // Separa-se a mensagem do buffer.
    int _message = (int) _sbuffer % 10000;

    // Verifica se a origem é o arduino com ID anterior ao dele, se não for, significa uma violação e ignora a mensagem.
    if (_from != (ID - 1)) return;
    // Verifica se o arduino de destino é o atual, se não for, passa a mensagem afrente.
    //  Percebe-se que, caso o destino seja 0, ele deve continuar o código.
    if ((_to != ID) or (_to == 0))
    {
      if (ID != 9) {                          // Se o ID do arduino for '9', significa que ele é o final da série e não pode passar a mensagem para nenhum outro.
        SendTo(_to, _code, _message);         //    ~ Faz o envio da mensagem para o próximo arduino.
        if (_to != 0) return;                 //    ~ Se o '_to" não for 0, interrompe o recebimendo dos dados.
      }
    }
    // Passa os elementos para o tratamento de dados.
    HandleData(_code, _message);
  }
  
  /* Faz o envio de uma mensagem para outro arduino. */
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
