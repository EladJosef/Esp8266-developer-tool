<script>
  import { createEventDispatcher } from "svelte";
  import Control from "./Control/Control.svelte";
  import LogExplorer from "./Log/LogExplorer.svelte";
  import Code from "./Code/Code.svelte";
  const dispatch = createEventDispatcher();

  export let address;
  let menu_index = 0;

  function exit() {
    dispatch("is_connect", false);
  }
</script>

{#if menu_index == 0}
  <div class="grid-container">
    <div class="title" />
    <div class="option1">Menu</div>
    <div class="option2">
      <div class="connect-button" on:click={() => (menu_index = 1)}>
        Message Debugger
      </div>
    </div>
    <div class="option3">
      <div class="connect-button" on:click={() => (menu_index = 2)}>
        Log Explorer
      </div>
    </div>
    <div class="option4">
      <div class="connect-button" on:click={() => (menu_index = 3)}>
        Skeleton Code Generator
      </div>
    </div>
    <div class="exit">
      <div class="connect-button" on:click={exit}>Exit</div>
    </div>
    <div class="footer" />
  </div>
{:else if menu_index == 1}
  <Control on:menu_index={(event) => (menu_index = event.detail)} {address} />
{:else if menu_index == 2}
  <LogExplorer on:menu_index={(event) => (menu_index = event.detail)} />
{:else}
  <Code on:menu_index={(event) => (menu_index = event.detail)} />
{/if}

<style>
  .grid-container {
    display: grid;
    grid-template-columns: 1fr 1fr 1fr 1fr;
    grid-template-rows: 1fr 1fr 1fr 1fr 1fr 1fr 1fr;
    gap: 0px 0px;
    grid-template-areas:
      "title title title title"
      ". option1 option1 ."
      ". option2 option2 ."
      ". option3 option3 ."
      ". option4 option4 ."
      ". exit exit ."
      "footer footer footer footer";
    height: 94vh;
    border-style: double;
    border-color: #222831;
    background-color: #dddddd;
    border-width: 3vh;
  }

  .option1 {
    grid-area: option1;
    font-size: 10vh;
    text-align: center;
    font-family: "Poppins", sans-serif;
    background-color: #222831;
    color: #ffffff;

    width: 100%;
    -webkit-app-region: drag;
  }

  .option2 {
    grid-area: option2;
  }

  .option3 {
    grid-area: option3;
  }

  .option4 {
    grid-area: option4;
  }

  .exit {
    grid-area: exit;
  }

  .title {
    grid-area: title;
    -webkit-app-region: drag;
  }

  .footer {
    grid-area: footer;
    -webkit-app-region: drag;
  }

  .connect-button {
    font-size: 5vh;
    padding-top: 3vh;
    text-align: center;
    font-family: "Poppins", sans-serif;
    background-color: #222831;
    color: #ffffff;
    width: 100%;
    height: 100%;
    margin-left: 0vw;
    cursor: pointer;
    -webkit-app-region: no-drag;
    transition: 0.3s;
  }
  .connect-button:hover {
    background-color: #f05454;
    color: #dddddd;
  }
</style>
