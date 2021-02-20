<img src="https://raw.githubusercontent.com/EladJosef/Esp8266-developer-tool/126f1b2abe30ad8c57463810e340db1f2a61f622/img/banner.svg" width="1000">

# Esp8266 Developer Tool

Is a tool that help you develop code for esp8266

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

You have 1 function on the Create skeleton code mode:

- save: create code template with leter input in table
  - for input : used for api
  - retrun: return string for the input that type in "for"
  - settings: used for set ssid, wifi password, port and file name

## Screenshots from the app

<p float="left">
  <kbd>
  <img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/master/img/connect.png" width="180">
  </kbd>
  <kbd>
  <img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/develop/img/menu.png" width="180">
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
  <kbd>
  <img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/develop/img/upload.png" width="180">
  </kbd>
  <kbd>
  <img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/develop/img/stat-log.png" width="180">
  </kbd>
  <kbd>
  <img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/develop/img/data-log.png" width="180">
  </kbd>
  <kbd>
  <img src="https://raw.githubusercontent.com/EladJosef/Esp8266-debugger/develop/img/code.png" width="180">
  </kbd>
  <kbd>
  <img src="https://raw.githubusercontent.com/EladJosef/Esp8266-developer-tool/develop/img/settings.png" width="180">
  </kbd>
</p>

now you can use the control panel to test your esp8266

## What's new in 1.2.4v ?

- [x] Dark mode
- [x] Significant code improvement
- [x] Improving Performance
- [x] Fix bugs 
