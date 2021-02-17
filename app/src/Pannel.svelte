<script>
  import Control from "./Control.svelte";
  import Menu from "./Menu.svelte";
  export let address;
  let debug = true;
  let current = 0;
  let just_pressed = false;
  let key;
  let keyCode;
  let is_connect = debug || false;
  let has_click = false;

  function handleKeydown(event) {
    if (is_connect) {
      return;
    }
    key = event.key;
    keyCode = event.keyCode;

    if ((keyCode > 47 && keyCode < 58) || (keyCode > 95 && keyCode < 106)) {
      if (just_pressed) {
        address[current] = "";
        just_pressed = false;
      }
      setNewNumber(current, key);
    } else if (keyCode === 37) {
      just_pressed = true;
      if (current - 1 !== -1) {
        current = current - 1;
      } else {
        current = 4;
      }
    } else if (keyCode === 38) {
      addValueAdder(current, 1);
    } else if (keyCode === 39) {
      just_pressed = true;
      if (current + 1 !== 5) {
        current = current + 1;
      } else {
        current = 0;
      }
    } else if (keyCode === 40) {
      addValueAdder(current, -1);
    } else if (key === "Backspace") {
      if (String(address[current]).length === 1) {
        address[current] = "0";
      } else {
        address[current] = Number(String(address[current]).slice(0, -1));
      }
    }
    address[current] = Number(address[current]);
  }

  function setNewNumber(num, key) {
    if (num !== 4) {
      if (Number(address[num] + key) < 256) {
        address[num] = address[num] + key;
      }
    } else {
      if (Number(address[num] + key) < 65536) {
        address[num] = address[num] + key;
      }
    }
  }

  function addValueAdder(index, value) {
    just_pressed = false;
    let value_after = Number(address[index]) + value;
    if (index !== 4) {
      if (value_after < 256 && value_after > -1) {
        address[index] = value_after;
      }
    } else {
      if (value_after < 65536 && value_after > -1) {
        address[index] = value_after;
      }
    }
  }

  function accept(data, tcp) {
    var enc = new TextDecoder("utf-8");
    let msg = enc.decode(data["buffer"]);
    if (msg === "yes") {
      console.log("Esp8266 are on !");
      is_connect = true;
      has_click = false;
    } else {
      console.log("Esp8266 dosn't found !");
      is_connect = false;
    }
    tcp.destroy();
  }

  function connect() {
    has_click = true;
    const net = window.require("net");
    const ip = `${address[0]}.${address[1]}.${address[2]}.${address[3]}`;
    const port = Number(address[4]);
    let tcp = new net.Socket();
    tcp.connect(port, ip, function () {
      tcp.write("on?");
    });
    tcp.on("data", (data) => accept(data, tcp));
  }
</script>

<svelte:window on:keydown={handleKeydown} />
<main>
  {#if is_connect}
    <Menu on:is_connect={(event) => (is_connect = event.detail)} {address} />
  {:else}
    <h2>Connect esp8266</h2>
    <div style="margin-top: -10vh;">
      {#each address as address, i}
        <h1
          class={current === i ? "setFont" : "setDef"}
          on:click={() => {
            current = i;
            just_pressed = true;
          }}
        >
          {address}
        </h1>
        {#if i == 3}
          <h1>:</h1>
        {:else if i != 4}
          <h1>.</h1>
        {/if}
      {/each}
    </div>
    <div class="connect-button" on:click={connect}>Connect</div>
    {#if !is_connect && has_click}
      <h3>Connect failed</h3>
    {/if}
  {/if}
</main>

<style>
  h1 {
    text-align: center;
    font-family: "Montserrat", sans-serif;
    color: #222831;
    font-size: 15vh;
    display: inline;
    user-select: none;
    -webkit-app-region: no-drag;
  }
  .setFont {
    color: #f05454;
  }

  .setDef {
    color: #222831;
  }

  h2 {
    font-family: "Poppins", sans-serif;
    color: #222831;
    font-size: 15vh;
    text-align: center;
    margin-bottom: 15vh;
    -webkit-app-region: drag;
  }

  h3 {
    color: rgb(255, 37, 37);
    font-family: "Poppins", sans-serif;
  }

  .connect-button {
    font-size: 8vh;
    text-align: center;
    font-family: "Poppins", sans-serif;
    background-color: #222831;
    color: #ffffff;
    width: 26vw;
    margin-left: 37vw;
    margin-top: 10vh;
    cursor: pointer;
    -webkit-app-region: no-drag;
  }
  main {
    text-align: center;
  }
</style>
