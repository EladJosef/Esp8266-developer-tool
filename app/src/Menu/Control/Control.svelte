<script>
  import { createEventDispatcher } from "svelte";
  const net = window.require("net");
  export let address;
  let massages = [];
  let temp = "";
  let auto_scroll = true;
  let macros = ["A", "B", "C", "D", "E"];
  let edit_macro = false;
  let statistics = {};
  let send_time = 0;

  statistics.send_msg = 0;
  statistics.accept_msg = 0;

  statistics.sum_time_between = 0;
  statistics.address =
    address[0] +
    "." +
    address[1] +
    "." +
    address[2] +
    "." +
    address[3] +
    ":" +
    address[4];

  statistics.create_time = "";

  const dispatch = createEventDispatcher();

  Array.prototype.clear_diracters = function () {
    for (var i = 0; i < this.length; i++) {
      this[i] = this[i][1]
        ? this[i][0] + " => send at " + this[i][2]
        : this[i][0] + " => receive at " + this[i][2];
    }
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
      statistics.send_msg += 1;
      send_time = Date.now();
      massages = [...massages, [temp, true, send_time]];
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
    if (event.key === "Enter" && !edit_macro) {
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
    var file = new File([JSON.stringify(statistics) + "\n" + log.join("\n")], {
      type: "text/plain",
    });
    if (window.navigator.msSaveOrOpenBlob)
      window.navigator.msSaveOrOpenBlob(file, "logData.log");
    else {
      var a = document.createElement("a"),
        url = URL.createObjectURL(file);
      a.href = url;
      a.download = "logData.log";
      document.body.appendChild(a);
      a.click();
      setTimeout(function () {
        document.body.removeChild(a);
        window.URL.revokeObjectURL(url);
      }, 0);
    }
  }

  function use_macro(index) {
    temp = macros[index];
  }

  function exit() {
    clearInterval(scroll_auto_int);
    dispatch("menu_index", 0);
  }

  function accept(data, tcp) {
    statistics.accept_msg += 1;
    let enc = new TextDecoder("utf-8");
    let msg = enc.decode(data["buffer"]);
    let aaccept_time = Date.now();
    statistics.sum_time_between += aaccept_time - send_time;
    massages = [...massages, [msg, false, aaccept_time]];
    tcp.destroy();
  }

  function connect(msg) {
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
  <div class="title">
    <h2>ESP8266 massages debugger</h2>
  </div>
  <div class="seced-title">
    <h2>control panel</h2>
  </div>
  <div class="macros-panel">
    <table style="width: 100%;" class="fixed panel">
      <tbody>
        <tr>
          <td
            style="background-color:{auto_scroll
              ? 'var(--active-auto-scrolling)'
              : 'var(--complementary-main-color)'}"
            on:click={auto_scroll_me}>Auto Scroll</td
          >
          <td
            style="background-color:{edit_macro
              ? 'var(--highlight-color)'
              : 'var(--complementary-main-color)'}"
            class="set-macro"
            on:click={edit_on}>Set Macros</td
          >
        </tr>
        <tr>
          {#if edit_macro}
            <td><input bind:value={macros[0]} /></td>
            <td><input bind:value={macros[1]} /></td>
          {:else}
            <td on:click={() => use_macro(0)}>{macros[0]}</td>
            <td on:click={() => use_macro(1)}>{macros[1]}</td>
          {/if}
        </tr>
        <tr>
          {#if edit_macro}
            <td><input bind:value={macros[2]} /></td>
            <td><input bind:value={macros[3]} /></td>
          {:else}
            <td on:click={() => use_macro(2)}>{macros[2]}</td>
            <td on:click={() => use_macro(3)}>{macros[3]}</td>
          {/if}
        </tr>
        <tr>
          {#if edit_macro}
            <td><input bind:value={macros[4]} /></td>
          {:else}
            <td on:click={() => use_macro(4)}>{macros[4]}</td>
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
    background-color: var(--main-color);
    grid-template-areas:
      "title title title title"
      "msg-panel msg-panel seced-title seced-title"
      "msg-panel msg-panel macros-panel macros-panel"
      "msg-panel msg-panel macros-panel macros-panel"
      "msg-panel msg-panel macros-panel macros-panel"
      "msg-panel msg-panel macros-panel macros-panel"
      "send-msg-area send-msg-area send-msg-area send-msg-area";
  }
  .title {
    grid-area: title;
    display: relative;
    text-align: center;
    height: 10vh;
    width: 100%;
    background-color: var(--main-color);
    color: var(--secondary-color);
    font-family: "Poppins", sans-serif;
    font-size: 5vh;
    -webkit-app-region: drag;
  }
  .title h2 {
    position: relative;
    top: -6vh;
    align-self: center;
  }
  .seced-title {
    grid-area: seced-title;
    background-color: var(--blank-color);
    color: var(--main-color);
    -webkit-app-region: drag;
    font-size: 2.5vh;
    font-family: "Poppins", sans-serif;
  }
  .send-msg-area {
    grid-area: send-msg-area;
  }
  .msg-panel {
    grid-area: msg-panel;
    background-color: var(--secondary-color);
    color: var(--secondary-color);
    font-size: 5vh;
    font-family: "Montserrat", sans-serif;
    direction: rtl;
    overflow: auto;
  }
  .macros-panel {
    grid-area: macros-panel;
    background-color: var(--main-color);
  }
  table.fixed {
    table-layout: fixed;
    height: 100%;
    width: 100%;
  }
  .panel td {
    background-color: var(--complementary-main-color);
    color: var(--blank-color);
    font-size: 3vh;
    font-family: "Poppins", sans-serif;
  }
  .panel td:hover {
    cursor: pointer;
    filter: brightness(1.1);
  }
  .clear:hover {
    background-color: var(--active-clear-button);
  }
  .exit:hover {
    background-color: var(--active-exit-button);
  }
  .log-file:hover {
    background-color: var(--active-log-button);
  }
  .input_text {
    font-family: "Poppins", sans-serif;
    width: 100%;
    padding: 8px;
    display: block;
    border: none;
    border-bottom: 1px solid var(--blank-color);
    width: 100%;
    height: 6vh;
    font-size: 3vh;
  }
  button.send {
    background-color: var(--main-color);
    color: var(--secondary-color);
    border: none;
    font-family: "Poppins", sans-serif;
    font-size: 3vh;
    width: 100%;
    height: 6vh;
  }
  .massage1 {
    background-color: var(--active-send-msg);
    border-style: solid;
    border-width: 1px;
    word-wrap: break-word;
    border-color: var(--main-color);
    color: aliceblue;
  }
  .massage2 {
    background-color: var(--active-accepted-msg);
    border-style: solid 1px;
    border-width: 1px;
    word-wrap: break-word;
    border-color: var(--main-color);
    color: aliceblue;
  }
  /* width */
  ::-webkit-scrollbar {
    width: 1vh;
  }

  /* Track */
  ::-webkit-scrollbar-track {
    background: var(--track-color);
  }

  /* Handle */
  ::-webkit-scrollbar-thumb {
    background: var(--thumb-color);
  }

  /* Handle on hover */
  ::-webkit-scrollbar-thumb:hover {
    background: var(--thumb-hover-color);
  }
</style>
