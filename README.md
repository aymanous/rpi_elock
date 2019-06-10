# RPI ELOCK

## Etapes d'utilisation :

  1. Copie du repository Github sur votre machine :
  </br>git clone https://github.com/aymanous/rpi_elock.git

  2. Paramètrage de l'IP du serveur
  </br>Dans 'utils.h' : modifer la valeur de "BASE_URL" par l'IP du serveur exposant l'API eLock
  
  3. Lancement du projet (via Makefile)
  </br>make

## Technologies utilisées :
  - PYTHON
  - C (+ CURL + THREADS...)

## Dépendances :
  Ce module du projet eLock nécessite au préalable :
  - Le lancement de l'API eLock (+BDD)
  
