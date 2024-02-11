cd wcat/
echo "Test wcat:"
./test-wcat.sh $*
cd ../wgrep/
echo "Test wgrep:"
./test-wgrep.sh $*
cd ../wunzip/
echo "Test wunzip:"
./test-wunzip.sh $*
cd ../wzip/
echo "Test wzip:"
./test-wzip.sh $*
