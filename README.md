# project2
Student ID: 10602888		name: Riccardo		Surname: De Rosi
Student ID: 10661470		name: Marco		Surname: Corso
Student ID: 10628499		name: Luca		Surname: Lobriglio

Abbiamo creato diverse cartelle tra cui cfg, launch, maps, rviz, scripts, src, srv e cmakelists.
la cartella launch è quella principale dove sono presenti tutti i file launch per la creazione della mappa e per la localizzazione. ci sono 2 file per l'amcl, uno comprende i valori fissi dei parametri (noi variamo solo il valore di laser_max_range e laser_max_beam) e l'altro comprende i vari richiami per i pacchetti (rviz, mapsaver, hector_trajectory_server e map_server). ci sono altrettanti 2 file per il gmapping, uno comprende sempre i parametri della mappatura e l'altro il richiamo dei pacchetti (rviz e scan_merger). i valori da cambiare sono stati maxrange e manxurange (in gmapping), il primo è la distanza massima raggiungibile dal sensore e il secondo è la distanza che vogliamo noi per avere una mappa migliore. l'ultimo file è lo scan merger dove uniamo in un unico programma il sensore davanti e quello dietro. nello scan merger abbiamo cambiato i valori dei parametri in base ai valori dei due sensori (scritti del datasheet).
maps è dove salviamo le mappe.
Rviz contiene il file per aprire il programma rviz con già preimpostati tutti i valori.
src contiene il nodo (broadcaster) per creare la mappa.
scripts contiene i file per il salvataggio della mappa e della traiettoria.
per far partire i nodi basta lanciare uno dei due programmi (gmapping.launch o amcl.launch)
