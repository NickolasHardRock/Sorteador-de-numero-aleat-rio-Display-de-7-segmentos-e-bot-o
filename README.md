# Sorteador de números com display de 7 segmentos

Projeto acadêmico com Arduino Uno. O display mostra números aleatórios rapidamente; o botão **SORTEAR** interrompe a animação e deixa visível o número escolhido.

## Funcionamento

- **INICIAR (D11):** liga a animação. Se pressionado novamente durante a animação, apaga o display.
- **SORTEAR (D12):** para a animação e exibe um número aleatório de **0 a 9**. Para iniciar outro sorteio, pressione INICIAR e depois SORTEAR.
- A animação atualiza aproximadamente a cada 55 ms.
- Os botões usam `INPUT_PULLUP`; portanto, cada botão liga o pino correspondente ao GND quando pressionado.


## Ligações

O código usa a ordem de segmentos **a, b, c, d, e, f, g**. Em cada linha de segmento, coloque um resistor em série.

| Segmento do display | Resistor em série | Pino Arduino |
|---|---:|---:|
| a | 220–330 Ω | D3 |
| b | 220–330 Ω | D4 |
| c | 220–330 Ω | D5 |
| d | 220–330 Ω | D6 |
| e | 220–330 Ω | D7 |
| f | 220–330 Ω | D8 |
| g | 220–330 Ω | D9 |
| Pinos comuns do display | — | GND (cátodo comum) |

**Botões:** conecte um terminal do botão INICIAR ao D11 e o outro ao GND. Faça o mesmo com o botão SORTEAR no D12. Não é necessário resistor externo, pois o programa ativa os resistores internos de pull-up.

**A0:** deixe sem conexão para variar a semente pseudoaleatória. Essa técnica não garante aleatoriedade criptográfica, mas é suficiente para uma demonstração didática.


## Como carregar e testar

1. Monte o circuito com o Arduino desconectado do USB.
2. Abra `src/sorteio_7_segmentos.ino` na Arduino IDE.
3. Selecione **Arduino Uno** em **Ferramentas > Placa** e a porta correta em **Ferramentas > Porta**.
4. Faça upload do sketch.
5. Pressione INICIAR: números devem mudar rapidamente.
6. Pressione SORTEAR: a animação para e um número fica no display.
7. Pressione INICIAR novamente: o display apaga; pressione outra vez para começar nova animação.

## Diagrama da montagem

A imagem `montagem.png` mostra o arranjo em protoboard adaptado à referência. A pinagem indicada corresponde ao sketch: D3–D9 para os segmentos, D11 para INICIAR e D12 para SORTEAR. Use um resistor de 220–330 Ω em série com cada segmento (7 resistores no total) e ligue o(s) cátodo(s) comum(ns) ao GND.

![Diagrama da montagem do sorteador](montagem.png)
