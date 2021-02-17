<img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/314465702463d86e7e67cb41d26b78e2950b80eb/img/banner.svg" width="1000">

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


You can use the keyboard Numpad and arrows to input the address.

## how to use
You have 7 functions on the debug panel:
- send: send a string to the esp8266 and print result
- auto scroll: scroll automatically to the end of the log 
- edit macros: give you the option to edit macros 
- five macros buttons: macro is a const string that you can reuse instead of retyping every time 
- clear : clear dialogue from screen
- logfile : save the log file of your esp8266 communication 
- exit : disconnect esp8266

You have 2 functions on the log explorerr after open log-file:
- show: Show all log data
- auto scroll: Show the log statistics 

<p float="left">
  <kbd>
  <img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/master/img/connect.png" width="180">
  </kbd>
  <kbd>
  <img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/master/img/Control.png" width="180">
  </kbd>
  <kbd>
  <img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/master/img/edit-macro.png" width="180">
  </kbd>
  <kbd>
  <img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/master/img/log.png" width="180">
  </kbd>
</p>


now you can use the control panel to test your esp8266

## What's new in 1.2.1v ?
- [X] Logfile viewer
- [X] Logfile view option
- [X] Logfile statistics option
- [X] Menu css improvment
- [X] logfile improvment (time and statistics)



