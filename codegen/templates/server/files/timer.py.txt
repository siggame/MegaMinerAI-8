import aspects

from game_app.match import Match
from twisted.internet import reactor

games = []

def install():
  def wrapNextTurn(func):
    def inner(self):
      if self not in games:
        games.append(self)
      if self.turn == self.players[0]:
        self.objects.players[1].time += self.timeInc
      elif self.turn == self.players[1]:
        self.objects.players[0].time += self.timeInc
      return func(self)
    return inner

  aspects.wrap_function(Match.nextTurn, wrapNextTurn)

  def tick():
    for i in games:
      p = i.objects.players
      if len(i.players) > 1:
        if i.turn == i.players[0]:
          p[0].time -= 1
          if p[0].time < 0:
            i.declareWinner(i.players[1], 'Player 1 Lagged Out, Player 2 Wins')
        elif i.turn == i.players[1]:
          p[1].time -= 1
          if p[1].time < 0:
            i.declareWinner(i.players[0], 'Player 2 Lagged Out, Player 1 Wins')
        else:
          games.remove(i)

    reactor.callLater(1, tick)

  reactor.callWhenRunning(reactor.callLater, 1, tick)

