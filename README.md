# Epi-KTANE Documentation

## 📋 Table of Contents
- [🖥️ Epi-KTANE documentation- Epi-KTANE Project](#️-gui-documentation---zappy-project)
  - [📋 Table of Contents](#-table-of-contents)
  - [📌 Introduction](#-introduction)
  - [🔗 Launch the game](#Launch-the-game)
  
  - [Modules](#Module)
    - [Wire Module](#Wire-Module)


## 📌 Introduction

The **Epi-KTANE** is a game developed in **C++** using the **Raylib** library. It is inspired by the famous game *Keep Talking and Nobody Explodes*. The goal is to defuse a bomb by solving various modules, with or without the help of an external manual.

## 🔗 Launch the game

To lauch, the user executes the following command:

```bash
./epi_ktane -m <module> -e <error> -t <time> -g
```

- `-m <module>`: number of module do you want to play [int]  
- `-e <error>`: number of authorized error [int]
- `-t <time>`: time for defusing the bomb in seconde [int]
- `-g`: specify for lauch graphical mode


## Module

This is the list of all implemented modules:

### Wire Module


- **3 wires**:
  - If there are no red wires, cut the **second wire**.
  - Otherwise, if the last wire is white, cut the **last wire**.
  - Otherwise, if there is more than one blue wire, cut the **last blue wire**.
  - Otherwise, cut the **last wire**.

- **4 wires**:
  - If there is more than one red wire and the last digit of the serial number is odd, cut the **last red wire**.
  - If the last wire is yellow and there are no red wires, cut the **first wire**.
  - If there is exactly one blue wire, cut the **first wire**.
  - If there is more than one yellow wire, cut the **last wire**.
  - Otherwise, cut the **second wire**.
- **5 wires**:
  - If the last wire is black and the last digit of the serial number is odd, cut the **fourth wire**.
  - If there are exactly one red wire and there are more than one yellow wire, cut the **first wire**.
  - If there are no black wire, cut the **second wire**.
  - Otherwise, cut the **first wire**.
- **6 wires**:
  - If there are no yellow wire and the last digit of the serial number is odd, cut the **third wire**.
  - If there are exactly one yellow wire and there are more than one white wire, cut the **fourth wire**.
  - If there are no red wire, cut the **last wire**.
  - Otherwise, cut the **fourth wire**.

