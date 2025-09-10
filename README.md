# Simulador de Câmbio - Eixos X e Y com Arduino Nano

Este projeto implementa a leitura das marchas de um câmbio manual para uso em **simuladores de corrida** utilizando um **Arduino Nano**.  
O sistema converte o estado das marchas em sinais **PWM** para dois eixos: **Y (vertical)** e **X (horizontal)**, simulando a posição real do câmbio.

---

## Hardware

- Arduino Nano
- Sensores de fim de curso ou switches para cada marcha:
  - 1ª: D12
  - 2ª: D2
  - 3ª: D11
  - 4ª: D3
  - 5ª: D10
  - 6ª: D4
  - Ré: D5
- Saídas PWM:
  - Eixo Y: D9
  - Eixo X: D6
- Alimentação: 5V (pino 5V ou VIN conforme explicado)

---

## Lógica do Código

1. **Leitura das marchas**  
   - Todos os switches usam `INPUT_PULLUP`.  
   - Uma função genérica `getMarchaAtiva()` verifica qual marcha está acionada.  
   - Se nenhuma marcha estiver acionada, considera-se **Neutro**.

2. **Eixo Y (vertical)**  
   - Marchas 1, 3, 5 → PWM alto (~90% = 230)  
   - Marchas 2, 4, 6 e Ré → PWM baixo (~10% = 26)  
   - Neutro → PWM médio (~50% = 127)

3. **Eixo X (horizontal)**  
   - Simetria em torno do neutro (127):  
     - Esquerda 1 → 77  
     - Esquerda 2 → 102  
     - Direita 1 → 152  
     - Direita 2 → 178  
   - Mapeamento de marchas:
     - 1ª → Esquerda 1  
     - 2ª → Esquerda 1  
     - 3ª → Esquerda 2  
     - 4ª → Esquerda 2  
     - 5ª → Direita 1  
     - 6ª → Direita 1  
     - Ré → Direita 2  
     - Neutro → 127

4. **Debug**  
   - A cada mudança de marcha, o Serial imprime de forma compacta:
   ```
   (marcha, pwmX, pwmY)
   ```
   - Exemplo: `(3, 102, 230)` → marcha 3ª, PWM eixo X = 102, PWM eixo Y = 230

---

## Diagrama ASCII dos eixos e PWM

```
         Y (Vertical PWM)
        Upgear 230
   5th  *
   3rd  *
   1st  *
        |
      127 (Neutro)
        |
   2nd  *
   4th  *
   6th  *
   R    *
        Downgear 26

         X (Horizontal PWM)
Left 77      Left 102        127        Right 152      Right 178
  L1            L2          N           R1             R2
1st 2nd       3rd 4th                  5th 6th         R
```

---

## Benefícios do Código

- Limpo e enxuto, sem dezenas de `if/else` ou `switch/case` duplicados.  
- Mapas diretos (`mapaPWMY` e `mapaPWMX`) permitem alterar PWM facilmente.  
- Debug compacto e fácil de monitorar no **Serial Monitor**.  
- Escalável para futuras melhorias, como gráficos ou integração com outros sistemas de simulação.

---

## Instalação / Uso

1. Conecte os switches aos pinos indicados e ao GND do Arduino.  
2. Conecte os pinos PWM aos sistemas que vão ler os sinais.  
3. Abra o código no **Arduino IDE**.  
4. Configure a **placa Arduino Nano** e a porta correta.  
5. Faça upload do código.  
6. Abra o **Serial Monitor** para visualizar o debug `(marcha, pwmX, pwmY)`.

---

## Notas

- Não é possível acionar múltiplas marchas simultaneamente mecanicamente.  
- Valores PWM podem ser ajustados conforme necessidade do simulador.  
- Delay de 100ms garante estabilidade e evita spam no Serial Monitor.

---

## Estrutura do Código

- `pinosMarchas[]` → lista de pinos das marchas  
- `mapaPWMY[8]` → mapa direto de PWM para eixo Y  
- `mapaPWMX[8]` → mapa direto de PWM para eixo X  
- `getMarchaAtiva()` → função genérica para retornar marcha ativa  
- Loop principal → aplica PWM e envia debug apenas quando a marcha muda
```

