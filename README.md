README - Controle de LED RGB com Raspberry Pi Pico

Link de video: https://drive.google.com/file/d/1GgNbj8MXUhP_1BDKWSAqLvJ_ilyzTuuS/view?usp=sharing 

Descrição do Projeto

Este projeto demonstra como controlar um LED RGB WS2812 (comumente conhecido como Neopixel) utilizando a Raspberry Pi Pico. O sistema é configurado para fazer o LED piscar cinco vezes por segundo, e seu padrão de iluminação pode ser alterado de forma interativa através de dois botões de pressão. O código também utiliza interrupções e buffers para gerenciar diferentes padrões de cores no LED, evitando bloqueios no loop principal e oferecendo uma experiência de controle eficiente.

Requisitos de Hardware
Para montar este projeto, você precisará dos seguintes componentes:

Raspberry Pi Pico 
LED RGB WS2812 (Neopixel): Este LED endereçável permite controlar individualmente cada um dos seus componentes de cor (vermelho, verde e azul).
2 Botões de Pressão: Um para incrementar e outro para decrementar o padrão de iluminação.
Resistores de pull-up: Para garantir um nível lógico estável nos pinos de entrada dos botões.
Protoboard e fios de conexão: Para facilitar a montagem do circuito.
Pinos Utilizados
Abaixo está a lista dos pinos da Raspberry Pi Pico e suas funções neste projeto:

Pino 7: Controle do LED WS2812 (Neopixel).
Pino 5: Botão de incremento (avança para o próximo padrão de iluminação).
Pino 6: Botão de decremento (volta para o padrão anterior de iluminação).
Pino 13: LED indicador externo que pisca a cada 100ms (para sinalizar o funcionamento do sistema).
Funcionamento do Sistema
Inicialização do Sistema: O programa inicia com a configuração dos pinos GPIO necessários. Ele configura os pinos para controle do LED, botões e o LED indicador.

Piscar do LED Indicador: O LED no pino 13 pisca cinco vezes por segundo, indicando que o sistema está funcionando corretamente e aguardando interações.

Controle de LED WS2812: O LED RGB WS2812 exibe uma sequência de cores com base em padrões armazenados em 11 buffers diferentes. Cada buffer contém um padrão de cores específico, como transições de cores ou efeitos específicos.

Interação com os Botões:

O botão no Pino 5 (incremento) avança para o próximo padrão de iluminação.
O botão no Pino 6 (decremento) retrocede para o padrão anterior.
As pressões dos botões são detectadas por interrupções, o que permite uma troca rápida e eficiente de padrões de iluminação sem bloquear o fluxo principal do código.
Debounce de Botões: Para evitar leituras errôneas e múltiplas leituras causadas por contatos instáveis, um debounce de 500ms é aplicado a cada pressão de botão.

Atualização dos LEDs: Quando um botão é pressionado, o programa atualiza o buffer de cores e altera o comportamento do LED RGB de acordo com o novo padrão escolhido.

Melhorias Futuras
Este projeto pode ser expandido com as seguintes melhorias:

Interface Serial: Implementar uma interface de comunicação via serial (USB ou Bluetooth) para permitir o controle remoto e o envio de comandos de configuração.
Animações de LED: Desenvolver modos de animação para o LED, como transições suaves de cores, efeitos de fade, etc.
Suporte para Múltiplos LEDs: Expandir o controle para múltiplos LEDs WS2812, criando efeitos em cadeia e novas interações.
Otimização de Interrupções: Melhorar a utilização das interrupções para otimizar o desempenho e reduzir o consumo de recursos, especialmente em cenários mais complexos.
Como Usar
Para configurar e usar o sistema, siga os passos abaixo:

Carregar o Código: Compile e carregue o código no seu Raspberry Pi Pico.

O código pode ser escrito em MicroPython ou C++, dependendo da sua preferência de ambiente de desenvolvimento.
Conexões:

Conecte o LED WS2812 ao Pino 7 (atenção para a necessidade de um resistor limitador de corrente, se necessário).
Conecte os dois botões de pressão aos Pinos 5 e 6.
Conecte o LED indicador externo ao Pino 13.
Certifique-se de usar resistores de pull-up ou pull-down conforme necessário para garantir que os botões funcionem corretamente.
Observação:

O LED indicador piscará 5 vezes por segundo.
Pressione os botões para alternar entre os diferentes padrões de iluminação no LED WS2812.
Configuração de Buffers:

O código já vem conta com 11 padrões de iluminação predefinidos, mas você pode personalizá-los ou adicionar novos buffers conforme desejado.

Conclusão
Este projeto é uma excelente oportunidade para aprender a usar a Raspberry Pi Pico para controlar LEDs RGB WS2812 de maneira eficiente com interrupções e buffers. Ele serve como uma base sólida para explorar animações de LEDs, controle remoto e muito mais. 
