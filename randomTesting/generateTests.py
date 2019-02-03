import os
import glob
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

def create_coverage():
    os.chdir("..")
    os.system("clang++ -std=c++17 -fprofile-instr-generate -fcoverage-mapping main.cpp -o coverage")
    os.system("touch fuzzOutput.profdata")
    testSet = glob.glob("./randomTesting/tests/*txt")

    for test in testSet:
        subStringTest = test[:-4]
        os.system("./coverage < " + subStringTest + ".txt > ./output.txt")
        os.system("llvm-profdata merge -sparse ./default.profraw -o ./" + subStringTest + ".profdata")

    profDataSet = glob.glob("./randomTesting/tests/*profdata")
    combinedProfDataString = " ".join(profDataSet)

    os.system("llvm-profdata merge -sparse " + combinedProfDataString + " -o ./randomOutput.profdata")
    os.system("llvm-cov show ./coverage -instr-profile=./randomOutput.profdata > coverage.txt")

    os.chdir("./randomTesting")

def run_tests():
    os.chdir("./tests")

    testSet = glob.glob("*txt")
    sortedTests = sorted(testSet, key=lambda name: int(name[4:-4]))

    for test in sortedTests:
        print(test[:-4] + ":")
        os.system("../../ShapeFinder < " + test)

    os.chdir("..")

clean_old_files()

#random valid ints
for x in range(1, 101):
    filename = "Test" + str(x) + ".txt"
    file = open("./tests/" + filename, "w+")

    for y in range (0, 5):
        file.write(str(random.randint(0, 100)))
        file.write(" ")
    file.write(str(random.randint(0, 100)))

#random characters
for x in range(101, 201):
    filename = "Test" + str(x) + ".txt"
    file = open("./tests/" + filename, "w+")

    for y in range (0, random.randint(0, 100)):
        file.write(random.choice(string.ascii_letters + string.digits + string.punctuation))

#random squares
for x in range(201, 301):
    filename = "Test" + str(x) + ".txt"
    file = open("./tests/" + filename, "w+")

    scaler = random.randint(1, 100)

    file.write(str(scaler) + " " + str(0))
    file.write(" ")
    file.write(str(scaler) + " " + str(scaler))
    file.write(" ")
    file.write(str(0) + " " + str(scaler))

#random rectangles
for x in range(301, 401):
    filename = "Test" + str(x) + ".txt"
    file = open("./tests/" + filename, "w+")

    xscaler = random.randint(1, 100)
    yscaler = random.randint(1, 100)

    file.write(str(xscaler) + " " + str(0))
    file.write(" ")
    file.write(str(xscaler) + " " + str(yscaler))
    file.write(" ")
    file.write(str(0) + " " + str(yscaler))


run_tests()
create_coverage()