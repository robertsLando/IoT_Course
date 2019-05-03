# Guida Installazione InfluxDB e GUI su Raspberry Pi

Questa guida serve per installare InfluxDB e l'interfaccia grafica per la creazione dei database e query.

## Installazione InfluxDB

Come prima cosa andiamo ad installare InfluxDB, quindi andiamo ad **aprire il terminale** e digitiamo i seguenti comandi:

`curl -sL https://repos.influxdata.com/influxdb.key | sudo apt-key add -`
_______________________________________________________

`echo "deb https://repos.influxdata.com/debian stretch stable" | sudo tee /etc/apt/sources.list.d/influxdb.list`
_______________________________________________________

`sudo apt update`
_______________________________________________________

`sudo apt install influxdb`
_______________________________________________________

`sudo systemctl enable influxdb`
_______________________________________________________

`sudo systemctl start influxdb`
_______________________________________________________

Ottimo, ora abbiamo installato correttamente InfluxDB sul nostro Raspberry.

## Installazione e configurazione Chronograf

Andiamo ad installare l'interfaccia grafica per la gestione di InfluxDB. Una volta fatto sara' possibile gestire tutto il DB grazie all'interfaccia grafica.

`sudo apt-get install chronograf`

Ottimo, ora appena finita l'installazione procediamo ad avviarlo e far si che si avvii automaticamente al boot del Raspberry.

`sudo systemctl start chronograf`

`sudo systemctl enable chronograf`

**Consiglio di fare un riavvio del Raspberry.**

_______________________________________________________

Ora **andiamo su un browser** e andiamo a scrivere l'indirizzo IP del raspberry e la porta 8888, per esempio: http://indirizzoipraspberry:8888 

Da qui possiamo vedere la Welcome Page, clicchiamo su Get Started

![](https://i.imgur.com/Pjihl2D.png "Welcome Page InfluxDB")

La prossima page e' la configurazione del collegamento tra Chronograf e InfluxDB, **ci basta inserire l'indirizzo IP del raspberry e lasciare la porta preconfigurata** di InfluxDB (a meno che non la si abbia cambiata).

![](https://i.imgur.com/tvRg7HW.png "Page configurazione")

Ora sulla schermata delle Dashboard clicchiamo sul pulsante **Skip** che troviamo in fondo alla schermata web.

Stesso identico processo per quanto riguarda la schermata Kapacitor Connection, premere il pulsante **Skip**.

Una volta finito il setup iniziale clicchiamo su **View All Connection** e abbiamo finito.

Ora si potra' gestire tutto il DB semplicemente via Interfaccia Web.