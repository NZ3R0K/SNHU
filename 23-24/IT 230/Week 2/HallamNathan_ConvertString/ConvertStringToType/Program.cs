public class Program
{
	public static void Main()
	{
		// Define local variables
		bool continueProgram = true;
		string userInput;

		do
		{
			// Get user input
			Console.Write("Please enter a string: ");
			userInput = Console.ReadLine();

			// If input empty, skip handle
			if (userInput == string.Empty)
				Console.WriteLine("Input is empty!");
			else
				HandleOutput(userInput);


			// Query if program should close
			Console.Write("\nClose Program? (Y/N): ");
			userInput = Console.ReadLine();
			Console.Write("\n\n");

			if (char.TryParse(userInput, out char result))
				if (char.ToUpper(result) == 'Y')
					continueProgram = false;
		}
		while (continueProgram);


		Console.WriteLine("\n\nProgram stopped, press any key to continue...");
		Console.ReadLine();
	}


	// Handles the checking of the user's input and writes to console depending on the type
	static void HandleOutput(string input)
	{
		if (ConvertToType(input, out int intOut))
			Console.WriteLine($"Integer: {intOut}");

		else if (ConvertToType(input, out float singleOut))
			Console.WriteLine($"Float: {singleOut}");

		else if (ConvertToType(input, out char charOut))
			Console.WriteLine($"Character: {charOut}");

		else if (ConvertToType(input, out bool boolOut))
			Console.WriteLine($"Boolean: {boolOut}");

		else
			Console.WriteLine($"String: {input}");
	}


	// Takes in a defined type and returns true if it was able to convert, otherwise false.
	static bool ConvertToType<T>(string input, out T? output)
	{
		try
		{
			// Uses the generic type 'T' to allow for any type to be defined
			output = (T)Convert.ChangeType(input, typeof(T));
			return true;
		}
		catch
		{
			output = default;
			return false;
		}
	}
}