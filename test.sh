
./ShapeFinder < input.txt > output.txt
diff key.txt output.txt
if [ $? -eq 0 ]; then
    echo "No Errors!"
    exit 0
else
    echo "Errors Found!"
    exit 1
fi
