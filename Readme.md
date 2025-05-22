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

# Structure du projet

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

## Licence

Ce projet est sous licence MIT.

---

> Ce README est une base et doit être adapté selon vos implémentations spécifiques et vos choix techniques.
