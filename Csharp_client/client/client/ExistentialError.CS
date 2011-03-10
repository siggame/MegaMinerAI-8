public class ExistentialError : System.ApplicationException
{
  ExistentialError()
  {
    super("Object does not exist anymore.");
  }
}
