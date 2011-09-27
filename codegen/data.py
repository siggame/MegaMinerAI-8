# -*- coding: iso-8859-1 -*-
from structures import *

# Informs the codegen if it should include turn timing
aspects = []

# Variables the server needs to send the client each game
globals = [
  Variable('turnNumber', int, 'How many turns it has been since the beginning of the game'),
  Variable('playerID', int, 'Player Number; either 0 or 1 (0 is player 1, 1 is player 2)'),
  Variable('gameNumber', int, 'What number game this is for the server'),
  Variable('basecost', int, 'BaseCost used in the virus price formula'),
  Variable('scalecost', float, 'Scalar used in the virus price formula'),
  ]

# Constants that are built directly into the client
constants = [
  ]

# Defines a player object, used to store information for each player, like score, gold, etc
Player = Model('Player',
  # Container holding all of the Player's variables 
  data = [
    Variable('playerName',str, "Player's Name"),
    Variable('byteDollars', int, "Player's points, one with more at end of game wins"),
    Variable('cycles', int, "Player's machine cycles, used to create new Virus's"),
    ],
  # The documentation string for Player objects
  doc = 'Stores information about a player in the game',
  # Container holding all of the functions a Player can perform
  functions = [
    Function('talk',
      arguments = [Variable('message', str, 'The message that the player should say')],
      doc = 'Allows a player to display a message to the screen.'
      ),
    ]
  )
  
#gives each inherited class instance an x and y cooridinate variable
Mappable = Model("Mappable",
  data = [
    Variable ('x',int, 'The x coordinate'),
    Variable ('y',int, 'The y cooridnate'),
    ],
  #The documentation string for the mappable class
  doc = 'The base object for all mappable things',
  type = 'virtual'
  )

#A virus is the dominant unit of the game. Can move left and right. Has a level, player_id and cost(?) variable.  
Virus = Model('Virus',
  parent = Mappable,
  data = [
    Variable('owner', int, "The owner of this Virus"),
    Variable('level', int, "The Virus's level"),
    Variable('movesLeft', int, "The number of times this virus can still move"),
    ],
  # the documentation for Virus objects
  doc = 'Stores the information about a virus',
  functions = [
    Function ('move',
      arguments = [Variable('x',int,'The x coordinate to move to'),
                   Variable('y',int,'The y coordinate to move to')],
      doc = "Moves a unit to the given (x,y) position"
      ),
    ]
  )
    
Base = Model('Base',
  parent = Mappable,
  data = [
    Variable ('owner',int,"Whose base this is, all your base are belong to who"),
    ],
  doc = 'The information on the base',
  functions = [
    Function ('Spawn',
      arguments = [Variable ('Level', int, 'The level of the Virus to be created')],
      doc = 'Creates a Virus on the base with certain level.'
      ),
    ]
  )
            
Tile = Model('Tile',
  parent = Mappable,
  data = [
    Variable('owner', int, "who owns this tile: 0-First Player, 1-Second Player, 2-Not Owned, 3-Blocked"),
    ],
  doc = 'Represents a single space on the map, can be owned by either player, neither player, or be a wall',
  )

# Defines an Animation, which is sent to the visualizer to let it know something happened
playerTalk = Animation("PlayerTalk",
  data = [
    Variable("speaker", Player), 
    Variable("message", str),
    ]
  )

virusTalk = Animation("VirusTalk",
  data = [
    Variable("speaker",Virus),
    Variable("message",str)
    ]
  )
  
combine = Animation("Combine",
  data = [
    Variable("moving", Virus),
    Variable("stationary", Virus),
    Variable("created", Virus),
    ]
  )

combat = Animation("Combat",
  data = [
    Variable("moving", Virus),
    Variable("stationary", Virus),
    ]
  )

move = Animation("Move",
  data = [
    Variable("moving", Virus),
    Variable("dx", int),
    Variable("dy", int)
    ]
  )

crash = Animation("Crash",
  data = [
    Variable("crashing", Virus),
    Variable("dx", int),
    Variable("dy", int)
    ]
  )

create = Animation("Create",
  data = [
    Variable("creating", Virus)
    ]
  )
suicide = Animation("Recycle",
  data = [
    Variable("recycling", Virus),
    Variable("base", Base),
    ]
  )
