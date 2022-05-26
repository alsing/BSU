n, k = map(int, input().split())

chu = [1, 3, 8]
ka = [1, 3, 8]
pi = [1, 3, 8]

for i in range(3, n + 1):
    chu.append(chu[i - 1] + ka[i - 1] + pi[i - 1] - pi[i - 2])
    ka.append(chu[i - 1] + ka[i - 1] + pi[i - 1] - chu[i - 3] - pi[i - 3])
    pi.append(chu[i - 1] + ka[i - 1] + pi[i - 1] - chu[i - 3] - ka[i - 3])

town_name = ''
previous_syllable = ''
current_syllable = ''

for i in range(n - 1, -1, -1):
    if k <= chu[i]:
        current_syllable = 'chu'
        town_name += current_syllable
        if i >= 2:
            ka[i - 1] -= pi[i - 2]
    elif k <= chu[i] + ka[i]:
        current_syllable = 'ka'
        town_name += current_syllable
        k -= chu[i]
        if previous_syllable == 'ka':
            ka[i - 1] = 0
        elif i >= 2:
            ka[i - 1] = chu[i - 2] + pi[i - 2]
    else:
        current_syllable = 'pi'
        town_name += current_syllable
        k = k - chu[i] - ka[i]
        if i >= 2:
            pi[i - 1] = chu[i - 2] + ka[i - 2]

    previous_syllable = current_syllable

print(town_name)
