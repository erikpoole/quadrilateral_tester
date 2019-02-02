import os
import glob
import random

for x in range(1, 101):
    filename = "Test" + str(x) + ".txt"
    file = open("./tests/" + filename, "w+")

    for y in range (0, 5):
        file.write(str(random.randint(0, 101)))
        file.write(" ")
    file.write(str(random.randint(0, 101)))

os.chdir("..")
os.system("clang++ -std=c++17 -fprofile-instr-generate -fcoverage-mapping main.cpp -o coverage")
os.system("rm -f *.profdata")
os.system("rm -f *.profraw")


os.chdir("./randomTesting/tests")
os.system("rm -f *.profdata")
os.system("rm -f *.profdata")
os.chdir("../..")

os.system("touch randomOutput.profdata")
testSet = glob.glob("./randomTesting/tests/*txt")

for test in testSet:
    subStringTest = test[:-4]
    os.system("./coverage < " + subStringTest + ".txt > ./output.txt")
    os.system("llvm-profdata merge -sparse ./randomOutput.profdata ./default.profraw -o ./randomOutput.profdata")


os.system("llvm-cov show ./coverage -instr-profile=./randomOutput.profdata")