# -*- coding: iso-8859-1 -*-
from structures import *

# Informs the codegen if it should include turn timing
aspects = ['timer']

# Variables the server needs to send the client each game
globals = [
  Variable('turnNumber', int, 'How many turns it has been since the beginning of the game'),
  Variable('playerID', int, 'Player Number; either 0 or 1 (0 is player 1, 1 is player 2)'),
  Variable('gameNumber', int, 'What number game this is for the server'),
  ]

# Constants that are built directly into the client
constants = [
  ]

# Defines a player object, used to store information for each player, like score, gold, etc
Player = Model('Player',
  # Container holding all of the Player's variables 
  data = [
    Variable('playerName',str, "Player's Name"),
    Variable('bytedollars',int,"Player's points, one with more at end of game wins"),
    Variable('cycles',int,"Player's machine cycles"),
    ],
  # The documentation string for Player objects
  doc = 'Stores information about all of the players in the game',
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
            Variable('level',int, "The Unit's current level"),
            #ownder<<
            ],
            # the documentation for Virus objects
            doc = 'Stores the information about all viruses (virusi?) in the game',
            functions = [
              Function ('move',
                arguments = [Variable('x',int,'move x direction'),
                             Variable('y',int,'move y direction')],
                doc = ""
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
        arguments = [Variable ('Level',int,'The level of the Virus created')],
        doc = 'Creates a Virus Unit on the base with certain level.'
        ),
      ]
    )
            
Tile = Model('Tile',
    parent = Mappable,
    data = [
        Variable('owned_by',int,"who owns this tile"),
        Variable('type',int,"is this a tile or wall"),
        ],
        doc = 'A tile is either floor space, or a wall. Floor space belongs to no one, p1 or p2',
        )
               
    



# Defines an Animation, which is sent to the visualizer to let it know something happened
talk = Animation("PlayerTalk",
  data = [
    Variable("speaker", Player), 
    Variable("message", str)
    ]
  )

virus_talk = Animation("UnitTalk",
    data = [
        Variable("speaker",Virus),
        Variable("message",str)
        ]
  )
  
combine = Animation("Combine",
     data = [
        Variable("moving_V", Virus),
        Variable("stay_V",Virus)
       ]
    )
    
combat = Animation ("Combat",	
    data = [
        Variable("friend_V",Virus),
        Variable("foe_V",Virus)
        ]
    )

move = Animation ("Move",
    data = [
        Variable("unit", Virus),
        Variable("dx", int),
        Variable("dy", int)
        ]
    )    

crash = Animation ("Crash",
    data = [
        Variable("unit", Virus),
        Variable("dx", int),
        Variable("dy", int)
        ]
    )

create = Animation ("Create",
    data = [
        Variable("unit", Virus)
        ]
    )

