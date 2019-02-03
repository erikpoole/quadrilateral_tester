import os
import glob
import random

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
    os.chdir("..")

    testSet = glob.glob("./randomTesting/tests/*txt")

    for test in testSet:
        print(test[22:-4])
        os.system("./ShapeFinder < " + test)

    os.chdir("./randomTesting")

clean_old_files()

for x in range(1, 101):
    filename = "Test" + str(x) + ".txt"
    file = open("./tests/" + filename, "w+")

    for y in range (0, 5):
        file.write(str(random.randint(0, 101)))
        file.write(" ")
    file.write(str(random.randint(0, 101)))

run_tests()
create_coverage()