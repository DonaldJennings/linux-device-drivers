cmd_/home/donald/Programming/linux-device-drivers/hello-world/Module.symvers := sed 's/ko$$/o/' /home/donald/Programming/linux-device-drivers/hello-world/modules.order | scripts/mod/modpost -m -a  -o /home/donald/Programming/linux-device-drivers/hello-world/Module.symvers -e -i Module.symvers   -T -
