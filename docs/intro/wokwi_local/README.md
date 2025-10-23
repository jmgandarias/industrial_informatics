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

You can find an updated guide [here](https://docs.Wokwi.com/vscode/getting-started).
