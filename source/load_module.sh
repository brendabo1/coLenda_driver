#!/bin/bash

# Carregar o módulo do kernel
modprobe colenda_driver

# Criar o nó de dispositivo (substitua por informações reais)
mknod /dev/colenda c 241 0

# Ajustar as permissões do nó de dispositivo
chmod 666 /dev/colenda

chmod +x /path/to/load_module.sh