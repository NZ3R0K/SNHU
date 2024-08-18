#  Nathan Hallam
#  Must have room_data.csv to load room_data and play game

import csv
import time

room_data = {}
current_room = {}
inventory = []

end_game = False
start_hour_in_seconds = 25200 + 3300  # 7:55 AM
end_hour_in_seconds = 28800   # 8:00 AM
start_time = time.time()
time_elapsed = 0


def show_instructions():
    # print a main menu and the commands
    print("Paranoid Master Text Game")
    print("You are a servant working for a rather paranoid master.")
    print("Arriving at your masters mansion in the morning you find that almost every door is locked!")
    print("However, you feel that if you search about in each room you may find the necessary keys to progress further.")
    print("Reach the masters bedroom before he wakes, with an already prepared meal and a paper to read.")
    print("You best act quickly! Only 5 minutes remain!")


def show_loss_timeout():
    print("--------------------")
    print("\nYou tried your best, but it was not enough!")
    print("The master has woken from his slumber and hungers for his meal and itches for the daily paper.")
    print("His voices tremors throughout the mansion as your master barrels out of his room"
          " to give you a taste of despair...")
    print("\nYou are fired...")
    print("\nGAME OVER")
    print("REASON : TIMEOUT")


def show_loss_lack_item():
    print("--------------------")
    print("\nYou tried your best, but it was not enough!")
    print("You awoke the master by entering the room.")
    print("His voices tremors throughout the mansion as your master jumps out of his bed"
          " to give you a taste of despair for not being properly prepared...")
    print("\nYou are fired...")
    print("\nGAME OVER")
    print("REASON : LACK REQUIRED ITEM")


def show_win():
    print("--------------------")
    print("\nYou enter the masters room well prepared, and as you close the door your master wakes.")
    print("His voices tremors, but for a moment, as you throw the daily paper in his face as a means to placate him.")
    print("He takes the paper and begins to read, as you set up a breakfast in bed.")
    print("\nYou get to keep your job... For now...")
    print("\nGAME OVER")
    print("REASON : YOU HAVE WON")


def get_room_data_from_file():
    with open('room_data.csv', 'r') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')

        row_num = 0
        for row in reader:
            row_num += 1
            if row_num == 1:
                continue
            room_data[row[0]] = {'Name': row[0], 'Item': row[1], 'Key': row[2], 'Directions': {}}
            if row[3] != '':
                room_data[row[0]]['Directions'][row[3]] = row[4]
            if row[5] != '':
                room_data[row[0]]['Directions'][row[5]] = row[6]
            if row[7] != '':
                room_data[row[0]]['Directions'][row[7]] = row[8]
            if row[9] != '':
                room_data[row[0]]['Directions'][row[9]] = row[10]


def set_room(room):
    global current_room

    if room['Key'] == '':
        print("--------------------")
        print('\nYou have moved to the {}\n'.format(room['Name']))
        current_room = room

    elif room['Key'] in inventory:
        print("--------------------")
        print('\nThe door appears to be locked...')
        print('\nYou used {} to unlock the door'.format(room['Key']))
        inventory.remove(room['Key'])
        room['Key'] = ''
        print('Inventory: {}\n'.format(inventory))
        print('You have moved to the {}\n'.format(room['Name']))
        current_room = room

    else:
        print("--------------------")
        print('\nThe door appears to be locked... Perhaps there is a key somewhere?\n')

    if current_room["Name"] == "Master Bedroom":
        check_win_condition()
        return True

    return False


def handle_base_user_command(command):
    command = command.title()

    if (command == 'Exit') or (command == '5'):
        return True
    elif (command == 'Move') or (command == '1'):
        return handle_move(command)
    elif (command == 'Search Room') or (command == '2'):
        search_room(command, current_room)
    elif (command == 'Check Inventory') or (command == '3'):
        print("--------------------")
        print('\nInventory: {}\n'.format(inventory))
    elif (command == 'Check Time') or (command == '4'):
        print("--------------------")
        print("\nCurrent Time: {}\n".format(get_time()))
    else:
        print("--------------------")
        print("Command {} not recognised!".format(command))
    return check_loss_condition()


def handle_move(command):
    global current_room

    print("\n--------------------")
    print('\nYou can move:')
    iterations = get_move_directions(current_room['Name'])

    user_input = input('Enter a command: ')
    return handle_user_move_command(current_room['Name'], user_input, iterations)


def handle_user_move_command(current_room_name, command, stop_iteration):
    command = command.title()  # Ensure command has proper capitalization of words

    if (command == 'Cancel') or (command == stop_iteration):
        print()
        return False

    elif command in room_data[current_room_name]['Directions'].keys():  # User Input Direction
        # Rerun handle command to set room properly
        return handle_user_move_command(current_room_name, room_data[current_room_name]['Directions'][command], stop_iteration)

    elif command.isnumeric():  # User Input Number
        new_command = ''
        iterations = 1
        for value in room_data[current_room_name]['Directions'].values():
            if iterations == int(command):
                new_command = value
            iterations += 1
        # Rerun handle command to set room properly
        return handle_user_move_command(current_room_name, new_command, stop_iteration)

    else:  # User Input Room Name
        for value in (room_data[current_room_name]['Directions']).values():
            if value == command:
                return set_room(room_data[command])


def get_move_directions(current_room_name):
    global room_data

    iterations = 1

    for direction in room_data[current_room_name]['Directions']:
        print("{}. {} > {}".format(iterations, direction, room_data[current_room_name]['Directions'][direction]))
        iterations += 1

    print('{}. Cancel'.format(iterations))
    return iterations


def search_room(command, room):
    if room['Item'] != '':
        print("--------------------")
        print('\nYou have found {}!'.format(room['Item']))
        inventory.append(room['Item'])
        room['Item'] = ''
        print('Inventory: {}\n'.format(inventory))
    else:
        print("--------------------")
        print('\nThere is nothing of value here...\n')


def get_time():
    global start_time
    global time_elapsed
    time_elapsed = round((start_time - time.time()) * -1, 2)
    hours = round((start_hour_in_seconds + time_elapsed) // 3600, 2)
    minutes = round(((start_hour_in_seconds + time_elapsed) % 3600) // 60, 2)
    seconds = round((((start_hour_in_seconds + time_elapsed) % 3600) % 60), 2)
    return "{:02d}:{:02d}:{:02d}".format(int(hours), int(minutes), int(seconds))


def check_loss_condition():
    get_time()

    if time_elapsed + start_hour_in_seconds >= end_hour_in_seconds:
        show_loss_timeout()
        return True
    return False


def check_win_condition():
    if (inventory.__contains__("Daily Newspaper")) and (inventory.__contains__("Prepared Meal")):
        show_win()
    else:
        show_loss_lack_item()
    return True


def main():
    get_room_data_from_file()
    global current_room
    global end_game
    current_room = room_data['Foyer']

    show_instructions()

    while not end_game:
        print("--------------------")
        print("You are in the {}".format(current_room['Name']))
        print("\nActions:\n1. Move \n2. Search Room \n3. Check Inventory \n4. Check Time \n5. Exit")
        user_input = input('Enter a command: ')
        end_game = handle_base_user_command(user_input)


main()
