# Digitale Input Output

## Pinout

![WEMOS D1 Mini](../assets/images/WEMOS-D1-mini.png)

[Pin reference](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)

## Digitale Input

```arduino
pinMode(D1, INPUT);
```

```arduino
boolean high = digitalRead(D1);
```

## Digitale Output

```arduino
pinMode(D1, OUTPUT);
```

```arduino
digitalWrite(D1, HIGH);
```

## Analoge Input
```arduino
int value = analogRead(A0);
```

## PWM Output

![PWM](../assets/images/pwm.png)

```arduino
pinMode(D1, OUTPUT);
```

```arduino
analogWrite(D1, 512);
```
