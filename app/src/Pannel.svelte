<script>
  import Menu from "./Menu/Menu.svelte";
  export let address;
  export let debug;

  const net = window.require("net"); // importing net

  // current index on GUI address input
  let current = 0;

  // used for keyboard input
  let key;
  let keyCode;

  // used for know user actions
  let just_pressed = false;
  let is_connect = debug || false;
  let has_click = false;
  let has_skip = true;

  function handleKeydown(event) {
    // handleKeydown used for find keydowns that
    // related to entering input into the address
    if (is_connect) {
      // if user connect all keysdown are not necessary
      return;
    }
    key = event.key;
    keyCode = event.keyCode;

    // if numbers was input
    if ((keyCode > 47 && keyCode < 58) || (keyCode > 95 && keyCode < 106)) {
      // If this is a first value insertion
      if (just_pressed) {
        address[current] = "";
        just_pressed = false;
      }
      setNewNumber(current, key);
    } else if (keyCode === 37) {
      // user move left on address input
      move_index(-1);
    } else if (keyCode === 38) {
      // user Increase the index value by 1
      addValueAdder(current, 1);
    } else if (keyCode === 39) {
      // user move right on address input
      move_index(1);
    } else if (keyCode === 40) {
      // Decrease the index value by 1
      addValueAdder(current, -1);
    } else if (keyCode === 13) {
      // user try to connect address
      connect();
    } else if (key === "Backspace") {
      // user delet lest digit in index
      delete_index();
    }
    address[current] = Number(address[current]); // update address at current index with new input
  }

  function setNewNumber(num, key) {
    // check if value are valid to address
    // and aplay new value
    if (num !== 4) {
      // for ip value
      if (Number(address[num] + key) < 256) {
        address[num] = address[num] + key;
      }
    } else {
      // for port value
      if (Number(address[num] + key) < 65536) {
        address[num] = address[num] + key;
      }
    }
  }

  function addValueAdder(index, value) {
    // used for add or subtraction values from index
    just_pressed = false;
    let value_after = Number(address[index]) + value;
    // for add or subtraction ip index value
    if (index !== 4) {
      if (value_after < 256 && value_after > -1) {
        address[index] = value_after;
      }
    }
    // for add or subtraction port index value
    else {
      if (value_after < 65536 && value_after > -1) {
        address[index] = value_after;
      }
    }
  }

  function move_index(direction) {
    // if direction is equals to -1 index move left
    // if direction is equals to 1 index move right
    console.log(direction);
    just_pressed = true;
    if (current + direction !== 3 * direction + 2) {
      current = current + direction;
    } else {
      current = -2 * direction + 2;
    }
  }

  function delete_index() {
    // delet lest digit in current index
    if (String(address[current]).length === 1) {
      address[current] = "0";
    } else {
      address[current] = Number(String(address[current]).slice(0, -1));
    }
    just_pressed = false;
  }

  function accept(data, tcp) {
    var enc = new TextDecoder("utf-8");
    let msg = enc.decode(data["buffer"]);

    // if msg that accepted is yes this means that the esp8266 is reactive
    if (msg === "yes") {
      console.log("Esp8266 are on !");
      is_connect = true;
      has_click = false;
      has_skip = false;
    }
    // else this is not the correct address
    else {
      console.log("Esp8266 dosn't found !");
      is_connect = false;
    }

    tcp.destroy(); // disconect
  }

  function connect() {
    // try to connect esp8266
    has_click = true;
    const ip = `${address[0]}.${address[1]}.${address[2]}.${address[3]}`;
    const port = Number(address[4]);
    let tcp = new net.Socket();
    tcp.connect(port, ip, function () {
      tcp.write("on?");
    });
    tcp.on("data", (data) => accept(data, tcp));
  }

  function skip_connect() {
    // If a user wants to use functions
    // unrelated to the component connection
    is_connect = true;
    has_click = false;
    has_skip = true;
  }
</script>

<svelte:window on:keydown={handleKeydown} />
<main>
  {#if is_connect}
    <Menu
      on:is_connect={(event) => (is_connect = event.detail)}
      {address}
      {has_skip}
    />
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
      <h3 on:click={() => (has_click = !has_click)}>Connect failed</h3>
    {:else}
      <h3 on:click={skip_connect} class="skip">Skip connect</h3>
    {/if}
  {/if}
</main>

<style>
  h1 {
    text-align: center;
    font-family: "Montserrat", sans-serif;
    color: var(--main-color);
    font-size: 15vh;
    display: inline;
    user-select: none;
    -webkit-app-region: no-drag;
  }
  .setFont {
    color: var(--highlight-color);
  }

  .setDef {
    color: var(--main-color);
  }

  h2 {
    font-family: "Poppins", sans-serif;
    color: var(--main-color);
    font-size: 15vh;
    text-align: center;
    margin-bottom: 15vh;
    -webkit-app-region: drag;
  }

  h3 {
    color: var(--highlight-color);
    font-family: "Poppins", sans-serif;
  }

  .connect-button {
    font-size: 8vh;
    text-align: center;
    font-family: "Poppins", sans-serif;
    background-color: var(--main-color);
    color: var(--blank-color);
    width: 26vw;
    margin-left: 37vw;
    margin-top: 10vh;
    cursor: pointer;
    -webkit-app-region: no-drag;
  }
  .skip {
    color: var(--main-color);
    -webkit-app-region: no-drag;
  }
  .skip:hover {
    cursor: pointer;
  }
  main {
    text-align: center;
  }
</style>
