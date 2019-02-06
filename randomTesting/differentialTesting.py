import os
import glob
import filecmp
import random
import string


def clean_old_files():
    os.chdir("./tests")
    os.system("rm -f *.profdata")
    os.system("rm -f *.profdata")
    os.system("rm -f *.txt")

    os.chdir("../..")
    os.system("rm -f *.profdata")
    os.system("rm -f *.profraw")
    os.system("rm -f coverage.txt")

    os.chdir("./randomTesting")

def print_points_to_file(file, input_list):
    file.write(str(input_list[0]) + " " + str(input_list[1]))
    file.write(" ")
    file.write(str(input_list[2]) + " " + str(input_list[3]))
    file.write(" ")
    file.write(str(input_list[4]) + " " + str(input_list[5]))


def compare_file_results():
    global errorFound
    os.chdir("./tests")
    test_set = glob.glob("*txt")
    sorted_tests = sorted(test_set, key=lambda name: int(name[4:-4]))

    count = 0
    for test in sorted_tests:
        if (count % 1000 == 0):
            print(test)
        count = count + 1

        os.system("../../ShapeFinder < " + test + "> output1.txt")
        os.system("../../will_classifier < " + test + "> output2.txt")

        if not filecmp.cmp("output1.txt", "output2.txt", shallow=False):
            print(test[:-4] + " Error")
            file1 = open("output1.txt")
            print("Erik Says: " + file1.readline())
            file1.close()
            file2 = open("output2.txt")
            print("Will Says: " + file2.readline())
            file2.close()
            errorFound = errorFound + 1

    os.chdir("..")


#****************************************************************************************************
#****************************************************************************************************


def generate_random_chars(start, end):
    for x in range(start, end):
        filename = "Test" + str(x) + ".txt"
        currentFile = open("./tests/" + filename, "w+")

        for y in range(0, random.randint(0, 100)):
            currentFile.write(random.choice(string.printable))

        currentFile.close()


def generate_valid_ints(start, end):
    for x in range(start, end):
        filename = "Test" + str(x) + ".txt"
        currentFile = open("./tests/" + filename, "w+")
        valueList = [];

        for y in range(0, 6):
            valueList.append(random.randint(0, 100))

        print_points_to_file(currentFile, valueList)

        currentFile.close()


def generate_squares(start, end):
    for x in range(start, end):
        filename = "Test" + str(x) + ".txt"
        currentFile = open("./tests/" + filename, "w+")

        scaler = random.randint(1, 100)
        valueList = [scaler, 0, scaler, scaler, 0, scaler];

        print_points_to_file(currentFile, valueList)

        currentFile.close()


def generate_rectangles(start, end):
    for x in range(start, end):
        filename = "Test" + str(x) + ".txt"
        currentFile = open("./tests/" + filename, "w+")

        xScaler = random.randint(1, 100)
        yScaler = random.randint(1, 100)

        while xScaler == yScaler:
            xScaler = random.randint(1, 100)

        valueList = [xScaler, 0, xScaler, yScaler, 0, yScaler];

        print_points_to_file(currentFile, valueList)

        currentFile.close()


def generate_parallelograms(start, end):
    for x in range(start, end):
        filename = "Test" + str(x) + ".txt"
        currentFile = open("./tests/" + filename, "w+")

        xStart = random.randint(1, 50)
        yStart = random.randint(1, 50)
        yShift = random.randint(1, 50)
        valueList = [xStart, yStart, xStart, yStart + yShift, 0, yShift];

        print_points_to_file(currentFile, valueList)

        currentFile.close()


def generate_trapezoids(start, end):
    for x in range(start, end):
        filename = "Test" + str(x) + ".txt"
        currentFile = open("./tests/" + filename, "w+")

        yShift = random.randint(1, 100)
        xBottom = random.randint(1, 100)
        xTopRight = random.randint(51, 100)
        xTopLeft = random.randint(1, 50)

        while xTopRight - xTopLeft == xBottom:
            xTopRight = random.randint(51, 100)

        valueList = [xBottom, 0, xTopRight, yShift, xTopLeft, yShift];

        print_points_to_file(currentFile, valueList)

        currentFile.close()

# Highly redundant...
def generate_rhombi(start, end):
    for x in range(start, end):
        filename = "Test" + str(x) + ".txt"
        currentFile = open("./tests/" + filename, "w+")

        value1 = 0;
        while True:
            value1 = random.randint(3, 10)
            if value1 % 2 == 1:
                break
        value2 = value1 * value1 / 2;
        hypotenuse = value1 * value1 / 2 + 1;

        valueList = [value1, value2, value1, value2 + hypotenuse, 0, hypotenuse];

        print_points_to_file(currentFile, valueList)

        currentFile.close()


def generate_kites(start, end):
    for x in range(start, end):
        filename = "Test" + str(x) + ".txt"
        currentFile = open("./tests/" + filename, "w+")

        scaler = random.randint(1, 50)
        shift = random.randint(1, 50);
        valueList = [scaler, 0, scaler + shift, scaler + shift, 0, scaler];

        print_points_to_file(currentFile, valueList)

        currentFile.close()


#****************************************************************************************************
#****************************************************************************************************


errorFound = 0

os.system("mkdir tests")
clean_old_files()

generate_random_chars(1, 2001)
generate_valid_ints(2001, 4001)
generate_squares(4001, 5001)
generate_rectangles(5001, 6001)
generate_parallelograms(6001, 7001)
generate_trapezoids(7001, 8001)
generate_rhombi(8001, 9001)
generate_kites(9001, 10001)

compare_file_results()

print("Errors Found: " + str(errorFound))
