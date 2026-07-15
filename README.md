Includes a custom nice_view sheild that replaces the wpm monior with a message

#Setup
Building will be done in docker so all we need to do is add zmk and create modules dir. 
```shell
mkdir modules
cd zmk
git submodule add -b v0.3-branch https://github.com/zmkfirmware/zmk.git zmk
```


We will mount our repo into a docker for development and execution. Docker should be using the Ubuntu WSL distro.
1. `sudo docker volume create --driver local -o o=bind -o type=none   -o device="/mnt/c/code/zmk-config-lily58/config" zmk-config`
2. `sudo docker volume create --driver local -o o=bind -o type=none   -o device="/mnt/c/code/zmk-config-lily58/modules" zmk-modules`
3. go to zmk/.devcontainer/devcontainer.json.
4. Click cube in corner > "Create Dev Container and Mount Sources"
5. Create docker toolchain: https://www.jetbrains.com/help/clion/clion-toolchains-in-docker.html#create-docker-toolchain
6. Open the image in CLion and go to `/workspaces/zmk-config`. It should mirror the `config` folder.
7. `west init -l app/`
8. `west update`

#Building from inside the docker image

copy output files from `zmk-config-lily58\zmk\app\build\zephyr\zmk.uf2`

Commands for zmk 0.3:
```shell
cd app 

# Build dongle- working in zmk 0.3
west build -p -b seeeduino_xiao_ble -- -DSHIELD="settings_reset" -DZMK_CONFIG=/workspaces/zmk-config/
west build -p -b seeeduino_xiao_ble -- -DSHIELD="lily58_dongle" -DZMK_CONFIG=/workspaces/zmk-config/

# build sides- working in zmk 0.3
west build -p -b nice_nano_v2 -- -DSHIELD="settings_reset" -DZMK_CONFIG=/workspaces/zmk-config/
west build -p -b nice_nano_v2 -- -DSHIELD="lily58_left nice_view_adapter nice_view" -DZMK_CONFIG=/workspaces/zmk-config/ -DCONFIG_ZMK_SPLIT=y -DCONFIG_ZMK_SPLIT_ROLE_CENTRAL=n
west build -p -b nice_nano_v2 -- -DSHIELD="lily58_right nice_view_adapter nice_view" -DZMK_CONFIG=/workspaces/zmk-config/ -DCONFIG_ZMK_SPLIT=y -DCONFIG_ZMK_SPLIT_ROLE_CENTRAL=n

# build dongleless- working in zmk 0.3
west build -p -b nice_nano_v2 -S studio-rpc-usb-uart -- -DSHIELD="lily58_left nice_view_adapter nice_view" -DZMK_CONFIG=/workspaces/zmk-config/ -DCONFIG_ZMK_STUDIO=y 
west build -p -b nice_nano_v2 -- -DSHIELD="lily58_right nice_view_adapter nice_view" -DZMK_CONFIG=/workspaces/zmk-config/ 
```