# project2
Student ID: 10602888		name: Riccardo		Surname: De Rosi
Student ID: 10661470		name: Marco		Surname: Corso
Student ID: 10628499		name: Luca		Surname: Lobriglio

Abbiamo creato diverse cartelle tra cui cfg, launch, maps, rviz, scripts, src, srv e cmakelists.
La cartella launch è quella principale dove sono presenti tutti i file launch per la creazione della mappa e per la localizzazione. Ci sono 2 file per il gmapping, uno comprende sempre i parametri della mappatura e l'altro il richiamo dei pacchetti (rviz e scan_merger). Sono stati cambiati alcuni valori nel file .xml, diversamente da quelli predefiniti, per una migliore mappatura (in particolare il maxrange, ovvero la distanza massima raggiungibile dal sensore, e maxurange, ovvero la distanza che vogliamo noi per avere una mappa migliore).
Ci sono 2 file per l'amcl, uno comprende i valori dei parametri e l'altro comprende i vari richiami per i pacchetti (rviz, mapsaver, hector_trajectory_server e map_server). Modificando alcuni parametri all'interno del file .xml abbiamo cercato di ottenere la migliore localizzazione sulla mappa ottenuta attraverso il gmapping. 
maps è dove salviamo le mappe.
L'ultimo file è lo scan merger dove uniamo in un unico programma il sensore davanti e quello dietro. nello scan merger abbiamo cambiato i valori dei parametri in base ai valori dei due sensori (scritti del datasheet).
Rviz contiene il file per aprire il programma rviz con già preimpostati tutti i valori.
src contiene il nodo (broadcaster) per creare la mappa.
scripts contiene i file per il salvataggio della mappa e della traiettoria.
per far partire i nodi basta lanciare uno dei due programmi (gmapping.launch o amcl.launch)
per usare i nodi in python si deve richiamare il server map_saver_service tramite terminale.
per creare la mappa abbiamo usato la bag 1, invece per le traiettorie abbiamo usato le bag 2 e 3.
tf tree è formato da world map odom base_footprint base_link in serie e poi in parallelo laser_rear scan laser_front.
