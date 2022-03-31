# Thermal modification on VCK5000

## Intro 

Anyone who receives this card would complain about it. As an student who majors in eletronics and information engineering, I cannot put up with it.

After checking out its fan connection(12V), I came up with the following approach.

**Note: The changes made to VCK5000’s thermal is not recommended, for it cannnot endure long  time, full power testing.(Only about 10min for performance testing). But this is the one of the compromise of the noise for individual developers.**

## Approach

- unplugged the connected of the fan, use an adapter to stretch the wires.
- using a UNO board that can be bought easily with a cheap price
- using a 5V to power the fans, and using a PWM to control it(also 5V max).
- further more if you have configurable power supply, you can get whatever fan speed you want.

Adapter used:

<img src="..\doc-imgs\image-20220331145605872.png" alt="adapter img" style="zoom: 25%;" />

UNO board Used :

![Arduino UNO](..\doc-imgs\Arduino_UNO.jpeg)

final outline:

![image-20220331145833290](..\doc-imgs\image-20220331145833290.png)



