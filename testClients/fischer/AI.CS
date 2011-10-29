using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

enum Direction { Up = 0, Left = 1, Down = 2, Right = 3 }
enum NodeType { Unset = -1, Wall, EnemyBase, MyBase, MyTile, EnemyTile, NeutralTile, EnemyVirus, MyVirus }

class GameNode {
    public NodeType Type = NodeType.Unset;
    public int VirusLevel = -1;
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
    private const int UNSET = -1;
    
    public override string username() { return "Geordi's Visor"; }
    public override string password() { return "TNG"; }
    public AI(IntPtr c) : base(c) {}
    public override void end() {}
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
        
        Console.WriteLine("Hello World");
    }

    public override bool run()
    {
        update_map();
        
        int desired_virus_level = 0;
        int enemy_virus_count = 0;
        
        // find the desired level for our viruses
        foreach(var virus in viruses)
            if(virus.getOwner() == enemyID())
            {
                desired_virus_level += virus.getLevel();
                enemy_virus_count++;
            }
        if(enemy_virus_count > 0)
            desired_virus_level = (int)Math.Ceiling((double)desired_virus_level/(double)enemy_virus_count);
        
        // for each of my bases try to spawn a virus
        foreach(var my_base in bases)
            if(
                my_base.getOwner() == playerID() && 
                map[my_base.getX(),my_base.getY()].VirusLevel == -1 &&
                players[playerID()].getByteDollars() > (int)(baseCost() * scaleCost()) &&
                my_base.getSpawnsLeft() > 0 &&
                players[playerID()].getCycles() > 0
               )
                my_base.spawn(0);
        
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
                map[tile.getX(), tile.getY()].Type = NodeType.NeutralTile;
            else if(tile.getOwner() == playerID())
                map[tile.getX(), tile.getY()].Type = NodeType.MyTile;
            else if(tile.getOwner() == enemyID())
                map[tile.getX(), tile.getY()].Type = NodeType.EnemyTile;
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
    }
    
    public GamePoint find_point(int x, int y, int this_virus_level, int desired_virus_level)
    {
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
            
            var node = map[pt.X, pt.Y];
            
            // if it is interesting let's go to it
            if(node.Type == NodeType.EnemyTile ||
               node.Type == NodeType.NeutralTile ||
              (node.Type == NodeType.EnemyVirus && node.VirusLevel < this_virus_level) ||
              (node.Type == NodeType.MyVirus && node.VirusLevel == this_virus_level && this_virus_level < desired_virus_level ))
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
              (node.Type == NodeType.MyVirus))
            {
                points.Remove(pt);
            }
            // else if it is my tile look for something else
            else if(node.Type == NodeType.MyTile)
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
            
            foreach(var returnablePoint in returnablePoints)
                if(map[returnablePoint.X, returnablePoint.Y].Type == NodeType.EnemyVirus)
                    return returnablePoint;
            
            foreach(var returnablePoint in returnablePoints)
                if(map[returnablePoint.X, returnablePoint.Y].Type == NodeType.EnemyTile)
                    return returnablePoint;
            
            foreach(var returnablePoint in returnablePoints)
                if(map[returnablePoint.X, returnablePoint.Y].Type == NodeType.NeutralTile)
                    return returnablePoint;
            
            foreach(var returnablePoint in returnablePoints)
                if(map[returnablePoint.X, returnablePoint.Y].Type == NodeType.MyVirus)
                    return returnablePoint;
            
            Console.WriteLine("PROBLEM: No returnablePoints have any Priority!");
            return returnablePoints[0];
        }
        else
        {
            Console.WriteLine("PROBLEM: No point was found to return...\n");
        }
        
        return null;
    }
    
    
}
