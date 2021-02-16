<script>
  import { createEventDispatcher } from "svelte";
  export let address;
  let massages = [];
  let temp = "";
  let auto_scroll = true;
  let macros = ["A", "B", "C", "D", "E"];
  let edit_macro = false;

  const dispatch = createEventDispatcher();

  Array.prototype.clear_diracters = function () {
    for (var i = 0; i < this.length; i++) {
      this[i] = this[i][1]
        ? this[i][0] + " => send at " + this[i][2]
        : this[i][0] + " => receive at " + this[i][2];
    }
    console.log(this);
    return this;
  };

  function updateScroll() {
    if (auto_scroll) {
      let element = document.getElementById("chat");
      if (element !== null) {
        element.scrollTop = element.scrollHeight;
      }
    }
  }
  let scroll_auto_int = setInterval(updateScroll, 500);

  function edit_on() {
    edit_macro = !edit_macro;
  }

  function send() {
    if (temp !== "") {
      massages = [...massages, [temp, true, time()]];
      connect(temp);
      temp = "";
      let element = document.getElementById("chat");
      element.scrollTop = element.scrollHeight + 1000;
    }
  }
  function clear() {
    massages = [];
  }
  function handleKeydown(event) {
    if (event.key === "Enter") {
      send();
    }
  }
  function time() {
    var d = new Date();
    var s = d.getSeconds();
    var m = d.getMinutes();
    var h = d.getHours();
    return h + ":" + m + ":" + s;
  }

  function auto_scroll_me() {
    auto_scroll = !auto_scroll;
  }

  function save_log_file() {
    let log = massages.clear_diracters();
    var file = new File([log.join("\n")], {
      type: "text/plain",
    });
    if (window.navigator.msSaveOrOpenBlob)
      window.navigator.msSaveOrOpenBlob(file, "log.txt");
    else {
      var a = document.createElement("a"),
        url = URL.createObjectURL(file);
      a.href = url;
      a.download = "log.txt";
      document.body.appendChild(a);
      a.click();
      setTimeout(function () {
        document.body.removeChild(a);
        window.URL.revokeObjectURL(url);
      }, 0);
    }
  }

  function m1() {
    temp = macros[0];
  }
  function m2() {
    temp = macros[1];
  }
  function m3() {
    temp = macros[2];
  }
  function m4() {
    temp = macros[3];
  }
  function m5() {
    temp = macros[4];
  }

  function exit() {
    clearInterval(scroll_auto_int);
    dispatch("menu_index", 0);
  }

  function accept(data, tcp) {
    var enc = new TextDecoder("utf-8");
    let msg = enc.decode(data["buffer"]);
    massages = [...massages, [msg, false, time()]];
    tcp.destroy();
  }

  function connect(msg) {
    const net = window.require("net");
    const ip = `${address[0]}.${address[1]}.${address[2]}.${address[3]}`;
    const port = Number(address[4]);
    let tcp = new net.Socket();
    tcp.connect(port, ip, function () {
      tcp.write(msg);
    });
    tcp.on("data", (data) => accept(data, tcp));
  }
</script>

<svelte:window on:keydown={handleKeydown} />
<div id="frame">
  <div class="titel">
    <h2>ESP8266 massages debugger</h2>
  </div>
  <div class="seced-titel">
    <h2>control panel</h2>
  </div>
  <div class="macros-panel">
    <table style="width: 100%;" class="fixed panel">
      <tbody>
        <tr>
          <td
            style="background-color:{auto_scroll ? '#4CAF50' : '#30475e'}"
            on:click={auto_scroll_me}>Auto Scroll</td
          >
          <td
            style="background-color:{edit_macro ? '#f05454' : '#30475e'}"
            class="set-macro"
            on:click={edit_on}>Set Macros</td
          >
        </tr>
        <tr>
          {#if edit_macro}
            <td><input bind:value={macros[0]} /></td>
            <td><input bind:value={macros[1]} /></td>
          {:else}
            <td on:click={m1}>{macros[0]}</td>
            <td on:click={m2}>{macros[1]}</td>
          {/if}
        </tr>
        <tr>
          {#if edit_macro}
            <td><input bind:value={macros[2]} /></td>
            <td><input bind:value={macros[3]} /></td>
          {:else}
            <td on:click={m3}>{macros[2]}</td>
            <td on:click={m4}>{macros[3]}</td>
          {/if}
        </tr>
        <tr>
          {#if edit_macro}
            <td><input bind:value={macros[4]} /></td>
          {:else}
            <td on:click={m5}>{macros[4]}</td>
          {/if}
          <td class="clear" on:click={clear}>clear</td>
        </tr>
        <tr>
          <td class="log-file" on:click={save_log_file}>Save to log file</td>
          <td class="exit" on:click={exit}>Return</td>
        </tr>
      </tbody>
    </table>
  </div>
  <div class="msg-panel chat" id="chat">
    {#each massages as msg}
      <div class="massage {msg[1] ? 'massage1' : 'massage2'}">
        <div class="msg-data">{time()}</div>
        Data : {msg[0]}
      </div>
    {/each}
  </div>
  <div class="send-msg-area">
    <input class="input_text" type="text" bind:value={temp} />
    <button class="send" on:click={send}>Send</button>
  </div>
</div>

<style>
  #frame {
    display: grid;
    grid-template-columns: 1fr 1fr 1fr 1fr;
    grid-template-rows: 0.9fr 0.8fr 1.1fr 1.1fr 1.1fr 1.1fr 0.9fr;
    gap: 0 0;
    height: 100vh;
    background-color: #222831;
    grid-template-areas:
      "titel titel titel titel"
      "msg-panel msg-panel seced-titel seced-titel"
      "msg-panel msg-panel macros-panel macros-panel"
      "msg-panel msg-panel macros-panel macros-panel"
      "msg-panel msg-panel macros-panel macros-panel"
      "msg-panel msg-panel macros-panel macros-panel"
      "send-msg-area send-msg-area send-msg-area send-msg-area";
  }
  .titel {
    grid-area: titel;
    display: relative;
    text-align: center;
    height: 10vh;
    width: 100%;
    background-color: #222831;
    color: #dddddd;
    font-family: "Poppins", sans-serif;
    font-size: 5vh;
    -webkit-app-region: drag;
  }
  .titel h2 {
    position: relative;
    top: -6vh;
    align-self: center;
  }
  .seced-titel {
    grid-area: seced-titel;
    background-color: #f1f1f1;
    color: #222831;
    -webkit-app-region: drag;
    font-size: 2.5vh;
    font-family: "Poppins", sans-serif;
  }
  .send-msg-area {
    grid-area: send-msg-area;
  }
  .msg-panel {
    grid-area: msg-panel;
    background-color: #dddddd;
    color: #dddddd;
    font-size: 5vh;
    font-family: "Montserrat", sans-serif;
    direction: rtl;
    overflow: auto;
  }
  .macros-panel {
    grid-area: macros-panel;
    background-color: #222831;
  }
  table.fixed {
    table-layout: fixed;
    height: 100%;
    width: 100%;
  }
  .panel td {
    background-color: #30475e;
    color: #f1f1f1;
    font-size: 3vh;
    font-family: "Poppins", sans-serif;
  }
  .panel td:hover {
    cursor: pointer;
    filter: brightness(1.1);
  }
  .clear:hover {
    background-color: #54b2f0;
  }
  .exit:hover {
    background-color: #f05454;
  }
  .log-file:hover {
    background-color: #f09d54;
  }
  .input_text {
    font-family: "Poppins", sans-serif;
    width: 100%;
    padding: 8px;
    display: block;
    border: none;
    border-bottom: 1px solid #ccc;
    width: 100%;
    height: 6vh;
    font-size: 3vh;
  }
  button.send {
    background-color: #222831;
    color: #dddddd;
    border: none;
    font-family: "Poppins", sans-serif;
    font-size: 3vh;
    width: 100%;
    height: 6vh;
  }
  .massage1 {
    background-color: #30475e;
    border-style: solid;
    border-width: 1px;
    word-wrap: break-word;
    border-color: #222831;
  }
  .massage2 {
    background-color: #f05454;
    border-style: solid 1px;
    border-width: 1px;
    word-wrap: break-word;
    border-color: #222831;
  }
  /* width */
  ::-webkit-scrollbar {
    width: 1vh;
  }

  /* Track */
  ::-webkit-scrollbar-track {
    background: #f1f1f1;
  }

  /* Handle */
  ::-webkit-scrollbar-thumb {
    background: #888;
  }

  /* Handle on hover */
  ::-webkit-scrollbar-thumb:hover {
    background: #555;
  }
</style>
