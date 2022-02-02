# Projekt centrali alarmowej
## TM-AVR-STM-LAB

Centrala alarmowa z hasłem , 6-wejść typu NC oraz wyjściem przekaźnika naruszenia typu NO.

![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/2.jpg)

## Cechy projektu:
* MCU: AtMega32A w obudowie TQFP44
* Wyświetlacz 2x16 ze sterownikiem HD44780
* Zasilanie 12V DC-IN Max:1,2A
* Zasilacznie czujek 12V DC ~1A obc.
* Wyjście naruszenia typu NO ~1A obciążenie styków
* Wejścia czujek NC wyzwalane stanem niskim
* Pamięć naruszeń
* Kontrola kontrastu wyświetlacza
* Diody LED statusu centrali (alarm,uzbrojenie,stan spoczynku,odliczanie)
* 6 przycisków w roli klawiatury (ESC,1-4,ENTER)
* Dioda LED zasilania

## Działanie centrali:

Centrala posiada 2 tryby, uzbrojony oraz nieuzbrojony. Po wciśnięciu przycisku ENTER następuje przejście do funkcji wpisywania hasła.
Do wpisywania hasła dostępne mamy przyciski 1-4, ENTER oraz ESC który kasuje błędnie wpisaną liczbę .
Po poprawnym wpisaniu hasła następuje odliczanie 20sekund symulujące czas na wyjście z mieszkania. Po upływie czasu uzbrajania centrali,
wejścia czujek aktywują się. Wejścia ustawione są w tryb NC ze zwarciem do GND, kiedy jedna z czujek przez minimum 1,6sek 
zostanie aktywowana zaczyna się przejście do funkcji wpisywania hasła na które ma się ponowne 20sekund. Po upływie tego czasu,
bądź 3-krotnym złym wpisaniu hasła następuje wyzwolenie alarmu i załączenie wyjścia. Podczas trwanai alarmu można przejść do funkcji 
wpisywania hasła przyciskiem ENTER. Po rozbrojeniu centrali po alarmie zapamiętane zostaje zdarzenie naruszenia systemu, po następnym uzbrojeniu
centrali błąd się kasuje.

## Mikrokontroler Atmega32A:

![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/pinout.jpg)

 * Taktowanie w projekcie: 16MHz zewnętrzne
 * Zasilanie układu: 5V DC
 * Programowanie : złącze ISP
 * 1kB EEPROM
 * 2kB SRAM
 * 32kB flash
 
![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/1.jpg)

## Zdjęcia schematu oraz płytki z programu EAGLE:

![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/sch1.png)
![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/sch2.png)
![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/sch3.png)
![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/sch4.png)
![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/board1.png)
![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/board2.png)

## Zdjęcia wykonanego układu oraz filmik prezentacyjny:

![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/2.png)
![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/3.png)
![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/4.png)
![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/5.png)
![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/6.png)
![](https://github.com/PawZar/TM-AVR-STM-LAB/blob/main/Foto/IMG_4203.MOV)
