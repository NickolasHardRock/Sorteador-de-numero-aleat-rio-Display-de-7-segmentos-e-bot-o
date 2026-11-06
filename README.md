# Sorteador de números com display de 7 segmentos

Projeto acadêmico com Arduino Uno. O display mostra números aleatórios rapidamente; o botão **SORTEAR** interrompe a animação e deixa visível o número escolhido.

## Funcionamento

- **INICIAR (D11):** liga a animação. Se pressionado novamente durante a animação, apaga o display.
- **SORTEAR (D12):** para a animação e exibe um número aleatório de **0 a 9**. Para iniciar outro sorteio, pressione INICIAR e depois SORTEAR.
- A animação atualiza aproximadamente a cada 55 ms.
- Os botões usam `INPUT_PULLUP`; portanto, cada botão liga o pino correspondente ao GND quando pressionado.

## Materiais

- Arduino Uno (ou compatível)
- Display de 7 segmentos de **1 dígito, cátodo comum**
- 7 resistores de 220 Ω a 330 Ω (um por segmento)
- 2 botões tácteis
- Protoboard e jumpers

> Confira o datasheet do display para identificar os pinos dos segmentos e os pinos comuns. A posição dos terminais varia entre modelos. Não conecte os LEDs do display diretamente ao Arduino sem resistores.

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

### Atenção ao tipo de display

Este sketch foi escrito para **cátodo comum**: os pinos comuns vão ao GND e `HIGH` acende cada segmento. Se seu display for **ânodo comum**, os pinos comuns devem ir a 5 V e a lógica dos segmentos precisa ser invertida (HIGH e LOW trocados nas funções `mostrarDigito()` e `apagarDisplay()`). Identifique o tipo antes de alimentar o circuito.

## Como carregar e testar

1. Monte o circuito com o Arduino desconectado do USB.
2. Abra `src/sorteio_7_segmentos.ino` na Arduino IDE.
3. Selecione **Arduino Uno** em **Ferramentas > Placa** e a porta correta em **Ferramentas > Porta**.
4. Faça upload do sketch.
5. Pressione INICIAR: números devem mudar rapidamente.
6. Pressione SORTEAR: a animação para e um número fica no display.
7. Pressione INICIAR novamente: o display apaga; pressione outra vez para começar nova animação.

## Ajustes

- Para alterar a rapidez, mude `intervaloAnimacao` no início do sketch. Um número menor deixa a animação mais rápida.
- Para sortear em outra faixa, altere `random(0, 10)` e prepare os padrões e a exibição para essa faixa. O exemplo foi mantido em um dígito (0–9).
- Se os números aparecerem com segmentos incorretos, confirme o pinout do display e ajuste a ordem `pinosSegmentos`.

## Estrutura

```text
sorteio-7-segmentos/
├── README.md
└── src/
    └── sorteio_7_segmentos.ino
```

## Observação sobre o botão

O botão SORTEAR é lido continuamente no `loop()` com debounce por software. Isso permite interromper rapidamente a animação sem usar interrupção externa de hardware e evita conflito com os pinos dos segmentos.

## Diagrama da montagem

A imagem `montagem.png` mostra o arranjo em protoboard adaptado à referência. A pinagem indicada corresponde ao sketch: D3–D9 para os segmentos, D11 para INICIAR e D12 para SORTEAR. Use um resistor de 220–330 Ω em série com cada segmento (7 resistores no total) e ligue o(s) cátodo(s) comum(ns) ao GND.

![Diagrama da montagem do sorteador](montagem.png)
