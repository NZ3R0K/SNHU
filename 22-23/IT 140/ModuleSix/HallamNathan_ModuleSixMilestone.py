# Nathan Hallam
rooms = {
    'Foyer': {'North': 'Stair Hall', 'East': 'Den', 'West': 'Writing Room'},
    'Writing Room': {'North': 'Library', 'East': 'Foyer'},
    'Den': {'North': 'Dining Room', 'West': 'Foyer'},
    'Library': {'East': 'Stair Hall', 'South': 'Writing Room'},
    'Dining Room': {'North': 'Butlers Pantry', 'South': 'Den', 'West': 'Stair Hall'},
    'Stair Hall': {'North': 'Balcony', 'East': 'Dining Room', 'South': 'Foyer', 'West': 'Library'},
    'Butler''s Pantry': {'North': 'Kitchen', 'South': 'Dining Room'},
    'Kitchen': {'South': 'Butlers Pantry'},
    'Balcony': {'North': 'Master Bedroom', 'East': 'Study', 'South': 'Stair Hall', 'West': 'Guest Bedroom'},
    'Guest Bedroom': {'East': 'Balcony'},
    'Study': {'West': 'Balcony'},
    'Master Bedroom': {'West': 'Balcony'}
    }

user_command = ''
current_room = 'Foyer'


def set_room(room):
    global current_room
    current_room = room
    print('You have moved to {}'.format(room))


def move_to_room(command):
    print(command)


def handle_user_main_command(command):

    if (command == "exit") or (command == "2"):
        return True

    elif (command == "move") or (command == "1"):
        print("\nYou can move:")
        get_move_directions()
        return False

    else:
        print('Command Not Recognized, try again...')
        return False


def handle_user_move_command(command, stop_iteration):
    command = command.title()  # Ensure command has proper capitalization of words

    if (command == 'Cancel') or (command == stop_iteration):
        return

    elif command in rooms[current_room].values():  # User Input Room Name
        set_room(command)

    elif command in rooms[current_room].keys():  # User Input Direction
        handle_user_move_command(rooms[current_room][command], stop_iteration)  # Rerun handle command to set room properly

    elif command.isnumeric():  # User Input Number
        new_command = ''
        iterations = 1
        for value in rooms[current_room].values():
            if iterations == int(command):
                new_command = value
            iterations += 1
        handle_user_move_command(new_command, stop_iteration)  # Rerun handle command to set room properly


def get_move_directions():

    iterations = 1

    for directions in rooms[current_room]:
        print("{}. {} > {}".format(iterations, directions, rooms[current_room][directions]))
        iterations += 1

    print('{}. Cancel'.format(iterations))

    handle_user_move_command(str.lower(input("Type in a command...\n > ")), iterations)


print("Text Adventure Game --- START")
end_game = False

while not end_game:
    print("\nYou can:")
    print("1. Move \n2. Exit")
    user_command = str.lower(input("Type in a command...\n > "))
    end_game = handle_user_main_command(user_command)

print("Game End")
