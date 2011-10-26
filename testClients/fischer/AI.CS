using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

///The class implementing gameplay logic.
class AI : BaseAI
{
    // Variables
    public bool[,] blocked_map;
    public int opponentID;
    
    public override string username()
    {
        return "Team Name, Why Not Zoidberg?";
    }
    public override string password()
    {
        return "Woop Woop Woop Woop Woop";
    }

    //This function is called once, before your first turn
    public override void init() 
    {
        blocked_map = new bool[width(),height()];
        opponentID = (playerID() == 0 ? 1 : 0);
        Console.WriteLine("PlayerID: " + playerID() + "   OpponentID: " + opponentID);
        Console.WriteLine("Initialization called");
    }
    
    //This function is called each time it is your turn
    //Return true to end your turn, return false to ask the server for updated information
    public override bool run()
    {
        update_map();
        
        foreach(var the_base in bases)
            if(the_base.getOwner() == playerID())
                the_base.spawn(0);
        
        Random rand = new Random();
        foreach(var virus in viruses)
            if(virus.getOwner() == playerID())
            {
                // try to find a direction that isn't blocked
                int attempts = 0;
                while(virus.getMovesLeft() > 0 && attempts != 100)
                {
                    if(virus.getX() + 1 != width() && !blocked_map[virus.getX() + 1,virus.getY()])
                    {
                        Console.WriteLine("I want to logically move RIGHT\n");
                        virus.move(virus.getX() + 1, virus.getY());
                        update_map();
                    }
                    else if(virus.getX() != 0 && !blocked_map[virus.getX() - 1,virus.getY()])
                    {
                        Console.WriteLine("I want to logically move LEFT\n");
                        virus.move(virus.getX() - 1, virus.getY());
                        update_map();
                    }
                    else if(virus.getY() + 1 != height() && !blocked_map[virus.getX(),virus.getY() + 1])
                    {
                        Console.WriteLine("I want to logically move DOWN\n");
                        virus.move(virus.getX(), virus.getY() + 1);
                        update_map();
                    }
                    else if(virus.getY() != 0 && !blocked_map[virus.getX(),virus.getY() - 1])
                    {
                        Console.WriteLine("I want to logically move UP\n");
                        virus.move(virus.getX(), virus.getY() - 1);
                        update_map();
                    }
                    else // just go somewhere random...
                    {
                        int dir = rand.Next(0,4);
                        Console.WriteLine("I DON'T KNOW WHAT TO DO\n");
                        switch(dir)
                        {
                            case 0:
                                virus.move(virus.getX(), virus.getY() + 1);
                                update_map();
                                break;
                            case 1:
                                virus.move(virus.getX(), virus.getY() - 1);
                                update_map();
                                break;
                            case 2:
                                virus.move(virus.getX() + 1, virus.getY());
                                update_map();
                                break;
                            case 3:
                                virus.move(virus.getX() - 1, virus.getY());
                                update_map();
                                break;
                        }
                    }
                    
                    attempts++;
                }
                
                if(attempts == 100)
                    Console.WriteLine("hit 100 attempts...\n");
            }

        return true;
    }

    //This function is called once, after your last turn
    public override void end()
    {
        update_map();
    }

    public AI(IntPtr c) : base(c) {}
    
    // My Functions
    public void update_map()
    {
        // reset map
        for(int y = 0; y < height(); y++)
            for(int x = 0; x < width(); x++)
                blocked_map[x,y] = true;
        
        // block the map
        foreach(var tile in tiles)
            if(tile.getOwner() == 2 || tile.getOwner() == opponentID)
                blocked_map[tile.getX(), tile.getY()] = false;
        
        foreach(var the_base in bases)
            blocked_map[the_base.getX(), the_base.getY()] = true;
        
        /*for(int y = 0; y < height(); y++)
        {
            string line = "";
            for(int x = 0; x < width(); x++)
            {
                line += blocked_map[x,y] ? "X" : ".";
            }
            
            Console.WriteLine(line);
        }*/
    }
}
