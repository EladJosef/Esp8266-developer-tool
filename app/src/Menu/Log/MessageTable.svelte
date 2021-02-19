<script>
  export let messages;

  function manage_messages() {
    let buffer = "";
    let result = [];
    let time_buffer;
    for (var i = 1; i < messages.length; i++) {
      buffer = messages[i].split(" => ");
      time_buffer = new Date(buffer[1].split(" at ")[1] * 1);
      result.push([
        buffer[0],
        buffer[1].split(" at ")[0] === "send",
        String(time_buffer.getHours()) +
          ":" +
          String(time_buffer.getMinutes()) +
          ":" +
          String(time_buffer.getSeconds()) +
          "." +
          String(time_buffer.getMilliseconds()),
      ]);
    }
    return result;
  }

  messages = manage_messages(messages);
</script>

{#each messages as message}
  <div class={message[1] ? "snd msg" : "rev msg"}>
    `{message[0]}` {message[1] ? "send" : "accepted"} at {message[2]}
  </div>
{/each}

<style>
  .msg {
    font-size: 5vh;
    font-family: "Montserrat", sans-serif;
    color: #f1f1f1;
  }
  .snd {
    background-color: #008891;
  }
  .rev {
    background-color: #00587a;
  }
</style>
