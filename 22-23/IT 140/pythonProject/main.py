import random

print("Welcome to the higher/lower game, Bella!")
lower_bound = int(input("Enter the lower bound: "))
upper_bound = int(input("Enter the upper bound: "))

while lower_bound >= upper_bound:
    print("\nThe lower bound must be less than the upper bound. ")
    lower_bound = int(input("Enter the lower bound: "))
    upper_bound = int(input("Enter the upper bound: "))

random_value = random.randint(lower_bound, upper_bound)

user_guess = int(input("Great, now guess a number between " + str(lower_bound) + " and " + str(upper_bound) + ": "))

while user_guess < lower_bound or user_guess > upper_bound:
    print("\nYou did not give a value between the associated bounds!")
    user_guess = int(input("Guess a number between " + str(lower_bound) + " and " + str(upper_bound) + ": "))

while user_guess != random_value:
    if user_guess > random_value:
        print("Nope, too high.")
    elif user_guess < random_value:
        print("Nope, too low.")

    user_guess = int(input("\nGuess another number: "))

print("You got it!")