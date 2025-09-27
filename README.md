# drinkDB


export DISPLAY=$(grep -m1 nameserver /etc/resolv.conf | awk '{print $2}'):0
export LIBGL_ALWAYS_INDIRECT=1