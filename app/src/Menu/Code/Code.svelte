<script>
  import { NotificationDisplay, notifier } from "@beyonk/svelte-notifications";
  import { createEventDispatcher } from "svelte";
  const dispatch = createEventDispatcher();
  const { dialog } = require("electron").remote;
  const path = require("path");
  const fs = require("fs");

  let n = 0;
  let folder_name = "skeleton_code";
  let full_code = [
    ["", ""],
    ["", ""],
    ["", ""],
    ["", ""],
    ["", ""],
  ];

  function exit() {
    dispatch("menu_index", 0);
  }

  function add_line() {
    full_code = [...full_code, ["", ""]];
  }

  function remove_line() {
    let buff;
    if (full_code.length != 1) {
      full_code.pop();
      buff = full_code.pop();
      full_code = [...full_code, buff];
    }
  }
  function save() {
    for (let i = 0; i < full_code.length; i++) {
      for (let j = 0; j < full_code.length; j++) {
        if (full_code[i][0] === full_code[j][0] && i !== j) {
          bad_input = true;
          notifier.danger(
            "Duplicate input at line " + (i + 1) + " and " + (j + 1),
            4000
          );
          return;
        }
      }
    }

    dialog
      .showOpenDialog({
        properties: ["openFile", "openDirectory"],
      })
      .then((result) => {
        if (!result.canceled) {
          let folder_path = path.join(result.filePaths[0], folder_name);
          if (fs.existsSync(folder_path)) {
            create_file(folder_path, code_to_data(full_code));
          } else {
            fs.mkdir(folder_path, (err) => {
              if (err) {
                notifier.danger(err, 4000);
                return console.error(err);
              }
              create_file(folder_path, code_to_data(full_code));
            });
          }
        }
      })
      .catch((err) => {
        notifier.danger(err, 4000);
      });
  }

  function create_file(path, data) {
    fs.appendFile(
      path + "\\" + folder_name + ".ino",
      data,
      { flag: "w+" },
      function (err) {
        if (err) {
          notifier.danger(err, 4000);
          return console.log(err);
        }
        notifier.success("File are create (" + folder_name + ".ino)");
      }
    );
  }

  function code_to_data(code) {
    return (
      `#include <ESP8266WiFi.h>                               //| Include the Wi-Fi library
                                                      // |
                                                     //  |
const char* SSID     = "Julius Caesar";             //   |The SSID (name) of the Wi-Fi network you want to connect to
const char* PASSWORD = "12345678e";                //    |The password of the Wi-Fi network
const int   PORT     = 8500;                      //     |
bool blinked = true;                             //      |
WiFiServer wifiServer(PORT);                    //       |Set listen port to 8500

void wait_msg(int time){
  delay(1000);
  Serial.print(".");
}

void blink_led(){
  if(blinked){
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN, LOW); 
  }
  blinked = !blinked;
}

void connect_msg(IPAddress ip, int port){
  Serial.print("\n");
  Serial.print("Connected to WiFi on IP : ");
  Serial.println(ip);
  Serial.print("Listen on port : ");
  Serial.print(PORT);
}

char* commend_msg(String msg)
{
  Serial.println("accept from user :\""+msg+"\"");
  blink_led(); 
` +
      create_api(code) +
      `
  return "error-v1-unknown-command";
}

void setup() {
 
  Serial.begin(115200); 
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting..");
  pinMode(LED_BUILTIN, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    wait_msg(1000);
  }
  
  connect_msg(WiFi.localIP(),PORT);
  wifiServer.begin();
}
 
void loop() {
  WiFiClient client = wifiServer.available();
  String buff = "";
  if (client) 
  {
    while(client.connected()>0)
    {
      while(client.available()>0)
      {
        buff = buff + char(client.read());
      }
      if(buff != "")
      {
        client.print(commend_msg(buff));
        client.stop();
        buff = "";
      }
    }
  }
}   
  `
    );
  }
  function create_api(code) {
    let buffer = "";

    for (let i = 0; i < code.length; i++) {
      buffer +=
        '\tif(msg.equals("' +
        code[i][0] +
        '"))\n\t{\n\t\treturn "' +
        code[i][1] +
        '";\n\t}\n';
    }

    return buffer;
  }
</script>

<NotificationDisplay bind:this={n} />
<div class="grid-container">
  <div class="return main-title-panel" on:click={exit}>Return</div>
  <div class="save main-title-panel" on:click={save}>Save</div>
  <div class="title main-title-panel">Skeleton code generator</div>
  <div class="liners main-title-panel">
    <span style="cursor: context-menu;">{full_code.length}</span>
    <span on:click={add_line}>+</span>
    <span on:click={remove_line}>-</span>
  </div>
  <div class="code-area">
    <table>
      <table style="width: 100%;">
        <tbody>
          <tr class="data-labal">
            <td class="line-num-title line-title">line numer</td>
            <td class="for line-title">For</td>
            <td class="run line-title">Return</td>
          </tr>
          {#each full_code as line, i}
            <tr>
              <td class="line-num">{i + 1}</td>
              <td class="for">
                <input type="text" bind:value={full_code[i][0]} />
              </td>
              <td class="run">
                <input type="text" bind:value={full_code[i][1]} />
              </td>
            </tr>
          {/each}
        </tbody>
      </table>
    </table>
  </div>
</div>

<style>
  .grid-container {
    display: grid;
    grid-template-columns: 1fr 1fr 1fr 1fr;
    grid-template-rows: 0.7fr 1fr 1fr 1fr 1fr 1fr 0.5fr;
    gap: 0px 0px;
    grid-template-areas:
      "return title title liners"
      "code-area code-area code-area code-area"
      "code-area code-area code-area code-area"
      "code-area code-area code-area code-area"
      "code-area code-area code-area code-area"
      "code-area code-area code-area code-area"
      "save save save save";
    height: 100vh;
    transition: 0.3s;
  }
  .return {
    grid-area: return;
    font-size: 3vh;
    line-height: 10vh;
    padding: 10px;
    -webkit-app-region: no-drag;
  }
  .return:hover {
    cursor: pointer;
    filter: brightness(1.5);
    font-size: 2.75vh;
  }
  .save {
    grid-area: save;
    font-size: 4vh;
    line-height: 10vh;
    -webkit-app-region: no-drag;
  }
  .save:hover {
    cursor: pointer;
    filter: brightness(1.5);
    font-size: 3vh;
  }
  .title {
    grid-area: title;
    line-height: 10vh;
    font-size: 5vh;
    padding: 10px;
  }
  .code-area {
    grid-area: code-area;
    overflow: auto;
  }
  .liners {
    grid-area: liners;
    padding: 10px;
  }
  .liners span {
    -webkit-app-region: no-drag;
  }
  .liners span:hover {
    cursor: pointer;
    filter: brightness(1.5);
  }
  .line-title {
    font-size: 2.5vh;
    color: #dddddd;
    border: 0.1vh solid #dddddd;
    border-left-style: none;
    background-color: #222831;
  }
  .data-labal {
    height: 7%;
    font-family: "Rubik", sans-serif;
    background-color: #222831;
  }
  table {
    table-layout: fixed;
    height: 100%;
    width: 100%;
  }
  table,
  td,
  td {
    border: 0.1vh solid #222831;
    font-size: 5vh;
    color: #222831;
    border-collapse: collapse;
  }
  table .line-num {
    width: 10%;
    font-family: "Rubik", sans-serif;
    background-color: #f05454;
    color: #dddddd;
  }
  table .line-num-title {
    width: 10%;
    font-family: "Rubik", sans-serif;
    background-color: #222831;
    color: #dddddd;
  }
  table .for {
    width: 25%;
  }
  table .run {
    width: 75%;
  }
  input {
    width: 98%;
    height: 98%;
    background-color: #dddddd;
    border: none;
    font-size: 4vh;
    font-family: "Rubik", sans-serif;
  }
</style>
