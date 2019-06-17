# Database su MySql e implementazione su NodeRed

## Copiare xampp sul desktop
Andiamo a copiare `IRIGEM_xampp.exe` sul desktop e facciamo il doppio click sopra per estrarre il tutto. Una volta fatto ci troviamo la cartella xampp sul desktop.

## Configurare xampp
Ora andiamo dentro la cartella xampp, e avviamo `setup_xamppp.bat` (si apre un terminale) e una volta finito il processo di configurazione automatica clicchiamo un qualunque tasto.

Una volta fatto quello scritto sopra andiamo ad avviare `xampp_control.exe` e selezioniamo al lingua. Se siamo in info3 dobbiamo andare sul servizio Apache e clicchiamo su Config, e poi clicchiamo sul primo file `Apache (httpd.conf)`. Scorrendo dobbiamo trovare la voce "Listen 80" e cambiamola in "Listen 8080".

## Creare il Database e l'utente su phpmyadmin

Andiamo su http://localhost:8080/phpmyadmin e andiamo sulla voce (nella colonna di sinistra) **nuovo** e specifichiamo il nome del DB e clicchiamo su Crea.

Andiamo a cliccare sull'icona della casetta (Home) sulla colonna sinistra di phpmyadmin e andiamo sulla voce **Account utenti** e clicchiamo su **Aggiungi account utente**, specifichiamo:
1. nome utente
2. Nome host (qui lasciamo `Qualsiasi host` e la `%`)
3. password
4. re-inserire la password
5. sulla voce genera password ripetiamo la password scritta precedentemente.

Nella sezione **Privilegi Globali** mettiamo la spunta su

..*Dati
..*Struttura

e così abbiamo garantito gli accessi. 

## Configurare il nodo Mysql su Nodered

Andiamo su nodered, prendiamo il nodo di Mysql e facciamo click per configurarlo.

Andiamo a cliccare sulla "matita" e configuriamo così:

1. Host: andiamo a mettere l'ip dove abbiamo avviato MySql
2. User: l'utente che abbiamo creato
3. Password: la password che abbiamo scritto
4. database: il nome del database che abbiamo creato
5. Timezone: Bho non lo abbiamo configurato

## FINEEE

