# pokecenter-monitor
This is a recreation of the poke center monitor visible from most Pokémon games, also seen in pokepark! A project that took about a week, this project is meant to replicate the feeling of seeing your Pokémon heal... Made to be buildable at home! Credits to the pokeapi sprite repository for the Pokémon sword and shield pokemon images.

This project uses any kind of esp32, as long as its flashed using arduino ide. I handmade some assets for the turbowarp project that runs on a separate device connected to a monitor. I specifically chose turbowarp as it included a websocket extension to communicate wirelessly with the esp32, as long as its connected through wifi. 

# SETUP

Items/peices needed needed:
  *ESP32 DEV BOARD
  *RC522 READER (X2)
  *WIRES
  *BREADBOARD
  *MB102 POWER SUPPLY
  *MB102 WALL ADAPTER (or anything to power it)
  *NFC TAGS (doesnt matter if data is written in, project should work fine)
  *POKEBALL MODELS (recommended for looks)

  # WIRING

  RC522 pin	                    ESP32 pin
  ---------------------------------------
  SDA / SS (Reader 1)          	GPIO 27
  SDA / SS (Reader 2)	          GPIO 26
  SCK	                          GPIO 18
  MISO (both)                   GPIO 19
  MOSI	(both)                  GPIO 23
  RST (both)	                  GPIO 22
  3.3V	                        3.3V
  GND	                          GND

# RUNNING

1.move your legs fast (kidding)

0. download the damn thing and build the setup
1. upload the arduino ide code and upload to the esp32
2. save down the ip address of the esp through the serial monitor (115200)
3. open turbowarp through online or desktop app
4. open the turbowarp file in code and edit it. (reason why it isnt compiled as an app)
5. go to backdrop, and at the top change ip address to that esp32 ip adress
6. compile or run as is. your choice.
7. it will play a ding when connected, but will be a bit hard to hear.
connect through wifi to the esp32. ( "PokeCenter Connecter" ), password ("epokpass")
8. add tags manually if editing, or scan the new tags and follow the prompts.
9. Enjoy! (note: im new to this, so expect bugs... also some pokemon might be missing...)

# CONTROLS
1 = activate healing animation (this wipes the data in the slots)
2 = turn off cooldown (turned on every time the animation plays to prevent bugs)
3 = background music toggle
4 = delete last tag data from lists (up to see)
5 = show the data the esp32 is sending

up = show data screen (shows logs, data, cooldown (1 for active), 
the tag data (matches up with pokemon data), pokemon data (# S/R F/M) or poke#, shiny or regular?, female or male?

down = hide data screen
