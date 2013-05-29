
LIBS="/home/elesd/Documents/programing2/c++/libraries"
SCRIPTS="/home/elesd/Documents/programing2/c++/scripts"
TARGET_DIR=$1

echo -e "Copy Exceptions"
mkdir "$TARGET_DIR/Exceptions"
cp -r "$LIBS/Exceptions/" "$TARGET_DIR/Exceptions/"

echo -e "Copy StringUtil"
mkdir "$TARGET_DIR/StringUtil"
cp -r "$LIBS/StringUtil/" "$TARGET_DIR/StringUtil/"

echo -e "Copy Tester"
mkdir "$TARGET_DIR/Tester"
cp -r "$LIBS/Tester/" "$TARGET_DIR/Tester/"

mkdir "$TARGET_DIR/MATH"
mkdir "$TARGET_DIR/MATH/projects"

echo -e "Copy MATH::Algebra"
mkdir "$TARGET_DIR/MATH/projects/Algebra"
cp -r "$LIBS/MATH/projects/Algebra" "$TARGET_DIR/MATH/projects/Algebra"

echo -e "Copy MATH::Graphs"
mkdir "$TARGET_DIR/MATH/projects/Graphs"
cp -r "$LIBS/MATH/projects/Graphs" "$TARGET_DIR/MATH/projects/Graphs"

echo -e "Copy MATH::LinearAlgebra"
mkdir "$TARGET_DIR/MATH/projects/LinearAlgebra"
cp -r "$LIBS/MATH/projects/LinearAlgebra" "$TARGET_DIR/MATH/projects/LinearAlgebra"

echo -e "Copy MATH::NumberSystem"
mkdir "$TARGET_DIR/MATH/projects/NumberSystem"
cp -r "$LIBS/MATH/projects/NumberSystem" "$TARGET_DIR/MATH/projects/NumberSystem"

echo -e "Copy install scripts"
cp "$SCRIPTS/builder.sh" "$TARGET_DIR/"
cp "$SCRIPTS/install.sh" "$TARGET_DIR/"
cp "$SCRIPTS/install" "$TARGET_DIR/"
cp "$SCRIPTS/setBaseDir.pl" "$TARGET_DIR/"

cd $TARGET_DIR 
builder.sh -clean
cd -

