# ft_irc

## Description

**ft_irc** est un projet développé en C++ qui consiste à implémenter un serveur IRC (Internet Relay Chat) basique conforme à la norme IRC, personnelement j'ai utilisé [RFC2119](https://modern.ircdocs.horse). Ce projet a pour objectif de vous familiariser avec la gestion des sockets réseau, de vous ameliorer en C++, la gestion d’événements et les protocoles de communication.

## Objectifs du projet

- Comprendre le fonctionnement du protocole IRC et ses commandes principales.
- Gérer plusieurs connexions clients en simultané (multi-clients).
- Implémenter la gestion des canaux (channels), des utilisateurs, des modes, et des messages privés/publics.

## Fonctionnalités principales

- Connexion de plusieurs clients au serveur via un client IRC (ex. : nc, hexchat,...).
- Authentification des utilisateurs avec un mot de passe serveur.
- Création, jointure, et gestion des channels IRC.
- Envoi de messages publics (dans un channel) ou privés (entre utilisateurs).
- Gestion de commandes IRC de base : NICK, USER, JOIN, PART, PRIVMSG, QUIT, etc.
- Gestion des modes utilisateurs et channels.

## Structure de mon IRC

```txt
ft_irc
├── bonus/
│   ├── main.cpp
│   ├── server.cpp
│   └── client.cpp
├── includes/
│   └── colors.hpp
├── manda/
│   ├── Client/
│   │   ├── Client.cpp
│   │   └── Client.hpp
│   ├── Channel/
│   │   ├── Channel.cpp
│   │   └── Channel.hpp
│   ├── Commands/
│   │   ├── handleInvite.cpp
│   │   ├── handleJoin.cpp
│   │   ├── handleKick.cpp
│   │   ├── handleMode.cpp
│   │   ├── handlePart.cpp
│   │   ├── handlePrivmsg.cpp
│   │   ├── handleQuit.cpp
│   │   ├── handleTopic.cpp
│   │   └── handleWho.cpp
│   ├── includes/
│   │   ├── Irc.hpp
│   │   └── IRCMacro.hpp
│   ├── handleCommands.cpp
│   ├── handleConnection.cpp
│   ├── main.cpp
│   ├── server.cpp
│   └── utils.cpp
├── Makefile
└── README.md
```
# Manda

# BONUS
```bash
make bonus
./ircserver_bonus <port> <password>
```

Selon mon appellation durant le projet, mon bonus s'appelle le jeu du Gamble. J'ai appris après que c'est un jeu de soirée qui s'appelle en réalité [Le Bus Magique](https://psycatgames.com/fr/magazine/party-games/ride-the-bus/).

## Le principe du jeux
-> tu mise une somme
-> le groupier tire 4 cartes aleatoires allant de As(1) a roi(13)
-> le jeux se base sur 4 tours
-> si tu rate un pronostique tu pers ta mise et ton avancement dans les tours
-> entre chaque tour tu as la possibilte de te retirer et donc prend le multiplicateur actuel

Premier tour:
- tu parie pour un X2 de ta mise de depart sur es ce que la premiere des 4 cartes est rouge ou noir
  
Deuxieme tour:
- tu parie pour un X3 de ta mise de depart sur es ce que la deuxieme carte est inferieur ou superieur a la premier carte
- si la deuxieme carte est la meme que la premiere tu gagne dans tous les cas ce tour

Troisieme tour:
- tu parie pour un X5 de ta mise de depart sur es ce que la troisieme carte est entre la premiere et la deuxieme ou en dehors
- si la troisieme carte est la meme que la premiere ou la deuxieme la troisieme carte est concidere comme a l'interieur

Quatrieme tour:
- tu parie pour un X10 de ta mise de depart sur qu'elle est le symbole de la quatrieme carte, entre carreaux(club), coeur(heart), pique(spade), trefle(diamond)

apres le quatrieme tour le jeux s'arrete et tu peux recommencer jusqu'a que tu arretes ou tu n'a plus d'argent  

## Comment jouer sur mon Irc
```bash
./gamble <port> <password>
```
cette executable va lancer le client **GambleDealer**, qui va creer un salon **GambleRoom**, mettre une limitation de 2 personnes et va activer le mode *invation only* et va attendre qu'un autre client lui envoie en message prive ```GAMBLE```

nc
```nc
PRIVMSG GambleDealer GAMBLE
```
hexchat
```hexchat
/privmsg GambleDealer GAMBLE
```

par la suite le client va recevoir une invatation a rejoindre le channel GambleRoom, il pourra donc faire

nc
```nc
JOIN #GambleRoom
```
hexchat
```hexchat
/join #GambleRoom
```

Une fois arrive dans le channel il recevra se message :
```
--------------------------- command ---------------------------
'PLAY' : for play camble
'EXIT' : for exit
'BANK' : for bank amount
--------------------------- command ---------------------------
```
Chaque Client commence avec 100$ sur son compte si il tombe a 0 il se fera expluser du channel et devra se faire re-inviter et recevra gracieusement 10$.

Apres avoir fais
nc
```
PRIVMSG #GambleRoom PLAY
```
hexchat
```
/privmsg #gambleRoom PLAY
```
ou
```PLAY``` directement depuis le channel #gambleRoom

## Licence

Ce projet est sous licence MIT.

---

> Ce README est une base et doit être adapté selon vos implémentations spécifiques et vos choix techniques.
