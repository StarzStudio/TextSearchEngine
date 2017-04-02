using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsClient
{
  class Program
  {
    static void Main(string[] args)
    {
      ATLProject3Lib.IBuildDemo proxy = new ATLProject3Lib.BuildDemo();
      proxy.putString("Hi from client.");
      string answer = proxy.getString();
      Console.Write("\n  {0}\n\n", answer);
    }
  }
}
