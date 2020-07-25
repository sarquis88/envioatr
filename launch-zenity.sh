#!/bin/bash

Username=$(cat ./resources/host_name.txt)
Selection=$(zenity --list --radiolist --height=250 --width 300 --title="envioatr" --text "Welcome $Username! What do you want to do?" --hide-header --column "envioatr" --column "Item" FALSE "Send file" FALSE "Receive file" FALSE "Clear receptions folder" FALSE "Change username" FALSE "Make" FALSE "Exit")
TestList=""

if [[ $Selection == *"Send file"* ]]; then
if test -f "./main/bin/main"; then
./main/bin/main -s
else
zenity --info --title="envioatr" --height=50 --width 300 --text="You have first to make the proyect!"
fi
fi

if [[ $Selection == *"Receive file"* ]]; then
if test -f "./main/bin/main"; then
./main/bin/main -r
else
zenity --info --title="envioatr" --height=50 --width 300 --text="You have first to make the proyect!"
fi
fi

if [[ $Selection == *"Clear receptions folder"* ]]; then
if test -f "./main/bin/main"; then
./main/bin/main -c
else
zenity --info --title="envioatr" --height=50 --width 300 --text="You have first to make the proyect!"
fi
fi

if [[ $Selection == *"Change username"* ]]; then
if test -f "./main/bin/main"; then
Username=$(zenity --entry --title="envioatr" --text="Enter new username")
./main/bin/main -u $Username
else
zenity --info --title="envioatr" --height=50 --width 300 --text="You have first to make the proyect!"
fi
fi

if [[ $Selection == *"Make"* ]]; then
make
fi

if [[ $Selection == *"Exit"* ]]; then
echo "Bye"
fi