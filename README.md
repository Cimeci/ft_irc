# PROJET [42](https://42.fr/en/homepage/) : Ft_irc 🌐 


## Description

[**Ft_irc**](https://cdn.intra.42.fr/pdf/pdf/154982/fr.subject.pdf) est un projet développé en C++ qui consiste à implémenter un serveur IRC (Internet Relay Chat) basique conforme à la norme IRC, personnellement j'ai utilisé [RFC2119](https://modern.ircdocs.horse). Ce projet a pour objectif de vous familiariser avec la gestion des sockets réseau, de vous améliorer en C++, la gestion d’événements et les protocoles de communication.

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

### La structure de mon IRC

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
│   ├── ircUtils.cpp
│   ├── main.cpp
│   ├── server.cpp
│   └── utils.cpp
├── Makefile
└── README.md
```

---

## Les clients:

<details>
<summary><h2>NetCat</h2></summary>

### [NetCat (nc)](https://www.varonis.com/fr/blog/netcat-commands)

Nc est un client obligatoire demandé par le sujet. Il s'utilise depuis un terminal et se lance de cette facon :
```
nc <addresse du serveur> <port du serveur>
```
Pour ma part
```
nc localhost 8080
```
Depuis nc on doit tout écrire en brut, c'est-à-dire que nc ne fait rien à notre place, et ne nous affiche rien par lui-même, c'est donc au serveur d'envoyer les infos sur nc.

#### La structure des commandes nc

Sur nc, la struture est la plus part du temps comme ceci :
``` 
<COMMAND> <Target> <L'information à transmettre> <autres options>
```
Par exemple pour la commande privmsg, si on veut parler à ilan et noa:
```
PRIVMSG ilan,noa hello world
```
Ici la commande est ```PRIVMSG```, les targets ```ilan et noa``` et le message ```hello world```

</details>

<details>
<summary><h2>Hexchat</h2></summary>

### [Hexchat](https://hexchat.github.io)

Hexchat est un des clients possibles que l'on peut ajouter au projet comme demandé par le sujet, j'ai décidé de l'utiliser car la première fois que j'ai vu IRC c'était sur le client hexchat, il m'a été recommandé, il permet le transfert des fichiers automatiques (bonus), on peut afficher les logs de communication entre client et serveur et puis je le trouve relativement accessible et facile à comprendre.

Il s'utilise depuis son application, pour la télécharger :
```
flatpak install flathub io.github.Hexchat
```

Une fois lancée tu verras :

![image](https://github.com/user-attachments/assets/f0a3e571-b2e1-46ff-b4d8-90f3efee15ad)

Tu peux soit tester des clients déjà reliés à des serveurs pour que tu comprennes comment cela doit fonctionner, personnellement j'ai utilisé 2600net, soit tu peux te lancer sur la création de ton client pour ton serveur.

Si c'est le cas alors, tu peux faire :

-> En haut dans les 4 cases tu peux definir:
- ton nickname (que le serveur utilise)
- ton deuxieme nickname
- ton troisieme nickanme
- ton nom de user (que le serveur utilise)

-> ```Add``` et tu peux choisir le nom d'appellation de ton serveur

-> ```Edit``` tu vas trouver ceci :

![image](https://github.com/user-attachments/assets/5a4c5ca3-e872-421a-b835-5035ea4ae2b2)

La ligne du haut doit être modifiée pour qu'elle soit en lien avec les paramètres que tu as mis lors du lancement de ton serveur.

Tu lances ton serveur avec ces parametres:
```
./ircserver 8080 123
```
Alors la ligne en haut doit être
```
localhost/8080
```
Le localhost est dans tout les cas ici car on héberge le serveur sur notre machine et on ne le partage pas à tous et il y a le port sur lequel ton serveur est ouvert.

Ensuite sur la base de l'exemple il faut aussi que tu renseignes le mot de passe au client hexchat pour que de lui-même il donne les commandes à ton serveur:
tu dois avoir ceci visuellement:

![image](https://github.com/user-attachments/assets/5badaa14-87ab-46be-a11b-2dec6a940c9d)

Tu peux faire autrement et tester les autres facons si tu en as envie mais personnellement j'ai choisi ceci.

Après cela tu peux faire ```close``` et ensuite ```connect``` depuis ton Client hexchat crée.

Par la suite tu te retrouves avec un client qui essaie perpetuellement de se connecter à ton serveur.

![image](https://github.com/user-attachments/assets/a2a69d51-3348-41f7-a28b-6e6125b4790b)

Des choses intéressantes à savoir:
- **Window/Raw Logs** -> ceci t'affiche les logs de communication entre le serveur et le client, ça te permet de comprendre ce que tu va recevoir et ce que tu lui envoies, je te conseille de regarder le raw log d'autres clients que le tien pour que tu comprennes ce que tu as à faire.

Voici ce que tu pourrais voir :

![image](https://github.com/user-attachments/assets/c334bb41-10c6-45af-86e6-e1056ab6be42)

- **Hexchat/Network List** -> tu peux créer plusieurs clients en changeant le nom du client et en te connectant toujours à ton serveur.


#### La structure des commandes hexchat

Sur hexchat, la struture est la plupart du temps comme ceci :
``` 
/<command> <Target> <L'information à transmettre> <autres options>
```
Par exemple pour la commande privmsg, si on veut parler à ilan et noa:
```
/privmsg ilan,noa hello world
```
Ici hexchat va transformer ma ligne en
```
PRIVMSG ilan,noa :hello world
```
On peut voir ceci depuis la fenêtre raw_logs.

Ici la commande est ```PRIVMSG```, les targets ```ilan et noa``` et le message ```hello world```

La subtilité de hexchat c'est son interpretation des commandes qu'il recoit et t'envoie en respectant la norme IRC et aussi son interpretation des lignes que tu vas lui envoyer, par exemple quand des clients sont dans un channel, si hexchat recoit selon la commande ```WHO``` qu'une personne a un ```@``` avant son nickname hexchat l'interprête et le présente comme opérateur du channel (la pastille verte à côté du nickanme dans la liste)

</details>

---

# MANDA

## Le serveur

Pour le serveur vous allez avoir besoin d'utiliser:

Les structures :
- [sockaddr_in](https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html)
- liée à accept [socklen_t](http://manpagesfr.free.fr/man/man2/accept.2.html)
- liée à poll [pollfd](http://manpagesfr.free.fr/man/man2/poll.2.html)

Les fonctions :
- [socket](https://linux.die.net/man/2/socket)
- [setsockopt](https://linux.die.net/man/2/setsockopt)
- [bind](https://man7.org/linux/man-pages/man2/bind.2.html)
- [listen](https://man7.org/linux/man-pages/man2/listen.2.html)
- [send](https://man7.org/linux/man-pages/man2/send.2.html)
- [poll](http://manpagesfr.free.fr/man/man2/poll.2.html)
- [accept](http://manpagesfr.free.fr/man/man2/accept.2.html)
- [inet_ntop](https://man7.org/linux/man-pages/man3/inet_ntop.3.html)
- [ntohs](https://linux.die.net/man/3/ntohs)

## La logique de la structure de notre code

On en a utilisé plusieurs :
- [std::map](https://cplusplus.com/reference/map/map/) pour stocker les clients, les channels, les clients dans les channels, les grades des clients dans les channels...
    - std::map<int, Client *> _clientBook; -> ici j'index mon objet de ma class Client par rapport au socket du client.
- [enum](https://en.cppreference.com/w/cpp/language/enum) pour une meilleur lisibilité et une amélioration de la logique
- [macros](https://learn.microsoft.com/en-us/cpp/preprocessor/hash-define-directive-c-cpp?view=msvc-170) pour les RPL et ERR
- [find()](https://cplusplus.com/reference/algorithm/find/) bien utile pour trouver des valeurs dans nos maps

##  La gesstion des signaux :

Il faudra gérer les signaux ctrl D et ctrl C.
- le ctrl D sera à gerer sur nc, afin de traiter une commande, vous devez en premier lieu la reconstituer en concaténant les paquets reçus.
- le ctrl C vous permetera d'arrêter proprement votre serveur.

Tout ce que je vais dire va etre basé sur la norme [RFC2119](https://modern.ircdocs.horse)

## [La connection au serveur](https://modern.ircdocs.horse/#connection-messages) 

La connection au serveur doit suivre une logique bien precise.

Les commandes à faire:
1) ```PASS``` : va permettre de donner le mot de passe attendu par le serveur.
2) ```NICK``` : va permettre de définir un nickname.
3) ```USER``` : va permettre de définir un username.

Hexchat peut t'envoyer aussi ```CAP LS 302```, je te laisse te renseigner.

Personnellement j'ai fait un switch case d'un enum qui definit les grades de connection:

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

Une fois connecté, le client doit recevoir [des messages de bienvenue du serveur](https://modern.ircdocs.horse/#rplwelcome-001).

## Les commandes à gérer :

### [QUIT](https://modern.ircdocs.horse/#quit-message)

### [JOIN](https://modern.ircdocs.horse/#join-message)

### [PART](https://modern.ircdocs.horse/#part-message)

### [TOPIC](https://modern.ircdocs.horse/#topic-message)

### [INVITE](https://modern.ircdocs.horse/#invite-message)

### [KICK](https://modern.ircdocs.horse/#kick-message)

### [MODE](https://modern.ircdocs.horse/#mode-message)
<details>
<summary>Mode Options</summary>

- le - pour enlever le mode et le + pour ajouter
- i -> activer/désactiver le mode invitation uniquement
- t -> activer/désactiver l'obligation d'être operator pour modifier le topic
- l -> activer/désactiver une limite de client sur le serveur
- k -> activer/désactiver la connection avec un mot de passe au channel
- o -> donner/retirer les permissions d'opérateur à un client
</details>

### [PRIVMSG](https://modern.ircdocs.horse/#privmsg-message)

### [WHO](https://modern.ircdocs.horse/#who-message)
pas obligatoire qu'il fonctionne de base mais sa logique va servir pour JOIN

## [Les Reponses IRC](https://modern.ircdocs.horse/#numerics)

-> Mon fichier macros pour les réponses d'irc : [IRCMacros](manda/includes/IRCMacros.hpp)

### Les RPL
Les réponses RPL sont des formats de reponses aux commandes envoyées.

### Les ERR
Les réponses ERR sont des formats d'erreurs à renvoyer au client.

---

# BONUS

Pour lancer le serveur bonus

```bash
make bonus
./ircserver_bonus <port> <password>
```

<details>
<summary><h2>Le transfert de fichier</h2></summary>

Sur hexchat, le transfert de fichier se fait de base si votre serveur est bien defini.
Pour le realiser, dans l'onglet **Window** tu pourras retrouver **File Transfers**.
</details>

<details>
<summary><h2>Le bot</h2></summary>

Dans le sujet il vous est demandé de faire un [bot](https://fr.wikipedia.org/wiki/Bot_informatique)
Personnellement j'ai voulu faire plus qu'un simple agent qui se connecte et ne fait rien.
Alors j'ai réalisé un petit jeu avec lequel les clients peuvent jouer.

Selon mon appellation durant le projet, mon bot vous permez de jouer au jeu du Gamble, je me suis inspiré d'un jeu que j'ai vu en regardant une video sur le jeu video Schudule. J'ai appris après que c'est un jeu de soirée qui s'appelle en réalité [Le Bus Magique](https://psycatgames.com/fr/magazine/party-games/ride-the-bus/).

### Le principe du jeux
- tu mises une somme
- le croupier tire 4 cartes aléatoires allant de As(1) a roi(13)
- le jeu se base sur 4 tours
- si tu rates un pronostic tu perds ta mise et ton avancement dans les tours
- entre chaque tour tu as la possibilté de te retirer et donc prends le multiplicateur actuel

Premier tour:
- tu paries pour un X2 de ta mise de depart sur est ce que la premiere des 4 cartes est rouge ou noire
  
Deuxième tour:
- tu paries pour un X3 de ta mise de depart sur er ce que la deuxième carte est inferieure ou superieure à la première carte
- si la deuxième carte est la même que la première tu gagnes dans tous les cas ce tour

Troisième tour:
- tu paries pour un X5 de ta mise de depart sur es ce que la troisieme carte est entre la premiere et la deuxieme ou en dehors
- si la troisieme carte est la même que la première ou la deuxième la troisième carte est considérée comme à l'intérieur

Quatrième tour:
- tu paries pour un X10 de ta mise de départ sur quel est le symbole de la quatrième carte, entre carreaux(club), coeur(heart), pique(spade), trèfle(diamond)

apres le quatrième tour le jeu s'arrête et tu peux recommencer jusqu'à que tu arretes ou que tu n'aies plus d'argent  

### Comment jouer sur mon Irc
```bash
./gamble <port> <password>
```
cet executable va lancer le client **GambleDealer**, qui va créer un salon **GambleRoom**, mettre une limitation de 2 personnes et va activer le mode *invation only* et va attendre qu'un autre client lui envoie en message privé ```GAMBLE```

nc
```nc
PRIVMSG GambleDealer GAMBLE
```
hexchat
```hexchat
/privmsg GambleDealer GAMBLE
```

par la suite le client va recevoir une invitation à rejoindre le channel GambleRoom, il pourra donc faire

nc
```nc
JOIN #GambleRoom
```
hexchat
```hexchat
/join #GambleRoom
```

Une fois arrivé dans le channel il recevra ce message :
```
--------------------------- command ---------------------------
'PLAY' : for play camble
'EXIT' : for exit
'BANK' : for bank amount
--------------------------- command ---------------------------
```
Chaque Client commence avec 100$ sur son compte s'il tombe à 0 il se fera expulser du channel et devra se faire re-inviter et recevra gracieusement 10$.

Apres avoir envoyer ```PLAY``` directement depuis le channel #GambleRoom, ça vous lancera en partie et vous demandera de choisir le montant à miser.
À tout moment vous pouvez faire ```OUT``` pour sortir du jeu.

### Classement Jeux du Gamble

| login 42 | Argent total |
|----------|--------------|
| [stetrel](https://profile.intra.42.fr/users/stetrel) | 18446744073709551516(bug) 	  |
| [matheo(ami ilan)](https://profile.intra.42.fr/users/inowak--) | 19500 	  |
| [alaualik](https://profile.intra.42.fr/users/alaualik) | 1080 	  |
| [matde-ol](https://profile.intra.42.fr/users/matde-ol) | 1050	      |
| [mblanch](https://profile.intra.42.fr/users/mblanch)(🥇​)  | 1000		  |

</details>

---

## Credit

Readme réalisé par:
- Ilan Nowak--Glandier ([inowak--](https://profile.intra.42.fr/users/inowak--))

Projet IRC realisé par:
- [inowak--](https://profile.intra.42.fr/users/inowak--), Ilan Nowak--Glandier
- [ncharbog](https://profile.intra.42.fr/users/ncharbog), Noa Charbogne

---

> Ce README est une base et doit être adapté selon vos implémentations spécifiques et vos choix techniques.
