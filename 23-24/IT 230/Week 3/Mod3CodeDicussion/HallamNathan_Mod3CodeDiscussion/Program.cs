using System;

namespace DailyRate
{
	class Program
	{
		static void Main(string[] args)
		{
			(new Program()).run();
		}


		void run()
		{
			double dailyRate = readDouble("Enter your daily rate: ");
			int noOfDays = readInt("Enter the number of days: ");
			writeFee(dailyRate, noOfDays);
		}


		private void writeFee(double p, int n)
		{
			Console.WriteLine("The consultant's fee is: {0}", calculateFee(p, n) * 1.1);
		}


		private double calculateFee(double dailyRate, int noOfDays)
		{ 
			return dailyRate* noOfDays;
		}


		private int readInt(string p)
		{
			Console.Write(p);
			string line = Console.ReadLine();
			return int.Parse(line);
		}


		private double readDouble(string p)
		{
			Console.Write(p);
			string line = Console.ReadLine();
			return double.Parse(line);
		}
	} 
} 