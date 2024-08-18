input_file = input()

seasons = {}
keys_sorted = []
shows = []

with open(input_file, 'r') as file:
    contents = file.readlines()

    i = 0
    for line in contents:
        contents[i] = line.replace('\n', '')
        i += 1

    for line in range(0, len(contents) - 1):
        if line % 2 == 1:
            continue

        if contents[line] in seasons.keys():
            seasons[contents[line]] += '; {}'.format(contents[line + 1])
            shows.append(contents[line + 1])
        else:
            seasons[contents[line]] = contents[line + 1]
            shows.append(contents[line + 1])

    for key in seasons.keys():
        keys_sorted.append(key)

    keys_sorted.sort()
    shows.sort()

    with open('output_keys.txt', 'w') as output_keys_write:
        for key in keys_sorted:
            output_keys_write.write('{}: {}\n'.format(int(key), seasons[key]))

    with open('output_titles.txt', 'w') as output_titles_write:
        for show in shows:
            output_titles_write.write('{}\n'.format(show))
