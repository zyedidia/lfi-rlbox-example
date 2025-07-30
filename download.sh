set -ex

mkdir -p deps

if [ ! -d deps/lfi-runtime ]; then
    git clone https://github.com/lfi-project/lfi-runtime deps/lfi-runtime
fi

if [ ! -d deps/rlbox ]; then
    git clone https://github.com/PLSysSec/rlbox deps/rlbox
fi

if [ ! -d deps/rlbox_lfi_sandbox ]; then
    git clone https://github.com/PLSysSec/rlbox_lfi_sandbox deps/rlbox_lfi_sandbox
fi
