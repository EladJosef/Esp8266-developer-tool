<script>
  import { getNotificationsContext } from "svelte-notifications";
  const { addNotification } = getNotificationsContext();
  import { createEventDispatcher } from "svelte";
  const dispatch = createEventDispatcher();
  const { dialog } = require("electron").remote;
  const path = require("path");
  const fs = require("fs");

  let folder_name = "skeleton_code";
  let wifi_password = "None";
  let ssid = "None";
  let run_port = 8500;
  let settings_has_clicked = false;

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
          return input_error(
            "Duplicate input at line " + (i + 1) + " and " + (j + 1)
          );
        }
      }
    }

    if (!set_settings()) {
      return;
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
                return input_error(err);
              }
              create_file(folder_path, code_to_data(full_code));
            });
          }
        }
      })
      .catch((err) => {
        return input_error(err);
      });
  }

  function create_file(path, data) {
    fs.appendFile(
      path + "\\" + folder_name + ".ino",
      data,
      { flag: "w+" },
      function (err) {
        if (err) {
          return input_error(err);
        }
        addNotification({
          text: "File was create successfully (" + folder_name + ".ino)",
          position: "bottom-right",
          removeAfter: 4000,
          type: "success",
        });
      }
    );
  }

  function code_to_data(code) {
    return (
      `#include <ESP8266WiFi.h>                               //|Include the Wi-Fi library
                                                       //|
                                                       //|
const char* SSID     = \"` +
      ssid +
      `\";                //|The SSID (name) of the Wi-Fi network you want to connect to
const char* PASSWORD = \"` +
      wifi_password +
      `\";                    //|The password of the Wi-Fi network
const int   PORT     = ` +
      run_port +
      `;                           //|
WiFiServer wifiServer(PORT);                           //|Set listen port to 8500

void connect_msg(IPAddress ip, int port){
  // print all connecting info
  Serial.println("");
  Serial.print("Connected to WiFi on IP : ");
  Serial.println(ip);
  Serial.print("Listen on port : ");
  Serial.println(PORT);
}

char* commend_msg(String msg)
{
  // The program API
  Serial.println("accept from user :\""+msg+"\"");
  ` +
      create_api(code) +
      `
  return "error-v1-unknown-command";
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD); // Connecting wifi
  Serial.print("Connecting..");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  
  connect_msg(WiFi.localIP(),PORT); // Print connect data
  wifiServer.begin();
}

void loop() {
  WiFiClient client = wifiServer.available();
  String buff = ""; // creating buffer for messages
  if (client)
  {
    while(client.connected()>0)
    {
      while(client.available()>0)
      {
        buff = buff + char(client.read()); // Read msg
      }
      if(buff != "")
      {
        client.print(commend_msg(buff)); // Send API result to client
        client.stop(); // End connection
        buff = "";
      }
    }
  }
}`
    );
  }
  function create_api(code) {
    let buffer = "";
    code = [...code, ["on?", "yes"]];

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

  function set_settings() {
    if (!(ssid.length > 0)) {
      return input_error("No SSID was input");
    }
    if (!(wifi_password.length > 0)) {
      return input_error("No WiFi password was input");
    }
    if (!(String(run_port).length > 0)) {
      return input_error("No Port was input");
    }
    if (!isNumeric(run_port)) {
      return input_error("Port need to be a number");
    }
    if (run_port > 65535 || run_port < 1) {
      return input_error("Port need to be in the range 1-65535");
    }
    if (!folder_name.length > 0) {
      return input_error("No File name was input");
    }
    return true;
  }

  function input_error(input) {
    addNotification({
      text: input,
      position: "bottom-right",
      removeAfter: 4000,
      type: "danger",
    });
    return false;
  }

  function isNumeric(str) {
    if (typeof str != "string") return false;
    return !isNaN(str) && !isNaN(parseFloat(str));
  }
</script>

<div class="grid-container">
  <div class="return main-title-panel" on:click={exit}>Return</div>
  <div class="save main-title-panel" on:click={save}>Save</div>
  <div class="title main-title-panel">Skeleton code generator</div>
  <div class="liners main-title-panel">
    <span style="cursor: context-menu;">{full_code.length}</span>
    <span style="cursor: context-menu;">|</span>
    <span on:click={add_line}>+</span>
    <span on:click={remove_line}>-</span>
    <span style="cursor: context-menu;">|</span>
    <span style="padding-right:4vh">&nbsp;</span>
    <img
      class="settings"
      on:click={() => (settings_has_clicked = !settings_has_clicked)}
      src={!settings_has_clicked ? "./icon-settings.svg" : "./icon-code.png"}
      alt=""
    />
  </div>
  <div class="code-area">
    {#if settings_has_clicked}
      <table>
        <tbody>
          <tr>
            <td class="settings_titel">Properties</td>
            <td class="settings_titel">Values</td>
          </tr>
          <tr>
            <td class="properties">SSID </td>
            <td><input type="text" bind:value={ssid} /> </td>
          </tr>
          <tr>
            <td class="properties">WiFi password </td>
            <td><input type="text" bind:value={wifi_password} /> </td>
          </tr>
          <tr>
            <td class="properties">Port </td>
            <td><input type="text" bind:value={run_port} /> </td>
          </tr>
          <tr>
            <td class="properties">File name </td>
            <td><input type="text" bind:value={folder_name} /> </td>
          </tr>
        </tbody>
      </table>
    {:else}
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
    {/if}
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
    color: var(--secondary-color);
    border: 0.1vh solid var(--secondary-color);
    border-left-style: none;
    background-color: var(--main-color);
  }
  .data-labal {
    height: 7%;
    font-family: "Rubik", sans-serif;
    background-color: var(--main-color);
  }
  table {
    table-layout: fixed;
    height: 100%;
    width: 100%;
  }
  table,
  td,
  td {
    border: 0.1vh solid var(--main-color);
    font-size: 5vh;
    color: var(--main-color);
    border-collapse: collapse;
  }
  table .line-num {
    width: 10%;
    font-family: "Rubik", sans-serif;
    background-color: var(--highlight-color);
    color: var(--secondary-color);
  }
  table .line-num-title {
    width: 10%;
    font-family: "Rubik", sans-serif;
    background-color: var(--main-color);
    color: var(--secondary-color);
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
    background-color: var(--secondary-color);
    border: none;
    font-size: 4vh;
    font-family: "Rubik", sans-serif;
    color: var(--thumb-hover-color);
  }
  img {
    width: 5vh;
    position: absolute;
    filter: invert(100%);
    margin-top: 2.5vh;
    margin-left: -3.75vw;
  }
  .settings {
    -webkit-transition: -webkit-transform 0.8s ease-in-out;
    transition: transform 0.8s ease-in-out;
    text-align: center;
    display: inline;
  }
  .settings:hover {
    -webkit-transform: rotate(90deg);
    transform: rotate(90deg);
    cursor: pointer;
  }
  .settings_titel {
    background: var(--main-color);
    color: var(--blank-color);
    font-family: "Rubik", sans-serif;
  }
  .properties {
    font-family: "Poppins", sans-serif;
    text-align: left;
    padding-left: 2vh;
  }
</style>
