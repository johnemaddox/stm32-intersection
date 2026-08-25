# TRAFFIC SIGNAL INTERSECTION SCHEMATIC

## LED Circuit
```
  QA:15 ----[ 220Ω ]---->|----.  (North Green)
  QB:01 ----[ 220Ω ]---->|---.|  (North Red)
                              |
                              |
  QC:02 ----[ 220Ω ]---->|---.|  (East Green)
  QD:03 ----[ 220Ω ]---->|---.|  (East Red)
                              |
                              |
  QE:04 ----[ 220Ω ]---->|---.|  (South Green)
  QF:05 ----[ 220Ω ]---->|---.|  (South Red)
                              |
                              |
  QG:06 ----[ 220Ω ]---->|---.|  (West Green)
  QH:07 ----[ 220Ω ]---->|---.|  (West Red)
                              |
                              v
                         [ GND RAIL ]
```

## Pinouts
```
                    +--------------------+
                    |     SN74HC595N     |
                    |   SHIFT REGISTER   |
                    +--------------------+
    (North Red) <-- | 01:QB       VCC:16 | <-- [ PWR RAIL ]
   (East Green) <-- | 02:QC        QA:15 | --> (North Green)
     (East Red) <-- | 03:QD       SER:14 | <-- CN5P7:MOSI/D11
  (South Green) <-- | 04:QE       ~OE:13 | <-- [ GND RAIL ]
    (South Red) <-- | 05:QF      RCLK:12 | <-- CN8P3:Latch/A2
   (West Green) <-- | 06:QG     SRCLK:11 | <-- CN5P5:SCK/D13
     (West Red) <-- | 07:QH    ~SRCLR:10 | <-- [ PWR RAIL ]
   [ GND RAIL ] --> | 08:GND      QHs:09 | --- (NC)
                    +--------------------+

                    +---------------------+
                    | STM32 NUCLEO-G071RB |
                    +---------------------+
                    |                     |
                    |       CN5P5:SCK/D13 | --> SRCLK:11
                    |      CN5P7:MOSI/D11 | --> SER:14
                    |                     |
                    | [B1 User Button]    |
                    | (PC13 - Onboard)    |
                    |                     |
   [ PWR RAIL ] <-- | CN6P4:3v3           |
   [ GND RAIL ] <-- | CN6P6:GND           |
                    |                     |
        RCLK:12 <-- | CN8P3:Latch/A2      |
                    +---------------------+
```

## POWER & DECOUPLING
```
                              CN6P4:3v3
                                  |
   [ PWR Rail ] ------+-----------+-----------+
                      |           |           |
                      v           |           v
                    VCC:16        |       ~SRCLR:10
                                  v
                            [ C1: 0.1µF ]--.
                                           |
                 08:GND       ~OE:13       |
                   |             |         |
   [ GND Rail ] ---+-------------+---------+
                   |
                   v
             [ CN6P6 GND ]
```