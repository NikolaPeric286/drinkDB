# drinkDB


windows compilation instructions

git clone https://github.com/NikolaPeric286/drinkDB
cd drinkDB
git submodule update --init --recursive
cd build
cmake .. -G Ninja
ninja 


Linux
export DISPLAY=$(grep -m1 nameserver /etc/resolv.conf | awk '{print $2}'):0
export LIBGL_ALWAYS_INDIRECT=1