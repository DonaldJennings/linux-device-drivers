cmd_/home/donald/Programming/linux-device-drivers/hello-world/modules.order := {   echo /home/donald/Programming/linux-device-drivers/hello-world/hello-world.ko; :; } | awk '!x[$$0]++' - > /home/donald/Programming/linux-device-drivers/hello-world/modules.order