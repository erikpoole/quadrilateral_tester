#Original code skeleton created by Adam Quintana

#compile
clang++ -std=c++17 -fprofile-instr-generate -fcoverage-mapping main.cpp -o coverage

#remove any previous profdata files
rm -f *.profdata
rm -f *.profraw

#declare tests
tests=(
input0
input1
input2
input3
input4
input5
input6
input7
input8
input9
input10
)

#create the first .profdata
touch input10.profdata
lastTest=input10

#loop through tests and merge each profraw file with the last generated profdata file
for currentTest in "${tests[@]}"
do
#LLVM_PROFILE_FILE=./${lastTest}.profraw
./coverage < ./${currentTest}.txt > ./output.txt
llvm-profdata merge -sparse ./${lastTest}.profdata ./default.profraw -o ./${currentTest}.profdata
lastTest=${currentTest}
done

#show code coverage
xcrun llvm-cov show ./coverage -instr-profile=./${lastTest}.profdata main.cpp

