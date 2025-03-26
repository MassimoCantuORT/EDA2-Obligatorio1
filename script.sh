GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

ej=0

if [ $# -ne 0 ]; then
    ej=$1
fi

find ./compilado/ -type f -name "*.exe" -exec rm {} \;
find ./tests/_out/ -type f -name "*.out.txt" -exec rm {} \;
find ./tests/_out/ -type f -name "*.diff.txt" -exec rm {} \;

# Compile all .cpp files into executables
mkdir -p compilado # Ensure the directory exists
for item in *.cpp; do
    if [[ ej -eq 0 ]] || [[ "$item" =~ ^ejercicio"$ej"\.cpp$ ]]; then
        printf "Compilando %s\n" "$item"
        g++ -o "./compilado/${item%.cpp}.exe" "$item" -std=c++11
    fi
done


mkdir -p ./tests/_out
# Run each executable with each test input file
for item in ./compilado/*.exe; do
    printf "\n\n"
    base_item="$(basename "${item%.exe}")"

    printf "Ejecutando pruebas de %s:\n" "$base_item"

    # Check if there are any test files for the current executable
    test_files=(./tests/"$base_item"/*.in.txt)
    if [ ! -e "${test_files[0]}" ]; then
        echo "No test files found for $base_item. Skipping..."
        continue
    fi

    for prueba in ./tests/"$base_item"/*.in.txt; do
        startTime=$(date "+%s%3N")
        # Remove the directory path and .in.txt extension
        output_name="${prueba##*/}"          # Extract the base name of the file
        output_name="${output_name%.in.txt}" # Remove the .in.txt extension
        mkdir -p "./tests/_out/$base_item"

        ./"$item" <"$prueba" | dos2unix > "./tests/_out/$base_item/${output_name}.out.txt"
        hash1=$(sha256sum "./tests/_out/$base_item/${output_name}.out.txt" | awk '{print $1}')
        hash2=$(sha256sum "./tests/$base_item/${output_name}.out.txt" | awk '{print $1}')

        # Compare the hashes
        if [ "$hash1" == "$hash2" ]; then
            endTime=$(date "+%s%3N")
            totalTime=$(($endTime - $startTime))
            echo -e "${GREEN}Prueba $prueba OK${NC} Took ${totalTime}ms"
        else
            echo -e "${RED}ERROR: Prueba $prueba${NC}"
            diff "./tests/_out/$base_item/${output_name}.out.txt" "./tests/$base_item/${output_name}.out.txt" > "./tests/_out/$base_item/${output_name}.diff.txt"
        fi
    done
done