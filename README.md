# ZechcykDev
Card Game - Sixty-six variation for three players.

Zechcyk is a card game which is variation of game sixty-six with three players instead two.

Short game rules description:

Game is played using 24 cards: 9 J D K 10 A
Card values:
9 - 0       J - 2       D - 3      K - 4      10 - 10       A - 11

Game can be played in four different ways called: 
- warsow - all colours are equal. Player who will get the most points - loses. No teams - everyone play for himself.
- colour - one player picks one colour which form this moment will be trump and it will beat other colours. He
           need to gain 66 pts or win last trick. Other players play in team against him - their points sum up - if they will
           gain 66 pts before player who picked a colour - he loses. Colour can overthrow warsow.
           In this type of game any player who have king and queen in one colour and have initiative
           (he won previous trick) can meld by throwing one on them. If meld is in trump colour - he gains 40pts.
           Otherwise - he gains 20pts.
- misery - all colours are equal. Player who established misery wins when he will be able not to win any trick. Other players play
           against him. Misery can overthrow colour. In this type of game 10 higher then 9 and lower than J.
- durh   - all colours are equal. PLayer who established misery wins when he will be able to win all tricks.
           Durh can overthrow colour and misery.
           
IMPORTANT. DURH AND MISERY CAN BE PICKED ONLY IN SECOND AUCTION. WARSOW CAN BE PICKED ONLY IN THE FIRST AUCTION.

Throwing cards rules:
First player can throw any card. Other players need to throw card which fulfil condition with highest priority:
1. Higher Card in the same colour (if it will win the trick - if second player throw trump, third need to throw any card in colour)
2. Card in the same colour.
3. Higher card in trump colour. (if it was thrown)
4. Card in trump colour.
5. Any card.

Phases of the game:

All three players get 4 cards each (taken form the deck in a row). 
First player see his cards and have a decision to make, he can:
1. say Warsow
2. pick a Colour

If he will say Warsow, next player have the same decision to make. If all players will say warsow - the warsow starts.
If one of the players will chose a colour - another 4 cards are given to players and he need to decise if
he want to play with this cards or not. If not - he throws cards and loses for 2 points. Cards are being shuffled and process repats.
If he will chose to play he says: "I am asking". Then other players can say:

1.Play - if they just want to begin the game
2.Double - if they think that he will lose - it doubles the point stake for the game.
3.Misery - if one of them want to overthrow the colour and play against two other players.
4.Durh - if one of them want to overthor colour or the misery and play against two other players.

If they will chose to double the stake. Player who picked a colour can response by doubleing it once again by deing Redouble!
Durh and misery can also be doubled after picking them.

When the one of the sides will say play (both players who play against one, or that one after they say double) established game begins.
First throwing player will be the one who play against two others.


About the code:
Game at this moment is fully in console. Soon GUI will be added.
I have decided to divide program into 10 clases:

Run - class responsible for running the program in the planned sequence

Text - class responsible for loading and displaying text on the console

Card - class responsible for creating cards and storing their symbols

Player - class responsible for storing intel about player, it contains all methods connected with interaction with player

Auction - class responsible for carring two auctions and asking player if he want to play after receiving second four cards.

Game - base class for other game classes. Contains most of the methods responsible for carring the game.

GameWarsow, GameColour, GameMisery, GameDurh - subclasses responsible for obtaining specyfic for each game type mechanics.






