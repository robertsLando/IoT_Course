#Installare e configurare Microsoft VS Code con GitHub su Linux

## Installare Microsoft VS Code su Linux

Per installare cliccare su questo [Link di download diretto](https://go.microsoft.com/fwlink/?LinkID=760868) di Microsoft VS Code.

Una volta scaricato clicchiamoci sopra e facciamo click poi sul pulsante installa.


## Passi per configurare GitHub su VS Code

1. Per prima cosa dobbiamo andare ad aprire un terminale e scrivere il comando per installare git che e' `sudo apt-get install git`

2. Una volta fatto quello dobbiamo andare a creare una semplice repository locale sul nostro computer (per esempio andiamo su documenti e creiamo la cartella progetti).

3. Andiamo ora sulla repository GitHub da copiare e selezioniamo e copiamo il link per clonarla.

4. Andiamo su Visual Studio Code --> Select File --> Add Folder to Workspace --> e selzioniamo ora la cartella locale creata precedentemente.

5. Andiamo ad aprire il terminale, e scriviamo questi comandi:

`git config --global user.name <github userID>`

`git clone <url copiato precedentemente dalla repository di github>`

`git config --global user.email "latua@email"`

`git config --global user.name "nomeutente"`

Questo e' tutto...ora dalla scheda Source Control si dovrebbe vedere il contenuto della cartella ed e' anche possibile eseguire dei pull o altro.