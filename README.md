## This repo is no longer maintained

Windows 7 and DirectX 12 is unsupported. This tool works without the randomizer mod, but is also compatible and will use it to add items if it's installed. If for whatever reason it doesn't work, make sure your game is in English and up to date.

# hitman2ge 

A simple C++ tool for changing your starting gear in Hitman 2. I tried to keep the code clean and well documented, for people who would like to learn a bit about internal modding/hacking stuff. 

You can find the release builds [here](https://github.com/dom-ve/hitman2ge/releases). 
Only game version 2.71.0+ is officially supported.

![](https://i.imgur.com/urqrLfW.png)
## Usage
 1. Extract the archive you downloaded.
 2. Open Hitman 2 (make sure you are not using DirectX12 or Exclusive Fullscreen)
 3. Run the injector.exe bundled with the tool, or use your own DLL injector and load tool.dll into HITMAN2.exe
 4. Press insert to open the menu, enable the mod and select the items you want
 5. Start / restart a mission, and you will now start with your items!

## Building 
The project was made using VS2019, only this is supported by default.
Make sure you install all the necessary NuGet packages in Visual Studio before compiling (rapidjson and MinHook). 
To get a command line and debug messages, compile as Debug.

## Credits
hitman2ge uses the following tools/libraries:
 - [MinHook](https://github.com/TsudaKageyu/minhook)
 - [rapidjson](https://github.com/Tencent/rapidjson)
 - [universal-graphics-hook](https://github.com/alxbrn/universal-graphics-hook/)
 - [imgui](https://github.com/ocornut/imgui)

and also thanks to pawREP for a method of swapping items in [ZHM5Randomizer](https://github.com/pawREP/ZHM5Randomizer)! (*which is now also compatible with my mod*)
