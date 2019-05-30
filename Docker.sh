#!/bin/bash

#      Instalar Docker

#Actualizar lista de paquetes
sudo apt update
#Instalar paquetes previos que permiten a "apt" usar paquetes mediante HTTPS
sudo apt install apt-transport-https ca-certificates curl software-properties-common
#agregar la clave GPG para el repositorio oficial de Docker 
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
#Agregar el repositorio de Docker a las fuentes de APT
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu bionic stable"
#Actualizar lista de paquetes
sudo apt update
#Instalar Docker
sudo apt install docker-ce

#      Agrega el nombre de usuario al grupo Docker

#Agregar el nombre de usuario al grupo docker 
sudo usermod -aG docker ${USER}
#confirmar que se haya agregado el usuario
id -nG

#      instalar Docker-compose

#Descargar el archivo binario Docker Compose
sudo curl -L "https://github.com/docker/compose/releases/download/1.23.1/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose 
#aplicar los permisos ejecutables al binario
sudo chmod +x /usr/local/bin/docker-compose 

#      versión de Docker y Docker-compose

docker --version
docker-compose --version
