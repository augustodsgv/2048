echo " * Building program * "
if ! [ -d "table_library" ]; then
    echo "Downloading table library..."
    git clone https://github.com/augustodsgv/table_library.git
fi

echo "compiling..."
gcc -g3 2048.c main.c table_library/table.c -o main -lm

echo "Opening debug..."
gdb ./main