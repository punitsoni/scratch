#!/bin/sh

MOD_NAME=h_uio

pr_err_exit() {
    echo "$1 failed" >&2;
    exit 1;
}

insmod $MOD_NAME.ko

if [ $? -ne 0 ]; then
    pr_err_exit insmod;
fi

rmmod $MOD_NAME

echo "DONE."
