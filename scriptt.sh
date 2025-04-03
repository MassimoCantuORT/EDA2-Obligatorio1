GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

ej=0

if [ $# -ne 0 ]; then
    ej=$1
fi

find ./tests/_out/ -type f -name "*.out.txt" -exec rm {} \;
find ./tests/_out/ -type f -name "*.diff.txt" -exec rm {} \;
find ./tests/_out/ -type f -name "order.txt" -exec rm {} \;

./scriptc.sh $ej

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

    mkdir -p "./tests/_out/$base_item"

    for prueba in ./tests/"$base_item"/*.in.txt; do
        
        lines=$(wc -l < $prueba | bc)
        # Remove the directory path and .in.txt extension
        output_name="${prueba##*/}"          # Extract the base name of the file
        output_name="${output_name%.in.txt}" # Remove the .in.txt extension
        
        startTime=$(date "+%s%3N")
        ./"$item" <"$prueba" | unix2dos > "./tests/_out/$base_item/${output_name}.out.txt"
        endTime=$(date "+%s%3N")
        
        hash1=$(sha256sum "./tests/_out/$base_item/${output_name}.out.txt" | awk '{print $1}')
        hash2=$(sha256sum "./tests/$base_item/${output_name}.out.txt" | awk '{print $1}')

        # Compare the hashes
        if [ "$hash1" == "$hash2" ]; then
            totalTime=$(($endTime - $startTime))
            echo -e "${GREEN}Prueba $prueba OK${NC} Took ${totalTime}ms"
            echo -e "$lines, $totalTime" >> "./tests/_out/$base_item/order.txt"
        else
            echo -e "${RED}ERROR: Prueba $prueba${NC}"
            diff "./tests/_out/$base_item/${output_name}.out.txt" "./tests/$base_item/${output_name}.out.txt" > "./tests/_out/$base_item/${output_name}.diff.txt"
        fi
    done
done