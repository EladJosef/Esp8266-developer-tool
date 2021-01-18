# Esp8266-debugger
debugger for Esp8266 module

# install
Go to `/app/` dir, open terminal and run with npm
```node
npm i
npm start
```
compile the code from `/Esp8266/` dir and upload it to your Esp8266, I recommend using the `Arduino IDE` to compile and upload

# usage

## connect

Enter your local Esp8266 address (IP: port)

<img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/master/img/connect.png" width="250">

You can use the keyboard Numpad and arrows to input the address.

## how to use
You have 7 functions on the debug panel:
- send: send a string to the esp8266 and print result
- auto scroll: scroll automatically to the end of the log 
- edit macros: give you the option to edit macros 
- macro one: macro is a const string that you can reuse instead of retyping every time 
- macro two: same 
- macro three: same 
- macro four: same 
- logfile : save the log file of your esp8266 communication 
- exit : disconnect esp8266


<img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/master/img/Control.png" width="250">
<img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/master/img/edit-macro.png" width="250">

now you can use the control panel to test your esp8266

# todo
- [ ] connect functions to send function
- [ ] upload hotfix to esp8266 code
