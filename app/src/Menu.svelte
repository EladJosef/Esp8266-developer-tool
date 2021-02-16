<script>
  import { createEventDispatcher } from "svelte";
  import Control from "./Control.svelte";
  const dispatch = createEventDispatcher();

  export let address;
  let menu_index = 0;

  function exit() {
    dispatch("is_connect", false);
  }
</script>

<div class="grid-container">
  <div class="menu">
    {#if menu_index == 0}
      <div class="connect-button" on:click={() => (menu_index = 1)}>
        message debugger
      </div>
      <div class="connect-button" on:click={exit}>Exit</div>
    {:else if menu_index == 1}
      <Control
        on:menu_index={(event) => (menu_index = event.detail)}
        {address}
      />
    {:else}
      1
    {/if}
  </div>
</div>

<style>
  .connect-button {
    font-size: 8vh;
    text-align: center;
    font-family: "Poppins", sans-serif;
    background-color: #222831;
    color: #ffffff;
    width: 100%;
    margin-left: 0vw;
    margin-top: 5vh;
    cursor: pointer;
    -webkit-app-region: no-drag;
    transition: 0.3s;
  }
  .connect-button:hover {
    background-color: #244250;
  }
</style>
