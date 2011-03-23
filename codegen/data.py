# -*- coding: iso-8859-1 -*-
from structures import *

aspects = ['timer']

Mappable = Model('Mappable',
  data = [ Variable('x', int, 'The X position of this object.  X is horizontal, with 0,0 as the top left corner'),
    Variable('y', int, 'The Y position of this object.  Y is vertical, with 0,0 as the top left corner'),
    ],
  doc = 'An object that exists on the grid',
  type = 'virtual'
  )

Unit = Model('Unit',
  parent = Mappable,
    data = [Variable('owner', int, 'The owner of the unit'),
    Variable('health', int, 'health of the unit'),
    Variable('strength', int, 'attacking strength of the unit'),
    Variable('hasMoved', int, 'checks if the unit has moved this turn'),
    Variable('hasAttacked', int, 'checks if the unit has moved this turn'),
    ],
  doc = 'Generic Unit',
  functions = [
    Function('move',
      arguments = [Variable('x', int, 'The x coordinate of where to move the unit'), 
	    Variable('y', int, 'The Y coordinate of where to move the unit')],
      result = bool,
      doc = 'Move the unit to the designated X and Y coordinates'
    ),
    Function('talk',
      arguments = [Variable('message', str, 'The message that the unit should say')],
      doc = 'Allows a unit to display a message to the screen.'
    ),
  ],
  type = 'virtual'
)

Unit.functions.append(Function('attack',
      arguments = [Variable('Target', Unit, 'The unit to attack')],
      result = bool,
      doc = 'Attempt to attack the given unit'
      ))


Pirate = Model('Pirate',
  parent = Unit,
  doc = 'A generic pirate',
  functions = [
    Function('pickupTreasure',
      arguments = [Variable('amount', int, 'The amount of gold you wish to pickup')],
      doc = 'Allows the pirate to pickup treasure on the ground.'
    ),
    Function('dropTreasure',
      arguments = [Variable('amount', int, 'The amount of gold you wish to drop')],
      doc = 'Allows the pirate to drop treasure on the groud.'
    ),
    Function('buildPort',
      arguments = [],
      result = bool,
      doc = 'Pirate builds a port on a land tile with water tile adjacent'
    )
  ]
)


Ship = Model('Ship',
  parent = Unit,
  doc = 'A generic ship',
)

Port = Model('Port',
  parent = Mappable,
  data = [ Variable('owner', int, 'The ownder of the port'),
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
  parent = Mappable,
  data = [ Variable('type', int, 'land = 0, water = 1'),
    ],
  doc = 'A basic tile',
)

Treasure = Model('Treasure',
  parent = Mappable,
  data = [ Variable('pirateID', int, 'The ID of the pirate carrying this treasure, 0 if not carried'),
  Variable('amount', int, 'The amount of gold in this treaure'),
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
  Variable('player0Gold', str, 'Player 0\'s gold amount'),
  Variable('player1Gold', str, 'Player 1\'s gold amount'),
  Variable('pirateCost', int, 'The cost of a pirate'),
  Variable('shipCost', int, 'The cost of a ship'),
  Variable('portCost', int, 'The cost to build a new port'),
	Variable('boardX', int, 'The boards width'),
	Variable('boardY', int, 'the boards height')
  ]
