# Use Wokwi in VSCode (local)

This page explains how to use Wokwi inside [Visual Studio Code](https://code.visualstudio.com/). 

## Why do you want to use Wokwi inside VS Code?

When using Wokwi in the browser you may have noticed some delays when compiling the project.

<img src="images/compiling_delay.png" width="60%"/>

This is because everytime a user press the *Start simulation* button, the code has to be, first compiled (the user sends a compilation request when pressing the button), and then simulated. Compiling code takes some time (especially for large codes or when using several libraries). Hence, the compilation request gets queued and waits to be attended by the Wokwi server to get the compilation done. If the server is very busy (i.e., many requests with high amounts of code occurring at the same time), your compilation request may be queued for long time even though your code takes very short time to be compiled, and you experience high delays.

If you use Wokwi in VS Code, you'll still use Wokwi server to simulate your code (i.e., you need internet connection as the simulation won't run in your local machine), but you'll compile your code in your local machine and tell Wokwi where are the binaries to be used for the simulation. This way you'll skip the main reason of the delays: the compilation request queue.

## Installation

You have to do the following:

1. Install VS Code:
    - You can download it from [here](https://code.visualstudio.com/download).
2. Install the Wokwi for VS Code extension:
    - You can install it directly from the *Extensions* panel inside VS Code (recommended).

    <img src="images/wokwi_extension.svg" width="100%"/>
    
    - You can also install it from [here](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode).

3. Install the Arduino Community Edition for VS Code extension:

    <img src="images/arduino_extension.svg" width="100%"/>

## Wokwi license

Wokwi is free, but to use it locally in your machine you need a licence. If you don't want (or can't) pay for it, you can use the 30-days free license. Don't worry, after these 30 days you can update the free license again 

## Create your Wokwi project in VS Code

As you may already know, when using Wokwi in the browser you need, at least, two files. These files are `sketch.ino` and the `diagram.json`. To use Wokwi in VS Code you'll need some more files. 

1. First, create your project in your local computer. You can do this by hand or you can [download a template here](other/template_wokwi.zip). If you download that template, you need to unzip it.

2. Open your project from VS Code

    <img src="images/open_folder.svg" width="70%"/>

3. Once the project is open, you should see the following:

    <img src="images/project.png" width="60%"/>

    - **build**: This is an empty folder at this moment. Here is where the binaries will be storage when you compile your code.
    - **diagram.json**: This is the same `diagram.json` as the one in the browser version. I.e., the definition of the system components and connections.

        !!! tip
            The best way to edit this file is to use thw GUI in the browser. I.e., create your diagram in the browser version, copy the code inside the `diagram.json` and then go to your local project and paste it there. This is because you don't have the GUI in VS Code (you can only edit the text).
        
        !!! note
            It might happen that if you double-click this file aiming at editing it, you'll see the diagram instead of the code. If you press with the right-click on top of the file name and click on *Open with* and then *Text editor* you'll be able to see the code.

    - **template_wokwi.ino**: This is the same as the `sketch.ino` in the browser. I.e., your arduino code.
    - **wokwi.toml**: This file contains the path of the binary files that wokwi needs to start the simulation. I.e., where the binaries after the compilation will go. If you open this file you will see the following:

        ```toml
        [wokwi]
        version = 1
        firmware='build/template_wokwi.ino.bin'
        elf='build/template_wokwi.ino.elf'
        ```
    
    !!! warning
        - As you may notice, this project is called `template_wokwi`. It is critical that the name of the project is the same as the name of the `.ino` file, and the one inside the `toml` file. 
        - Hence, if your project is called `project_test`, then you should have the following:

        ```txt
        project_test
            |
            |── build
            |── diagram.json
            |── project_test.ino
            └── wokwi.toml
        ```

        - And inside the `.toml` you should have:

         ```toml
        [wokwi]
        version = 1
        firmware='build/project_test.ino.bin'
        elf='build/project_test.ino.elf'
        ``` 

## 

## 

You can find an updated guide [here](https://docs.Wokwi.com/vscode/getting-started).
