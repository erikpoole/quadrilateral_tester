
./ShapeFinder < input.txt > output.txt
diff key.txt output.txt
if [ $? -eq 0 ]; then
    echo "No Errors!"
else
    echo "Errors Found!"
fi
