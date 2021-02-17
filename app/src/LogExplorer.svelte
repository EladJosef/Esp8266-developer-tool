<script>
  import { createEventDispatcher } from "svelte";
  import FileDrop from "./FileDrop.svelte";
  import MessageTable from "./MessageTable.svelte";
  import StaticsTable from "./StaticsTable.svelte";
  const dispatch = createEventDispatcher();

  let title_data = ["data", "statistics"];
  let file_has_loaded = false;
  let fs = require("fs");
  let show_data = true;
  let messages = "";
  let path = "";

  function exit() {
    dispatch("menu_index", 0);
  }

  function load_file(file_status) {
    fs.readFile(file_status[0], "utf-8", (err, data) => {
      if (err) {
        alert("An error ocurred reading the file :" + err.message);
        return;
      }
      messages = data.split("\n");
      file_has_loaded = file_status[1];
    });
  }
</script>

<div class="grid-container">
  <div class="return main-title-panel"><h1 on:click={exit}>return</h1></div>
  <div class="title main-title-panel"><h1>Log Explorer</h1></div>
  <div class="mode main-title-panel">
    <h1 class="title-link" on:click={() => (show_data = !show_data)}>
      Show {show_data ? title_data[1] : title_data[0]}
    </h1>
  </div>
  <div class="mode-title">{show_data ? title_data[0] : title_data[1]}</div>
  {#if file_has_loaded}
    {#if show_data}
      <div class="main-page">
        <div id="message_table"><MessageTable {messages} /></div>
      </div>
    {:else}
      <div class="main-page"><StaticsTable {messages} /></div>
    {/if}
  {:else}
    <div class="main-page">
      <FileDrop on:file_has_loaded={(event) => load_file(event.detail)} />
    </div>
  {/if}
</div>

<style>
  .grid-container {
    display: grid;
    grid-template-columns: 1fr 1fr 1fr 1fr;
    grid-template-rows: 0.35fr 0.3fr 1fr 1fr 1fr 1fr;
    gap: 0px 0px;
    grid-template-areas:
      "return title title mode"
      "mode-title mode-title mode-title mode-title"
      "main-page main-page main-page main-page"
      "main-page main-page main-page main-page"
      "main-page main-page main-page main-page"
      "main-page main-page main-page main-page";
    height: 100vh;
  }

  .return {
    grid-area: return;
    font-size: 1vh;
  }

  .title {
    grid-area: title;
    font-size: 2vh;
  }

  .mode {
    grid-area: mode;
    font-size: 1vh;
  }

  .mode-title {
    grid-area: mode-title;
    background-color: #dddddd;
    color: #222831;
    font-size: 5vh;
    font-family: "Poppins", sans-serif;
    -webkit-app-region: drag;
    border-style: solid;
    border-color: #222831;
    border-width: 1vh;
    border-bottom-style: none;
  }

  .main-page {
    grid-area: main-page;
    border-style: solid;
    border-color: #222831;
    border-width: 1vh;
    background-color: #dddddd;
    overflow: auto;
  }

  .return h1,
  .mode h1 {
    font-size: 3.5vh;
    -webkit-app-region: no-drag;
    transition: 0.3s;
  }
  .return h1:hover,
  .mode h1:hover {
    cursor: pointer;
    filter: brightness(1.5);
    margin-top: 2vh;
    font-size: 4vh;
  }
  .return h1 {
    padding-left: 5vh;
    float: left;
  }
  .mode h1 {
    padding-right: 5vh;
    float: right;
  }
  .title h1 {
    font-size: 5vh;
    margin-top: 1vh;
    float: center;
  }

  ::-webkit-scrollbar {
    width: 1vw;
  }

  ::-webkit-scrollbar-track {
    box-shadow: inset 0 0 0 rgb(63, 63, 63);
    border-radius: 1vw;
  }

  ::-webkit-scrollbar-thumb {
    background: rgb(127, 127, 127);
    border-radius: 1vw;
  }

  ::-webkit-scrollbar-thumb:hover {
    background: #8b8b8b;
  }
</style>
