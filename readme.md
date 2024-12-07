first run
`docker build buildenv -t solis_os`

powershell `docker run --rm -it -v "${pwd}:/root/env solis_os"`
to enter the docker shell thing

in there run make clean -i first and then run make build.

in another enviroment/shell use `qemu-system-x86_64 -cdrom ./bin/x86_64/iso/boot.iso"`
and this should start. if it doesnt add an additional  -L "C:\Program Files\qemu to the
end of the previus command