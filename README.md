# PROJET 42 : 🌐 Ft_irc 


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

## Les clients:

### [NetCat (nc)](https://www.varonis.com/fr/blog/netcat-commands)

nc est un client obligatoire demander par le sujet. Il s'utilise depuis un terminal est se lance de cette facon :
```
nc <addresse du serveur> <port du serveur>
```
pour ma part
```
nc localhost 8080
```
depuis nc on doit tout ecrire en brute, c'est a dire que nc ne fait rien a notre place, et ne nous affiche rien par lui meme, c'est donc au serveur d'envoyer les infos sur nc.

#### La structure des commandes nc

Sur nc, la struture est la plus part du temp comme ceci :
``` 
<COMMAND> <Target> <L'information a transmettre> <autres options>
```
par exemple pour la commande privmsg, si on veut parler a ilan et noa:
```
PRIVMSG ilan,noa hello world
```
ici la commande est ```PRIVMSG```, les targets ```ilan et noa``` et le message ```hello world```


### [Hexchat](https://hexchat.github.io)

Hexchat est un des client possible que l'on peux ajouter au projet comme demande par le sujet, j'ai decide de l'utiliser car la premiere fois que j'ai vue IRC c'etait sur le client hexchat, il m'a ete recommande, il permet le transfere des fichiers automatiques (bonus), on peut afficher les logs de communication entre client et serveur et puis je le trouve relativement accessible et facile a comprendre.

Il s'utilise depuis son application, pour la telecharger :
```
flatpak install flathub io.github.Hexchat
```

Une fois lancer tu peux soit tester des clients deja relie a des serveurs pour que tu comprennes comment cela doit fonctionner, personnellement j'ai utilise 2600net, soit tu peux te lancer sur la creation de ton client pour ton serveur

Si c'est le cas alors, tu peux faire :

-> En haut dans les 4 cases tu peux definir:
--> ton nickname
--> ton deuxieme nickname
--> ton troisieme nickanme
--> ton nom de user

-> ```Add``` et tu peux choisir le nom d'appellation de ton serveur.

-> ```Edit``` tu va trouver ceci :

<image menu entree hexchat>

sur la ligne en haut il faut que tu la modifie pour qu'elle soit en lien avec les parametres que tu as mis sur le set de ton serveur:
exemple:
tu lance ton serveur avec ces parametres:
```
./ircserver 8080 123
```
alors la ligne en haut doit etre
```
localhost/8080
```
le localhost est dans tout les cas ici car on heberge le serveur sur notre machine et on ne le partage pas a tous
et ensuite il y a le port sur lequel ton serveur est ouvert.

apres ceci sur la base de l'exemple il faut aussi que tu renseigne le mot de passe au client hexchat pour que de lui meme il donne les commandes a ton serveur:
tu dois avoir ceci visuellement:

<image page edit>

tu peux faire autrement et tester les autres facons si tu en a envie mais personnelement j'ai choisie ceci.
apres cela tu peux faire ```close```
et ensuite ```connect``` depuis ton Client hexchat cree.

Apres cela tu te retrouve avec un client qui essaye perpetuellement de se connecter a ton serveur.

Des choses interressantes a savoir:
- **🚧!!a verifier🚧!!** Window/raw_logs -> ceci t'affiche les logs de communication entre le serveur et le client, ca te permet de comprendre ce que tu va recevoir et se que tu lui envoie, je te conseille de regarder le raw log d'autre client que le tiens pour que tu comprennes ce que tu as a faire
- **🚧!!a verifier!!🚧** Hexchat/server_select -> tu peux creer plusieurs clients en changeant le nom du client et en te connectant toujours a ton serveur.


#### La structure des commandes hexchat

Sur hexchat, la struture est la plus part du temp comme ceci :
``` 
/<COMMAND> <Target> <L'information a transmettre> <autres options>
```
par exemple pour la commande privmsg, si on veut parler a ilan et noa:
```
/privmsg ilan,noa hello world
```
ici hexchat va transformer ma ligne en
```
PRIVMSG ilan,noa :hello world
```
on peux voir ceci depuis la fenetre raw_logs.

Ici la commande est ```PRIVMSG```, les targets ```ilan et noa``` et le message ```hello world```

La subtilite de hexchat c'est son interpretation des commandes qu'il recoit et t'envoie en respectant la norme IRC et aussi son interpretation des lignes que tu va lui envoyer, par exemple quand des clients sont dans un channel, si hexchat recoit selon la commande ```WHO``` qu'une personne a un ```@``` avant son nickname hexchat l'interprete est le presente comme operateur du channel (la pastille verte a coter du nickanme dans la liste)

# Manda

Tout ce que je vais dire va etre basse sur la norme [RFC2119](https://modern.ircdocs.horse)

## [La connection au serveur](https://modern.ircdocs.horse/#connection-messages) 

La connection au serveur doit suivre une logique bien precise.

Les commandes a faire:
1) ```PASS``` : va permettre de donner le mot de passe attendu par le serveur.
2) ```NICK``` : va permettre de definir un nickname.
3) ```USER``` : va permettre de definir un username.

Hexchat peux t'envoyer aussi ```CAP LS 302```, je te laisse te renseigner.

Personnellement j'ai fais un switch case d'un enum qui definie les grades de connection:

```cpp
enum State {
	 CONNECTED,
	 AUTHENTICATED,
	 REGISTERED,
		USER
};
```

```cpp
switch(state){
  case CONNECTED:
    handlePass();
  case AUTHENTICATED:
    handleNick();
  case REGISTERED:
    handleUser();
  case USER:
    handleCommands();
}
```

Une fois connecte, le client dois recevoir [des messages de bienvenue du serveur](https://modern.ircdocs.horse/#rplwelcome-001).

## Les commandes a gerer :

### [QUIT](https://modern.ircdocs.horse/#quit-message)

### [JOIN](https://modern.ircdocs.horse/#join-message)

### [PART](https://modern.ircdocs.horse/#part-message)

### [TOPIC](https://modern.ircdocs.horse/#topic-message)

### [INVITE](https://modern.ircdocs.horse/#invite-message)

### [KICK](https://modern.ircdocs.horse/#kick-message)

### [MODE](https://modern.ircdocs.horse/#mode-message)
#### le - pour enlever le mode et le + pour ajouter
#### i -> activer/desactiver le mode invitation uniquement
#### t -> activer/desactiver l'obligation d'etre operator pour modifier le topic
#### l -> activer/desactiver une limite de client sur le serveur
#### k -> activer/desactiver la connection avcec un mot de passe au channel
#### o -> donner/retirer les permissions d'operateur a un client

### [PRIVMSG](https://modern.ircdocs.horse/#privmsg-message)

### [WHO](https://modern.ircdocs.horse/#who-message)
pas obligatoire qu'il fonctionne de base mais sa logique va servire pour join

## [Les Reponses IRC](https://modern.ircdocs.horse/#numerics)

### Les RPL
Les reponses RPL sont des formats de reponses aux commandes envoyées

### Les ERR
Les reponses ERR sont des formats d'erreurs à renvoyer au client

## La logique de la structure de notre code

On a utilise plusieurs [std::map](https://cplusplus.com/reference/map/map/) qui nous on etait utile pour stocker les clients, les channels, les clients dans les channels, les grades des clients dans les channels...

# BONUS

## Le transfert de fichier

Sur hexchat, le transfert de fichier se fait de base si votre serveur est bien defini.
Pour le realiser 🚧!!!A Faire!!!🚧

## LE BOT

```bash
make bonus
./ircserver_bonus <port> <password>
```

Selon mon appellation durant le projet, mon bonus s'appelle le jeu du Gamble, je me suis inspire d'un jeux que j'ai vue en regardant une video sur le jeux video Schudule. J'ai appris après que c'est un jeu de soirée qui s'appelle en réalité [Le Bus Magique](https://psycatgames.com/fr/magazine/party-games/ride-the-bus/).

### Le principe du jeux
-> tu mise une somme
-> le croupier tire 4 cartes aleatoires allant de As(1) a roi(13)
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

apres le quatrieme tour le jeux s'arrete et tu peux recommencer jusqu'a que tu arretes ou que tu n'ai plus d'argent  

### Comment jouer sur mon Irc
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

Apres avoir envoyer ```PLAY``` directement depuis le channel #gambleRoom, sa vous lancera en partie est vous demandera de choisir le montant a miser.
A tout moment vous pouvez faire ```OUT``` pour sortir du jeux.

### Classement Jeux du Gamble

LOGIN 42		| Argent total
------------------------+---------------
alualik			| 1060
matde-ol		| 1050
mblanch			| ?


## Credit

Readme realise par Ilan Nowak--Glandier (login: inowak--)

Le projet IRC a ete realise par:
nom 			| login 42
------------------------+------------
Ilan Nowak--Glandier	| inowak--
Noa Charbog		| ncharbog

---

> Ce README est une base et doit être adapté selon vos implémentations spécifiques et vos choix techniques.
