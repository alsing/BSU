def CalculateArea(right, left, top, bottom):
    return (right - left) * (top - bottom)


def TakeX(elements):
    return elements[0]


with open("input.txt", "r") as input_file:
    n_trees, width, height = list(map(int, input_file.readline().split()))
    trees = []
    unique_y = set()
    for line in input_file:
        x, y = map(int, line.split())
        trees.append([x, y])
        unique_y.add(y)

trees.sort(key=TakeX)
unique_y_list = list(unique_y)
unique_y_list.insert(0, 0)
unique_y_list.append(height)

area = 0
for i in range(len(unique_y_list) - 1, -1, -1):
    for j in range(len(unique_y_list) - 1, i, -1):
        left_border = 0
        right_border = 0
        for tree in trees:
            if unique_y_list[i] < tree[1] < unique_y_list[j] and right_border != tree[0]:
                right_border = tree[0]
                area = max(area, CalculateArea(right_border, left_border, unique_y_list[j], unique_y_list[i]))
                left_border = right_border
        right_border = width
        area = max(area, CalculateArea(right_border, left_border, unique_y_list[j], unique_y_list[i]))

with open("output.txt", "w") as output_file:
    output_file.write(str(area))
