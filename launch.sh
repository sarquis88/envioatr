#!/bin/bash

Username=$(cat ./resources/host_name.txt)
Selection=$(zenity --list --radiolist --height=175 --width 300 --title="envioatr" --text "Welcome $Username! What do you want to do?" --hide-header --column "envioatr" --column "Item" FALSE "Send file" FALSE "Receive file" FALSE "Make" FALSE "Exit")

if [[ $Selection == *"Send file"* ]]; then
./sender/bin/sender
fi

if [[ $Selection == *"Receive file"* ]]; then
./receiver/bin/receiver
fi

if [[ $Selection == *"Make"* ]]; then
make
fi

if [[ $Selection == *"Exit"* ]]; then
echo "Bye"
fi