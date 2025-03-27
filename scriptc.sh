GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

ej=0

if [ $# -ne 0 ]; then
    ej=$1
fi

find ./compilado/ -type f -name "*.exe" -exec rm {} \;

# Compile all .cpp files into executables
mkdir -p compilado # Ensure the directory exists
for item in *.cpp; do
    if [[ ej -eq 0 ]] || [[ "$item" =~ ^ejercicio"$ej"\.cpp$ ]]; then
        printf "Compilando %s\n" "$item"
        g++ -o "./compilado/${item%.cpp}.exe" "$item" -std=c++11
    fi
done
