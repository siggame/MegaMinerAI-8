# -*- coding: iso-8859-1 -*-
from structures import *

aspects = []

Unit = Model('Unit',
    data = [Variable('owner', int, 'The owner of the piece'),
    Variable('X', int, 'The X coordinate for the pieces position'),
    Variable('Y', int, 'The Y coordinate for the pieces position'),
    Variable('health', int, 'health of the unit'),
    Variable('strength', int, 'attacking strength of the unit'),
    ],
  doc = 'Generic Unit',
  functions = [
    Function('move',
      arguments = [Variable('X', int, 'The x coordinate of where the unit is moving'), 
	    Variable('Y', int, 'The Y coordinate of where the unit is moving')],
      result = bool,
      doc = 'Move the unit to the designated X and Y coordinates'
    ),
    Function('talk',
      arguments = [Variable('message', str, 'The message that the unit should say')],
      doc = 'Allows a unit to display a message to the screen.'
    ),
    Function('attack',
      arguments = [Variable('UnitID', int, 'The ID of the unit being attacked')],
      result = bool,
      doc = 'Attempt to attack the unit whose ID is given'
    ),
  ],
  type = 'virtual'
)

Pirate = Model('Pirate',
  parent = Unit,
  doc = 'A generic pirate',
)

Pirate.addFunctions([
  Function('pickupTreasure',
    arguments = [Variable('amount', int, 'The amount of gold you wish to pickup')],
    doc = 'Allows the pirate to pickup treasure on the ground.'
  ),
  Function('dropTreasure',
    arguments = [Variable('amount', int, 'The amount of gold you wish to drop')],
    doc = 'Allows the pirate to drop treasure on the groud.'
  ),]
)


Ship = Model('Ship',
  parent = Unit,
  doc = 'A generic ship',)

Port = Model('Port',
  data = [ Variable('owner', int, 'The ownder of the piece'),
      Variable('X', int, 'The X coordinate for the pieces position'),
      Variable('Y', int, 'The Y coordinate for the pieces position'),
    ],
  doc = 'A generic port',
  functions = [ 
    Function('createPirate',
	  arguments = [],
	  result = bool,
	  doc = 'Creates a Pirate at the calling Port'
	),
    Function('createShip',
	  arguments = [],
	  result = bool,
	  doc = 'Creates a Ship at the calling Port'
	),
  ]
)

Tile = Model('Tile',
  data = [ Variable('type', int, 'land = 0, land = 1'),
	  Variable('X', int, 'The X coordinate for the tile'),
      Variable('Y', int, 'The Y coordinate for the tile'),
    ],
  doc = 'A basic tile',
)

Treasure = Model('Treasure',
  data = [ Variable('pirate', Pirate, 'The pirate carrying this treasure'),
    Variable('X', int, 'The X coordinate for the pieces position'),
    Variable('Y', int, 'The Y coordinate for the pieces position'),
    ],
  doc = 'A treasure',
)

globals = [
  Variable('turnNumber', int, 'How many turns it has been since the beginning of the game'),
  Variable('playerID', int, 'Player Number; either 0 or 1'),
  Variable('gameNumber', int, 'What number game this is for the server'),
  ]

constants = [
  Variable('player0Name', str, 'Player 0\'s name'),
  Variable('player1Name', str, 'Player 1\'s name'),
  ]

import timerAspect
timerAspect.install()
