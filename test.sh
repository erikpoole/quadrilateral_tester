# Shape Classification
./ShapeFinder < input0.txt > output.txt
diff key0.txt output.txt
if [ $? -eq 0 ]; then
    echo "No Errors!"
else
    echo "Errors Found in Shape Classification!"
    exit 1
fi

# Error 1 - Input Value Too High
./ShapeFinder < input1.txt > output.txt
diff key1.txt output.txt
if [ $? -eq 0 ]; then
    echo "No Errors!"
else
    echo "Errors Found - Input Value Too High!"
    exit 1
fi

# Error 1 - Leading Spaces
./ShapeFinder < input2.txt > output.txt
diff key2.txt output.txt
if [ $? -eq 0 ]; then
echo "No Errors!"
else
echo "Errors Found - Leading Spaces!"
exit 1
fi

# Error 1 - Ending Spaces
./ShapeFinder < input3.txt > output.txt
diff key3.txt output.txt
if [ $? -eq 0 ]; then
echo "No Errors!"
else
echo "Errors Found - Ending Spaces!"
exit 1
fi

# Error 1 - Middle Whitespaces
./ShapeFinder < input4.txt > output.txt
diff key4.txt output.txt
if [ $? -eq 0 ]; then
echo "No Errors!"
else
echo "Errors Found - Middle Whitespace!"
exit 1
fi

# Error 1 - Invalid Character
./ShapeFinder < input5.txt > output.txt
diff key5.txt output.txt
if [ $? -eq 0 ]; then
echo "No Errors!"
else
echo "Errors Found - Invalid Character!"
exit 1
fi

# Error 1 - Too Few Inputs
./ShapeFinder < input6.txt > output.txt
diff key6.txt output.txt
if [ $? -eq 0 ]; then
echo "No Errors!"
else
echo "Errors Found - Too Few Inputs!"
exit 1
fi


# Error 1 - Too Many Inputs
./ShapeFinder < input7.txt > output.txt
diff key7.txt output.txt
if [ $? -eq 0 ]; then
echo "No Errors!"
else
echo "Errors Found - Too Many Inputs!"
exit 1
fi

exit 0
