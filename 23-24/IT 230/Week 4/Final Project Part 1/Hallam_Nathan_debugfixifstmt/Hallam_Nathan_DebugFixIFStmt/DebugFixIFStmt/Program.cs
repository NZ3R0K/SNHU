using System;

namespace DebugFixIFStmt
{
    class Program
    {
        static void Main()
        {
            (new Program()).Run();
        }


        void Run()
        {
            int firstChoice = 0; int secondChoice = 0; int thirdChoice = 0;

            Console.WriteLine("Hallam's Copy");

            WriteCurrentChoices(firstChoice, secondChoice, thirdChoice);

            firstChoice = 2; secondChoice = 0; thirdChoice = 0;
            WriteCurrentChoices(firstChoice, secondChoice, thirdChoice);

            firstChoice = 2; secondChoice = 5; thirdChoice = 0;
            WriteCurrentChoices(firstChoice, secondChoice, thirdChoice);

            firstChoice = 2; secondChoice = 5; thirdChoice = 7;
            WriteCurrentChoices(firstChoice, secondChoice, thirdChoice);

            WaitForKey();
        }


        void WriteCurrentChoices(int firstChoice, int secondChoice, int thirdChoice)
        {
            if (firstChoice == 0)   //was secondChoice == 0
                Console.WriteLine("Choices are: {0}, {1}, {2} => There are no choices yet", firstChoice, secondChoice, thirdChoice);
            else if (secondChoice == 0)   //was secondChoice = 0
                Console.WriteLine("Choices are: {0}, {1}, {2} => Currently choices are {0}", firstChoice, secondChoice, thirdChoice);
            else if (thirdChoice == 0)   //was thirdChoice === 0
				Console.WriteLine("Choices are: {0}, {1}, {2} => Currently choices are {0}, {1}", firstChoice, secondChoice, thirdChoice);
            else if(thirdChoice != 0 )//    was thirdChoice == 0
                Console.WriteLine("Choices are: {0}, {1}, {2} => Currently choices are {0}, {1}, {2}",
                    firstChoice, secondChoice, thirdChoice);
        }


        //Added method to wait for key input from user
        void WaitForKey()
        {
			Console.WriteLine("Press any key to continue . . .");
			Console.ReadKey();
		}
    }
}