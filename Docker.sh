#!/bin/bash

#instalar Docker

sudo apt update

sudo apt install apt-transport-https ca-certificates curl software-properties-common

curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -

sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu bionic stable"

sudo apt update

sudo apt install docker-ce

#Agrega el nombre de usuario al grupo Docker

sudo usermod -aG docker ${USER}
#confirmar que se haya agregado el usuario
id -nG
echo -e "se agrego el usuario al grupo\n";

# instalar Docker-compose

sudo curl -L "https://github.com/docker/compose/releases/download/1.23.1/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose 

sudo chmod +x /usr/local/bin/docker-compose 

#versión de Docker y Docker-compose
docker --version
docker-compose --version
