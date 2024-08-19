class Program
{
	static void Main()
	{
		Console.WriteLine("Hallam's Copy");
		
		//Get user input
		Console.Write("Enter a number: ");
		int userChoice = int.Parse(Console.ReadLine());

		//Print selection
		Console.WriteLine($"Your choice of {userChoice} is the course {SwitchInput(userChoice)}");

		AwaitKey();
	}


	//Uses a switch statement to parse an int selection to a string value
	static string SwitchInput(int selection)
	{
		return selection switch
		{
			1 => "IT 145",
			2 => "IT 200",
			3 => "IT 201",
			4 => "IT 270",
			5 => "IT 315",
			6 => "IT 328",
			7 => "IT 330",
			_ => "INVALID",
		};
	}


	//Prints and waits for the user to input a key to close program
	static void AwaitKey()
	{
		Console.WriteLine("Press any key to continue . . .");
		Console.ReadKey();
	}
}