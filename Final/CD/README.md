# Manuál pro práci s prototypem

Bakalářská práce: Výukový tutoriál pro využití Arduina v robotice

Autor: Jan Beran (xberan43)

## Instalace Arduino IDE

Pro programování desek Arduino je třeba si stáhnour program Arduino IDE, oficiální vývojové prostředí z webových stránek projektu Arduino: https://www.arduino.cc/en/main/software (tento postup je vhodný pro Windows a Ubuntu). Pro systém Fedora je možné využít RPM balíček (nainstaluje se příkazem *sudo dnf install arduino*), pro systém Fedora Silverblue a další systémy, podporující flatpak, je možné nainstalovat verzi ze serveru flathub.org pomocí *flatpak install cc.arduino.arduinoide*.

## Struktura zdrojových kódů na CD, jejich otevření v Arduino IDE

Zdrojové kódy jsou rozděleny podle jednotlivých obtížností ve složce Code, vždy ve verzi pro doplnění (složka Blank) a s již doplněnými funkcemi (Done). Pro otevření libovolné verze kódu z Arduino IDE je třeba:

* Pomocí nabídky *File-Open* nebo zkratky *CTRL + O* se vyvolá dialog pro otevření souboru.
* Nyní je třeba navigovat do správného adresáře podle toho, jaký kód má být otevřen. Například pro otevření prázdného kódu pro vysokoškolskou verzi tutoriálu bbude cesta *Code/University(VS)/Blank/trilobot*. V této cestě se již nachází mj. soubor trilobot.ino. Ten je třeba otevřít.
* Arduino IDE kromě něj otevře i všechny ostatní závislé soubory.

## Připojení Trilobota k počítači, případně ke zdroji napájení

Trilobot se připojuje k počítači jako normální deska Arduino, tedy prostřednictvím USB-B konektoru. Po fyzickém připojení je třeba zkontrolovat, zda byla deska psrávně rozpoznána:

* V nabídce *Tools* je třeba zkontrolovat položky Board, Processor a Port. 
	* Board: Arduino ?ega or Mega 2560
	* Processor: ATmega2560 (Mega 2560)
	* Port: Port se bude lišit v závislosti na portu, do jakého se Trilobot připojuje, aktuální obsazenosti portů atp. Jelikož je Arduino deska použitá v Trilobotovi originální, u správného portu by se měl zobrazit název desky (Arduino Mega 2560). 

Externí zdroj napájení je třeba pro provoz motorů. Pro jeho připojení disponuje Trilobot kulatým konektorem 5.5/2.1 mm. Doporučené charakteristiky zdroje jsou 12 V a 1 A. Bez tohoto zdroje není Trilobot schopen pohybu, ostatní senzory ovšem fungují beze změny, pokud je deska Arduino napájena z počítače. 

## Přeložení a nahrání kódu

Pokud je kód úspěšně otevřen a Trilobot připojen, je možné přeložit a nahrát kód pomocí tlačítka *Upload* v Arduino IDE (druhé tlačítko zleva s ikonkou šipky doprava). Překlad by měl proběhnout bez problémů. V ojedinělých případech může deska Arduino odmítat nový kód. V takovém případě je třeba zmáčknout reset na desce Arduino (červené tlačítko), případně odpojit a znovu připojit Trilobota, resetovat desku Arduino (červené tlačítko zhruba uprostřed), restartovat Arduino IDE, případně restartovat celý počítač. Tyto problémy jsou ojedinělé a jsou způsobeny samotnou deskou Arduino a autor této práce bohužel nemůže jakkoli ovlivnit jejich výskyt. 

Probíhající nahrávání indikuje dioda vlevo od displeje. Poté, co přestane blikat, je kód úspěšně nahrán. 

Součástí zdrojových kódů jsou i dvě knihovny třetích stran: TimerThree a LiquidCrystal_I2C. Obě knihovny jsou součástí zdrojových kódů z důvodu zjednodušení práce se zdrojovými kódy před tutoriálem. Není třeba je instalovat a jelikož nové verze knihoven nevycházejí, nehrozí ani problém se zastaráváním.  

## Programování robota Trilobot

Kód pro robota Trilobot lze využít i mimo tutoriál, v jakékoli verzi kódu je dostupná plná funkcionalita robota (podrobnější informace lze nalézt v technické zprávě, například v sekci 5.1 - Podrobnější popis tříd). 

## HW struktura robota Trilobot

Zapojení všech komponent lze nalézt v technické zprávě na obrázku 4.1. Zapojení odpovídá realitě včetně barvy kabelů. 