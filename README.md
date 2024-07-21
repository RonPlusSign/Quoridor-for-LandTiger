# Quoridor game

Quoridor game implemented using Keil µVision and a LandTiger board, for the course "Architetture dei sistemi di elaborazione" (Politecnico of Turin).

![image](https://github.com/user-attachments/assets/d8d5b2a9-79c5-43f4-8bc3-4d76994053b9)
![image](https://github.com/user-attachments/assets/7736b738-7acd-4980-8943-5739ba3f293b)

## Rules

Each player is equipped with a token and eight barriers. The game board is a 7x7 wooden square,
with the peculiar feature that the lines dividing and forming the squares are grooved, allowing
walls to be inserted.

Each player starts from the center of their perimeter line (the 4th square), and the goal is to get
their token to the opposite perimeter line. The player who achieves this objective first wins.

On their turn, a player has two choices:
1. They can choose to move their token horizontally or vertically;
2. He/she can choose to place a wall. The wall cannot be jumped over but must be navigated around.

At every step of the game, there are always two players: the moving player (the one who is making
the choice), and the opponent. Their roles alternate at every step.

• If two tokens (the moving player and the opponent) are facing each other, the moving player
can jump over the opponent and position themselves behind them if there is no barrier behind
the opponent.

• It is not allowed to "trap" a player with the help of walls; you must always leave them a way
to reach the goal.

• A move must be chosen within 20 seconds, or else it loses the turn.

• If players are facing each other, you can jump an extra square as in the figure below.

![image](https://github.com/user-attachments/assets/610abd0f-16e8-4a3c-93d3-30e6da60acb8)

• In case players are facing each other, and there is a wall behind the opponent, you can move to the square next to the opponent, as Figures below show.

![image](https://github.com/user-attachments/assets/22ef492d-e32a-48ae-a94a-9a90e307a21d)

## Game modes

There are 3 game modes you can choose, sharting from the main Menu. Start by selecting the game mode: single board, and two boards.
This menu is shown after INT0 is pressed (in multiplayer mode, who presses INT0 becomes the player 1).

There is a handshake between the “Two Boards“ in multiplayer mode.
In case the handshake fails, it means that you cannot play in multiplayer mode (i.e., there is no other LandTiger board attached) and the system shows an error message.
Use the JOYSTICK to move between the options and the JOY SEL to confirm the choice.

After the number of boards is selected, the you can choose the opposite player (Human or NPC).

### Single player mode
This is the classic mode, 2 users play on a single board by alternating its usage.

### Multiplayer Mode

A multiplayer mode (1 vs. 1) of Quoridor game has been implemented, by connecting two LandTiger Board through the CAN bus, as Figure below shows.

![image](https://github.com/user-attachments/assets/b0444a40-91fa-4f5c-946c-a523d208cbde)

#### Specification for coordinates
The system in charge of handling the coordinates information is crucial.
It must be commonly defined among all the Extra Point implementations to play in multiplayer mode effectively.
The following figure shows a coordinate system (using integer coordinates on the LCD).

![image](https://github.com/user-attachments/assets/56650849-1848-447d-b195-dc29dbf314c6)

The y_token and x_token are the axes used to represent the player's center. For example, Player in (5,4) represents the center of the square where the player is placed.

Where the y_wall and x_wall are the axes used to represent the center of the wall. For example, wall in (2,2) represents the center of the wall in which the wall is
placed.

Please note that the x_wall and y_wall axis are coordinate within the Player move coordinate system.

Data is exchanged between boards through the CAN bus (in the data field of the CAN Frame) witht he following structure:

![image](https://github.com/user-attachments/assets/fe001ff9-c218-4170-a893-d698b6cdf995)

In simple words (x and y in the aforementioned data structure):

• Wall position (WallPlacement) must represent the wall’s center in the wooden square on the LCD.

• Player position(PlayerMove=0) must represent the player’s center in a given square on the LCD.

### Non-Player Character (NPC)

You can play versus the board itself (NPC) as your opponent.
Your opponent plays a turn right after you place a wall or move your character.

The opponent uses a Depth-First-Search (DFS) algorithm to find the best path to follow, and tries to block your way by placing the wall in the position that slows you the most.

## Specifics

![image](https://github.com/user-attachments/assets/208218b7-3833-48e7-b25f-b204926f1e8c)

Using the DISPLAY library, draw your game board as a 7x7 wooden square.
Draw the two tokens using two colours: white (PLAYER1) and red (PLAYER2).
Remember that each player has 8 available barriers (or walls).
The tokens must move using squares (vertically or horizontally).
The barriers must be placed between squares.

![image](https://github.com/user-attachments/assets/d8628023-44b7-47f2-812c-e5c6e50e1a08)

When the system starts, to start a match, you must press INT0 (otherwise you remain in wait mode).
From now on, you are in the match/game mode.

Each player has 20 seconds to do the move. If time expires, the player loses the turn.

At this point, remember that the player has two choices:

1. He/she moves of 1 step vertically or horizontally. To do this, use the JOYSTICK.
  1. JOY UP
  2. JOY DOWN
  3. JOY LEFT
  4. JOY RIGHT
  5. JOY SELECT: confirm the choice. The game continues with PLAYER2.
  6. The 4 squares surrounding the player (as in Figure 1) are highlighted, i.e., the player’s possible moves.

2. He/she can insert a wall to block the opposite player. To enter in this mode, the player must
press KEY1. A wall will appear in the centre (the map itself is 7x7 and the wall is placed
between two squares).
  1. After pressing KEY1, it appears in the centre of the 7x7 square.
  2. Use the JOYSTICK to determine the position of the wall. Once that the position is found, press JOY SELECT to confirm the position.
  3. Be careful about the wall position. A wall is sized with two squares plus a space between them.
  4. Each player has only 8 walls to position. If it ends them, a warning message will appear on the screen: “No walls available, move the token”.
  5. Pressing KEY2 rotates the wall in the current position of 90 degree.
  6. Pressing KEY1 again before confirming the position of the wall disable the wall insertion mode and return to player move mode.

### Example

An example on how the wall functionality is implemented is shown in the following figures:

1. After pressing KEY1 a wall appears in a central place on the map. If you want, you can customize its colour to show that the position is not yet finalized.

![image](https://github.com/user-attachments/assets/78fcd7d0-fad6-40d6-be7f-e69fab67bcae)

2. By going up with the Joystick the wall is moved up by one square

![image](https://github.com/user-attachments/assets/2057d5dc-6d1d-41ec-bbb9-c1cb23499ae2)

3. By clicking KEY2 the wall is rotated by 90 degrees

![image](https://github.com/user-attachments/assets/edbb1262-a6e6-42c1-acca-88843f6ad229)

4. By clicking JOY SELECT you finalise the position of the wall, and your turn is finished

5. The game ends when one of the players reaches the opposite side of the 7x7 square

![image](https://github.com/user-attachments/assets/ee731673-d6d4-4119-aaf8-8e7d82de893a)

## Implementation details

The real grid used under the hood is a matrix of size 13x13 that can be used to place both the walls and the players, as shown in the image below.

![image](https://github.com/user-attachments/assets/9df93f10-56a0-4570-9356-d22c0f2cd6c1)

#### i even, j even = player position

![image](https://github.com/user-attachments/assets/ef39e67f-148e-4756-98f8-22474479451e)

#### i even, j odd = vertical wall position

![image](https://github.com/user-attachments/assets/036f4259-73c4-4d20-bfba-f1f528fb2d94)

#### i odd, j even = horizontal wall position

![image](https://github.com/user-attachments/assets/b1d20ee4-e526-4d79-9405-62fda703b369)

#### i odd, j odd = invalid position, not used

![image](https://github.com/user-attachments/assets/98376a35-2620-40ce-b11c-900cbed523de)


