Inicialmente, instale o OpenJDK Java 6, na central de programas do Ubuntu.

Para instalar o gravador via USB pelo Terminal do Ubuntu, basta digitar (como root):
• wget http://sanusb.org/tools/SanUSBlinux.zip
• unzip SanUSBlinux.zip
• cd SanUSBlinux
• sudo dpkg -i sanusb_linux.deb 
• cp sanusb /usr/share/sanusb




OUTRA FORMA:

Baixe o arquivo atualizado em: https://dl.dropboxusercontent.com/u/101922388/121007SanUSBOrig.zip .

Baixe a pasta completa 121007SanUSBOrig e dentro da pasta \121007SanUSBOrig\SanUSBPlugandPlay\Linux, instale o pacote 
SanUSB_linux_para_OpenJDK6_64bits.deb: dpkg -i SanUSB_linux_para_OpenJDK6_64bits.deb,
e  digite como root no terminal: sanusb
e tente gravar o microcontrolador com o arquivo exemplo1.hex. Mais detalhes em https://www.youtube.com/watch?v=S30wVi9RWEs

Para o modo gráfico, instale o pacote SanUSB_linux_para_OpenJDK6_64bits.deb: dpkg -i SanUSB_linux_para_OpenJDK6_64bits.deb,
dentro da pasta /121007SanUSBOrig/SanUSBPlugandPlay/Linux e  digite como root no terminal: sanusb
e tente gravar o microcontrolador com o arquivo exemplo1.hex. Mais detalhes em https://www.youtube.com/watch?v=S30wVi9RWEs

Para máquinas de 64 bits , cole o arquivo sanusb (antes de usar: chmod +x sanusb) em /usr/share/sanusb  e tente novamente como no vídeo.

Caso não funcione o modo gráfico, utilize o modo de linha de comando com o arquivo sanusb. Escrevendo
no terminal e o microcontrolador em modo de gravação, como root, para teste em /SanUSBPlugandPlay/Linux utilize o help (./sanusb -h) : 
./sanusb -h  
E para gravar (-w) e resetar (-r): 

./sanusb -w exemplo1.hex -r . 

ou

Endereço absoluto executável sanusb + -w + endereço absoluto arquivo .hex + -r:
/usr/share/sanusb/./sanusb –w  ~/Projeto1C18.X/dist/default/production/Projeto1C18.X.production.hex -r

Mais detalhes também em https://www.youtube.com/watch?v=S30wVi9RWEs


MPLABX C18 e XC8

Dessa forma, é  simples utilizar a placa SanUSB em Linux, Windows ou Mac OSX com o MPLAX C18 Lite (free) . 
Inicialmente, tem que instalar o MPLABX e o C18 em https://drive.google.com/open?id=0B5332OAhnMe2cjVRcmF5RU9aMTQ&authuser=0
baixando os instaladores, indo na pasta do instalador MPLABX Linux pelo terminal como root e digitando
ROOTPROMPT$> chmod 770 MPLABX-linux-.run
ROOTPROMPT$> ./MPLABX-linux-.run

e depois:

Em seguida clicando  simplesmente em Next e Next...

Depois de instalado basta abrir o MPLAX e clicar em Open project e escolher um projeto.X, como em
https://dl.dropbox.com/u/101922388/ProjSanUSB1_MPLABX/Projeto1C18.X.zip
Pronto, este projeto já pisca um led no pino B7 como neste vídeo e em http://www.youtube.com/watch?v=lB21b3zA4Ac , http://www.youtube.com/watch?v=oBdpr29fFyg e http://www.youtube.com/watch?v=p9j7uQuOXS8 

Mais detalhes nos tutoriais disponíveis em https://dl.dropbox.com/u/101922388/121007SanUSBOrig.zip

Para modificar o programa exemplo, altere o programa.c, ou o substitua no source file em Project por outro, e clique em Clean und Build Project para compilar (˜cone que tem um martelo e uma vassoura)
O arquivo compilado Projeto1C18.hex, para gravação via USB, está dentro de /Projeto1C18.X/dist/default/production. Para gravar:

Endereço absoluto executável sanusb + -w + endereço absoluto arquivo .hex + -r:
/usr/share/sanusb/./sanusb –w  ~/Projeto1C18.X/dist/default/production/Projeto1C18.X.production.hex -r


Este exemplo, bem como muitos outros da pasta Projeto1C18.X, foram compilados em Linux, Windows e Mac OSX, e funcionaram normalmente.


