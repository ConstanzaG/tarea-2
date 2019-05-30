#!/bin/bash

#      Instalar Docker

echo -e "\n	*Instalacion de Docker*\n";
#Actualizar lista de paquetes
sudo apt update
#Instalar paquetes previos que permiten a "apt" usar paquetes mediante HTTPS
sudo apt install apt-transport-https ca-certificates curl software-properties-common
#agreguar la clave GPG para el repositorio oficial de Docker 
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
#Agregar el repositorio de Docker a las fuentes de APT:
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu bionic stable"
#Actualizar lista de paquetes
sudo apt update
#Instalar Docker
sudo apt install docker-ce
echo -e "\n	*Instalacion de Docker realizada*\n";

#      Agregar el nombre de usuario al grupo Docker

echo -e "\n	*Agregar el nombre de usuario al grupo*\n";
#Agregar el nombre de usuario al grupo docker 
sudo usermod -aG docker ${USER}
#confirmar que se haya agregado el usuario
id -nG
echo -e "\n	*nombre de usuario agregado al grupo*\n";

#      instalar Docker-compose

echo -e "\n	*Instalacion de Docker-compose*\n";
#Descargar el archivo binario Docker Compose
sudo curl -L "https://github.com/docker/compose/releases/download/1.23.1/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose 
#aplicar los permisos ejecutables al binario
sudo chmod +x /usr/local/bin/docker-compose 
echo -e "\n	*Instalacion de Docker-compose realizada*\n";

#      versión de Docker y Docker-compose

echo -e "\n	*Version de Docker: *\n";
docker --version
echo -e "\n	*Version de Docker-compose: *\n";
docker-compose --version
