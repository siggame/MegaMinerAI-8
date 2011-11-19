using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Linq;

enum Direction { Up = 0, Left = 1, Down = 2, Right = 3 }
enum NodeType { Unset = -1, Wall, EnemyBase, MyBase, MyTile, EnemyTile, NeutralTile, EnemyVirus, MyVirus }

class GameNode {
    public NodeType Type = NodeType.Unset;
    public int VirusLevel = -1;
    public int DistanceToNearestTakenTile = 1;
}

class GamePoint {
    public int X = -1;
    public int Y = -1;
    public int Depth = 1;
    public GamePoint Parent = null;
    
    public GamePoint(int x, int y) { X = x; Y = y; }
    public GamePoint(GamePoint parent, Direction dir) { Parent = parent; Depth = parent.Depth + 1; switch(dir) { case Direction.Up:    X = parent.X;  Y = parent.Y - 1; break; case Direction.Right: X = parent.X + 1;  Y = parent.Y; break; case Direction.Down:  X = parent.X;  Y = parent.Y + 1; break; case Direction.Left:  X = parent.X - 1;  Y = parent.Y; break; } }
}

///The class implementing gameplay logic.
class AI : BaseAI
{
    public GameNode[,] map;    
    Random rand;
    int desiredX = -1, desiredY = -1;
    private const int UNSET = -1;
    public bool goingAfterEnemy = false;
    
    public override string username() { return "mst00140"; }
    public override string password() { return "raDei6oo"; }
    public AI(IntPtr c) : base(c) {}
    public int wall() { return 3; }
    public int neutral_tile() { return 2; }
    public int enemyID() { return (playerID() == 0 ? 1 : 0 ); }
    
    public override void init()
    {
        map = new GameNode[width(), height()];
        for(int x = 0; x < width(); x++)
            for(int y = 0; y < height(); y++)
                map[x,y] = new GameNode();
        
        rand = new Random();
        rand.Next(1);  // To surpress warnings about rand not being used.
        
        int farthestDistance = 0;
        
        update_map();
        
        desiredX = 0;
        desiredY = 0;
        
        for(int x = 0; x < width(); x += 2)         // have to do every 4th tile to no LAGGGGG out
            for(int y = 0; y < height(); y += 2)
                if(map[x, y].Type == NodeType.NeutralTile)
                {
                    int d = distanceToNearestTakenNode(x, y);
                    
                    if(d > farthestDistance)
                    {
                        farthestDistance = d;
                        desiredX = x;
                        desiredY = y;
                    }
                }
        
        Console.WriteLine("Desired Point: " + desiredX + "," + desiredY);
        players[playerID()].talk("Bolting for: (" + desiredX + "," + desiredY + ")");
    }
    
    public override void end()
    {
        if(players[enemyID()].getByteDollars() > players[playerID()].getByteDollars())
          players[playerID()].talk("I curse Wooly Willy on you, " + players[enemyID()].getPlayerName());
    }

    public override bool run()
    {
        update_map();
        
        int desired_virus_level = 0;
        int enemy_virus_count = 0;
        
        // see if we need to find a new 
        
        // find the desired level for our viruses
        foreach(var virus in viruses)
            if(virus.getOwner() == enemyID())
            {
                desired_virus_level += virus.getLevel();
                enemy_virus_count++;
            }
        if(enemy_virus_count > 0)
            desired_virus_level = (int)Math.Ceiling((double)desired_virus_level/(double)enemy_virus_count) + 1;
        
        // for each of my bases try to spawn a virus
        var my_bases = new Dictionary<Base, int>();
        foreach(var my_base in bases)
            if(
                my_base.getOwner() == playerID() && 
                map[my_base.getX(),my_base.getY()].VirusLevel == -1 &&
                players[playerID()].getCycles() >= 10
               )
            {
                
                var grid = get_pathnode_map(my_base.getX(), my_base.getY(), -1, false);
                var aStar = new SettlersEngine.SpatialAStar<GamePathNode, Object>(grid);
                var path = aStar.Search(new Point(my_base.getX(), my_base.getY()), new Point(desiredX, desiredY), null);
                
                //Console.WriteLine("Base at: " + my_base.getX() + "," + my_base.getY() + " has a path of length " + (path != null ? Convert.ToString(path.Count) : "NULL") );
                
                my_bases.Add(my_base, path != null ? path.Count : int.MaxValue);
            }
        
        var sortedBases = from key in my_bases.Keys
                          orderby my_bases[key] ascending
                          select key;
                          
        foreach(var my_base in sortedBases)
            my_base.spawn(0);
            
        // check to see if we will loose soon
        if(players[enemyID()].getByteDollars() >= 118)
            players[playerID()].talk("I curse Wooly Willy on you, " + players[enemyID()].getPlayerName());
        
        // for each of my viruses find a point to go to, then go there!
        foreach(var virus in viruses)
        {
            if(virus.getOwner() == playerID())
            {
                update_map();
                
                var pt = find_point(virus.getX(), virus.getY(), virus.getLevel(), desired_virus_level);
                
                var points = new List<GamePoint>();
                int loopCount = 0;
                while(pt != null && loopCount < 1000)
                {
                    loopCount++;
                    points.Insert(0, pt);
                    pt = pt.Parent;
                }
                
                if(loopCount >= 999)
                    Console.WriteLine("ALERT: Preventing Infinite Loop at UNPACKING POINTS.");
                
                loopCount = 0;
                while(virus.getMovesLeft() > 0 && points.Count > 0 && loopCount < 1000)
                {
                    //switch(rand.Next(5)) { case 0: virus.move(virus.getX() + 1, virus.getY()); break;  case 1: virus.move(virus.getX(), virus.getY() + 1); break;  case 2: virus.move(virus.getX(), virus.getY() - 1); break;  case 3: virus.move(virus.getX() - 1, virus.getY()); break; }
                    loopCount++;
                    virus.move(points[0].X, points[0].Y);
                    //if we just move to the desired point
                    if(goingAfterEnemy && points[0].X == desiredX && points[0].Y == desiredY)
                        find_new_desired_point(points[0].X, points[0].Y);
                    points.RemoveAt(0);
                }
                
                if(loopCount >= 999)
                    Console.WriteLine("ALERT: Preventing Infinite Loop at DOING MOVE.");
            }
        }
        
        return true;
    }
    
    public void update_map()
    {
        int neutralTiles = 0, takenTiles = 0;
        
        // reset the map
        for(int x = 0; x < width(); x++)
            for(int y = 0; y < height(); y++)
            {
                map[x, y].VirusLevel = -1;
                map[x, y].Type = NodeType.Unset;
            }
        
        // map all the tiles
        foreach(var tile in tiles)
        {
            if(tile.getOwner() == wall())
                map[tile.getX(), tile.getY()].Type = NodeType.Wall;
            else if(tile.getOwner() == neutral_tile())
            {
                map[tile.getX(), tile.getY()].Type = NodeType.NeutralTile;
                neutralTiles++;
            }
            else if(tile.getOwner() == playerID())
            {
                map[tile.getX(), tile.getY()].Type = NodeType.MyTile;
                takenTiles++;
            }
            else if(tile.getOwner() == enemyID())
            {
                map[tile.getX(), tile.getY()].Type = NodeType.EnemyTile;
                takenTiles++;
            }
        }
        
        // map all the viruses
        foreach(var virus in viruses)
        {
            if(virus.getOwner() == playerID())
            {
                map[virus.getX(), virus.getY()].Type = NodeType.MyVirus;
                map[virus.getX(), virus.getY()].VirusLevel = virus.getLevel();
            }
            else if(virus.getOwner() == enemyID())
            {
                map[virus.getX(), virus.getY()].Type = NodeType.EnemyVirus;
                map[virus.getX(), virus.getY()].VirusLevel = virus.getLevel();
            }  
        }
        
        // map all the bases (a base with a virus on it will still have the VirusLevel set)
        foreach(var some_base in bases)
        {
            if(some_base.getOwner() == playerID())
                map[some_base.getX(), some_base.getY()].Type = NodeType.MyBase;
            else if(some_base.getOwner() == enemyID())
                map[some_base.getX(), some_base.getY()].Type = NodeType.EnemyBase;
        }
        
        if(neutralTiles < takenTiles && !goingAfterEnemy)
        {
            find_new_desired_point(desiredX, desiredY);
            
            goingAfterEnemy = true;
            
            Console.WriteLine("I SAY: die enemy viruses!");
        }
    }
    
    public GamePoint find_point(int x, int y, int this_virus_level, int desired_virus_level)
    {
        if(x >= width() || y >= height() || y < 0 || x < 0)
            return null;
        
        // BEGIN: First find a path to the desired position to influence our movement
        var grid = get_pathnode_map(x, y, this_virus_level, !goingAfterEnemy);
        var aStar = new SettlersEngine.SpatialAStar<GamePathNode, Object>(grid);
        var path = aStar.Search(new Point(x, y), new Point(desiredX, desiredY), null);
        //LinkedList<GamePathNode> path = null;
        // END: First find a path to the desired position to influence our movement
        
        
        var points = new List<GamePoint>();
        var returnablePoints = new List<GamePoint>();
        //var startingPoint = new GamePoint(x, y);
        points.Add(new GamePoint(x + 1, y));
        points.Add(new GamePoint(x - 1, y));
        points.Add(new GamePoint(x, y + 1));
        points.Add(new GamePoint(x, y - 1));
        
        int loopCount = 0;
        int returnDepth = 0;
        
        while(points.Count > 0 && loopCount < 1000)
        {
            //Console.WriteLine("FloodFill: " + loopCount);
            var pt = points[0];
            loopCount++;
            
            // make sure the point is not out of range of the game board
            if(pt.X >= width() || pt.X < 0 || pt.Y >= height() || pt.Y < 0)
            {
                points.Remove(pt);
                continue;
            }
            
            
            // check to make sure this tile is not dangerous (eg >= enemy virus adjacent to it), if it is remove it
            if(pt.X + 1 < width())
            {
                if(map[pt.X + 1, pt.Y].Type == NodeType.EnemyVirus && map[pt.X + 1, pt.Y].VirusLevel >= this_virus_level)
                {
                    points.Remove(pt);
                    continue;
                }
            }
            if(pt.X - 1 >= 0)
            {
                if(map[pt.X - 1, pt.Y].Type == NodeType.EnemyVirus && map[pt.X - 1, pt.Y].VirusLevel >= this_virus_level)
                {
                    points.Remove(pt);
                    continue;
                }
            }
            if(pt.Y + 1 < height())
            {
                if(map[pt.X, pt.Y + 1].Type == NodeType.EnemyVirus && map[pt.X, pt.Y + 1].VirusLevel >= this_virus_level)
                {
                    points.Remove(pt);
                    continue;
                }
            }
            if(pt.Y - 1 >= 0)
            {
                if(map[pt.X, pt.Y - 1].Type == NodeType.EnemyVirus && map[pt.X, pt.Y - 1].VirusLevel >= this_virus_level)
                {
                    points.Remove(pt);
                    continue;
                }
            }
            
            // at this point we willa ctually look at this node
            var node = map[pt.X, pt.Y];
            
            // if it is interesting let's go to it
            if(node.Type == NodeType.EnemyTile ||
               node.Type == NodeType.NeutralTile ||
              (node.Type == NodeType.EnemyVirus && node.VirusLevel < this_virus_level) ||
              (node.Type == NodeType.MyVirus && node.VirusLevel == this_virus_level && this_virus_level < desired_virus_level && pt.Depth == 1))
            {
                returnablePoints.Add(pt);
                points.Remove(pt);
                
                if(returnDepth == 0)
                    returnDepth = pt.Depth;
            }
            // else if the pt is not interesting remove it
            else if(node.Type == NodeType.Wall ||
               node.Type == NodeType.MyBase ||
               node.Type == NodeType.EnemyBase ||
              (node.Type == NodeType.MyVirus && node.VirusLevel != this_virus_level) ||
              (node.Type == NodeType.EnemyVirus && node.VirusLevel >= this_virus_level) ||
              (node.Type == NodeType.MyVirus && pt.Depth == 1))
            {
                points.Remove(pt);
            }
            // else if it is my tile or my far away virus look for something else
            else if(node.Type == NodeType.MyTile || (node.Type == NodeType.MyVirus && pt.Depth > 1) )
            {
                // if we can add the point then do so
                if(returnDepth == 0 || pt.Depth < returnDepth)
                {
                    // for each direction made a seed point in that direction and add it to the points if that point is not already in points
                    foreach(Direction dir in Enum.GetValues(typeof(Direction)))
                    {
                        var seedPoint = new GamePoint(pt, dir);
                        
                        bool alreadyInPoints = false;
                        
                        foreach(var point in points)
                            if(point.X == seedPoint.X && point.Y == seedPoint.Y)
                            {
                                alreadyInPoints = true;
                                break;
                            }
                        
                        if(!alreadyInPoints)
                            points.Add(seedPoint);
                    }
                }
                points.Remove(pt);
            }
            else
            {
                Console.WriteLine("PROBLEM: I don't know what to do for this node of type: " + node.Type);
                return null;
            }
        }
        
        
        if(loopCount >= 999)
            Console.WriteLine("ALERT: Preventing Infinite Loop at Flood Fill.");
            
        if(returnablePoints.Count > 0)
        {
            // Check points for Priority in this order:
            //   1. Enemy Viruses
            //   2. Enemy Tiles
            //   3. Neutral Tiles
            //   4. My Viruses to join with
            
            var inOrder = new List<GamePoint>();
            
            foreach(var returnablePoint in returnablePoints)
                if(map[returnablePoint.X, returnablePoint.Y].Type == NodeType.EnemyVirus)
                    inOrder.Add(returnablePoint);
            
            foreach(var returnablePoint in returnablePoints)
                if(map[returnablePoint.X, returnablePoint.Y].Type == NodeType.EnemyTile)
                    inOrder.Add(returnablePoint);
            
            foreach(var returnablePoint in returnablePoints)
                if(map[returnablePoint.X, returnablePoint.Y].Type == NodeType.NeutralTile)
                    inOrder.Add(returnablePoint);
            
            foreach(var returnablePoint in returnablePoints)
                if(map[returnablePoint.X, returnablePoint.Y].Type == NodeType.MyVirus)
                    inOrder.Add(returnablePoint);
            
            // go through the points we want in order and if there is a path return the point that is in that path
            //   this basically says, "oh you have a many options? well take the one that mvoes you closer to the desired point".
            if(path != null && path.Count > 2)
            {
                path.RemoveFirst();
                GamePathNode firstStep = null;
                
                //because path.First won't compile :(
                foreach(var node in path)
                {
                    firstStep = node;
                    break;
                }
                
                foreach(var returnablePoint in inOrder)
                    if(returnablePoint.X == firstStep.X && returnablePoint.Y == firstStep.Y)
                        return returnablePoint;
            }
            
            //only should happen if there was no path
            return inOrder[0];
        }
        else
        {
            // just go where ever that path we found the the desired point is
            if(path != null && path.Count > 2)
            {
                path.RemoveFirst();
                GamePathNode firstStep = null;
                
                //because path.First won't compile :(
                foreach(var node in path)
                {
                    firstStep = node;
                    break;
                }

                return new GamePoint(firstStep.X, firstStep.Y);
            }
        }
        
        Console.WriteLine("PROBLEM: No point was found to return...\n");
        return null;
    }
    
    public int distanceToNearestTakenNode(int x, int y)
    {
        var points = new List<GamePoint>();
        points.Add(new GamePoint(x + 1, y));
        points.Add(new GamePoint(x - 1, y));
        points.Add(new GamePoint(x, y + 1));
        points.Add(new GamePoint(x, y - 1));
        
        int deepestPoint = 1;
        int loopCount = 0;
        
        while(points.Count > 0 && loopCount < 10000)
        {
            var pt = points[0];
            loopCount++;
            
            if(deepestPoint < pt.Depth)
                deepestPoint = pt.Depth;
            
            // make sure the point is not out of range of the game board
            if(pt.X >= width() || pt.X < 0 || pt.Y >= height() || pt.Y < 0)
            {
                points.Remove(pt);
                continue;
            }
            
            var node = map[pt.X, pt.Y];

            if(node.Type == NodeType.Wall)
            {
                points.Remove(pt);
            }
            else if(node.Type == NodeType.MyVirus ||
                    node.Type == NodeType.EnemyVirus ||
                    node.Type == NodeType.MyBase ||
                    node.Type == NodeType.EnemyBase ||
                    node.Type == NodeType.MyTile ||
                    node.Type == NodeType.EnemyTile)
            {
                //Console.WriteLine("OMG: Not preventing NTN!");
                return deepestPoint;
            }
            else // should be a Neutral Tile
            {
                foreach(Direction dir in Enum.GetValues(typeof(Direction)))
                {
                    var seedPoint = new GamePoint(pt, dir);
                    
                    bool alreadyInPoints = false;
                    
                    foreach(var point in points)
                        if(point.X == seedPoint.X && point.Y == seedPoint.Y)
                        {
                            alreadyInPoints = true;
                            break;
                        }
                    
                    if(!alreadyInPoints)
                        points.Add(seedPoint);
                }
                
                points.Remove(pt);
            }
        }
        
        if(loopCount >= 9999)
            Console.WriteLine("ALERT: Preventing Infinite Loop at Nearest Taken Node. (Which means node should be trapped)");
        
        return -1;
    }
    
    public GamePathNode[,] get_pathnode_map(int startX, int startY, int start_virus_level, bool my_tiles_are_blocked)
    {
        update_map();
        
        var pathNodeMap = new GamePathNode[width(), height()];
        
        for(int x = 0; x < width(); x++)
        {
            for(int y = 0; y < height(); y++)
            {
                Boolean isWall = false;
                
                var node = map[x, y];
                
                // WALL: node that can't be moved through
                if(node.Type == NodeType.MyBase ||
                   node.Type == NodeType.EnemyBase ||
                   node.Type == NodeType.Wall ||
                  (node.Type == NodeType.EnemyVirus && node.VirusLevel >= start_virus_level) ||
                  (node.Type == NodeType.MyTile && my_tiles_are_blocked)
                  )
                {
                    isWall = true;
                }
                // NOT WALL: starting location
                else if(x == startX && y == startY)
                {
                    isWall = false;
                }
                // WALL: adjacent virus of mine
                else if(
                            node.Type == NodeType.MyVirus &&
                            (
                                ( x == startX + 1 && y == startY ) ||
                                ( x == startX - 1 && y == startY ) ||
                                ( x == startX && y == startY + 1 ) ||
                                ( x == startX && y == startY - 1 )
                            )
                       )
                {
                    isWall = true;
                }
                // NOT WALL: anything else (hopefully)
                else
                {
                    isWall = false;
                }
                
                // WALL: Adjacent tile with adjecent >= level enemy virus
                if(
                    ( x == startX + 1 && y == startY ) ||
                    ( x == startX - 1 && y == startY ) ||
                    ( x == startX && y == startY + 1 ) ||
                    ( x == startX && y == startY - 1 )
                  )
                {
                    if(x + 1 < width())
                    {
                        if(map[x + 1, y].Type == NodeType.EnemyVirus && start_virus_level <= map[x + 1, y].VirusLevel)
                        {
                            isWall = true;
                        }
                    }
                    else if(x - 1 >= 0)
                    {
                        if(map[x - 1, y].Type == NodeType.EnemyVirus && start_virus_level <= map[x - 1, y].VirusLevel)
                        {
                            isWall = true;
                        }
                    }
                    else if(y + 1 < height())
                    {
                        if(map[x, y + 1].Type == NodeType.EnemyVirus && start_virus_level <= map[x, y + 1].VirusLevel)
                        {
                            isWall = true;
                        }
                    }
                    else if(y - 1 >= 0)
                    {
                        if(map[x, y - 1].Type == NodeType.EnemyVirus && start_virus_level <= map[x, y - 1].VirusLevel)
                        {
                            isWall = true;
                        }
                    }
                }
                
                if(start_virus_level == -1 && startX == x && startY == y)
                    isWall = false;
                
                pathNodeMap[x, y] = new GamePathNode()
                {
                    IsWall = isWall,
                    X = x,
                    Y = y,
                };
            }
        }
        
        return pathNodeMap;
    }
    
    public void find_new_desired_point(int previousX, int previousY)
    {
        foreach(var enemy_base in bases)
            if(enemy_base.getOwner() == enemyID())
                if(enemy_base.getX() != previousX && enemy_base.getY() != previousY)
                {
                    if(enemy_base.getX() + 1 < width())
                        if(map[enemy_base.getX() + 1, enemy_base.getY()].Type != NodeType.Wall)
                        {
                            desiredX = enemy_base.getX();
                            desiredY = enemy_base.getY();
                            players[playerID()].talk("Spawn Camp: (" + desiredX + "," + desiredY + ")");
                            break;
                        }
                    
                    if(enemy_base.getX() - 1 >= 0)
                        if(map[enemy_base.getX() - 1, enemy_base.getY()].Type != NodeType.Wall)
                        {
                            desiredX = enemy_base.getX();
                            desiredY = enemy_base.getY();
                            players[playerID()].talk("Spawn Camp: (" + desiredX + "," + desiredY + ")");
                            break;
                        }
                    
                    if(enemy_base.getY() + 1 < height())
                        if(map[enemy_base.getX(), enemy_base.getY() + 1].Type != NodeType.Wall)
                        {
                            desiredX = enemy_base.getX();
                            desiredY = enemy_base.getY();
                            players[playerID()].talk("Spawn Camp: (" + desiredX + "," + desiredY + ")");
                            break;
                        }
                    
                    if(enemy_base.getY() - 1 >= 0)
                        if(map[enemy_base.getX(), enemy_base.getY() - 1].Type != NodeType.Wall)
                        {
                            desiredX = enemy_base.getX();
                            desiredY = enemy_base.getY();
                            players[playerID()].talk("Spawn Camp: (" + desiredX + "," + desiredY + ")");
                            break;
                        }
                }
    }
}

public class GamePathNode : SettlersEngine.IPathNode<Object>
{
    public Int32 X { get; set; }
    public Int32 Y { get; set; }
    public Boolean IsWall { get; set; }

    public bool IsWalkable(Object unused)
    {
        return !IsWall;
    }
}

