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


def create_coverage():
    os.chdir("..")
    os.system("clang++ -std=c++17 -fprofile-instr-generate -fcoverage-mapping main.cpp -o coverage")
    os.system("touch fuzzOutput.profdata")
    test_set = glob.glob("./randomTesting/tests/*txt")

    for test in test_set:
        sub_string_test = test[:-4]
        os.system("./coverage < " + sub_string_test + ".txt > ./output.txt")
        os.system("llvm-profdata merge -sparse ./default.profraw -o ./" + sub_string_test + ".profdata")

    prof_data_set = glob.glob("./randomTesting/tests/*profdata")
    combined_prof_data_string = " ".join(prof_data_set)

    os.system("llvm-profdata merge -sparse " + combined_prof_data_string + " -o ./randomOutput.profdata")
    os.system("llvm-cov show ./coverage -instr-profile=./randomOutput.profdata > coverage.txt")

    os.chdir("./randomTesting")


def run_tests(input_set, input_type, start, end):
    os.chdir("./tests")

    for x in range(start, end):
        os.system("../../ShapeFinder < " + input_set[x] + "> output.txt")
        keyFile = open("key.txt", "w+")
        keyFile.write(input_type + "\n")
        keyFile.close()

        if not filecmp.cmp("key.txt", "output.txt", shallow=False):
            print(input_set[x][:-4] + " Error")

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

        scaler = random.randint(1, 51)
        shift = random.randint(1, 51);
        valueList = [scaler, 0, scaler + shift, scaler + shift, 0, scaler];

        print_points_to_file(currentFile, valueList)

        currentFile.close()


#****************************************************************************************************
#****************************************************************************************************

clean_old_files()

generate_random_chars(1, 101)
generate_valid_ints(101, 201)
generate_squares(201, 301)
generate_rectangles(301, 401)
generate_parallelograms(401, 501)
generate_trapezoids(501, 601)
generate_rhombi(601, 701)
generate_kites(701, 801)

os.chdir("./tests")
test_set = glob.glob("*txt")
sorted_tests = sorted(test_set, key=lambda name: int(name[4:-4]))
os.chdir("..")

run_tests(sorted_tests, "", 0, 100)
run_tests(sorted_tests, "", 100, 200)
run_tests(sorted_tests, "square", 200, 300)
run_tests(sorted_tests, "rectangle", 300, 400)
run_tests(sorted_tests, "parallelogram", 400, 500)
run_tests(sorted_tests, "trapezoid", 500, 600)
run_tests(sorted_tests, "rhombus", 600, 700)
run_tests(sorted_tests, "kite", 700, 800)

create_coverage()
