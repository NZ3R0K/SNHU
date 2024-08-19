using System;
//removed unnecessary using statements

namespace DebugFixMethods
{
    class Program
    {
        static void Main()
        {
            (new Program()).Run();
        }


        //renamed from run() to Run() to adhere to conventional naming schemes
        void Run()
        {
            Console.WriteLine("Hallam Copy");   //added personalization identifier

            WritePrompt();
			
            int choice = ReadChoice();   //removed initialization of choice being set to 0 and directly set it through ReadChoice return
           
            WriteChoice(choice);

            WaitForKey();
        }


        //Writeprompt() should be WritePrompt()
        void WritePrompt()
        {
            Console.WriteLine("Please select a course for which you want to register by typing the number inside []");
            Console.WriteLine("[1]IT 145\n[2]IT 200\n[3]IT 201\n[4]IT 270\n[5]IT 315\n[6]IT 328\n[7]IT 330");
            Console.Write("Enter your choice : ");
        }


        int ReadChoice()
        {
            string s = Console.ReadLine();
            return (int.Parse(s));   //returns string when expecting int, changed to parse string to an int
        }


        //No identifier, added int
        void WriteChoice(int choice)
        {
            Console.WriteLine("Your choice is {0}", choice);   //Choice should be choice
        }


        //Added to prevent program from closing
        void WaitForKey()
        {
			Console.WriteLine("Press any key to continue . . .");
			Console.ReadKey();
		}
    }
}
