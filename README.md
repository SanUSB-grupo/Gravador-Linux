# Instalador do Gravador SANUSB para Linux

## Pré requisitos

 * [OpenJDK Java](http://openjdk.java.net/install/) 6.

## Instalar

### Interface gráfica

Instale o **SanUSB Gravador - Linux** baixando o arquivo **sanusb_linux.deb** e executando-o. Algumas distros do Linux, como o Ubuntu, dão a possibilidade de instalar um _.deb_ abrindo-o (duplo clique no arquivo).

Alternativamente, você poderá instalar pelo terminal:

```bash
# Entrar no modo de administrador
sudo su
# Instalar o .deb
sudo dpkg -i ./sanusb_linux.deb
```

### Gravador

Por fim, insira o gravador (já compilado) para o diretório share. Após baixar o arquivo **sanusb**, execute no terminal.

```bash
# Entrar no modo de administrador
sudo su
# Copiar arquivo Gravador
cp sanusb /usr/share/sanusb
```

## Executar

Abra a interface gráfica após a instalação digitando **sanusb** no terminal.

```bash
sanusb
```

## Testar

Grave o exemplo pisca led pelo comando:

```bash
# Estando na pasta, execute
sanusb -w exemplo1.hex -r
```

Outros códigos de exemplo podem ser encontrados nos repositórios do [Grupo SanUSB no Github](https://github.com/SanUSB-grupo)

## Executar no terminal - Comandos

A lista de comandos pode ser obtida executando "sanusb -h"

```
Option     Description                                      Default
-------------------------------------------------------------------------
-w <file>  Write hex file to device (will erase first)      None
-e         Erase device code space (implicit if -w)         No erase
-r         Reset device on program exit                     No reset
-h         Help
```

