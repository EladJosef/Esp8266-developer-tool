<script>
  import { createEventDispatcher } from "svelte";
  export let address;
  let massages = [];
  let temp = "";
  let auto_scroll = true;
  let macros = ["A", "B", "C", "D"];
  let edit_macro = false;

  console.log(address);
  const dispatch = createEventDispatcher();

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
      massages = [...massages, [temp, true]];
      massages = [...massages, [temp, false]];
      temp = "";
      let element = document.getElementById("chat");
      element.scrollTop = element.scrollHeight + 1000;
    }
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
    var file = new Blob([massages], { type: "text/plain" });
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

  function exit() {
    clearInterval(scroll_auto_int);
    dispatch("is_connect", false);
  }
</script>

<svelte:window on:keydown={handleKeydown} />
<div class="title">
  <h2>Control esp8266</h2>
</div>
<div class="container">
  <div class="chat" id="chat">
    {#each massages as msg}
      <div class="massage {msg[1] ? 'massage1' : 'massage2'}">
        <div class="msg-data">{time()}</div>
        Data : {msg[0]}
      </div>
    {/each}
  </div>
  <div class="control-me">
    <div class="upper">
      <h1>Settings panel</h1>
    </div>
    <div class="downer">
      <table>
        <tr>
          <td
            style="background-color:{auto_scroll ? '#4CAF50' : '#30475e'}"
            on:click={auto_scroll_me}>Auto Scroll
          </td>
          <td
            style="background-color:{edit_macro ? '#f05454' : '#30475e'}"
            class="set-macro"
            on:click={edit_on}>Set Macros</td
          >
        </tr>
        <tr>
          {#if edit_macro}
            <td class="do-macro"><input bind:value={macros[0]} /></td>
            <td class="do-macro"><input bind:value={macros[1]} /></td>
          {:else}
            <td class="do-macro" on:click={m1}>{macros[0]}</td>
            <td class="do-macro" on:click={m2}>{macros[1]}</td>
          {/if}
        </tr>
        <tr>
          {#if edit_macro}
            <td class="do-macro"><input bind:value={macros[2]} /></td>
            <td class="do-macro"><input bind:value={macros[3]} /></td>
          {:else}
            <td class="do-macro" on:click={m3}>{macros[2]}</td>
            <td class="do-macro" on:click={m4}>{macros[3]}</td>
          {/if}
        </tr>
        <tr>
          <td class="log-file" on:click={save_log_file}>Save to log file</td>
          <td class="exit" on:click={exit}>Exit</td>
        </tr>
      </table>
    </div>
  </div>
</div>
<div class="footer">
  <input class="input_text" type="text" bind:value={temp} />
  <button class="send" on:click={send}>Send</button>
</div>

<style>
  h1 {
    font-family: "Poppins", sans-serif;
    font-size: 5vh;
  }
  h2 {
    font-family: "Poppins", sans-serif;
    color: #dddddd;
    font-size: 8vh;
    text-align: center;
    margin-bottom: 15vh;
    margin-top: 5vh;
  }
  table {
    height: 60vh;
    font-size: 3vh;
  }
  table:hover {
    cursor: pointer;
  }
  td {
    width: 23.85vw;
    background-color: #30475e;
  }
  div.upper {
    background-color: #f3f3f3;
    grid-area: 1 / 3 / 2 / 5;
    padding: 1vh;
    margin-bottom: -2vw;
    color: #222831;
    -webkit-app-region: drag;
  }
  div.downer {
    grid-area: 2 / 3 / 4 / 5;
    background-color: #222831;
    font-family: "Poppins", sans-serif;
    color: #dddddd;
    min-height: 75vh;
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
  .footer {
    position: fixed;
    left: 0;
    bottom: 0;
    width: 100%;
    background-color: #222831;
    color: #dddddd;
    text-align: center;
    -webkit-app-region: no-drag;
  }
  .title {
    position: relative;
    left: -5vw;
    top: -5vh;
    width: 110%;
    background-color: #222831;
    color: #dddddd;
    text-align: center;
    max-height: 25vh;
    -webkit-app-region: drag;
  }

  div.chat {
    width: 52vw;
    margin-top: -20vh;
    margin-left: -2vw;
    position: relative;
    font-family: "Montserrat", sans-serif;
    font-size: 5vh;
    overflow-y: scroll;
    overflow-x: hidden; /* Hide horizontal scrollbar */
    max-height: 74vh;
    min-height: 74vh;
    grid-area: msg-part;
  }
  div.control-me {
    display: inline;
    grid-area: buttons-p;
    margin-top: -20vh;
    min-height: 75vh;
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
  .exit:hover {
    background-color: #f05454;
  }
  .log-file:hover {
    background-color: #f09d54;
  }
  .set-macro:hover {
    background-color: #f05454;
    color: #222831;
  }
  .do-macro:hover {
    background-color: #549df0;
    color: #222831;
  }
  .massage {
    font-family: "Poppins", sans-serif;
    color: #ffffff;
    word-wrap: break-word;
    width: 100%;
  }
  .massage1 {
    background-color: #30475e;
  }
  .massage2 {
    background-color: #f05454;
  }
  .msg-data {
    color: #dddddd;
  }

  div.container {
    display: grid;
    grid-template-columns: 1fr 1fr 1fr 1fr;
    grid-template-rows: 1fr 1fr 1fr;
    gap: 0px 0px;
    grid-template-areas:
      "msg-part msg-part buttons-p buttons-p"
      "msg-part msg-part buttons-p buttons-p"
      "msg-part msg-part buttons-p buttons-p";
  }
  ::-webkit-scrollbar {
    width: 0vh;
  }
</style>
